#include "main_window.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent) {

    setWindowTitle("3dViewer");
    setFixedSize(800, 600);

    v = new Viewer;
    v->setMinimumSize(600, 600);

    QPushButton *loadButton = new QPushButton("Load Model");
    connect(loadButton, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Model File", "", "OBJ Files (*.obj)");
        if (!fileName.isEmpty()) {
            v->loadModel(fileName);
        }
    });

    QSlider *rotationXSlider = new QSlider(Qt::Horizontal);
    rotationXSlider->setRange(-180, 180);
    connect(rotationXSlider, &QSlider::valueChanged, [this](int value) {
        v->update_alpha(value - curr_rotateX, 0);
        v->rotate_event();
    });

    QSlider *rotationYSlider = new QSlider(Qt::Horizontal);
    rotationYSlider->setRange(-180, 180);
    connect(rotationYSlider, &QSlider::valueChanged, [this](int value) {
        v->update_alpha(0, value - curr_rotateY);
        v->rotate_event();
    });

    QSlider *moveXSlider = new QSlider(Qt::Horizontal);
    moveXSlider->setRange(-180, 180);
    connect(moveXSlider, &QSlider::valueChanged, [this](int value) {
        v->update_move_vector(value - curr_moveX, 0);
        v->move_event();
    });

    QSlider *moveYSlider = new QSlider(Qt::Horizontal);
    moveYSlider->setRange(-180, 180);
    connect(moveYSlider, &QSlider::valueChanged, [this](int value) {
        v->update_move_vector(0, value - curr_moveY);
        v->move_event();
    });

    QSlider *scaleSlider = new QSlider(Qt::Horizontal);
    scaleSlider->setRange(-180, 180);
    connect(scaleSlider, &QSlider::valueChanged, [this](int value) {
        v->update_scale(value - curr_scale);
        v->scale_event();
    });

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(v, 0, 0);
    layout->addWidget(loadButton, 0, 1);
    layout->addWidget(rotationXSlider, 1, 1);
    layout->addWidget(rotationYSlider, 2, 1);
    layout->addWidget(moveXSlider, 3, 1);
    layout->addWidget(moveYSlider, 4, 1);
    layout->addWidget(scaleSlider, 5, 1);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}
