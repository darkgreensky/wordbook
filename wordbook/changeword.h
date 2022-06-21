#ifndef CHANGEWORD_H
#define CHANGEWORD_H

#include "Dao.h"
#include "qlineedit.h"
#include "widgetInfo.h"
#include <QWidget>

namespace Ui {
class changeword;
}

class changeword : public QWidget
{
    Q_OBJECT

public:
    explicit changeword(widgetInfo t, QWidget *parent = nullptr);
    ~changeword();

protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_closeBtn_clicked();

    void on_backBtn_clicked();

    void on_findBtn_clicked();

    void on_changeBtn_clicked();

    void on_minBtn_clicked();

private:
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;

    QLineEdit *wordText;
    QLineEdit *meanText;
    widgetInfo t;
    Dao *a;
    Ui::changeword *ui;
};

#endif // CHANGEWORD_H
