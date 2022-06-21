#include "changeword.h"
#include "qevent.h"
#include "ui_changeword.h"
#include "widget.h"

changeword::changeword(widgetInfo t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeword),
    t(t)
{
    ui->setupUi(this);

    wordText = ui->wordText;
    meanText = ui->meanText;
    this->a = t.a;
    ui->wordText->setText(t.word);
    setGeometry(t.rc);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

changeword::~changeword()
{
    delete ui;
}

void changeword::on_closeBtn_clicked()
{
    close();
    return;
}

//拖拽操作
void changeword::mousePressEvent(QMouseEvent *event)
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

void changeword::mouseMoveEvent(QMouseEvent *event)
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

void changeword::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
    return;
}

void changeword::on_backBtn_clicked()
{
    t = {a, {x(), y(), width(), height()}, t.word};
    widget *w = new widget(t);
    // qDebug() << t.rc << '\n';
    w->show();
    close();
    return;
}


void changeword::on_findBtn_clicked()
{
    if (wordText->text().isEmpty())
    {
        QString dlgTitle="提示";
        QString strInfo="请输入单词";
        QMessageBox::information(this, dlgTitle, strInfo);
    }
    else
    {
        QString word = wordText->text();
        QString mean = meanText->text();
        t.word = word;
        wordInfo temp = {word, mean};
        if (a->findWord(temp))
        {
            ui->infoLabel->setText("查找成功");
            ui->meanText->setText(temp.mean);
        }
        else
        {
            ui->infoLabel->setText("并没有找到这个单词哦");
        }
    }
}


void changeword::on_changeBtn_clicked()
{
    if (wordText->text().isEmpty())
    {
        QString dlgTitle="提示";
        QString strInfo="请输入单词";
        QMessageBox::information(this, dlgTitle, strInfo);
    }
    else
    {
        QString word = wordText->text();
        QString mean = meanText->text();
        t.word = word;
        if (a->changeWord({word, mean}))
        {
            if (mean == "") ui->infoLabel->setText("删除成功");
            else ui->infoLabel->setText("修改成功");
            ui->wordText->setText("");
        }
        else
        {
            ui->infoLabel->setText("请确认单词是否存在");
        }
    }
}


void changeword::on_minBtn_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

