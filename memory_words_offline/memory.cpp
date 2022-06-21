#include "memory.h"
#include "qevent.h"
#include "ui_memory.h"
#include "widget.h"
#include <QMouseEvent>

memory::memory(widgetInfo t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::memory),
    t(t)
{
    ui->setupUi(this);
    ui->nextBtn->setVisible(0);
    ui->meanLabel->setVisible(0);
    setGeometry(t.rc);
    this->a = t.a;
    a->getWords(words);
    idx = 0;
    if (words.size() == 0)
    {
        ui->wordLabel->setText("No Words");
        ui->meanLabel->setText("词库没有单词");
    }
    else
    {
        ui->wordLabel->setText(words[idx].word);
        ui->meanLabel->setText(words[idx++].mean);
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
}

memory::~memory()
{
    delete ui;
}

void memory::on_closeBtn_clicked()
{
    close();
    return;
}


void memory::on_notBtn_clicked()
{
    ui->notBtn->setVisible(0);
    ui->okBtn->setVisible(0);
    ui->nextBtn->setVisible(1);
    ui->meanLabel->setVisible(1);
}


void memory::on_okBtn_clicked()
{
    ui->notBtn->setVisible(0);
    ui->okBtn->setVisible(0);
    ui->nextBtn->setVisible(1);
    ui->meanLabel->setVisible(1);
    if (idx != 0) a->wordTimesAdd(words[idx - 1].word);
}

void memory::on_nextBtn_clicked()
{
    ui->notBtn->setVisible(1);
    ui->okBtn->setVisible(1);
    ui->nextBtn->setVisible(0);
    ui->meanLabel->setVisible(0);
    if (words.size() == 0)
    {
        ui->wordLabel->setText("No Words");
        ui->meanLabel->setText("词库没有单词");
    }
    else
    {
        if (idx == words.size())
        {
            idx = 0;
            a->getWords(words);
        }
        ui->wordLabel->setText(words[idx].word);
        ui->meanLabel->setText(words[idx++].mean);
    }
}

//拖拽操作
void memory::mousePressEvent(QMouseEvent *event)
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

void memory::mouseMoveEvent(QMouseEvent *event)
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

void memory::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
    return;
}

void memory::on_backBtn_clicked()
{
    if (idx != 0) t = {a, {x(), y(), width(), height()}, words[idx - 1].word};
    else t = {a, {x(), y(), width(), height()}, ""};
    widget *w = new widget(t);
    w->show();
    close();
    return;
}


void memory::on_pushButton_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

