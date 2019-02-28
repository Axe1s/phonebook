#ifndef DIALOGADDEDIT_H
#define DIALOGADDEDIT_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include"database.h"

namespace Ui {
class DialogAddEdit;
}

class DialogAddEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddEdit(int row = -1, QWidget *parent = nullptr);
    ~DialogAddEdit();

signals:
    void signalReady();
private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::DialogAddEdit *ui;
    QSqlTableModel    *model;
    QDataWidgetMapper *mapper;

private:
    void setupModel();
//    void createUi();
//    void accept();
};

#endif // DIALOGADDEDIT_H
