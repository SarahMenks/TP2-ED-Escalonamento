#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <ctime>
#include "Patiant.hpp"
#include "Procedure.hpp"
#include "Scheduler.hpp"
#include "Queue.hpp"

class System{
    private:
        Procedure triagem, atendimento, medhosp, teste, exame, medic;
        Queue alta, media, baixa;

    public:
        void SetProcedures(int option, float time, int quant);
        Procedure* GetProcedure(Patiant *p);
        Queue* GetQueue(int priority);

        bool EmptyQueues();

        void CheckAndEnqueue(Patiant *p, double time);
        void ProcessQueue(int priority, double timekeeper, Scheduler &escalonador);
        void PrintStatistics(Patiant *p, int num_patiants);
        
};


#endif