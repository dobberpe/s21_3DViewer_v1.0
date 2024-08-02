#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

#include <QWheelEvent>
#include <QtOpenGL>
#include <iostream>
#include <algorithm>

extern "C" {
#include "common/common.h"
}

    class Viewer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    QPoint cur_pos;
    QPoint new_pos;
    Figure *new_data;
    double curr_scale = 1;
    int move_coef;

};
#endif // VIEWER_H
