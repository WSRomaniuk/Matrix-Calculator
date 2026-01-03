#pragma once

// Struktura zawierajaca wymiary i wartosci macierzy
typedef struct {
    int rows;
    int columns;
    float** values;
} Matrix;

// Struktura do przechowywania dwoch macierzy wynikowych
typedef struct {
    Matrix matrix1;
    Matrix matrix2;
} Matrices;

// Deklaracje funkcji
Matrix allocate_memory_for_matrix(rows, columns);
Matrix read_matrix_from_csv(char* filename);
void free_memory_for_matrix(Matrix matrix);
void write_matrix_to_csv(char* filename, Matrix matrix);