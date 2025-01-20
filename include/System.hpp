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
        Scheduler escalonador;
        Queue high, medium, low;

    public:
        // void InitializeProcedures(triagem, atendimento, medhosp, teste, exame, medic);

        // System();
        // ~System();

        void InitializeScheduler(Patiant *p, int num_patiants);
        bool ProgramEnded();


        void SetTriagem(float time, int quant);
        void SetAtendimento(float time, int quant);
        void SetMedHosp(float time, int quant);
        void SetTeste(float time, int quant);
        void SetExame(float time, int quant);
        void SetMedic(float time, int quant);
};


#endif