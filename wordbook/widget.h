#ifndef WIDGET_H
#define WIDGET_H

#include "Dao.h"
#include "widgetInfo.h"
#include <QMainWindow>

namespace Ui {
class widget;
}

class widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit widget(widgetInfo t, QWidget *parent = nullptr);
    ~widget();

protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_closeBtn_clicked();

    void on_memBtn_clicked();

    void on_addBtn_clicked();

    void on_changeBtn_clicked();

    void on_pushButton_clicked();

    void on_refreshBtn_clicked();

private:
    bool        m_bDrag;
    Dao *a;
    QString id;
    QString word;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
    Ui::widget *ui;
};

#endif // WIDGET_H
