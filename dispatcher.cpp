#include "dispatcher.h"

#include "constants.h"

#include <algorithm>

/*Конструктор за замовченням.*/
Dispatcher::Dispatcher()
{
    QueuesInitialization(Constants::COUNT_OF_QUEUES);

    QuantCalculation();

    minPriority = Constants::MIN_PRIORITY;

    ticksToWait = 0;

    currentRequest = NULL;

    currentRequestQueue = 0;

    done = vector<QueueRecord>();
}

/*Конструктор з параметрами.*/
Dispatcher::Dispatcher(unsigned int newCountOfQueues, unsigned int newMinPriority)
{
    QueuesInitialization(newCountOfQueues);

    QuantCalculation();

    minPriority = newMinPriority;

    ticksToWait = 0;

    currentRequest = NULL;

    currentRequestQueue = 0;

    done = vector<QueueRecord>();
}

/*Деструктор.*/
Dispatcher::~Dispatcher()
{
    for(unsigned int i = 0; i < queues.size(); i++){
        queues[i].clear();
    }
    queues.clear();

    done.clear();
}

/*Виконує прийом нової заявки.*/
void Dispatcher::AcceptRequest(Request& request, unsigned int tick)
{
    queues[0].push_back(
                TransformRequestToRecord(request, tick)
                );
}

/*Основний цикл роботи планувальника.*/
void Dispatcher::MainCycle()
{
    /*Чи готовий зараз планувальник обробити наступну заявку?*/
    if(ticksToWait == 0){
        if(currentRequest != NULL){
            /*Якщо заявка завершена, то вона із черг видаляється. Інакше переміщується до наступної черги.*/
            if(currentRequest->IsCompleted()){
                //delete currentRequest;
                done.push_back(*currentRequest);
            }else{
                queues[currentRequestQueue + 1].push_back(*currentRequest);
                SortQueueByPriorities(queues[currentRequestQueue + 1]);
            }
            currentRequest = NULL;
        }

        GetNext();
        /*Чи всі черги порожні?*/
        if(NULL == currentRequest){
            resourceWaitTime++;
            return;
        }

        /*Якщо заявка знаходиться у останній черзі, вона виконується до кінця.*/
        unsigned int ticksToDo;
        if(currentRequestQueue == queues.size() - 1){
            ticksToDo = currentRequest->GetTicksRemaining();
        }else{
            ticksToDo = CalculateTicksForRequest(*currentRequest);
        }

        ticksToWait = ticksToDo - 1;
        currentRequest->Do(ticksToDo);


    }else{
        ticksToWait--;
    }

    WaitAll(1);
}

/*Отримання текстової інформації про поточний стан заявок.*/
string Dispatcher::ToString()
{
    string ret = "";

    ret.append("Поточна заявка: ");
    if(currentRequest != NULL){
        ret.append(currentRequest->ToString());
    }else{
        ret.append("<пусто>\n");
    }
    ret.append("\n");

    for(unsigned int i = 0; i < queues.size(); i++){
        ret.append("\tЧерга номер ");
        ret.append(to_string(i));
        ret.append("\n");

        for(unsigned int j = 0; j < queues[i].size(); j++){
            ret.append(queues[i][j].ToString());
            ret.append("\n");
        }
    }

    return ret;
}

