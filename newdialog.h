#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include "vect.h"
#include "contact.h"
#include "ui_newdialog.h"

namespace Ui {
class newDialog;
}

class newDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newDialog(QWidget *parent, Vect &DataB);
    ~newDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Vect &DataB;
    Ui::newDialog *ui;
};

#endif // NEWDIALOG_H
