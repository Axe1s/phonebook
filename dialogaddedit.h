#ifndef DIALOGADDEDIT_H
#define DIALOGADDEDIT_H

#include <QDialog>

namespace Ui {
class DialogAddEdit;
}

class DialogAddEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddEdit(QWidget *parent = nullptr);
    ~DialogAddEdit();

signals:
    void signalReady();
private:
    Ui::DialogAddEdit *ui;
};

#endif // DIALOGADDEDIT_H
