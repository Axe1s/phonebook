#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Выделяем память под базу и соединяемся
    db = new DataBase();
    db->connectToDataBase();

    //Выделяем память и выбираем нужную таблицу для нашей модели
    model = new QSqlTableModel(this);
    model->setTable(TABLE);
    model->select();

    ui->setupUi(this);
    this->setWindowTitle("Телефонный справочник");
    //Настраиваем вид таблицы, передрал с сайта
    //Выделение строки
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //Выделение лишь одной строки
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //Размер таблицы по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    //Выводим таблицу на виджет
    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}
