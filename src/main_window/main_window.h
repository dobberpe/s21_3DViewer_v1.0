#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
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
  void on_backgroundColorButton_clicked();
  void on_vertexColorButton_clicked();
  void on_edgesColorButton_clicked();
  void on_vertexSizeSlider_valueChanged(int value);
  void on_edgesWidthSlider_valueChanged(int value);
  void on_projectionTypeButton_clicked();
  void on_vertexTypeButton_clicked();
  void on_edgesTypeButton_clicked();
  void on_screenshotButton_clicked();
  void on_gifButton_clicked();
  void on_timer_timeout();

 private:
  void saveGif(const QString &fileName, const int delayMs);
  void rotate_slider(double rotate_X, double rotate_Y, double rotate_Z);
  void move_slider(double move_X, double move_Y, double move_Z);
  void scale_slider(double scale);
  void setupUI();
  void setupFileInfo(QVBoxLayout *rightColumnLayout);
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
  QPushButton *backgroundColorButton;
  QPushButton *vertexColorButton;
  QPushButton *edgesColorButton;
  QSlider *vertexSizeSlider;
  QSlider *edgesWidthSlider;
  QPushButton *projectionTypeButton;
  QPushButton *vertexTypeButton;
  QPushButton *edgesTypeButton;
  QPushButton *screenshotButton;
  QLabel *fnameLabel;
  QLabel *amountVnumberLabel;
  QLabel *amountEnumberLabel;
  QPushButton *gifButton;
  QTimer *timer;

  const int width = 640;
  const int height = 480;
  const int fps = 10;
  const int duration = 5;
  const int totalFrames = fps * duration;
  int currentFrame = 0;
  QList<QImage> capturedFrames;

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
