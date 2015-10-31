#include "queuerecord.h"

/*Конструктор за замовченням*/
QueueRecord::QueueRecord()
{
    priority = 0;
    tickEntered = 0;
    ticksRequired = 0;
    ticksRemaining = ticksRequired;
    ticksWaited = 0;
    tickEnded = 0;
}

/*Конструктор з параметрами.*/
QueueRecord::QueueRecord(unsigned int newPriority, unsigned int newTickEntered, unsigned int newTicksRequired)
{
    priority = newPriority;
    tickEntered = newTickEntered;
    ticksRequired = newTicksRequired;
    ticksRemaining = ticksRequired;
    ticksWaited = 0;
    tickEnded = 0;
}

/*QueueRecord::QueueRecord(QueueRecord& other)
{
    priority = other.priority;
    tickEnded = other.tickEnded;
    tickEntered = other.tickEntered;
    ticksRemaining = other.ticksRemaining;
    ticksRequired = other.ticksRequired;
    ticksWaited = other.ticksWaited;
}*/

/*Деструктор.*/
QueueRecord::~QueueRecord()
{

}

/*Очікування заявки протягом визначеної кількості тактів.*/
void QueueRecord::Wait(unsigned int ticksToWait)
{
    ticksWaited += ticksToWait;
}

/*Виконання заявки протягом визначеної кількості тактів.*/
void QueueRecord::Do(unsigned int ticksToDo)
{
    ticksRemaining -= ticksToDo;

    if(IsCompleted()){
        tickEnded = tickEntered + ticksRequired + ticksWaited - 1;
    }
}

/*Чи є задача завершеною?*/
bool QueueRecord::IsCompleted()
{
    return 0 == ticksRemaining;
}

/*Отримання текстової інформації про заявку.*/
string QueueRecord::ToString()
{
    string ret = "";

    ret.append("Пріоритет: ");
    ret.append(to_string(priority));
    ret.append("\n");

    ret.append("Такт надходження: ");
    ret.append(to_string(tickEntered));
    ret.append("\n");

    ret.append("Такт завершення: ");
    if(tickEnded == 0){
        ret.append("<невідомо>");
    }else{
        ret.append(to_string(tickEnded));
    }
    ret.append("\n");

    ret.append("Довжина у тактах: ");
    ret.append(to_string(ticksRequired));
    ret.append("\n");

    ret.append("Тактів залишилося: ");
    ret.append(to_string(ticksRemaining));
    ret.append("\n");

    ret.append("Тактів очікувано: ");
    ret.append(to_string(ticksWaited));
    ret.append("\n");

    return ret;
}

unsigned int QueueRecord::GetTickEntered() const
{
    return tickEntered;
}

unsigned int QueueRecord::GetTicksRequired() const
{
    return ticksRequired;
}

unsigned int QueueRecord::GetTicksRemaining() const
{
    return ticksRemaining;
}

void QueueRecord::SetTicksRemaining(unsigned int value)
{
    ticksRemaining = value;
}

unsigned int QueueRecord::GetTicksWaited() const
{
    return ticksWaited;
}

void QueueRecord::SetTicksWaited(unsigned int value)
{
    ticksWaited = value;
}

unsigned int QueueRecord::GetTickEnded() const
{
    return tickEnded;
}

void QueueRecord::SetTickEnded(unsigned int value)
{
    tickEnded = value;
}

unsigned int QueueRecord::GetPriority() const
{
    return priority;
}

void QueueRecord::SetPriority(unsigned int value)
{
    priority = value;
}


