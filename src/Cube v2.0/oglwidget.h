#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QtOpenGLWidgets/qopenglwidget.h>
#include <stdlib.h>
#include <string.h>

#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QWidget>

#ifdef __cplusplus
extern "C" {
#include "affine.h"
}
#endif

class OGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  VertexData main_struct;
  QString file_name;
  FILE* file_for_write = NULL;
  int file_size = 0;
  int projection = 0;
  GLfloat mas_color[3] = {0, 0, 0};

  GLdouble mas_color_edges[3] = {1, 1, 1};
  GLfloat width_edges = 1;
  int flag_dotted_line = 0;

  GLdouble mas_color_points[3] = {1, 1, 1};
  GLfloat size_point = 1;
  int flag_draw_point = 0;

  OGLWidget(QWidget* parent = nullptr) : QOpenGLWidget(parent) {
    main_struct.count_of_facets = 0;
    main_struct.count_of_vertexes = 0;
    main_struct.polygons = NULL;
    main_struct.matrix_3d.matrix = NULL;
    main_struct.matrix_3d.columns = 0;
    main_struct.matrix_3d.rows = 0;
  }

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void shift(double* coord);
  void rotate(double* rotation);
  void scaling(double scale);
  void open();
  void open_config_file(char* path_to_file_str, char* file_name_str);
  void draw();
  void set_background_color(double red, double green, double blue);
  void set_edges_color(double red, double green, double blue);
  void set_edges_width(double width);
  void set_edges_type(int type);
  void set_vertices_type(int type);
  void set_vertices_color(double red, double green, double blue);
  void set_vertices_size(double size);
  void setScale(double s);
  void changeProjection(int index);

 private:
  float xRot, yRot;
  QPoint mousePos;

  void mousePressEvent(QMouseEvent* mp) override;
  void mouseMoveEvent(QMouseEvent* mp) override;
};

#endif  // OGLWIDGET_H
