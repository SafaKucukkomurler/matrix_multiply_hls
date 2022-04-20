#include "matrix_multiply_float.h"

void matrix_multiply(const MATRIX_T A[MATRIX_ELEMENT_NUMBER],
		const MATRIX_T B[MATRIX_ELEMENT_NUMBER],
		MATRIX_T C[MATRIX_ELEMENT_NUMBER]) {

#pragma HLS interface s_axilite port=return bundle=data
#pragma HLS interface s_axilite port=A bundle=data offset=0x0
#pragma HLS interface s_axilite port=B bundle=data offset=0x200
#pragma HLS interface s_axilite port=C bundle=data offset=0x300

//	MATRIX_T a_i[MATRIX_ELEMENT_NUMBER];
//	MATRIX_T b_i[MATRIX_ELEMENT_NUMBER];
//	MATRIX_T c_i[MATRIX_ELEMENT_NUMBER];

	// Copy input data to local memory

//	a_loop: for (int r = 0; r < MATRIX_ELEMENT_NUMBER; r++) {
//#pragma HLS unroll factor=36
//		a_i[r] = A[r];
//	}
//	b_loop: for (int r = 0; r < MATRIX_ELEMENT_NUMBER; r++) {
//#pragma HLS unroll factor=36
//		b_i[r] = B[r];
//	}

	//Column-major order matrix multiplication
	for_loop_1: for (int i = 0; i < M; i++) {
#pragma HLS unroll factor=4
		for_loop_2: for (int j = 0; j < N; j++) {
#pragma HLS unroll factor=6
			C[j * M + i] = 0;

			for_loop_3: for (int k = 0; k < L; k++) {
#pragma HLS unroll factor=6
				C[j * M + i] += A[k * M + i] * B[j * L + k];
			}
		}
	}

//	// Copy local memory contents to outputs
//	c_row_loop: for (int r = 0; r < MATRIX_ELEMENT_NUMBER; r++)
//#pragma HLS unroll factor=36
//		C[r] = c_i[r];
//
}

