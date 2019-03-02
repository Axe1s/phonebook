#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

#include <dialogaddedit.h>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAdd_clicked();
    void slotUpdateModel();
    void slotEditModel(QModelIndex index);

private:
    Ui::MainWindow  *ui;
    DataBase        *db;
    QSqlTableModel  *model;

    void createUI();
    void setupModel(const QString &tableName, const QStringList &headers);


};

#endif // MAINWINDOW_H
