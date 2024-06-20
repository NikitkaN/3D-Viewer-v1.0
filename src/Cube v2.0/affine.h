#ifndef AFFINE_H
#define AFFINE_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef struct matrix_struct
{
    double **matrix;
    unsigned int rows;
    unsigned int columns;
} matrix_t;

typedef struct facets
{
    unsigned int *vertexes;                     // массив номеров вершин
    unsigned int numbers_of_vertexes_in_facets; // кол-во вершин, нужные для соединения
} polygon_t;

typedef struct data
{
    unsigned int count_of_vertexes; // число вершин
    unsigned int count_of_facets;   // число полигонов
    matrix_t matrix_3d;             // матрица
    polygon_t *polygons;            // полигоны
} VertexData;

void shift_x(VertexData *main_struct, double a);
void shift_y(VertexData *main_struct, double a);
void shift_z(VertexData *main_struct, double a);
void rotate_ox(VertexData *main_struct, double L);
void rotate_oy(VertexData *main_struct, double L);
void rotate_oz(VertexData *main_struct, double L);
void change_scale(VertexData *main_struct, double a);
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int parser(VertexData *main_struct, char *filepath);
int start_parser(VertexData *main_struct, char *filepath);
int read_parser(VertexData *main_struct, char *filepath);
void parse_vertexes(VertexData *main_struct, char *line, int count);
void count_vertexes(VertexData *main_struct, char *line, int count);
void parse_polygons(VertexData *main_struct, char *line, int count);
void free_data(VertexData *main_struct);

#endif // AFFINE_H
