#include "graphics.h"

Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("3dViewer");
  new_data = new Figure();
  loadModel(start_file);
}

void Viewer::loadModel(QString filename) {
  destroy_figure(new_data);
  parse_obj_file(filename.toUtf8().constData(), new_data);
  align_to_center(new_data);
  std::vector<double> values{new_data->x_min, new_data->y_min, new_data->z_min,
                             new_data->x_max, new_data->y_max, new_data->z_max};
  const auto [min, max] = std::minmax_element(begin(values), end(values));
  move_coef = (*max - *min) * 1.4;
  update();
}

Viewer::~Viewer() {
  destroy_figure(new_data);
  delete new_data;
}

void Viewer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Viewer::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
  if (event->buttons() & Qt::LeftButton) {
    new_data->trv.move_vector[crd::x] = new_pos.x() * 0.00001 * move_coef;
    new_data->trv.move_vector[crd::y] = -new_pos.y() * 0.00001 * move_coef;
    move_figure(new_data);
    update();
  } else if (event->buttons() & Qt::RightButton) {
    new_data->alpha_x = -new_pos.y() * 0.005;
    new_data->alpha_y = new_pos.x() * 0.005;
    rotate_figure(new_data);
    update();
  }
}

void Viewer::wheelEvent(QWheelEvent *event) {
  int num_degrees = event->angleDelta().y();
  curr_scale *= num_degrees < 0 ? 0.99 : 1.01;
  scale_figure(new_data, curr_scale);
  update();
}

void Viewer::mousePressEvent(QMouseEvent *event) {
  cur_pos = event->globalPosition().toPoint();
}

void Viewer::paintGL() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1, 1, -1, 1, 1, move_coef * 8);
  glTranslatef(0, 0, -move_coef / 2);
  glEnableClientState(GL_VERTEX_ARRAY);

  // рисуем точки
  glVertexPointer(3, GL_DOUBLE, 0, new_data->vertex);
  glPointSize(3);
  glColor3f(0, 0, 1);
  glDrawArrays(GL_POINTS, 0, new_data->amount_vertex);

  // рисуем линии
  glLineWidth(1);
  glColor3f(0, 1, 0);
  for (int i = 0; i < new_data->amount_polygon; i++)
    glDrawElements(GL_LINES, new_data->polygon[i].amount_p, GL_UNSIGNED_INT,
                   new_data->polygon[i].vertex_p);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Viewer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
