#include "Procedure.hpp"

Procedure::Procedure(){
        this->duration = 0;
        this->quant_units = 0;
        this->units = nullptr;
}
Procedure::~Procedure(){
        delete this->units;
}

void Procedure::Inicialize(float t, int quant){
        this->duration = t;
        this->quant_units = quant;
        this->units = new Unit[quant];
}

void Procedure::UpdateIdle(int num, float present_time){
    if(present_time > this->units[num].service_ended)
        this->units[num].occupied_time += (present_time - this->units[num].service_ended);
}