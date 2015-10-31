#ifndef CONSTANTS_H
#define CONSTANTS_H


/*Містить константи для початкової ініціалізації планувальника згідно значень за замовченням.*/
class Constants
{
public:
    /*Число черг.*/
    static const unsigned int COUNT_OF_QUEUES = 1;

    /*
     * Мінімальний пріоритет.
     * Максимальний - 0.
     * */
    static const unsigned int MIN_PRIORITY = 0;
};

#endif // CONSTANTS_H
