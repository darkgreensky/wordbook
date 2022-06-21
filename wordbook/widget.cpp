#include "widget.h"
#include "addword.h"
#include "changeword.h"
#include "ui_widget.h"
#include <QMouseEvent>

#include "memory.h"
#include "widgetInfo.h"

widget::widget(widgetInfo t, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    this->a = t.a;
    this->word = t.word;
    setGeometry(t.rc);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

widget::~widget()
{
    delete ui;
}

//拖拽操作
void widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && ui->titleWidget->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        m_bDrag = true;
        //获得鼠标的初始位置
        mouseStartPoint = event->globalPosition().toPoint();
        //mouseStartPoint = event->pos();
        //获得窗口的初始位置
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
    return;
}

void widget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        //获得鼠标移动的距离
        QPoint distance = event->globalPosition().toPoint() - mouseStartPoint;
        //QPoint distance = event->pos() - mouseStartPoint;
        //改变窗口的位置
        this->move(windowTopLeftPoint + distance);
    }
    return;
}

void widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
    return;
}

void widget::on_closeBtn_clicked()
{
    close();
    return;
}
// ui->test2->setVisible(0);

void widget::on_memBtn_clicked()
{
    widgetInfo t = {a, {x(), y(), width(), height()}, word};
    memory *w = new memory(t);
    w->show();
    close();
}


void widget::on_addBtn_clicked()
{
    addword *w = new addword({a, {x(), y(), width(), height()}, word});
    w->show();
    close();
}


void widget::on_changeBtn_clicked()
{
    changeword *w = new changeword({a, {x(), y(), width(), height()}, word});
    w->show();
    close();
}

void widget::on_pushButton_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}


void widget::on_refreshBtn_clicked()
{
    if (a->refresh())
    {
        delete a;
        a = new Dao();
        // qDebug() <<"ok" << '\n';
    }
}

