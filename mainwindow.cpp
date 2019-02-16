#include "mainwindow.h"
#include "QFile"
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidget>
#include <QMessageBox>
#include <QCloseEvent>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->table->setRowCount(DataB.getLength());
    ui->table->setColumnCount(4);
    ui->table->setHorizontalHeaderLabels(QStringList() << "Телефон" << "Фамилия" << "Имя" << "Оператор");
    ui->table->setColumnHidden(4,true);
    ui->table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->table, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequest(QPoint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    ui->table->setRowCount(DataB.getLength());
    for(int i = 0; i < ui->table->rowCount(); i++)
        for (int j = 0; j<ui->table->columnCount();j++)
        {
            switch (j) {
                case(0):{
                    QTableWidgetItem *item = new QTableWidgetItem(DataB[i].getNumber());
                    ui->table->setItem(i,j,item);
                    ui->table->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    break;
                }
                case(1):{
                   QTableWidgetItem *item = new QTableWidgetItem(DataB[i].getSurname());
                    ui->table->setItem(i,j,item);
                    ui->table->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    break;
                }
                case(2):{
                    QTableWidgetItem *item = new QTableWidgetItem(DataB[i].getName());
                    ui->table->setItem(i,j,item);
                    ui->table->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    break;
                }
                case(3):{
                    QTableWidgetItem *item = new QTableWidgetItem(DataB[i].getDiller());
                    ui->table->setItem(i,j,item);
                    ui->table->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    break;
                }
                case(4):{
                    QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
                    ui->table->setItem(i,j,item);
                    ui->table->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    break;
                }
            }
        }
}

void MainWindow::on_action_open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Выберите файл", "", "*.txt");
    if(QFile::exists(filename)){
        QFile file(filename);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        int size=0;
        while(!file.atEnd()){
            file.readLine();
            size++;
        }
        file.close();
        if(size!=0){
            DataB.resize(size);
            DataB.readFromFile(filename);
            update();
            ui->mainToolBar->setEnabled(true);
            ui->menu->setEnabled(true);
            ui->searchLine->setEnabled(true);
            ui->checkNumber->setEnabled(true);
            ui->checkSurname->setEnabled(true);
            ui->checkName->setEnabled(true);
            ui->checkDiller->setEnabled(true);
            ui->searchStart->setEnabled(true);
        }
    }
}

void MainWindow::on_action_write_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Выберите файл", "", "*.txt");
    QFile file(filename);
    if(!filename.isEmpty()){
        file.open(QIODevice::WriteOnly| QIODevice::Text);
        if(file.isOpen()){
            if(unsaved == true){
                editRecord();
                unsaved = false;
            }
            QTextStream writeStream(&file);
            writeStream.setCodec("UTF-8");
            for(int i = 0; i<DataB.getLength(); i++){
                if(DataB[i].output().isEmpty()){
                    DataB.del(i+1);
                    i--;
                }
                else
                    writeStream << DataB[i].output() << endl;
            }
            file.close();
        }
        update();
    }
}

void MainWindow::on_action_add_triggered()
{
    newDialog window(nullptr, DataB);
    window.setModal(true);
    window.exec();
    update();
}

void MainWindow::on_action_concat_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Выберите файл", "", "*.txt");
    QFile file(filename);
    if(!filename.isEmpty()){
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        int size=0;
        if(file.isReadable()){
            while(!file.atEnd()){
                file.readLine();
                size++;
            }
            file.close();
            Vect DataB2(size);
            DataB2.readFromFile(filename);
            DataB.unite(DataB2);
            update();
        }
    }
}

void MainWindow::editRecord()
{
    if(DataB.getLength()>0){
        QTableWidgetItem *item = ui->table->currentItem();
        static QTableWidgetItem *lastItem;
        if(!unsaved){
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
            unsaved = true;
            lastItem = item;
        }
        else{
            switch(lastItem->column()){
                case(0):DataB[item->row()].setNumber(item->text()); break;
                case(1):DataB[item->row()].setSurname(item->text()); break;
                case(2):DataB[item->row()].setName(item->text()); break;
                case(3):DataB[item->row()].setDiller(item->text()); break;
                }
             unsaved = false;
             lastItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
             editRecord();
            }
    }
}

void MainWindow::deleteRecord()
{
    if(DataB.getLength()>0){
       QMessageBox::StandardButton confirmation = QMessageBox::question(this,"Удаление записи","Удалить запись?",QMessageBox::Ok|QMessageBox::Cancel);
       if(confirmation == QMessageBox::Ok){
           DataB.del(ui->table->item(ui->table->currentRow(),3)->text().toInt()+1);
           ui->table->removeRow(ui->table->currentRow());
       }
    }
}

