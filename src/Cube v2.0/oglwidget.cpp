#include "oglwidget.h"

void OGLWidget::initializeGL() {
  setGeometry(0, 0, 50, 50);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void OGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-12, 12, -12, 12, 1, 30);
}

void OGLWidget::paintGL() {
  glClearColor(mas_color[0], mas_color[1], mas_color[2], 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -16);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  projection ? glFrustum(-12, 12, -12, 12, 1, 30)
             : glOrtho(-12, 12, -12, 12, 1, 30);
  draw();
}

void OGLWidget::draw() {
  for (unsigned int i = 1; i < main_struct.count_of_vertexes + 1; i++) {
    if (flag_draw_point == 1) {
      glPointSize(size_point);
      glEnable(GL_POINT_SMOOTH);
      glBegin(GL_POINTS);
      glColor3d(mas_color_points[0], mas_color_points[1], mas_color_points[2]);
      glVertex3d(main_struct.matrix_3d.matrix[i][0],
                 main_struct.matrix_3d.matrix[i][1],
                 main_struct.matrix_3d.matrix[i][2]);
      glEnd();
      glDisable(GL_POINT_SMOOTH);
    } else if (flag_draw_point == 2) {
      glPointSize(size_point);
      glBegin(GL_POINTS);
      glColor3d(mas_color_points[0], mas_color_points[1], mas_color_points[2]);
      glVertex3d(main_struct.matrix_3d.matrix[i][0],
                 main_struct.matrix_3d.matrix[i][1],
                 main_struct.matrix_3d.matrix[i][2]);
      glEnd();
    }
  }

  for (unsigned int i = 1; i < main_struct.count_of_facets; i++) {
    for (unsigned int j = 0;
         j < main_struct.polygons[i].numbers_of_vertexes_in_facets; j++) {
      glLineWidth(width_edges);
      if (j == (main_struct.polygons[i].numbers_of_vertexes_in_facets - 1)) {
        if (flag_dotted_line == 1) {
          glBegin(GL_LINE_STRIP);
          glColor3d(mas_color_edges[0], mas_color_edges[1], mas_color_edges[2]);
          glVertex3d(main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[j]][0],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[j]][1],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[j]][2]);
          glVertex3d(main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[0]][0],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[0]][1],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[0]][2]);
          glEnd();
          glEnable(GL_LINE_SMOOTH);
          glEnable(GL_LINE_STIPPLE);
          glLineStipple(20, 0x333);
          break;
        } else if (flag_dotted_line == 0) {
          glBegin(GL_LINES);
          glColor3d(mas_color_edges[0], mas_color_edges[1], mas_color_edges[2]);
          glVertex3d(main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[j]][0],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[j]][1],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[j]][2]);
          glVertex3d(main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[0]][0],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[0]][1],
                     main_struct.matrix_3d
                         .matrix[main_struct.polygons[i].vertexes[0]][2]);
          glEnd();
          glDisable(GL_LINE_SMOOTH);
          glDisable(GL_LINE_STIPPLE);
          break;
        }
      }
      if (flag_dotted_line == 1) {
        glBegin(GL_LINE_STRIP);
        glColor3d(mas_color_edges[0], mas_color_edges[1], mas_color_edges[2]);
        glVertex3d(main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j]][0],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j]][1],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j]][2]);
        glVertex3d(main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j + 1]][0],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j + 1]][1],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j + 1]][2]);
        glEnd();
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(15, 0x3333);
      } else if (flag_dotted_line == 0) {
        glBegin(GL_LINES);
        glColor3d(mas_color_edges[0], mas_color_edges[1], mas_color_edges[2]);
        glVertex3d(main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j]][0],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j]][1],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[j]][2]);
        glVertex3d(main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[0]][0],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[0]][1],
                   main_struct.matrix_3d
                       .matrix[main_struct.polygons[i].vertexes[0]][2]);
        glEnd();
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_LINE_STIPPLE);
      }
    }
  }
}

void OGLWidget::set_background_color(double red, double green, double blue) {
  mas_color[0] = red;
  mas_color[1] = green;
  mas_color[2] = blue;
  update();
}

void OGLWidget::set_edges_color(double red, double green, double blue) {
  mas_color_edges[0] = red;
  mas_color_edges[1] = green;
  mas_color_edges[2] = blue;
  update();
}

