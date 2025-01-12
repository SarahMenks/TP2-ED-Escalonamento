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
        Scheduler esc;
        Queue high, medium, low;

    public:
        void InitializeProcedures(triagem, atendimento, medhosp, teste, exame, medic);


       //Acho q isso aqui ja é a funcao do inicializeprocedures 
        // void SetTriagem();
        // void SetAtendimento();
        // void SetMedHosp();
        // void SetTeste();
        // void SetExame();
        // void SetMedic();




};


#endif