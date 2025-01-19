#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP
#include "Patiant.hpp"
#include <fstream>
#include <ctime>

struct Event{
    struct tm *event_date;
    Patiant *p;

    Event();
    Event(Patiant *temp);

    bool operator < (Event &e) const{
        return (this->event_date < e.event_date);
    }
};

class Scheduler{
    private:
        Event *heap;
        int size;
        void LowHeapfy(int position);
        void HighHeapfy(int position); 

    public:
        Scheduler();
        ~Scheduler();

        void Initialize(int maxsize);
        void CreateEvent(Patiant *temp);
        void InsertEvent(Event Event);
        Patiant* RemoveNext();
        int GetParent(int posicao); 
        int GetLeftSucessor(int position);
        int GetRightSucessor(int position);
        
        void ShowStatistics();
        bool isEmpty();
        struct tm GetNextTime();
};

#endif