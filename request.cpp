#include "request.h"

/*Конструктор за замовченням.*/
Request::Request()
{
    priority = 0;

    ticksRequired = 0;
}

/*Конструктор з параметрами.*/
Request::Request(unsigned short int newPriority, unsigned int newCyclesRequired)
{
    priority = newPriority;

    ticksRequired = newCyclesRequired;
}

/*Деструктор.*/
Request::~Request()
{

}

/*Отримує текстову інформацію про запит.*/
string Request::ToString()
{
    string ret = "";

    ret.append("Пріоритет: ");
    ret.append(to_string(priority));
    ret.append("\n");

    ret.append("Довжина: ");
    ret.append(to_string(ticksRequired));
    ret.append("\n");

    return ret;
}

unsigned short int Request::GetPriority() const
{
    return priority;
}

unsigned int Request::GetTicksRequired() const
{
    return ticksRequired;
}
