#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP

#include <Patiant.hpp>

struct Unit{
    bool isEmpty;
    float occupied_time;
    float idle_time;
    float service_ended;
};

class Procedure{
    private:
        float duration;
        int num_units;
        Unit* units;
    
    public:
        Procedure();
        ~Procedure();
        void Inicialize(float t, int quant);
        void UpdateIdle(int num, float time);
        void PerformProcedure(Patiant *p);
        int FindEmptyUnit();
        int GetTime();
        void CheckServiceEnded(double const &time);
};
//registrar a utilização de cada unidade de cada procedimento
//e/ou seu tempo ocioso. 
//manter a data hora até a qual cada unidade está ocupada.

#endif