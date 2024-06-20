#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "oglwidget.h"
#include "QtGif/gifimage/qgifimage.h"
#include <QMessageBox>
#include <QImage>
#include <QVector>
#include <QSize>

#ifdef __cplusplus
extern "C" {
#include "affine.h"
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QImage> frames;

private slots:
    void press_shift();
    void press_rotate();
    void open_file();
    void save_file();
    void create_frame();
    void start_record();
    void stop_record();
    void changeScale();
    void write_to_file();
    QString get_filename(QString path_to_file);

    void on_refresh_background_clicked();

    void on_refresh_background_2_clicked();

    void on_refresh_background_3_clicked();

    void on_comboBox_projection_currentIndexChanged(int index);

    void on_comboBox_edges_type_currentIndexChanged(int index);

    void on_comboBox_vertices_type_currentIndexChanged(int index);

    void on_refresh_background_4_clicked();

    void on_refresh_background_5_clicked();

private:
    Ui::MainWindow *ui;
    bool red_dot_record = false;
    int scale_value = 1000;
    int projection = 0;
};


#endif // MAINWINDOW_H
