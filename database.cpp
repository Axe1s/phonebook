#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

//Функции подключения к базе
void DataBase::connectToDataBase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //Создание подключения базы данных
    db.setDatabaseName ("Data/" DATABASE_NAME); //Путь к базе данных


    if (!db.open())  //Проверка соединения с базой данных
    {
        qDebug() << "No connect";
    }
    else
    {
        qDebug() << "Connected";
    }
}

//Пока нафиг не нужно но пока оставлю
void DataBase::closeDataBase()
{
    db.close();
}
