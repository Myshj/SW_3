#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "queuerecord.h"

#include "request.h"

#include <vector>

using namespace std;

/*Планувальник заявок.*/
class Dispatcher
{
public:
    /*Конструктор за замовченням.*/
    Dispatcher();

    /*Конструктор з параметрами.*/
    Dispatcher(unsigned int newCountOfQueues, unsigned int newMinPriority);

    /*Деструктор.*/
    ~Dispatcher();

    /*Виконує прийом нової заявки.*/
    void AcceptRequest(Request& request, unsigned int tick);

    /*Основний цикл роботи планувальника.*/
    void MainCycle();

    /*Отримання текстової інформації про поточний стан заявок.*/
    string ToString();

    /*Генерує звіт про виконану роботу.*/
    string GetReport();

    bool IsEmpty() const;

    unsigned int resourceWaitTime = 0;


private:
    /*Черги заявок.*/
    vector< vector<QueueRecord> > queues;

    /*Виконані заявки.*/
    vector<QueueRecord> done;

    /*
     * Виконує порівняння пріоритетів двох заявок.
     * Повертає true, якщо друга заявка пріоритетніша за першу.
     * */
    static bool ComparePriorities(QueueRecord& a, QueueRecord& b);

    /*Ініціалізує черги.*/
    void QueuesInitialization(unsigned int queuesCount);

    /*Обчислення довжини кванта у тактах.*/
    void QuantCalculation();

    /*На основі наданої заявки будує запис про неї.*/
    QueueRecord TransformRequestToRecord(Request& request, unsigned int tick);

    /*Сортує чергу за зростанням або спаданням пріоритетів.*/
    void SortQueueByPriorities(vector<QueueRecord>& queue);

    /*Сортує всі черги, крім першої.*/
    void SortAllQueuesExceptFirst();

    /*Обирає наступну заявку із черги.*/
    void GetFirstInQueue(vector<QueueRecord>& queue);

    /*Обирає наступну заявку для обробки.*/
    void GetNext();

    /*Примушує всі заявки почекати визначену кількість тактів.*/
    void WaitAll(unsigned int ticksToWait);

    /*Обчислює кількість тактів, які повинні надатися заявці.*/
    unsigned int CalculateTicksForRequest(QueueRecord& queueRecord);

    /*Довжина кванта у тактах.*/
    unsigned int quantLength;

    /*
     * Мінімальний пріоритет заявки.
     * Максимальний - 0.
     * */
    unsigned int minPriority;

    /*Кількість тактів, під час яких планувальник нічого не робитиме.*/
    unsigned int ticksToWait;

    /*Поточна виконувана заявка.*/
    QueueRecord* currentRequest;

    /*Номер черги, з якої взята поточна заявка.*/
    unsigned int currentRequestQueue;


};

#endif // DISPATCHER_H
