#ifndef ADDWORD_H
#define ADDWORD_H

#include "Dao.h"
#include "qlineedit.h"
#include "widgetInfo.h"
#include <QWidget>

namespace Ui {
class addword;
}

class addword : public QWidget
{
    Q_OBJECT

public:
    explicit addword(widgetInfo t, QWidget *parent = nullptr);
    ~addword();

protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_closeBtn_clicked();

    void on_backBtn_clicked();

    void on_addBtn_clicked();

    void on_minBtn_clicked();

private:
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
    QLineEdit *wordText;
    QLineEdit *meanText;
    widgetInfo t;
    Dao *a;
    Ui::addword *ui;
};

#endif // ADDWORD_H
