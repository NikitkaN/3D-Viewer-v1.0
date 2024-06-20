#include "mainwindow.h"

#include "oglwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->shiftBtn, SIGNAL(clicked()), this, SLOT(press_shift()));
  connect(ui->rotateBtn, SIGNAL(clicked()), this, SLOT(press_rotate()));
  connect(ui->fileBtn, SIGNAL(clicked()), this, SLOT(open_file()));
  connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(save_file()));
  connect(ui->startRecordBtn, SIGNAL(clicked()), this, SLOT(start_record()));
  connect(ui->stopRecordBtn, SIGNAL(clicked()), this, SLOT(stop_record()));
  connect(ui->addFrameBtn, SIGNAL(clicked()), this, SLOT(create_frame()));
  connect(ui->horizontalSlider, &QSlider::valueChanged, this,
          &MainWindow::changeScale);
}

MainWindow::~MainWindow() {
  if (ui->widget->file_for_write) {
    write_to_file();
    fclose(ui->widget->file_for_write);
  }
  delete ui;
}

void MainWindow::press_shift() {
  double shiftX = ui->XLine->text().toDouble();
  double shiftY = ui->YLine->text().toDouble();
  double shiftZ = ui->ZLine->text().toDouble();

  double coord[3];
  coord[0] = shiftX;
  coord[1] = shiftY;
  coord[2] = shiftZ;

  ui->widget->shift(coord);
  create_frame();
}

void MainWindow::press_rotate() {
  double rotateX = ui->OXLine->text().toDouble();
  double rotateY = ui->OYLine->text().toDouble();
  double rotateZ = ui->OZLine->text().toDouble();

  double rotation[3];
  rotation[0] = rotateX;
  rotation[1] = rotateY;
  rotation[2] = rotateZ;

  ui->widget->rotate(rotation);
  create_frame();
}

QString MainWindow::get_filename(QString path_to_file) {
  QString res;
  char *path_to_file_str = new char[path_to_file.length()];
  QByteArray barr = path_to_file.toLatin1();
  strncpy(path_to_file_str, barr, path_to_file.length() + 1);
  char *file_name_str = strrchr(path_to_file_str, '/');
  file_name_str += 1;
  res = QString::fromUtf8(file_name_str);
  delete[] path_to_file_str;
  path_to_file_str = NULL;
  return res;
}

void MainWindow::open_file() {
  ui->horizontalSlider->setValue(1000);
  ui->widget->open();

  ui->file_name->setText(get_filename(ui->widget->file_name));
  ui->vertexes->setText(
      QString::number(ui->widget->main_struct.count_of_vertexes));
  ui->facets->setText(QString::number(ui->widget->main_struct.count_of_facets));

  if (!ui->widget->file_size) {
    ui->comboBox_projection->setCurrentIndex(ui->widget->projection);
    ui->background_red->setValue(ui->widget->mas_color[0]);
    ui->background_green->setValue(ui->widget->mas_color[1]);
    ui->background_blue->setValue(ui->widget->mas_color[2]);
    ui->edges_red->setValue(ui->widget->mas_color_edges[0]);
    ui->edges_green->setValue(ui->widget->mas_color_edges[1]);
    ui->edges_blue->setValue(ui->widget->mas_color_edges[2]);
    ui->vertices_red->setValue(ui->widget->mas_color_points[0]);
    ui->vertices_green->setValue(ui->widget->mas_color_points[1]);
    ui->vertices_blue->setValue(ui->widget->mas_color_points[2]);
    ui->edges_width->setValue(ui->widget->width_edges);
    ui->vertices_size->setValue(ui->widget->size_point);
    ui->comboBox_edges_type->setCurrentIndex(ui->widget->flag_dotted_line);
    ui->comboBox_vertices_type->setCurrentIndex(ui->widget->flag_draw_point);
  }
}

void MainWindow::save_file() {
  QString file = QFileDialog::getSaveFileName(this, "Сохранить как", "model",
                                              "BMP (*.bmp);; JPEG (*.jpeg)");
  ui->widget->grab().save(file);
}

void MainWindow::create_frame() {
  if (red_dot_record == true) {
    frames.push_back(ui->widget->grab().toImage());
  }
}

void MainWindow::start_record() {
  red_dot_record = true;
  ui->startRecordBtn->setEnabled(false);
  ui->addFrameBtn->setEnabled(true);
  ui->stopRecordBtn->setEnabled(true);
}

void MainWindow::stop_record() {
  red_dot_record = false;
  QString Gif_file = QFileDialog::getSaveFileName(
      this, "Сохранить запись", "record", "GIF (*.gif);;GIF (*.gif)");
  QGifImage gif(QSize(640, 480));
  QVector<QRgb> ctable;
  ctable << qRgb(255, 255, 255) << qRgb(0, 0, 0) << qRgb(255, 0, 0)
         << qRgb(0, 255, 0) << qRgb(0, 0, 255) << qRgb(255, 255, 0)
         << qRgb(0, 255, 255) << qRgb(255, 0, 255);

  gif.setGlobalColorTable(ctable);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator img = frames.begin(); img != frames.end();
       ++img) {
    gif.addFrame(*img);
  }
  gif.save(Gif_file);
  frames.clear();

  ui->startRecordBtn->setEnabled(true);
  ui->addFrameBtn->setEnabled(false);
  ui->stopRecordBtn->setEnabled(false);
}

void MainWindow::changeScale() {
  double scale = 1;
  if (scale_value < ui->horizontalSlider->value()) {
    scale = 1.2;
  } else {
    scale = 0.83;
  }
  scale_value += (ui->horizontalSlider->value() - scale_value);
  ui->widget->setScale(scale);
}

