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
        Unit *units;
    
    public:
        Procedure();
        ~Procedure();
        int GetTime();
        void Inicialize(float t, int quant);
        //void UpdateIdle(int num, float time);
        void PerformProcedure(Patiant *p, float const timekeeper);
        int CheckEmptyUnit(double const &time);
};

#endif