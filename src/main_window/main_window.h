#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

#include "graphics/graphics.h"

#define ROTATE true
#define MOVE false

class main_window : public QMainWindow {
  Q_OBJECT
 public:
  explicit main_window(QWidget *parent = nullptr);

 private slots:
  void on_loadButton_clicked();
  void on_rotationXSlider_valueChanged(int value);
  void on_rotationYSlider_valueChanged(int value);
  void on_rotationZSlider_valueChanged(int value);
  void on_moveXSlider_valueChanged(int value);
  void on_moveYSlider_valueChanged(int value);
  void on_moveZSlider_valueChanged(int value);
  void on_scaleSlider_valueChanged(int value);
  void on_increaseScaleButton_clicked();
  void on_decreaseScaleButton_clicked();
  void on_screenshotButton_clicked();

 private:
  void rotate_slider(double rotate_X, double rotate_Y, double rotate_Z);
  void move_slider(double move_X, double move_Y, double move_Z);
  void scale_slider(double scale);
  void setupUI();
  void setupSliderBox(QVBoxLayout *rightColumnLayout, bool rotate);

  Viewer *v;

  QPushButton *loadButton;
  QSlider *rotationXSlider;
  QSlider *rotationYSlider;
  QSlider *rotationZSlider;
  QSlider *moveXSlider;
  QSlider *moveYSlider;
  QSlider *moveZSlider;
  QSlider *scaleSlider;
  QPushButton *increaseScaleButton;
  QPushButton *decreaseScaleButton;
  QPushButton *screenshotButton;

  int curr_moveX = 0;
  int curr_moveY = 0;
  int curr_moveZ = 0;
  int curr_rotateX = 0;
  int curr_rotateY = 0;
  int curr_rotateZ = 0;
  int curr_scale = 0;
 signals:
};

#endif  // MAIN_WINDOW_H
