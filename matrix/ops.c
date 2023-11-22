#include "ops.h"
#include <stdlib.h>
#include <stdio.h>

Matrix* multiply(Matrix* m1, Matrix* m2){
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        printf("Matrices need to be the same multiplying\n");
        exit(EXIT_FAILURE);
    }

    // result Matrix [m1 rows] by [m2 cols]
    Matrix* res = matrix_create(m1->rows, m2->cols);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] = m1->entries[row][col] * m2->entries[row][col];
        }
    }

    return res;
}

Matrix* add(Matrix* m1, Matrix* m2){
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        printf("Matrices need to be the same for adding\n");
        exit(EXIT_FAILURE);
    }

    Matrix* res = matrix_copy(m1);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] += m2->entries[row][col];
        }
    }

    return res;
}

Matrix* subtract(Matrix* m1, Matrix* m2){
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        printf("Matrices need to be the same for subtracting\n");
        exit(EXIT_FAILURE);
    }

    Matrix* res = matrix_copy(m1);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] -= m2->entries[row][col];
        }
    }

    return res;
}

Matrix* dot(Matrix* m1, Matrix* m2){
    if (m1->cols != m2->rows) {
        printf("dot product meeds m1 to have as many cols and m2 has rows");
        exit(EXIT_FAILURE);
    }

    // how long the vectors will be for the entry dot prodcut
    int vector_length = m1->cols;

    Matrix* res = matrix_create(m1->rows, m2->cols);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            // now vector dot product the row/col
            double entry = 0;
            for (int i = 0; i < vector_length; i++) {
                entry += m1->entries[row][i] * m2->entries[i][col];
            }

            res->entries[row][col] = entry;
        }
    }

    return res;
}

Matrix* apply(double (*func)(double), Matrix* m){
    Matrix* res = matrix_copy(m);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] = (*func)(res->entries[row][col]);
        }
    }

    return res;
}

Matrix* scale(double n, Matrix* m){
    Matrix* res = matrix_copy(m);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] = n * res->entries[row][col];
        }
    }

    return res;
}

Matrix* addScalar(double n, Matrix* m){
    Matrix* res = matrix_copy(m);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] = n + res->entries[row][col];
        }
    }

    return res;
}

Matrix* transpose(Matrix* m){
    Matrix* res = matrix_create(m->cols, m->rows);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] = m->entries[col][row];
        }
    }

    return res;
}