#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP

struct Unit{
    float occupied_time;
    float idle_time;
    float fim_atendimento;
};

class Procedure{
    private:
        float duration;
        int quant_units;
        Unit* units;
    
    public:
        void Inicialize(float t, int quant);
        void UpdateIdle(int num, float time);
};
//registrar a utilização de cada unidade de cada procedimento
//e/ou seu tempo ocioso. 
//manter a data hora até a qual cada unidade está ocupada.

#endif