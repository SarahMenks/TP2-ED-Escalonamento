#ifndef PATIANT_HPP
#define PATIANT_HPP

#include <ctime>

struct Patiant{
        int id;
        bool discharge;
        struct tm *date;
        int urgency; //0 a 2
        int hosp_mesures;
        int tests;
        int exams;
        int medications;
        int status = 0; //vai de 0 a 13 (1 a 14)
        float queue_time, treatment_time, idle_time; //paciente tem tempo ocioso?

        void Initialize(int id, bool discharge, int year, int month, int day, int hour, int urgency, int hosp_mesures, int tests, int exams, int medications);
        struct tm GetPatiantTime(int id);

        void Print();
};

/*quais e quantos procedimentos deve realizar, estado atual e as estatísticas de atendimento do paciente*/
//COlcoar int tempo na fila?

#endif