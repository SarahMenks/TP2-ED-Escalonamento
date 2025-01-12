#include "Procedimento.hpp"
    
void Procedure::Inicialize(float t, int quant){
        this->duration = t;
        this->quant_units = quant;
        this->units = new Unit[quant];
};

void Procedure::Inicialize(float t, int quant){

}

void Procedure::UpdateIdle(int num, float present){
    if(present > this->units[num].fim_atendimento)
        this->units[num].occupied_time += (present - this->units[num].fim_atendimento);
}