string Dispatcher::GetReport()
{
    string ret = "";
    unsigned int averageWaitTime = 0;

    vector<unsigned int> waitTimeByPriority = vector<unsigned int>(minPriority + 1);
    vector<unsigned int> countByPriority = vector<unsigned int>(minPriority + 1);

    for(unsigned int i = 0; i < done.size(); i++){
        averageWaitTime += done[i].GetTicksWaited();

        waitTimeByPriority[done[i].GetPriority()] += done[i].GetTicksWaited();
        countByPriority[done[i].GetPriority()]++;
    }

    averageWaitTime /= done.size();

    for(unsigned int i = 0; i < waitTimeByPriority.size(); i++){
        if(countByPriority[i] != 0){
            waitTimeByPriority[i] /= countByPriority[i];
        }
    }

    ret.append("Кількість черг: ");
    ret.append(to_string(queues.size()));
    ret.append("\n");

    ret.append("Довжина кванту: ");
    ret.append(to_string(quantLength));
    ret.append("\n");

    ret.append("Оброблено заявок: ");
    ret.append(to_string(done.size()));
    ret.append("\n");

    ret.append("Відсоток простою ресурсу: ");
    ret.append(to_string(resourceWaitTime * 100 / done.back().GetTickEnded()));
    ret.append("\n\n");

    ret.append("Середній час очікування: ");
    ret.append(to_string(averageWaitTime));
    ret.append("\n");



    ret.append("По пріоритетам:\n");
    for(unsigned int i = 0; i < waitTimeByPriority.size(); i++){
        ret.append(to_string(i));
        ret.append(":\t");
        ret.append(to_string(waitTimeByPriority[i]));
        ret.append("\n");

    }

    return ret;
}

bool Dispatcher::IsEmpty() const
{
    if(currentRequest != NULL){
        return false;
    }
    for(unsigned int i = 0; i < queues.size(); i++){
        if(queues[i].begin() != queues[i].end()){
            return false;
        }
    }
    return true;
}


/*
 * Виконує порівняння пріоритетів двох заявок.
 * Повертає true, якщо друга заявка пріоритетніша за першу.
 * */
bool Dispatcher::ComparePriorities(QueueRecord& a, QueueRecord& b)
{
    return a.GetPriority() > b.GetPriority();
}

/*Ініціалізує черги.*/
void Dispatcher::QueuesInitialization(unsigned int queuesCount)
{
    queues = vector< vector<QueueRecord> >();

    for(unsigned int i = 0; i < queuesCount; i++){
        queues.push_back(vector<QueueRecord>());
    }
}

/*Обчислення довжини кванта у тактах.*/
void Dispatcher::QuantCalculation()
{
    quantLength = 2 * queues.size() - 1;
}

/*На основі наданої заявки будує запис про неї.*/
QueueRecord Dispatcher::TransformRequestToRecord(Request& request, unsigned int tick)
{
    return QueueRecord(request.GetPriority(), tick, request.GetTicksRequired());
}

/*Сортує чергу за зростанням або спаданням пріоритетів.*/
void Dispatcher::SortQueueByPriorities(vector<QueueRecord>& queue)
{
    sort(queue.begin(), queue.end(), ComparePriorities);
}

/*Сортує всі черги, крім першої.*/
void Dispatcher::SortAllQueuesExceptFirst()
{
    for(unsigned int i = 1; i < queues.size(); i++){
        SortQueueByPriorities(queues[i]);
    }
}

/*Обирає наступний елемент із черги.*/
void Dispatcher::GetFirstInQueue(vector<QueueRecord>& queue)
{
    currentRequest = new QueueRecord(queue.back());
    queue.pop_back();
}

/*Обирає наступну заявку для обробки.*/
void Dispatcher::GetNext()
{
    for(unsigned int i = 0; i < queues.size(); i++){
        if(queues[i].begin() != queues[i].end()){
            GetFirstInQueue(queues[i]);
            currentRequestQueue = i;
            return;
        }
    }
    currentRequest = NULL;
    currentRequestQueue = 0;
}

/*Примушує всі заявки почекати визначену кількість тактів.*/
void Dispatcher::WaitAll(unsigned int ticksToWait)
{
    for(unsigned int i = 0; i < queues.size(); i++){
        for(unsigned int j = 0; j < queues[i].size(); j++){
            queues[i][j].Wait(ticksToWait);
        }
    }
}

/*Обчислює кількість тактів, які повинні надатися заявці.*/
unsigned int Dispatcher::CalculateTicksForRequest(QueueRecord &queueRecord)
{
    unsigned int remainingTicks = queueRecord.GetTicksRemaining();

    if(remainingTicks < quantLength){
        return remainingTicks;
    }

    return quantLength;
}

