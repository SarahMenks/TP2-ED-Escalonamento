#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP
#include "Patiant.hpp"
#include <fstream>
#include <ctime>

struct Event{
    double event_date;
    Patiant *patiant;

    Event();
    Event(Patiant *temp);

    bool operator < (const Event& other) const {
        if (this->patiant->urgency != other.patiant->urgency && this->event_date == other.event_date) {
            return this->patiant->urgency > other.patiant->urgency; // Maior urgência tem prioridade
        }
        else if(this->event_date != other.event_date && this->patiant->urgency == other.patiant->urgency) {
            return this->event_date < other.event_date;
        }
       
        return false; //são iguais
    }
};

class Scheduler{
    private:
        Event *heap;
        int size;
        void LowHeapfy(int position);
        void HighHeapfy(int position); 

    public:
        Scheduler(int maxsize);
        ~Scheduler();

        void ResizeHeap(int newsize);
        void CreateEvent(Patiant *temp);
        void InsertEvent(Event Event);
        Patiant *RemoveNext();
        
        int GetParent(int posicao); 
        int GetLeftSucessor(int position);
        int GetRightSucessor(int position);
        
        bool isEmpty();
        int GetNextTime();
};

#endif