#include "main_window.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent) {

    setWindowTitle("3dViewer");
    setFixedSize(800, 600);

    v = new Viewer;
    v->setMinimumSize(600, 600);

    rotationXSlider = new QSlider(Qt::Horizontal);
    rotationXSlider->setRange(-180, 180);
    connect(rotationXSlider, &QSlider::valueChanged, this, &main_window::on_rotationXSlider_valueChanged);

    rotationYSlider = new QSlider(Qt::Horizontal);
    rotationYSlider->setRange(-180, 180);
    connect(rotationYSlider, &QSlider::valueChanged, this, &main_window::on_rotationYSlider_valueChanged);

    rotationZSlider = new QSlider(Qt::Horizontal);
    rotationZSlider->setRange(-180, 180);
    connect(rotationZSlider, &QSlider::valueChanged, this, &main_window::on_rotationZSlider_valueChanged);

    moveXSlider = new QSlider(Qt::Horizontal);
    moveXSlider->setRange(-180, 180);
    connect(moveXSlider, &QSlider::valueChanged, this, &main_window::on_moveXSlider_valueChanged);

    moveYSlider = new QSlider(Qt::Horizontal);
    moveYSlider->setRange(-180, 180);
    connect(moveYSlider, &QSlider::valueChanged, this, &main_window::on_moveYSlider_valueChanged);

    moveZSlider = new QSlider(Qt::Horizontal);
    moveZSlider->setRange(-180, 180);
    connect(moveZSlider, &QSlider::valueChanged, this, &main_window::on_moveZSlider_valueChanged);

    scaleSlider = new QSlider(Qt::Horizontal);
    scaleSlider->setRange(-180, 180);
    connect(scaleSlider, &QSlider::valueChanged, this, &main_window::on_scaleSlider_valueChanged);

    loadButton = new QPushButton("Load Model");
    connect(loadButton, &QPushButton::clicked, this, &main_window::on_loadButton_clicked);

    arrange_objects();

    centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void main_window::on_loadButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Model File", "", "OBJ Files (*.obj)");
    if (!fileName.isEmpty()) {
        v->loadModel(fileName);
        rotationXSlider->setValue(0);
        rotationYSlider->setValue(0);
        rotationZSlider->setValue(0);
        moveXSlider->setValue(0);
        moveYSlider->setValue(0);
        moveZSlider->setValue(0);
        scaleSlider->setValue(0);
        curr_rotateX = 0;
        curr_rotateY = 0;
        curr_rotateZ = 0;
        curr_moveX = 0;
        curr_moveY = 0;
        curr_moveZ = 0;
        curr_scale = 0;
    }
}

void main_window::on_rotationXSlider_valueChanged(int value) {
    rotate_slider(value - curr_rotateX, 0, 0);
    curr_rotateX = value;
}

void main_window::on_rotationYSlider_valueChanged(int value) {
    rotate_slider(0, value - curr_rotateY, 0);
    curr_rotateY = value;
}

void main_window::on_rotationZSlider_valueChanged(int value) {
    rotate_slider(0, 0, value - curr_rotateZ);
    curr_rotateZ = value;
}

void main_window::on_moveXSlider_valueChanged(int value) {
    move_slider(value - curr_moveX, 0, 0);
    curr_moveX = value;
}

void main_window::on_moveYSlider_valueChanged(int value) {
    move_slider(0, value - curr_moveY, 0);
    curr_moveY = value;
}

void main_window::on_moveZSlider_valueChanged(int value) {
    move_slider(0, 0, value - curr_moveZ);
    curr_moveZ = value;
}

void main_window::on_scaleSlider_valueChanged(int value) {
    int scale = value - curr_scale;
    v->curr_scale = pow(scale > 0 ? 1.001 : 0.999, abs(scale));
    scale_figure(v->new_data, v->curr_scale);
    v->update();
}

void main_window::rotate_slider(double rotate_X, double rotate_Y, double rotate_Z) {
    v->new_data->alpha_x = rotate_X;
    v->new_data->alpha_y = rotate_Y;
    v->new_data->alpha_z = rotate_Z;
    rotate_figure(v->new_data);
    v->update();
}

void main_window::move_slider(double move_X, double move_Y, double move_Z) {
    v->new_data->trv.move_vector[crd::x] = move_X;
    v->new_data->trv.move_vector[crd::y] = move_Y;
    v->new_data->trv.move_vector[crd::z] = move_Z;
    move_figure(v->new_data);
    v->update();
}

void main_window::arrange_objects() {
    layout = new QGridLayout;
    layout->addWidget(v, 0, 0, 9, 1);
    layout->addWidget(loadButton, 0, 1);
    layout->addWidget(rotationXSlider, 1, 1);
    layout->addWidget(rotationYSlider, 2, 1);
    layout->addWidget(rotationZSlider, 3, 1);
    layout->addWidget(moveXSlider, 4, 1);
    layout->addWidget(moveYSlider, 5, 1);
    layout->addWidget(moveZSlider, 6, 1);
    layout->addWidget(scaleSlider, 7, 1);
}
