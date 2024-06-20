#include "affine.h"
#include "stdio.h"

/*1. cчитать и проверить путь
2. открыть файл и считать его по строкам
3. посчитать количество вершин и полигонов
4. затем отправить в парсер
5. каждую строку запихнуть в матрицу*/

int parser(VertexData *main_struct, char *filepath) {
  int error = start_parser(main_struct, filepath);
  if (!error) {
    error = read_parser(main_struct, filepath);
  }
  return error;
}

int start_parser(VertexData *main_struct, char *filepath) {
  int error = 0;
  FILE *fp;
  size_t len = 0;
  fp = fopen(filepath, "r");
  if (fp) {
    char *str = NULL;
    main_struct->count_of_vertexes = 0;
    main_struct->count_of_facets = 0;
    while (getline(&str, &len, fp) != -1) // s21_getline
    {
      if (str[0] == 'v' && str[1] == ' ') {
        main_struct->count_of_vertexes += 1;
      }
      if (str[0] == 'f') {
        main_struct->count_of_facets += 1;
      }
    }
    free(str);
    fclose(fp);
  } else {
    error = 1;
  }

  return error;
}

int read_parser(VertexData *main_struct, char *filepath) {
  int v_count = 1;
  int f_count = 1;
  matrix_t vertex;
  int error = s21_create_matrix(main_struct->count_of_vertexes + 1, 3, &vertex);
  if (!error) {
    main_struct->matrix_3d = vertex;
    main_struct->polygons =
        calloc((main_struct->count_of_facets + 1), sizeof(polygon_t));
    FILE *fp;
    size_t len = 0;
    fp = fopen(filepath, "r");
    if (fp) {
      char *str = NULL;
      while (getline(&str, &len, fp) != -1) // s21_getline
      {
        if (str[0] == 'v' && str[1] == ' ') {
          parse_vertexes(main_struct, str, v_count);
          v_count++;
        } else if (str[0] == 'f') {
          count_vertexes(main_struct, str, f_count);
          parse_polygons(main_struct, str, f_count);
          f_count++;
        }
      }
      free(str);
      fclose(fp);
    } else {
      error = 1;
    }
  }
  return error;
}

void parse_vertexes(VertexData *main_struct, char *line, int count) {
  int j = 2;
  int check = 0;
  for (int i = 0; i < 3; i++) {
    char str[512];
    memset(str, '\0', 512);
    int index = 0;
    while (1) {
      if ((line[j] == ' ' && check) || line[j] == '\0') {
        check = 0;
        main_struct->matrix_3d.matrix[count][i] = atof(str);
        break;
      } else {
        check = 1;
        str[index] = line[j];
        index++;
        j++;
      }
    }
    j++;
  }
}

// f 1 2 3
// f 3/1 4/2 5/3
// f 6/4/1 3/5/3 7/6/
// f 6//1 3//3 7//5
// f …
void count_vertexes(VertexData *main_struct, char *line, int count) {
  int count_vertex = 0;
  // int bool_parse = 0;
  for (int i = 0; line[i] != '\0'; i++) {

    if (line[i] == ' ' && (line[i + 1] > 47 && line[i + 1] < 58)) {
      count_vertex++;
    }
  }

  main_struct->polygons[count].numbers_of_vertexes_in_facets = count_vertex;
}
void parse_polygons(VertexData *main_struct, char *line, int count) {
  main_struct->polygons[count].vertexes =
      calloc(main_struct->polygons[count].numbers_of_vertexes_in_facets,
             sizeof(unsigned int));
  int bool_parse = 0;
  int j = 0;
  int vertex_index = 0;
  char str[1024];
  memset(str, '\0', 1024);
  for (int i = 0; line[i] != '\0'; i++) {
    if ((line[i] == '/' || (line[i] == ' ') & (bool_parse == 1))) {
      bool_parse = 0;
      if (atoi(str) != 0) {
        main_struct->polygons[count].vertexes[vertex_index] = atoi(str);
        vertex_index++;
      }
      memset(str, '\0', 1024);
      j = 0;
    } else if (line[i] == ' ') {
      bool_parse = 1;
    } else if (bool_parse == 1) {
      str[j] = line[i];
      j++;
    }
  }
}

void free_data(VertexData *main_struct) // освободить структуру data
{
  s21_remove_matrix(&main_struct->matrix_3d);
  for (unsigned int i = 1; i <= main_struct->count_of_facets; i++) {
    free(main_struct->polygons[i].vertexes);
  }
  free(main_struct->polygons);
}
