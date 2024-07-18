#include "graphics.h"

Viewer::Viewer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("3dViewer");
    parse_obj();


    new_data = new Figure();
    new_data->amount_polygon = 1;
    new_data->amount_vertex = data.vertices_count;
    new_data->vertex = data.vertices_arr;
    new_data->polygon = new Polygon();
    new_data->polygon[0].vertex_p= data.vertex_indices_arr;
    new_data->polygon[0].amount_p = data.vertex_indices_count * 2;

}

Viewer::~Viewer()
{
}

void Viewer::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void Viewer::mouseMoveEvent(QMouseEvent *event)
{
    new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
    if (event->buttons() & Qt::LeftButton)
    {
        move_X(&this->data, new_pos.x() * 0.00001 * KOCTblJIb);
        move_Y(&this->data, -new_pos.y() * 0.00001 * KOCTblJIb);
        update();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        rotate_X(&this->data, -new_pos.y() * 0.005);
        rotate_Y(&this->data, new_pos.x() * 0.005);
        update();
    }
}

void Viewer::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 120;
    double step = 20;
    double scale_tmp = scale_val;
    if ((int)(scale_val + numDegrees.y() * step) > 0)
    {
        scale_val += numDegrees.y() * KOCTblJIb / 10;
        scale(&this->data, scale_val / scale_tmp);
        update();
    }

}

void Viewer::mousePressEvent(QMouseEvent *event)
{
    cur_pos = event->globalPosition().toPoint();
}

void Viewer::paintGL()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, KOCTblJIb);
    glTranslatef(0, 0, -KOCTblJIb / 3);
    glEnableClientState(GL_VERTEX_ARRAY);

    // рисуем точки
    glVertexPointer(3, GL_DOUBLE, 0, new_data->vertex);
    glPointSize(3);
    glColor3f(0, 0, 1);
    glDrawArrays(GL_POINTS, 0, data.vertices_count);

    // рисуем линии
    glLineWidth(1);
    glColor3f(0, 1, 0);
    for (int i = 0; i < new_data->amount_polygon; i++)
        glDrawElements(GL_LINES, new_data->polygon[i].amount_p, GL_UNSIGNED_INT,
                       new_data->polygon[i].vertex_p);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void Viewer::parse_obj()
{
    data = {0, NULL, 0, NULL};
    parse_obj_file("test.obj", &this->data);
    update();
}

void Viewer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