void MainWindow::customMenuRequest(QPoint pos)
{
    QMenu * menu = new QMenu(this);

    QAction * editRecord = new QAction("Редактировать", this);
    QAction * deleteRecord = new QAction("Удалить", this);

    connect(editRecord, SIGNAL(triggered()), this, SLOT(editRecord()));
    connect(deleteRecord, SIGNAL(triggered()), this, SLOT(deleteRecord()));

    menu->addAction(editRecord);
    menu->addAction(deleteRecord);

    menu->popup(ui->table->viewport()->mapToGlobal(pos));
}

void MainWindow::on_action_create_triggered()
{
    on_action_add_triggered();
    ui->mainToolBar->setEnabled(true);
    DataB.setLength(DataB.getSize());
    ui->searchLine->setEnabled(true);
    ui->checkNumber->setEnabled(true);
    ui->checkSurname->setEnabled(true);
    ui->checkName->setEnabled(true);
    ui->checkDiller->setEnabled(true);
    ui->searchStart->setEnabled(true);
}

void MainWindow::on_searchStart_clicked()
{
    int row = 0;
    bool number = ui->checkNumber->checkState();
    bool surname = ui->checkSurname->checkState();
    bool name = ui->checkName->checkState();
    bool diller = ui->checkDiller->checkState();
    QString whatToSearch = ui->searchLine->text();
    QString wtsInt = whatToSearch;
    if(wtsInt.startsWith("0")){
        for(int i =0; i<wtsInt.length(); i++){
            if((i==wtsInt.length()-1)||(wtsInt[i]!="0")){
                wtsInt.remove(0,i);
                break;
            }
        }
    }
    if(!(wtsInt.toInt()|| wtsInt == "0")){
        number = false;
    }
    else
    {
        surname = false; name = false; diller = false;
    }

    ui->table->setRowCount(0);

    for(int i = 0; i<DataB.getLength(); i++){
        if((number && DataB[i].getNumber().startsWith(whatToSearch,Qt::CaseInsensitive))||
           (surname && DataB[i].getSurname().startsWith(whatToSearch,Qt::CaseInsensitive))||
           (name && DataB[i].getName().startsWith(whatToSearch,Qt::CaseInsensitive))||
           (diller && DataB[i].getDiller().startsWith(whatToSearch,Qt::CaseInsensitive)))
        {
            ui->table->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(DataB[i].getNumber());
            ui->table->setItem(row,0,item);
            ui->table->item(row,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            item = new QTableWidgetItem(DataB[i].getSurname());
            ui->table->setItem(row,1,item);
            ui->table->item(row,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            item = new QTableWidgetItem(DataB[i].getName());
            ui->table->setItem(row,2,item);
            ui->table->item(row,2)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            item = new QTableWidgetItem(DataB[i].getDiller());
            ui->table->setItem(row,3,item);
            ui->table->item(row,3)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            row++;
        }
    }
    ui->returnButton->setEnabled(true);
}

void MainWindow::on_returnButton_clicked()
{
    ui->searchLine->clear();
    ui->checkNumber->setCheckState(Qt::CheckState(false));
    ui->checkSurname->setCheckState(Qt::CheckState(false));
    ui->checkName->setCheckState(Qt::CheckState(false));
    ui->checkDiller->setCheckState(Qt::CheckState(false));
    update();
    ui->returnButton->setEnabled(false);
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this,"About"," Курсовая работа\n студента 2-го курса группы ИКПИ-74\n Степанца Олега \n по теме: 'Разработка приложения для управления\n базой данных'");
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(DataB.getLength()>0 && unsaved == true){
           QMessageBox::StandardButton confirmation = QMessageBox::question(this,"Сохранение","Сохранить изменения?",QMessageBox::Yes|QMessageBox::No);
           if(confirmation == QMessageBox::Yes){
               QString filename = QFileDialog::getSaveFileName(this,"Выберите файл", "", "*.txt");
               QFile file(filename);
               if(!filename.isEmpty()){
                   file.open(QIODevice::WriteOnly| QIODevice::Text);
                   if(file.isOpen()){
                       if(unsaved == true){
                           editRecord();
                           unsaved = false;
                       }
                       QTextStream writeStream(&file);
                       writeStream.setCodec("UTF-8");
                       for(int i = 0; i<DataB.getLength(); i++){
                           if(DataB[i].output().isEmpty()){
                               DataB.del(i+1);
                               i--;
                           }
                           else
                               writeStream << DataB[i].output() << endl;
                       }
                       file.close();
                   }
                   update();
               }
           }
        }

}
