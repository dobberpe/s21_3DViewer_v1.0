#include "graphics.h"

Viewer::Viewer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("3dViewer");
    new_data = new Figure();

    parse_obj_file("test.obj", new_data);
    align_to_center(new_data);


    qDebug() << new_data->x_max << new_data->y_min;

    // KOCTblJIb = ((int)m_max(new_data->x_max, new_data->y_max, new_data->z_max, 1) - (int)m_max(new_data->x_min, new_data->y_min, new_data->z_min, -1)) / 22;
    KOCTblJIb = 1;
    qDebug() << KOCTblJIb;


}

Viewer::~Viewer()
{
    destroy_figure(new_data);
    delete new_data;
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
        new_data->trv.move_vector[crd::x] = new_pos.x() * 0.00001 * KOCTblJIb;
        new_data->trv.move_vector[crd::y] = -new_pos.y() * 0.00001 * KOCTblJIb;
        move_figure(new_data);
        update();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        new_data->alpha_x = -new_pos.y() * 0.005;
        new_data->alpha_y = new_pos.x() * 0.005;
        rotate_figure(new_data);
        update();
    }
}

void Viewer::wheelEvent(QWheelEvent *event)
{
    // QPoint numDegrees = event->angleDelta() / 120;
    // double step = 20;
    // double scale_tmp = scale_val;
    // if ((int)(scale_val + numDegrees.y() * step) > 0)
    // {
    //     scale_val += numDegrees.y() * KOCTblJIb / 10;
    //     scale_figure(new_data, numDegrees.y() * 1);
    //     update();
    // }


    QPoint numDegrees = event->angleDelta();
    double step = 10;
    double scale_tmp = scale_val;
    if ((int)(scale_val + numDegrees.y() * step) > 0) {
        scale_val += numDegrees.y() * step;
        scale_figure(new_data, scale_val / scale_tmp);
        update();
    }
}

double Viewer::m_max(double a, double b, double c, int fact)
{
    a *= fact;
    b *= fact;
    c *= fact;
    double m = a > b ? a : b;
    return (m > c ? m : c) * fact;
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
    glDrawArrays(GL_POINTS, 0, new_data->amount_vertex);

    // рисуем линии
    glLineWidth(1);
    glColor3f(0, 1, 0);
    for (int i = 0; i < new_data->amount_polygon; i++)
        glDrawElements(GL_LINES, new_data->polygon[i].amount_p, GL_UNSIGNED_INT,
                       new_data->polygon[i].vertex_p);

    glDisableClientState(GL_VERTEX_ARRAY);
}


void Viewer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
