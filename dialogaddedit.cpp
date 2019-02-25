#include "dialogaddedit.h"
#include "ui_dialogaddedit.h"

DialogAddEdit::DialogAddEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEdit)
{
    ui->setupUi(this);
}

DialogAddEdit::~DialogAddEdit()
{
    delete ui;
}
