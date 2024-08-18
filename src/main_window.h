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

private:
    void rotate_slider(double rotate_X, double rotate_Y, double rotate_Z);
    void move_slider(double move_X, double move_Y, double move_Z);
    void scale_slider(double scale);
    void arrange_objects();

    Viewer *v;

    QPushButton *loadButton;
    QSlider *rotationXSlider;
    QSlider *rotationYSlider;
    QSlider *rotationZSlider;
    QSlider *moveXSlider;
    QSlider *moveYSlider;
    QSlider *moveZSlider;
    QSlider *scaleSlider;
    QGridLayout *mainLayout;
    QWidget *centralWidget;

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
