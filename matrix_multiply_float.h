#ifndef MATRIX_MULTIPLY_H
#define MATRIX_MULTIPLY_H

#include "stdint.h"

#define MATRIX_ELEMENT_NUMBER 36

#define M 6
#define N 6
#define L 6

// Define implementation type
typedef float MATRIX_T;

void matrix_multiply(const MATRIX_T A[MATRIX_ELEMENT_NUMBER],
							const MATRIX_T B[MATRIX_ELEMENT_NUMBER],
								  MATRIX_T C[MATRIX_ELEMENT_NUMBER]);

#endif

