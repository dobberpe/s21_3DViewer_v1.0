#include "main_window.h"

main_window::main_window(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("3dViewer");
  setMinimumSize(800, 600);

  v = new Viewer;

  loadButton = new QPushButton("Выбор файла");
  connect(loadButton, &QPushButton::clicked, this,
          &main_window::on_loadButton_clicked);

  rotationXSlider = new QSlider(Qt::Horizontal);
  rotationXSlider->setRange(-180, 180);
  connect(rotationXSlider, &QSlider::valueChanged, this,
          &main_window::on_rotationXSlider_valueChanged);

  rotationYSlider = new QSlider(Qt::Horizontal);
  rotationYSlider->setRange(-180, 180);
  connect(rotationYSlider, &QSlider::valueChanged, this,
          &main_window::on_rotationYSlider_valueChanged);

  rotationZSlider = new QSlider(Qt::Horizontal);
  rotationZSlider->setRange(-180, 180);
  connect(rotationZSlider, &QSlider::valueChanged, this,
          &main_window::on_rotationZSlider_valueChanged);

  moveXSlider = new QSlider(Qt::Horizontal);
  moveXSlider->setRange(-180, 180);
  connect(moveXSlider, &QSlider::valueChanged, this,
          &main_window::on_moveXSlider_valueChanged);

  moveYSlider = new QSlider(Qt::Horizontal);
  moveYSlider->setRange(-180, 180);
  connect(moveYSlider, &QSlider::valueChanged, this,
          &main_window::on_moveYSlider_valueChanged);

  moveZSlider = new QSlider(Qt::Horizontal);
  moveZSlider->setRange(-180, 180);
  connect(moveZSlider, &QSlider::valueChanged, this,
          &main_window::on_moveZSlider_valueChanged);

  scaleSlider = new QSlider(Qt::Horizontal);
  scaleSlider->setRange(-180, 180);
  connect(scaleSlider, &QSlider::valueChanged, this,
          &main_window::on_scaleSlider_valueChanged);

  increaseScaleButton = new QPushButton("+");
  increaseScaleButton->setFixedSize(QSize(20, 20));
  connect(increaseScaleButton, &QPushButton::clicked, this,
          &main_window::on_increaseScaleButton_clicked);

  decreaseScaleButton = new QPushButton("-");
  decreaseScaleButton->setFixedSize(QSize(20, 20));
  connect(decreaseScaleButton, &QPushButton::clicked, this,
          &main_window::on_decreaseScaleButton_clicked);

  screenshotButton = new QPushButton("Сделать снимок");
  connect(screenshotButton, &QPushButton::clicked, this,
          &main_window::on_screenshotButton_clicked);

  setupUI();
}

void main_window::on_loadButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open Model File", "",
                                                  "OBJ Files (*.obj)");
  if (!fileName.isEmpty()) {
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
    v->loadModel(fileName);
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

void main_window::on_increaseScaleButton_clicked() {
  scaleSlider->setValue(scaleSlider->value() + 1);
}

void main_window::on_decreaseScaleButton_clicked() {
  scaleSlider->setValue(scaleSlider->value() - 1);
}

void main_window::on_screenshotButton_clicked() {
  // Создание QPixmap для захвата виджета
  QPixmap pixmap(v->size());
  v->render(&pixmap);

  // Открытие диалогового окна для сохранения файла
  QString fileName = QFileDialog::getSaveFileName(
      this, "Сохранение изображения", "", "PNG Files (*.png)");
  if (!fileName.isEmpty()) {
    pixmap.save(fileName, "PNG");
  }
}

void main_window::rotate_slider(double rotate_X, double rotate_Y,
                                double rotate_Z) {
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
  mainLayout->addWidget(v, 0, 0, 1, 1);  // Занимает весь левый столбец

  QLabel *scaleLabel = new QLabel("Масштабирование");
  QHBoxLayout *scaleLayout = new QHBoxLayout;
  scaleLayout->addWidget(decreaseScaleButton);
  scaleLayout->addWidget(scaleSlider);
  scaleLayout->addWidget(increaseScaleButton);

  // Компоновка для правого столбца
  QVBoxLayout *rightColumnLayout = new QVBoxLayout;
  rightColumnLayout->addWidget(loadButton);
  setupSliderBox(rightColumnLayout, ROTATE);
  setupSliderBox(rightColumnLayout, MOVE);
  rightColumnLayout->addWidget(scaleLabel);
  rightColumnLayout->addLayout(scaleLayout);
  rightColumnLayout->addWidget(screenshotButton);

  QSpacerItem *spacer =
      new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  rightColumnLayout->addItem(spacer);

  // Добавляем правый столбец в компоновку
  mainLayout->addLayout(rightColumnLayout, 0, 1);

  // Устанавливаем вес столбцов
  mainLayout->setColumnStretch(0, 8);
  mainLayout->setColumnStretch(1, 2);
}

void main_window::setupSliderBox(QVBoxLayout *rightColumnLayout, bool rotate) {
  QLabel *label = new QLabel(rotate ? "Поворот" : "Перемещение");

  QLabel *xLabel = new QLabel("x:");
  QHBoxLayout *xSliderLayout = new QHBoxLayout;
  xSliderLayout->addWidget(xLabel);
  xSliderLayout->addWidget(rotate ? rotationXSlider : moveXSlider);

  QLabel *yLabel = new QLabel("y:");
  QHBoxLayout *ySliderLayout = new QHBoxLayout;
  ySliderLayout->addWidget(yLabel);
  ySliderLayout->addWidget(rotate ? rotationYSlider : moveYSlider);

  QLabel *zLabel = new QLabel("z:");
  QHBoxLayout *zSliderLayout = new QHBoxLayout;
  zSliderLayout->addWidget(zLabel);
  zSliderLayout->addWidget(rotate ? rotationZSlider : moveZSlider);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  layout->addLayout(xSliderLayout);
  layout->addLayout(ySliderLayout);
  layout->addLayout(zSliderLayout);

  QFrame *frame = new QFrame;
  frame->setFrameShape(QFrame::Box);
  frame->setLineWidth(1);
  frame->setLayout(layout);

  rightColumnLayout->addWidget(frame);
}
