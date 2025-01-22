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

    bool operator<(const Event& other) const {
        if (this->patiant->urgency != other.patiant->urgency) {
            return this->patiant->urgency > other.patiant->urgency; // Maior urgência tem prioridade
        }
        // Se a urgência for igual, compara a data
        if (this->patiant->entry_date->tm_year != other.patiant->entry_date->tm_year) {
            return this->patiant->entry_date->tm_year < other.patiant->entry_date->tm_year;
        }
        if (this->patiant->entry_date->tm_mon != other.patiant->entry_date->tm_mon) {
            return this->patiant->entry_date->tm_mon < other.patiant->entry_date->tm_mon;
        }
        if (this->patiant->entry_date->tm_mday != other.patiant->entry_date->tm_mday) {
            return this->patiant->entry_date->tm_mday < other.patiant->entry_date->tm_mday;
        }
        if (this->patiant->entry_date->tm_hour != other.patiant->entry_date->tm_hour) {
            return this->patiant->entry_date->tm_hour < other.patiant->entry_date->tm_hour;
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

        void CreateEvent(Patiant *temp);
        void InsertEvent(Event Event);
        Patiant *RemoveNext();
        int GetParent(int posicao); 
        int GetLeftSucessor(int position);
        int GetRightSucessor(int position);
        
        void ShowStatistics();
        bool isEmpty();
        int GetNextTime();
};

#endif