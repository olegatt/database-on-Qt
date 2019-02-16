#include "newdialog.h"

newDialog::newDialog(QWidget *parent, Vect &DataB) : QDialog(parent),DataB(DataB), ui(new Ui::newDialog)
{
    ui->setupUi(this);
}

newDialog::~newDialog()
{
    delete ui;
}

void newDialog::on_okButton_clicked()
{
    Contact p(ui->numberLine->text(), ui->surnameLine->text(), ui->nameLine->text(), ui->dillerLine->text());
    DataB.pushback(p);
    close();
}

void newDialog::on_cancelButton_clicked()
{
    close();
}
