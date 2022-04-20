#include <stdio.h>
#include "xparameters.h"
#include "xil_exception.h"
#include "xintc.h"
#include "xmatrix_multiply.h"
#include "matrix.h"

XMatrix_multiply multiplier;

XIntc Intc;
static volatile u32 DoneIntrFlag = 0;
static volatile u32 ReadyIntrFlag = 0;

void Matrix_Multiply_Handler(void *CallBackRef);

int main() {

	int Status;

	Status = XMatrix_multiply_Initialize(&multiplier, XPAR_MATRIX_MULTIPLY_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	u32 mask = 0x01;
	XMatrix_multiply_InterruptEnable(&multiplier, mask);

	Status = XIntc_Initialize(&Intc, XPAR_INTC_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XIntc_Connect(&Intc, XPAR_INTC_0_MATRIX_MULTIPLY_0_VEC_ID,
			(XInterruptHandler) Matrix_Multiply_Handler, &multiplier);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XIntc_Start(&Intc, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XIntc_Enable(&Intc, XPAR_INTC_0_MATRIX_MULTIPLY_0_VEC_ID);
	Xil_ExceptionInit();

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XIntc_InterruptHandler, &Intc);

	Xil_ExceptionEnable();

	XMatrix_multiply_InterruptGlobalEnable(&multiplier);

	XMatrix_multiply_Write_A_Words(&multiplier, 0, (u32*) A,
	MATRIX_ELEMENT_NUMBER);
	XMatrix_multiply_Write_B_Words(&multiplier, 0, (u32*) B,
	MATRIX_ELEMENT_NUMBER);

	XMatrix_multiply_DisableAutoRestart(&multiplier);
	XMatrix_multiply_Start(&multiplier);

	while (1) {
		if (DoneIntrFlag) {
			DoneIntrFlag = 0;
			XMatrix_multiply_Read_C_Words(&multiplier, 0, (u32*) C,
			MATRIX_ELEMENT_NUMBER);
			break;
		}

	}

}

void Matrix_Multiply_Handler(void *CallBackRef) {
	XMatrix_multiply *multiplierPtr = (XMatrix_multiply *) CallBackRef;
	u32 isrReg = XMatrix_multiply_InterruptGetStatus(multiplierPtr);
	if ((isrReg & 0x01) == 0x01) {
		DoneIntrFlag = 1;
		/* Clear the Interrupt */
		XMatrix_multiply_InterruptClear(multiplierPtr, (u32) 0x01);
	} else if ((isrReg & 0x02) == 0x02) {
		ReadyIntrFlag = 1;
		/* Clear the Interrupt */
		XMatrix_multiply_InterruptClear(multiplierPtr, (u32) 0x02);
	}

}
