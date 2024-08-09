#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>

#include "graphics.h"

class main_window : public QMainWindow
{
    Q_OBJECT
    friend class Viewer;
public:
    explicit main_window(QWidget *parent = nullptr);
private:
    void rotate_slider(double rotate_X, double rotate_Y, double rotate_Z);
    void move_slider(double move_X, double move_Y, double move_Z);
    void scale_slider(double scale);

    Viewer *v;
    int curr_moveX = 0;
    int curr_moveY = 0;
    int curr_moveZ = 0;
    int curr_rotateX = 0;
    int curr_rotateY = 0;
    int curr_rotateZ = 0;
    int curr_scale = 0;
signals:
};

#endif // MAIN_WINDOW_H
