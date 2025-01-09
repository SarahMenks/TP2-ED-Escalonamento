#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP
#include "Paciente.hpp"
#include <fstream>
#include <ctime>

struct Event{
    int year, month, day; //use ctime?
    float hour;
    Patiant *p;

    Event();
    Event(Patiant *temp);

    bool operator < (Event &e) const{
        return (this->year <= e.year, this->month<= e.month, this->day <= e.day && this->hour < e.hour);
    }
};

class Scheduler{
    private:
        Event *heap;
        int size;
        void LowHeapfy(int position);
        void HighHeapfy(int position); 

    public:
        void CreateEvent(Patiant *temp);
        void Initialize(int maxsize);
        void InsertEvent(Event Event);
        Event RemoveNext();
        int GetParent(int posicao); 
        int GetLeftSucessor(int position);
        int GetRightSucessor(int position);
        void Finalize();
};

#endif