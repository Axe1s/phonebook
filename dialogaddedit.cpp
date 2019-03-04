#include "dialogaddedit.h"
#include "ui_dialogaddedit.h"

DialogAddEdit::DialogAddEdit(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEdit)
{
    ui->setupUi(this);

    //Инициализация модели из которой будут браться данные
    setupModel();

        /* Если строка не задана, то есть равна -1,
         * тогда диалог работает по принципу создания новой записи.
         * А именно, в модель вставляется новая строка и работа ведётся с ней.
         * */
        if(row == -1){
            model->insertRow(model->rowCount(QModelIndex()));
            mapper->toLast();
                      }
        //Иначе работаем с выбранной записью
        else {
            mapper->setCurrentModelIndex(model->index(row,0));
        }
}

DialogAddEdit::~DialogAddEdit()
{
    delete ui;
}

void DialogAddEdit::setupModel()
{
    //Инициализация модели для диалога
    model = new QSqlTableModel(this);
    model->setTable(TABLE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    //Инициализация маппера для модели

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->lineEditFname, 1);
    mapper->addMapping(ui->lineEditLName, 2);
    mapper->addMapping(ui->dateEdit, 3);
    mapper->addMapping(ui->lineEditPhone, 4);
    mapper->addMapping(ui->lineEditAdress,5);

    //Передираю, чужой код. Нужно разобрать как это работает.
    //Написано: ручное подтверждение изменения данных в мапере
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);


}

void DialogAddEdit::on_pushButtonOk_clicked()
{
    mapper->submit();
    model->submitAll();
    emit signalReady();
    this->close();
}
