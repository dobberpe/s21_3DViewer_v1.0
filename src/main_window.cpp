#include "main_window.h"

main_window::main_window(QWidget *parent)
    : QMainWindow(parent) {

    setWindowTitle("3dViewer");
    setMinimumSize(800, 600);

    v = new Viewer;

    loadButton = new QPushButton("Выбор файла");
    connect(loadButton, &QPushButton::clicked, this, &main_window::on_loadButton_clicked);

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

    screenshotButton = new QPushButton("Сделать снимок");
    connect(screenshotButton, &QPushButton::clicked, this, &main_window::on_screenshotButton_clicked);

    setupUI();
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

void main_window::on_screenshotButton_clicked() {
    // Создание QPixmap для захвата виджета
    QPixmap pixmap(v->size());
    v->render(&pixmap);

    // Открытие диалогового окна для сохранения файла
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранение изображения", "", "PNG Files (*.png)");
    if (!fileName.isEmpty()) {
        pixmap.save(fileName, "PNG");
    }
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

void main_window::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *mainLayout = new QGridLayout(centralWidget);
    mainLayout->addWidget(v, 0, 0, 1, 1); // Занимает весь левый столбец

    // компоновка слайдеров вращения
    QLabel *rotationLabel = new QLabel("Поворот");

    QLabel *rxLabel = new QLabel("x:");
    QHBoxLayout *rXSliderLayout = new QHBoxLayout;
    rXSliderLayout->addWidget(rxLabel);
    rXSliderLayout->addWidget(rotationXSlider);

    QLabel *ryLabel = new QLabel("y:");
    QHBoxLayout *rYSliderLayout = new QHBoxLayout;
    rYSliderLayout->addWidget(ryLabel);
    rYSliderLayout->addWidget(rotationYSlider);

    QLabel *rzLabel = new QLabel("z:");
    QHBoxLayout *rZSliderLayout = new QHBoxLayout;
    rZSliderLayout->addWidget(rzLabel);
    rZSliderLayout->addWidget(rotationZSlider);

    QVBoxLayout *rotationLayout = new QVBoxLayout;
    rotationLayout->addWidget(rotationLabel);
    rotationLayout->addLayout(rXSliderLayout);
    rotationLayout->addLayout(rYSliderLayout);
    rotationLayout->addLayout(rZSliderLayout);

    QFrame *rotationFrame = new QFrame;
    rotationFrame->setFrameShape(QFrame::Box);
    rotationFrame->setLineWidth(1);
    rotationFrame->setLayout(rotationLayout);

    // компоновка слайдеров перемещения
    QLabel *moveLabel = new QLabel("Перемещение");

    QLabel *mxLabel = new QLabel("x:");
    QHBoxLayout *mXSliderLayout = new QHBoxLayout;
    mXSliderLayout->addWidget(mxLabel);
    mXSliderLayout->addWidget(moveXSlider);

    QLabel *myLabel = new QLabel("y:");
    QHBoxLayout *mYSliderLayout = new QHBoxLayout;
    mYSliderLayout->addWidget(myLabel);
    mYSliderLayout->addWidget(moveYSlider);

    QLabel *mzLabel = new QLabel("z:");
    QHBoxLayout *mZSliderLayout = new QHBoxLayout;
    mZSliderLayout->addWidget(mzLabel);
    mZSliderLayout->addWidget(moveZSlider);

    QVBoxLayout *moveLayout = new QVBoxLayout;
    moveLayout->addWidget(moveLabel);
    moveLayout->addLayout(mXSliderLayout);
    moveLayout->addLayout(mYSliderLayout);
    moveLayout->addLayout(mZSliderLayout);

    QFrame *moveFrame = new QFrame;
    moveFrame->setFrameShape(QFrame::Box);
    moveFrame->setLineWidth(1);
    moveFrame->setLayout(moveLayout);

    // Слайдер масштабирования
    QLabel *scaleLabel = new QLabel("Масштабирование");

    // Компоновка для правого столбца
    QVBoxLayout *rightColumnLayout = new QVBoxLayout;
    rightColumnLayout->addWidget(loadButton);
    rightColumnLayout->addWidget(rotationFrame);
    rightColumnLayout->addWidget(moveFrame);
    rightColumnLayout->addWidget(scaleLabel);
    rightColumnLayout->addWidget(scaleSlider);
    rightColumnLayout->addWidget(screenshotButton);

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    rightColumnLayout->addItem(spacer);

    // Добавляем правый столбец в компоновку
    mainLayout->addLayout(rightColumnLayout, 0, 1);

    // Устанавливаем вес столбцов
    mainLayout->setColumnStretch(0, 8);
    mainLayout->setColumnStretch(1, 2);
}
