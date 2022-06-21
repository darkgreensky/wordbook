#ifndef WIDGETINFO_H
#define WIDGETINFO_H

#include "Dao.h"
#include "qrect.h"

class widgetInfo
{
public:
    Dao *a;
    QRect rc;
    QString word;
    widgetInfo(Dao *a, QRect rc, QString word)
    {
        this->a = a;
        this->rc = rc;
        this->word = word;
    }
};

#endif // WIDGETINFO_H
