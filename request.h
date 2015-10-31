#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;


/*Заявка на використання розподіленого ресурсу.*/
class Request
{
public:
    /*Конструктор за замовченням.*/
    Request();

    /*Конструктор з параметрами.*/
    Request(unsigned short int newPriority, unsigned int newCyclesRequired);

    /*Деструктор.*/
    ~Request();

    /*Отримує текстову інформацію про запит.*/
    string ToString();

    unsigned short int GetPriority() const;

    unsigned int GetTicksRequired() const;

private:
    /*Пріоритет заявки.*/
    unsigned short int priority;

    /*Необхідне число тактів процесора.*/
    unsigned int ticksRequired;
};

#endif // REQUEST_H
