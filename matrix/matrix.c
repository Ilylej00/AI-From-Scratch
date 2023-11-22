#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100

Matrix* matrix_create(int row, int col){
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = row;
    matrix->cols = col;

    matrix->entries = malloc(row * sizeof(void*));

    for (int rows = 0; rows < row; rows++) {
        matrix->entries[rows] = malloc(sizeof(double) * col);
    }

    return matrix;
    
}

void matrix_fill(Matrix *m, int n){
    for (int row = 0; row < m->rows; row++) {
        for (int col = 0; col < m->cols; col++) {
            m->entries[row][col] = n;
        }
    }
}

void matrix_free(Matrix *m){
    for (int row = 0; row < m->rows; row++) {
        free(m->entries[row]);
    }

    free(m->entries);

    free(m);
}

void matrix_print(Matrix *m){
    for (int row = 0; row < m->rows; row++) {
        printf("[");
        for (int col = 0; col < m->cols; col++) {
            printf("%lf", m->entries[row][col]);
            if (col + 1 < m->cols) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

Matrix* matrix_copy(Matrix* m){
    Matrix* res = matrix_create(m->rows, m->cols);

    for (int row = 0; row < res->rows; row++) {
        for (int col = 0; col < res->cols; col++) {
            res->entries[row][col] = m->entries[row][col];
        }
    }

    return res;
}

// This function was stolen
void matrix_save(Matrix* m, char* file_string) {
	FILE* file = fopen(file_string, "w");
	fprintf(file, "%d\n", m->rows);
	fprintf(file, "%d\n", m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fprintf(file, "%.6f\n", m->entries[i][j]);
		}
	}
	printf("Successfully saved matrix to %s\n", file_string);
	fclose(file);
}

// This function was stolen
Matrix* matrix_load(char* file_string) {
	FILE* file = fopen(file_string, "r");
	char entry[MAXCHAR]; 
	fgets(entry, MAXCHAR, file);
	int rows = atoi(entry);
	fgets(entry, MAXCHAR, file);
	int cols = atoi(entry);
	Matrix* m = matrix_create(rows, cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fgets(entry, MAXCHAR, file);
			m->entries[i][j] = strtod(entry, NULL);
		}
	}
	printf("Sucessfully loaded matrix from %s\n", file_string);
	fclose(file);
	return m;
}

// This function was stolen
double uniform_distribution(double low, double high) {
	double difference = high - low; // The difference between the two
	int scale = 10000;
	int scaled_difference = (int)(difference * scale);
	return low + (1.0 * (rand() % scaled_difference) / scale);
}

// This function was stolen - I have never used random floats in C before,
// and it looked like this needed to be kind of specific to make the NN function
void matrix_randomize(Matrix* m, int n){
    double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
    for (int row = 0; row < m->rows; row++) {
        for (int col = 0; col < m->cols; col++) {
            m->entries[row][col] = uniform_distribution(min, max);
        }
    }
}

int matrix_argmax(Matrix* m){
    Matrix* m_flat = matrix_flatten(m, 1);
    int max_index = 0;
    double max_entry = m_flat->entries[0][0];

    for (int col = 0; col < m_flat->cols; col++) {
        if (m_flat->entries[0][col] > max_entry) {
            max_index = col;
            max_entry = m_flat->entries[0][col];
        }
    }

    matrix_free(m_flat);

    return max_index;
}

// Only needed to know how I should interpret axis number
Matrix* matrix_flatten(Matrix* m, int axis){
    Matrix* flat_matrix;
    if (axis == 0) {
        flat_matrix = matrix_create(m->cols * m->rows, 1);
    } else {
        flat_matrix = matrix_create(1, m->cols * m->rows);
    }
    
    int fill_index = 0;
    for (int row = 0; row < m->rows; row++) {
        for (int col = 0; col < m->cols; col++) {
            if (axis == 0) {
                flat_matrix->entries[fill_index][0] = m->entries[row][col];
            } else {
                flat_matrix->entries[0][fill_index] = m->entries[row][col];
            }
            
            fill_index++;
        }
    }

    return flat_matrix;
}