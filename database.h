//Передрал с сайта evilneg

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>


//Директивы имён базы, таблицы и её полей

#define DATABASE_HOSTMANE "ExempleHostName" //В нашем случае этот параметр не обязательный достаточно имени, так как база на SQLight
#define DATABASE_NAME "base.db"

#define TABLE "book"
#define TABLE_ID "id"
#define TABLE_FIRSTNAME "fname"
#define TABLE_LASTSNAME "lname"
#define TABLE_DATA "data"
#define TABLE_PHONE "phone"
#define TABLE_ADRESS "adress"

class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();

    //Подключение к базе и добавление записей (добавление не обязательно, но разберусь позже, на всякий добавлю)
    void connectToDataBase();

private:
    QSqlDatabase db; //Объект базы данных

private:
    //Функции для основной работы с базой
    void closeDataBase();


};

#endif // DATABASE_H
