#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

#include <QWheelEvent>
#include <QtOpenGL>
#include <iostream>
#include "model.h"

typedef enum { x = 0, y, z } crd;

typedef struct Polygon {
    int* vertex_p;
    int amount_p;
} Polygon;

typedef struct Figure {
    double* vertex;
    int amount_vertex;
    Polygon* polygon;
    int amount_polygon;
    double x_max, y_max, z_max, x_min, y_min, z_min;
} Figure;



    class Viewer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

    obj_data data = {0, NULL, 0, NULL};
    void parse_obj();
    double scale_val = 30;
    QPoint cur_pos;
    QPoint new_pos;

    Figure *new_data;

    int KOCTblJIb = 30;



protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

};
#endif // VIEWER_H
