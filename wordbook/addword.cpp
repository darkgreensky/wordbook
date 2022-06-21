#include "addword.h"
#include "qevent.h"
#include "ui_addword.h"
#include "widget.h"
#include "widgetInfo.h"

addword::addword(widgetInfo t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addword),
    t(t)
{
    ui->setupUi(this);
    this->a = t.a;
    wordText = ui->wordText;
    meanText = ui->meanText;

    setGeometry(t.rc);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

addword::~addword()
{
    delete ui;
}

void addword::on_closeBtn_clicked()
{
    close();
    return;
}

//拖拽操作
void addword::mousePressEvent(QMouseEvent *event)
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

void addword::mouseMoveEvent(QMouseEvent *event)
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

void addword::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
    return;
}

void addword::on_backBtn_clicked()
{
    t = {a, {x(), y(), width(), height()}, t.word};
    widget *w = new widget(t);
    w->show();
    close();
    return;
}

void addword::on_addBtn_clicked()
{
    if (wordText->text().isEmpty())
    {
        QString dlgTitle="提示";
        QString strInfo="请输入单词";
        QMessageBox::information(this, dlgTitle, strInfo);
    }
    else if (meanText->text().isEmpty())
    {
        QString dlgTitle="提示";
        QString strInfo="请输入词义";
        QMessageBox::information(this, dlgTitle, strInfo);
    }
    else
    {
        QString word = wordText->text();
        QString mean = meanText->text();
        t.word = word;
        if (a->addWord({word, mean}))
        {
            ui->infoLabel->setText("添加成功");
        }
        else
        {

            ui->infoLabel->setText("添加失败");
        }
    }
}


void addword::on_minBtn_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

