#include "affine.h"

void shift_x(VertexData *main_struct, double a) {
  for (unsigned int i = 0; i < main_struct->matrix_3d.rows; i++)
    main_struct->matrix_3d.matrix[i][0] += a;
}

void shift_y(VertexData *main_struct, double a) {
  for (unsigned int i = 0; i < main_struct->matrix_3d.rows; i++)
    main_struct->matrix_3d.matrix[i][1] += a;
}

void shift_z(VertexData *main_struct, double a) {
  for (unsigned int i = 0; i < main_struct->matrix_3d.rows; i++)
    main_struct->matrix_3d.matrix[i][2] += a;
}

void rotate_ox(VertexData *main_struct, double L) {
  for (unsigned int i = 0; i < main_struct->matrix_3d.rows; i++) {

    double y = main_struct->matrix_3d.matrix[i][1];
    double z = main_struct->matrix_3d.matrix[i][2];
    main_struct->matrix_3d.matrix[i][1] = cos(L) * y - sin(L) * z;
    main_struct->matrix_3d.matrix[i][2] = sin(L) * y + cos(L) * z;
  }
}

void rotate_oy(VertexData *main_struct, double L) {
  for (unsigned int i = 0; i < main_struct->matrix_3d.rows; i++) {
    double x = main_struct->matrix_3d.matrix[i][0];
    double z = main_struct->matrix_3d.matrix[i][2];
    main_struct->matrix_3d.matrix[i][0] = cos(L) * x + sin(L) * z;
    main_struct->matrix_3d.matrix[i][2] = sin(L) * -x + cos(L) * z;
  }
}

void rotate_oz(VertexData *main_struct, double L) {
  for (unsigned int i = 0; i < main_struct->matrix_3d.rows; i++) {
    double x = main_struct->matrix_3d.matrix[i][0];
    double y = main_struct->matrix_3d.matrix[i][1];
    main_struct->matrix_3d.matrix[i][0] = cos(L) * x + sin(L) * y;
    main_struct->matrix_3d.matrix[i][1] = sin(L) * -x + cos(L) * y;
  }
}

void change_scale(VertexData *main_struct, double a) {
  for (unsigned int i = 0; i < main_struct->matrix_3d.rows && a != 0; i++) {
    double x = main_struct->matrix_3d.matrix[i][0];
    double y = main_struct->matrix_3d.matrix[i][1];
    double z = main_struct->matrix_3d.matrix[i][2];
    main_struct->matrix_3d.matrix[i][0] = x * a;
    main_struct->matrix_3d.matrix[i][1] = y * a;
    main_struct->matrix_3d.matrix[i][2] = z * a;
  }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
    }
  } else {
    error = 1;
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (unsigned int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL)
        free(A->matrix[i]);
    }
    if (A->matrix != NULL)
      free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}
