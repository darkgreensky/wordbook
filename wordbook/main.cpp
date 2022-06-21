#include <QMainWindow>
#include <QApplication>
#include "Dao.h"
#include <QtSql/QSqlDatabase>
#include "widget.h"

#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dao *dao = new Dao();
    widgetInfo t({dao, {GetSystemMetrics(SM_CXSCREEN) / 2 - 310,GetSystemMetrics(SM_CYSCREEN) / 2 - 220, 310, 400}, ""});
    widget *login = new widget(t);
    login->show();
    return a.exec();
}
