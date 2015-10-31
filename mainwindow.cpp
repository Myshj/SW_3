#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentTick = 0;

    dispatcher = Dispatcher(3, 32);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*Ця функція виконується на кожному такті.*/
void MainWindow::OnTick()
{
    currentTick++;

    int r = rand()%101;

    if(r <= ui->possibilityOfRequestIncoming->value()){
        Request newRequest = GenerateRequest();
        dispatcher.AcceptRequest(newRequest, currentTick);

    }

    dispatcher.MainCycle();

    /*string s = "Поточний такт: ";
    s.append(to_string(currentTick));
    s.append("\n");
    s.append(dispatcher.ToString());
    ui->dispatcherState->setText(QString::fromStdString(s));*/
}

/*Генерує новий запит. OK*/
Request MainWindow::GenerateRequest()
{
    unsigned int priority = rand()%(ui->minPriority->value() + 1) + ui->maxPriority->value();

    unsigned int complexity = rand()%ui->maxTaskComplexity->value() + ui->minTaskComplexity->value();

    return Request(priority, complexity);
}

void MainWindow::on_nextTick_clicked()
{
    OnTick();

    on_printDispatcher_clicked();
}

void MainWindow::on_startAutomatic_clicked()
{
    unsigned int currentPossibility = ui->possibilityOfRequestIncoming->value();
    ui->startAutomatic->setEnabled(false);

    for(unsigned int i = 0; i < ui->countOfTicksToGenerateTasks->value(); i++){
        OnTick();
    }
    ui->possibilityOfRequestIncoming->setValue(0);
    while(false == dispatcher.IsEmpty()){
        OnTick();
    }

    ui->possibilityOfRequestIncoming->setValue(currentPossibility);

    ui->startAutomatic->setEnabled(true);

    on_printDispatcher_clicked();

    ui->report->setText(QString::fromStdString(dispatcher.GetReport()));
}

void MainWindow::on_printDispatcher_clicked()
{
    string s = "Поточний такт: ";
    s.append(to_string(currentTick));
    s.append("\n");
    s.append(dispatcher.ToString());
    ui->dispatcherState->setText(QString::fromStdString(s));
}

void MainWindow::on_reset_clicked()
{
    currentTick = 0;

    dispatcher = Dispatcher(3, 32);

    ui->dispatcherState->setText("");
    ui->report->setText("");
}
