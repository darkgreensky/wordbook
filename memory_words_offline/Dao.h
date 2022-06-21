#ifndef DAO_H
#define DAO_H

#include "wordInfo.h"
#include <string>
#include <iostream>
#include <vector>

#include <QtSql/QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

class Dao {
private:
     QSqlDatabase db;
public:
     Dao() {
         db=QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
         // qDebug() << QSqlDatabase::drivers();
         QString aFile = "./dbWord.db";
         db.setDatabaseName(aFile)
         if (!db.open()) {
             QMessageBox::critical(0, QObject::tr("无法打开数据库"),"无法创建数据库连接！ ", QMessageBox::Cancel);
         }
         else {
             // QMessageBox::critical(0, QObject::tr("数据库打开了"),"创建数据库连接成功！ ", QMessageBox::Cancel);
         }
     }

    void wordTimesAdd(QString w)
    {
        QSqlQuery query;
        QString sql = QString("UPDATE words SET time = time + 1 WHERE word = '%1'").arg(w);
        query.exec(sql);
        return;
    }

    void getWords(std::vector<wordInfo> &a) {
        QSqlQuery query;
        QString sql = QString("SELECT word,mean,time FROM words");
        // qDebug() << sql << '\n';
        query.exec(sql);

        // qDebug() << query.size() << '\n';
        wordInfo t;
        while(query.next())
        {
            // qDebug() << "word" << '\n';
            t.word = query.value(0).toString();
            t.mean = query.value(1).toString();
            t.times = query.value(2).toInt();
            t.rands = rand();
            a.push_back(t);
        }
        srand(time(0));
        sort(a.begin(), a.end(), [&](wordInfo a, wordInfo b){
            if (a.times == b.times) return a.rands < b.rands;
            return a.times < b.times;
        });
        return;
    }

    bool addWord(const wordInfo &a)
    {
        QSqlQuery query;
        QString findDataStr = QString("SELECT word FROM words WHERE word='%1'").arg(a.word);
        QString sql = QString("Insert into words values('%1','%2', 0)").arg(a.word).arg(a.mean);
        query.exec(findDataStr);
        query.next();
        if (query.value(0).toString() == a.word)
        {
            QMessageBox::critical(0,"提示","词库中已有这个单词");
            return false;
        }
        else
        {
            // QMessageBox::information(0, "提示","注册成功",QMessageBox::Ok);
            query.exec(sql);
            return true;
        }
    }

    bool findWord(wordInfo &a)
    {
        QSqlQuery query;
        QString findDataStr = QString("SELECT word, mean FROM words WHERE word='%1'").arg(a.word);
        query.exec(findDataStr);
        query.next();
        if (query.value(0).toString() == a.word)
        {
            a.mean = query.value(1).toString();
            return true;
        }
        else
        {
            return false;
        }
    }

    bool changeWord(const wordInfo &a)
    {
         QSqlQuery query;
         QString findDataStr = QString("SELECT word FROM words WHERE word = '%1'").arg(a.word);
         query.exec(findDataStr);
         query.next();
         if (query.value(0).toString() != a.word)
         {
             return false;
         }
         else
         {
             QString sql;
             if (a.mean == "")
                 sql = QString("DELETE FROM words WHERE word = '%1'").arg(a.word);
             else
                 sql = QString("UPDATE words SET mean = '%1' WHERE word = '%2'").arg(a.mean).arg(a.word);
             // qDebug() << sql << '\n';
             query.exec(sql);
             return true;
         }
    }

    bool refresh()
    {
        QSqlQuery query;
        QString findDataStr = QString("SELECT account FROM user");
        query.exec(findDataStr);
        if (!query.isActive()) {
            return true;
        }
        return false;
    }
};

#endif // DAO_H
