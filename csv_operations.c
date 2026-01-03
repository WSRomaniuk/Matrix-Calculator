// 'csv_operations.c' zawiera funkcje do alokowania i zwalniania pamieci dla macierzy
// zawiera funkcje do odczytu i zapisu macierzy z pliku CSV

// Dyrektywy preprocesora
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_operations.h"

// Funkcja do alokacji pamieci dla macierzy na podstawie liczby wierszy i kolumn
Matrix allocate_memory_for_matrix(rows, columns) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.columns = columns;
    // Alokacja pamieci dla pierwszego wymiaru
    matrix.values = (float**)malloc(rows * sizeof(float*));
    // Zwrocenie bledu alokacji
    if (matrix.values == NULL) {
        perror("Memory allocation failed");
        Matrix matrix_error = { 0, 0, NULL };
        return matrix_error;
    }
    // Alokacja pamieci dla drugiego wymiaru
    for (int i = 0; i < rows; i++) {
        matrix.values[i] = (float*)malloc(columns * sizeof(float));
        // Zwrocenie bledu alokacji
        if (matrix.values[i] == NULL) {
            perror("Memory allocation failed");
            // Zwolenie zaalokowanej pamieci
            for (int j = 0; j < i; j++) {
                free(matrix.values[j]);
            }
            free(matrix.values);
            Matrix matrix_error = { 0, 0, NULL };
            return matrix_error;
        }
    }
    return matrix;
}

// Funkcja do zwalniania zaalokowanej pamieci dla macierzy
void free_memory_for_matrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        free(matrix.values[i]);
    }
    free(matrix.values);
}

// Funkcja odczytujaca macierz z pliku CSV
Matrix read_matrix_from_csv(char* filename) {
    // Otwarcie pliku w trybie odczytu
    FILE* fp = fopen(filename, "r");
    // Zwrocenie bledu odczytu
    if (fp == NULL) {
        perror("Error opening file");
        Matrix matrix_error = { 0, 0, NULL };
        return matrix_error;
    }
    char line[1024];
    int rows = 0;
    int columns = 0;
    // Sprawdzenie wymiarow macierzy na podstawie linii pliku CSV i separartora ';'
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (rows == 0) {
            char* token;
            char* next = NULL;
            token = strtok_s(line, ";", &next);
            while (token != NULL) {
                columns++;
                token = strtok_s(NULL, ";", &next);
            }
        }
        rows++;
    }
    // Powrot do poczatku pliku
    rewind(fp);
    // Alokacja pamieci
    Matrix matrix = allocate_memory_for_matrix(rows, columns);
    // Odczyt danych z pliku na podstawie linii pliku CSV i separartora ';'
    int row = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        int column = 0;
        char* token;
        char* next = NULL;
        token = strtok_s(line, ";", &next);
        while (token != NULL) {
            // Zamiana separatora dziesietnego
            char* delimiter_position = strchr(token, ',');
            if (delimiter_position != NULL) {
                *delimiter_position = '.';
            }
            // Przypisanie wartosci za pomoca konwersji zmiennej na typ float
            // Funkcja 'strtof' dla nieprawidlowej konwersji przyjmuje wartosc 0.0
            matrix.values[row][column] = strtof(token, NULL);
            token = strtok_s(NULL, ";", &next);
            column++;
        }
        row++;
    }
    fclose(fp);
    // Wyswietlenie informacji o prawidlowym odczycie macierzy z pliku CSV
    printf("Matrix: %s rows: %d columns: %d\n--read successfully--\n", filename, matrix.rows, matrix.columns);
    return matrix;
}

// Funkcja zapisujaca macierz do pliku CSV
void write_matrix_to_csv(char* filename, Matrix matrix) {
    // Otwarcie pliku w trybie zapisu
    FILE* fp = fopen(filename, "w");
    // Zwrocenie bledu odczytu
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            // Przypisanie wartosci do tymczasowej zmiennej za pomoca konwersji zmiennej na typu string
            char str_value[64];
            snprintf(str_value, sizeof(str_value), "%.3f", matrix.values[i][j]);
            // Zamiana separatora dziesietnego
            char* delimiter_position = strchr(str_value, '.');
            if (delimiter_position != NULL) {
                *delimiter_position = ',';
            }
            fprintf(fp, "%s", str_value);
            // Dodanie znaku separatora w pliku
            if (j < matrix.columns - 1) {
                fprintf(fp, ";");
            }
        }
        // Dodanie znaku konca linii
        fprintf(fp, "\n");
    }
    fclose(fp);
    // Wyswietlenie informacji o prawidlowym zapisie macierzy do pliku CSV
    printf("Matrix: %s rows: %d columns: %d\n--wrote successfully--\n", filename, matrix.rows, matrix.columns);
}