#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP
#include "Patiant.hpp"
#include <fstream>
#include <ctime>

struct Event{
    double event_time;
    Patiant *patiant;
    int type;

    Event();
    Event(Patiant *p, double time);

    bool operator < (const Event& other) const {
        if (this->patiant->urgency != other.patiant->urgency && this->event_time == other.event_time) {
            return this->patiant->urgency > other.patiant->urgency; // Maior urgência tem prioridade
        }
        else if(this->event_time != other.event_time && this->patiant->urgency == other.patiant->urgency) {
            return this->event_time < other.event_time;
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
        Scheduler();
        Scheduler(int maxsize);
        ~Scheduler();

        void ResizeHeap(int newsize);
        void CreateEvent(Patiant *p, double time);
        Event RemoveNext();

        int GetParent(int posicao); 
        int GetLeftSucessor(int position);
        int GetRightSucessor(int position);
        
        bool isEmpty();
        Event GetNext();
};

#endif