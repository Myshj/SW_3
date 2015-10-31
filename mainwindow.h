#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dispatcher.h"

#include "request.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_nextTick_clicked();

    void on_startAutomatic_clicked();

    void on_printDispatcher_clicked();

    void on_reset_clicked();

private:

    /*Ця функція виконується на кожному такті.*/
    void OnTick();

    /*Генерує новий запит.*/
    Request GenerateRequest();



    Ui::MainWindow *ui;

    Dispatcher dispatcher;

    unsigned int currentTick;
};

#endif // MAINWINDOW_H