void MainWindow::on_refresh_background_clicked() {
  ui->widget->set_background_color(ui->background_red->value(),
                                   ui->background_green->value(),
                                   ui->background_blue->value());
}

void MainWindow::on_refresh_background_2_clicked() {
  ui->widget->set_edges_color(ui->edges_red->value(), ui->edges_green->value(),
                              ui->edges_blue->value());
}

void MainWindow::on_refresh_background_3_clicked() {
  ui->widget->set_edges_width(ui->edges_width->value());
}

void MainWindow::on_comboBox_projection_currentIndexChanged(int index) {
  ui->widget->changeProjection(index);
}

void MainWindow::on_comboBox_edges_type_currentIndexChanged(int index) {
  ui->widget->set_edges_type(index);
}

void MainWindow::on_comboBox_vertices_type_currentIndexChanged(int index) {
  ui->widget->set_vertices_type(index);
}

void MainWindow::on_refresh_background_4_clicked() {
  ui->widget->set_vertices_color(ui->vertices_red->value(),
                                 ui->vertices_green->value(),
                                 ui->vertices_blue->value());
}

void MainWindow::on_refresh_background_5_clicked() {
  ui->widget->set_vertices_size(ui->vertices_size->value());
}

void MainWindow::write_to_file() {
  char proection = ui->widget->projection + '0';
  fputc(proection, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);

  QString qstr_back_red = QString::number(ui->widget->mas_color[0]);
  char *str_back_red = new char[qstr_back_red.length()];
  QByteArray barr_back_red = qstr_back_red.toLatin1();
  strncpy(str_back_red, barr_back_red, qstr_back_red.length() + 1);
  fputs(str_back_red, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_back_red;

  QString qstr_back_green = QString::number(ui->widget->mas_color[1]);
  char *str_back_green = new char[qstr_back_green.length()];
  QByteArray barr_back_green = qstr_back_green.toLatin1();
  strncpy(str_back_green, barr_back_green, qstr_back_green.length() + 1);
  fputs(str_back_green, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_back_green;

  QString qstr_back_blue = QString::number(ui->widget->mas_color[2]);
  char *str_back_blue = new char[qstr_back_blue.length()];
  QByteArray barr_back_blue = qstr_back_blue.toLatin1();
  strncpy(str_back_blue, barr_back_blue, qstr_back_blue.length() + 1);
  fputs(str_back_blue, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_back_blue;

  QString qstr_line_red = QString::number(ui->widget->mas_color_edges[0]);
  char *str_line_red = new char[qstr_line_red.length()];
  QByteArray barr_line_red = qstr_line_red.toLatin1();
  strncpy(str_line_red, barr_line_red, qstr_line_red.length() + 1);
  fputs(str_line_red, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_line_red;

  QString qstr_line_green = QString::number(ui->widget->mas_color_edges[1]);
  char *str_line_green = new char[qstr_line_green.length()];
  QByteArray barr_line_green = qstr_line_green.toLatin1();
  strncpy(str_line_green, barr_line_green, qstr_line_green.length() + 1);
  fputs(str_line_green, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_line_green;

  QString qstr_line_blue = QString::number(ui->widget->mas_color_edges[2]);
  char *str_line_blue = new char[qstr_line_blue.length()];
  QByteArray barr_line_blue = qstr_line_blue.toLatin1();
  strncpy(str_line_blue, barr_line_blue, qstr_line_blue.length() + 1);
  fputs(str_line_blue, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_line_blue;

  QString qstr_line_widht = QString::number(ui->widget->width_edges);
  char *str_line_widht = new char[qstr_line_widht.length()];
  QByteArray barr_line_widht = qstr_line_widht.toLatin1();
  strncpy(str_line_widht, barr_line_widht, qstr_line_widht.length() + 1);
  fputs(str_line_widht, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_line_widht;

  char line_type = ui->widget->flag_dotted_line + '0';
  fputc(line_type, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);

  QString qstr_point_red = QString::number(ui->widget->mas_color_points[0]);
  char *str_point_red = new char[qstr_point_red.length()];
  QByteArray barr_point_red = qstr_point_red.toLatin1();
  strncpy(str_point_red, barr_point_red, qstr_point_red.length() + 1);
  fputs(str_point_red, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_point_red;

  QString qstr_point_green = QString::number(ui->widget->mas_color_points[1]);
  char *str_point_green = new char[qstr_point_green.length()];
  QByteArray barr_point_green = qstr_point_green.toLatin1();
  strncpy(str_point_green, barr_point_green, qstr_point_green.length() + 1);
  fputs(str_point_green, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_point_green;

  QString qstr_point_blue = QString::number(ui->widget->mas_color_points[2]);
  char *str_point_blue = new char[qstr_point_blue.length()];
  QByteArray barr_point_blue = qstr_point_blue.toLatin1();
  strncpy(str_point_blue, barr_point_blue, qstr_point_blue.length() + 1);
  fputs(str_point_blue, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_point_blue;

  QString qstr_point_size = QString::number(ui->widget->size_point);
  char *str_point_size = new char[qstr_point_size.length()];
  QByteArray barr_point_size = qstr_point_size.toLatin1();
  strncpy(str_point_size, barr_point_size, qstr_point_size.length() + 1);
  fputs(str_point_size, ui->widget->file_for_write);
  fputc('\n', ui->widget->file_for_write);
  delete[] str_point_size;

  char point_type = ui->widget->flag_draw_point + '0';
  fputc(point_type, ui->widget->file_for_write);
}
