#ifndef VIEWER_H
#define VIEWER_H

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QtOpenGL>

extern "C" {
#include "../common/common.h"
}

class Viewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  Figure *new_data;
  double curr_scale = 1;

  Viewer(QWidget *parent = nullptr);
  ~Viewer();
  void loadModel(QString filename);
  void move_event();
  void rotate_event();
  void scale_event();
  void update_alpha(int valueX, int valueY);
  void update_move_vector(int valueX, int valueY);
  void update_scale(int value);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

  QPoint cur_pos;
  QPoint new_pos;
  QString start_file = QString("./obj_files/3dviewer.obj");
  double move_coef;
};
#endif  // VIEWER_H
