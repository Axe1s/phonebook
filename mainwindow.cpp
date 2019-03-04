#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Телефонный справочник");

    //Выделяем память под базу и соединяемся
    db = new DataBase();
    db->connectToDataBase();

    //Инициализируем модель и передаём имена колонок
    this->setupModel(TABLE, QStringList()    << ("id")
                                             << ("Имя")
                                             << ("Фамилия")
                                             << ("Дата")
                                             << ("Телефон")
                                             << ("Адрес")
                   );
    //Выводим таблицу
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

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditModel(QModelIndex)));
    connect(ui->pushButtonEdit, SIGNAL(clicked()), this, SLOT(slotEditModel(QModelIndex)));

}

//При нажатии кнопки, вызываем окно добавления
void MainWindow::on_pushButtonAdd_clicked()
{
    DialogAddEdit *addDialogAddEdit = new DialogAddEdit();
    connect(addDialogAddEdit, SIGNAL(signalReady()), this, SLOT(slotUpdateModel()));

    //Вызов диалогового окна
    addDialogAddEdit->setWindowTitle(("Новая запись"));
    addDialogAddEdit->exec();

}

//Обновление модели
void MainWindow::slotUpdateModel()
{
    model->select();
}

//Активация диалогового окна при передаче индекса выдранной строки
void MainWindow::slotEditModel(QModelIndex index)
{
    DialogAddEdit *addDialogAddEdit = new DialogAddEdit(index.row());
    connect(addDialogAddEdit,SIGNAL(signalReady()),this, SLOT(slotUpdateModel()));

    //Вызов диалогового окна
    addDialogAddEdit->setWindowTitle(("Редактирование записи"));
    addDialogAddEdit->exec();
}

//void MainWindow::on_pushButtonEdit_clicked(QModelIndex index)
//{
//     DialogAddEdit *addDialogAddEdit = new DialogAddEdit(index.row());
//    connect(addDialogAddEdit, SIGNAL(signalReady()), this, SLOT(slotUpdateModel()));

//    //Вызов диалогового окна
//    addDialogAddEdit->setWindowTitle(("Редактирование записи"));
//    addDialogAddEdit->exec();
//}

//Удаление записей в таблице
void MainWindow::on_pushButtonRemove_clicked()
{
    //Создаём запрос на удаление
    QMessageBox::StandardButtons stButton;
    // Присвоение значений для выбора пользователя: "Yes" или "No"
    stButton = QMessageBox::question(this, "Подтверждение удаления", "Вы точно хотите удалить запись?", QMessageBox::Yes | QMessageBox::No );

    //Проверяем подтверждение
    if (stButton == QMessageBox::Yes)
    {
        model->removeRow(ui->tableView->currentIndex().row());
        slotUpdateModel();
    }

}

void MainWindow::on_quit_triggered()
{
    this->close();
}

void MainWindow::on_version_triggered()
{
    QMessageBox stMessege;
    stMessege.setText("Опрограмме");
    stMessege.setInformativeText("Самая первая версия программы для обучения");
    stMessege.setStandardButtons((QMessageBox::Ok));
}
