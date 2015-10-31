#ifndef QUEUERECORD_H
#define QUEUERECORD_H

#include <string>

using namespace::std;

/*Запис про заявку у черзі.*/
class QueueRecord
{
public:
    /*Конструктор за замовченням*/
    QueueRecord();

    /*Конструктор з параметрами.*/
    QueueRecord(unsigned int newPriority, unsigned int newTickEntered, unsigned int newTicksRequired);

    /*Конструктор копіювання.*/
    //QueueRecord(QueueRecord& other);

    /*Деструктор.*/
    ~QueueRecord();

    /*Очікування заявки протягом визначеної кількості тактів.*/
    void Wait(unsigned int ticksToWait);

    /*Виконання заявки протягом визначеної кількості тактів.*/
    void Do(unsigned int ticksToDo);

    /*Чи є задача завершеною?*/
    bool IsCompleted();

    /*Отримання текстової інформації про заявку.*/
    string ToString();

    unsigned int GetTickEntered() const;

    unsigned int GetTicksRequired() const;

    unsigned int GetTicksRemaining() const;
    void SetTicksRemaining(unsigned int value);

    unsigned int GetTicksWaited() const;
    void SetTicksWaited(unsigned int value);

    unsigned int GetTickEnded() const;
    void SetTickEnded(unsigned int value);

    unsigned int GetPriority() const;
    void SetPriority(unsigned int value);

private:

    /*Пріоритет заявки.*/
    unsigned int priority;

    /*Такт, на якому заявка поступила.*/
    unsigned int tickEntered;

    /*Скільки тактів заявка повинна виконуватись.*/
    unsigned int ticksRequired;

    /*Скільки тактів заявці залишилося виконуватись.*/
    unsigned int ticksRemaining;

    /*Скільки тактів заявка очікувала.*/
    unsigned int ticksWaited;

    /*На якому такті заявка вийшла із системи.*/
    unsigned int tickEnded;
};

#endif // QUEUERECORD_H
