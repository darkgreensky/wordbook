#ifndef MEMORY_H
#define MEMORY_H

#include "Dao.h"
#include "widgetInfo.h"
#include <QWidget>

#include <vector>
#include <unordered_map>

namespace Ui {
class memory;
}

class memory : public QWidget
{
    Q_OBJECT

public:
    explicit memory(widgetInfo t, QWidget *parent = nullptr);
    ~memory();

protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private slots:
    void on_closeBtn_clicked();

    void on_notBtn_clicked();

    void on_okBtn_clicked();

    void on_nextBtn_clicked();

    void on_backBtn_clicked();

    void on_pushButton_clicked();

private:
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
    widgetInfo t;
    Dao *a;
    std::vector<wordInfo> words;
    int idx;
    Ui::memory *ui;
};

#endif // MEMORY_H
