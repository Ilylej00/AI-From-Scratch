#include "activations.h"

#include <math.h>
#include "../matrix/ops.h"

#define EULER 2.71828182845904523536

double sigmoid(double n){
    return (1/(1 + pow(EULER, -n)));
}

// stolen
Matrix* sigmoidPrime(Matrix* m){
    Matrix* ones = matrix_create(m->rows, m->cols);
	matrix_fill(ones, 1);
	Matrix* subtracted = subtract(ones, m);
	Matrix* multiplied = multiply(m, subtracted);
	matrix_free(ones);
	matrix_free(subtracted);
	return multiplied;
}

// stolen
Matrix* softmax(Matrix* m) {
	double total = 0;
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			total += exp(m->entries[i][j]);
		}
	}
	Matrix* mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < mat->rows; i++) {
		for (int j = 0; j < mat->cols; j++) {
			mat->entries[i][j] = exp(m->entries[i][j]) / total;
		}
	}
	return mat;
}