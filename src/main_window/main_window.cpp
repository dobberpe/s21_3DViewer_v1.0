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

  screenshotButton = new QPushButton("Снимок экрана");
  connect(screenshotButton, &QPushButton::clicked, this,
          &main_window::on_screenshotButton_clicked);

  gifButton = new QPushButton("Запись экрана");
  connect(gifButton, &QPushButton::clicked, this,
          &main_window::on_gifButton_clicked);

  setupUI();

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &main_window::on_timer_timeout);
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
    fnameLabel->setText(QFileInfo(fileName).fileName());
    amountVnumberLabel->setText(QString::number(v->new_data->amount_vertex));
    amountEnumberLabel->setText(QString::number(v->new_data->amount_polygon_edges));
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
    // Создание QPixmap для захвата виджета viewer
    QPixmap pixmap(v->size());
    v->render(&pixmap);

    QStringList filters;
    filters << "JPEG Files (*.jpg)" << "BMP Files (*.bmp)";

    QFileDialog dialog(this);
    dialog.setNameFilters(filters);

    QString fileName;
    if (dialog.exec()) {
        fileName = dialog.selectedFiles().first();
        QString selectedFilter = dialog.selectedNameFilter();

        // Определяем формат в зависимости от выбранного фильтра
        QString format;
        if (selectedFilter.contains("*.jpg")) {
            format = "JPEG";
        } else if (selectedFilter.contains("*.bmp")) {
            format = "BMP";
        }

        // Сохранение файла
        if (!fileName.isEmpty()) {
            pixmap.save(fileName, format.toUtf8().constData());
        }
    }
}

void main_window::on_gifButton_clicked() {
    qDebug() << "entered";

    if (!timer->isActive()) {
        timer->start(100);
        qDebug() << "start";
    }
}

void main_window::on_timer_timeout() {
    if (currentFrame < totalFrames) {
        QPixmap pixmap(v->size());
        v->render(&pixmap);
        qDebug() << "render";
        QImage scaledImage = pixmap.scaled(width, height, Qt::KeepAspectRatio).toImage();
        qDebug() << "scaled";
        capturedFrames.append(scaledImage);
        qDebug() << "append";
        currentFrame++;
        qDebug() << currentFrame;
    } else {
        qDebug() << "total " << totalFrames;
        timer->stop();
        currentFrame = 0;
        qDebug() << "Captured all frames, now saving GIF";
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранение GIF", "", "GIF Files (*.gif)");
        if (!fileName.isEmpty()) {
            qDebug() << "fname";
            saveGif(fileName, 100); // Сохраняем GIF
            qDebug() << "saved";
        }
        capturedFrames.clear();
    }
}

void main_window::saveGif(const QString& fileName, const int delayMs) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << fileName;
        return;
    }

    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    // GIF Header
    out.writeRawData("GIF89a", 6); // Signature and version

    // Logical Screen Descriptor
    out << static_cast<quint16>(width); // Ширина
    out << static_cast<quint16>(height); // Высота
    out << static_cast<quint8>(0xF7); // Global Color Table Flag, Color Resolution, and Sort Flag
    out << static_cast<quint8>(0);    // Background Color Index
    out << static_cast<quint8>(0);    // Pixel Aspect Ratio

    // Global Color Table (черно-белая палитра для простоты)
    out << static_cast<quint8>(0x00); // Черный
    out << static_cast<quint8>(0x00); // Черный
    out << static_cast<quint8>(0x00); // Черный
    out << static_cast<quint8>(0xFF); // Белый
    out << static_cast<quint8>(0xFF); // Белый
    out << static_cast<quint8>(0xFF); // Белый

    for (const QImage &image : capturedFrames) {
        // Graphics Control Extension
        out.writeRawData("\x21\xF9\x04", 3); // Extension Introducer, Graphics Control Label
        out << static_cast<quint8>(0);    // No Transparency, Disposal Method 0
        out << static_cast<quint16>(delayMs / 10); // Delay Time (in hundredths of a second)
        out << static_cast<quint8>(0);    // Transparent Color Index (none)
        out.writeRawData("\x00", 1);      // Block Terminator

        // Image Descriptor
        out.writeRawData("\x2C", 1); // Image Separator
        out << static_cast<quint16>(0); // Image Left Position
        out << static_cast<quint16>(0); // Image Top Position
        out << static_cast<quint16>(width); // Image Width
        out << static_cast<quint16>(height); // Image Height
        out << static_cast<quint8>(0);    // Local Color Table Flag, Interlace Flag, Sort Flag

        // Image Data
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "BMP"); // Конвертируем кадр в BMP для простоты
        out.writeRawData(buffer.data().data(), buffer.size());
    }

    // GIF Trailer
    out.writeRawData("\x3B", 1); // GIF Trailer

    file.close();
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

  QSpacerItem *spacer =
      new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

  // Компоновка для правого столбца
  QVBoxLayout *rightColumnLayout = new QVBoxLayout;
  rightColumnLayout->addWidget(loadButton);
  setupSliderBox(rightColumnLayout, ROTATE);
  setupSliderBox(rightColumnLayout, MOVE);
  rightColumnLayout->addWidget(scaleLabel);
  rightColumnLayout->addLayout(scaleLayout);
  rightColumnLayout->addWidget(screenshotButton);
  rightColumnLayout->addWidget(gifButton);
  rightColumnLayout->addItem(spacer);
  setupFileInfo(rightColumnLayout);

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

void main_window::setupFileInfo(QVBoxLayout *rightColumnLayout) {
    QLabel *filenameLabel = new QLabel("Имя файла:");
    QSpacerItem *fnameSpacer =
        new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    fnameLabel = new QLabel(QString("3dviewer.obj"));

    QHBoxLayout *fnameLayout = new QHBoxLayout;
    fnameLayout->addWidget(filenameLabel);
    fnameLayout->addItem(fnameSpacer);
    fnameLayout->addWidget(fnameLabel);

    QLabel *amountVLabel = new QLabel("Вершин:");
    QSpacerItem *amountVSpacer =
        new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    amountVnumberLabel = new QLabel(QString::number(v->new_data->amount_vertex));

    QHBoxLayout *amountVLayout = new QHBoxLayout;
    amountVLayout->addWidget(amountVLabel);
    amountVLayout->addItem(amountVSpacer);
    amountVLayout->addWidget(amountVnumberLabel);

    QLabel *amountELabel = new QLabel("Ребер:");
    QSpacerItem *amountESpacer =
        new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    amountEnumberLabel = new QLabel(QString::number(v->new_data->amount_polygon_edges));

    QHBoxLayout *amountELayout = new QHBoxLayout;
    amountELayout->addWidget(amountELabel);
    amountELayout->addItem(amountESpacer);
    amountELayout->addWidget(amountEnumberLabel);

    QVBoxLayout *fileinfoLayout = new QVBoxLayout;
    fileinfoLayout->addLayout(fnameLayout);
    fileinfoLayout->addLayout(amountVLayout);
    fileinfoLayout->addLayout(amountELayout);

    QFrame *frame = new QFrame;
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(1);
    frame->setLayout(fileinfoLayout);

    rightColumnLayout->addWidget(frame);
}