void OGLWidget::set_edges_width(double width) {
  width_edges = width;
  update();
}

void OGLWidget::set_edges_type(int type) {
  flag_dotted_line = type;
  update();
}

void OGLWidget::set_vertices_type(int type) {
  flag_draw_point = type;
  update();
}

void OGLWidget::set_vertices_color(double red, double green, double blue) {
  mas_color_points[0] = red;
  mas_color_points[1] = green;
  mas_color_points[2] = blue;
  update();
}

void OGLWidget::set_vertices_size(double size) {
  size_point = size;
  update();
}

void OGLWidget::setScale(double s) {
  this->scaling(s);
  update();
}

void OGLWidget::changeProjection(int index) {
  projection = index;
  update();
}

void OGLWidget::shift(double *coord) {
  shift_x(&main_struct, coord[0]);
  shift_y(&main_struct, coord[1]);
  shift_z(&main_struct, coord[2]);
  update();
}

void OGLWidget::rotate(double *rotation) {
  rotate_ox(&main_struct, rotation[0]);
  rotate_oy(&main_struct, rotation[1]);
  rotate_oz(&main_struct, rotation[2]);
  update();
}

void OGLWidget::scaling(double scale) {
  change_scale(&main_struct, scale);
  update();
}

void OGLWidget::open() {
  QString path_to_file =
      QFileDialog::getOpenFileName(NULL, "Open", "", "*.obj");
  char *path_to_file_str = new char[path_to_file.length()];
  QByteArray barr = path_to_file.toLatin1();
  strncpy(path_to_file_str, barr, path_to_file.length() + 1);
  parser(&main_struct, path_to_file_str);
  char *file_name_str = strrchr(path_to_file_str, '/');
  file_name_str += 1;
  file_name = path_to_file;
  open_config_file(path_to_file_str, file_name_str);
  delete[] path_to_file_str;
  path_to_file_str = NULL;
  update();
}

void OGLWidget::open_config_file(char *path_to_file_str, char *file_name_str) {
  char filename_config[20] = "config";
  char new_path[256];
  memset(new_path, '\0', 256);
  strncpy(new_path, path_to_file_str,
          strlen(path_to_file_str) - strlen(file_name_str));
  strcat(new_path, filename_config);
  file_for_write = fopen(new_path, "r");
  qDebug() << new_path;
  if (!file_for_write) {
    file_for_write = fopen(new_path, "w");
  } else {
    fseek(file_for_write, 0, SEEK_END);
    file_size = ftell(file_for_write);
    if (0 != file_size) {
      fseek(file_for_write, 0, SEEK_SET);
      char s[256];
      memset(s, '\0', 256);

      fgets(s, 5, file_for_write);
      projection = atoi(s);

      fgets(s, 5, file_for_write);
      mas_color[0] = atof(s);

      fgets(s, 5, file_for_write);
      mas_color[1] = atof(s);

      fgets(s, 5, file_for_write);
      mas_color[2] = atof(s);

      fgets(s, 5, file_for_write);
      mas_color_edges[0] = atof(s);

      fgets(s, 5, file_for_write);
      mas_color_edges[1] = atof(s);

      fgets(s, 5, file_for_write);
      mas_color_edges[2] = atof(s);

      fgets(s, 5, file_for_write);
      width_edges = atof(s);

      fgets(s, 5, file_for_write);
      flag_dotted_line = atoi(s);

      fgets(s, 5, file_for_write);
      mas_color_points[0] = atof(s);

      fgets(s, 5, file_for_write);
      mas_color_points[1] = atof(s);

      fgets(s, 5, file_for_write);
      mas_color_points[2] = atof(s);

      fgets(s, 5, file_for_write);
      size_point = atof(s);

      fgets(s, 5, file_for_write);
      flag_draw_point = atoi(s);
      qDebug() << file_size << mas_color_edges[1] << mas_color_edges[0];
    }
    fclose(file_for_write);
    file_for_write = fopen(new_path, "w");
  }
}

void OGLWidget::mousePressEvent(QMouseEvent *mp) { mousePos = mp->pos(); }

void OGLWidget::mouseMoveEvent(QMouseEvent *mp) {
  xRot = 1 / M_PI * (mp->pos().y() - mousePos.y());
  yRot = 1 / M_PI * (mp->pos().x() - mousePos.x());
  update();
}
