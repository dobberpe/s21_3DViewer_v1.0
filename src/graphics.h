#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

#include <QWheelEvent>
#include <QtOpenGL>
#include <iostream>


extern "C" {
#include "common/common.h"
}



    class Viewer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

    double scale_val = 30;
    QPoint cur_pos;
    QPoint new_pos;

    Figure *new_data;

    int KOCTblJIb = 3000;



protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    double m_max(double a, double b, double c, int fact);

};
#endif // VIEWER_H
