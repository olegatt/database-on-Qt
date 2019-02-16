#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vect.h"
#include "contact.h"
#include "newdialog.h"
#include "ui_mainwindow.h"

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
    void on_action_open_triggered();

    void on_action_write_triggered();

    void on_action_add_triggered();

    void on_action_concat_triggered();

    void customMenuRequest(QPoint pos);

    void update();

    void editRecord();

    void deleteRecord();

    void on_action_create_triggered();

    void on_searchStart_clicked();

    void on_returnButton_clicked();

    void on_action_about_triggered();

    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    bool unsaved = false;
    Vect DataB;
};

#endif // MAINWINDOW_H
