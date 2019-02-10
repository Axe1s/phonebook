#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Выделяем память под базу и соединяемся
    db = new DataBase();
    db->connectToDataBase();

    //Инициализируем и передаём имена колонок
    this->setupModel(TABLE, QStringList()    << trUtf8("id")
                                             << trUtf8("Имя")
                                             << trUtf8("Фамилия")
                                             << trUtf8("Дата")
                                             << trUtf8("Телефон")
                                             << trUtf8("Адрес")
                   );

    this->createUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    //Инициализируем модель и выбираем нужную таблицу для нашей модели
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
            model->setHeaderData(i,Qt::Horizontal,headers[j]);
        }
}

void MainWindow::createUI()
{
    ui->setupUi(this);
    this->setWindowTitle("Телефонный справочник");
    //Выводим таблицу на виджет
    ui->tableView->setModel(model);

    //Настраиваем вид таблицы, передрал с сайта

    // Скрываем колонку с id записей (сработало когда ui->tableView->setModel(model) поставил выше этой записи )
    ui->tableView->setColumnHidden(0, true);
    //Выделение строки
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //Выделение лишь одной строки
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //Размер таблицы по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

}
