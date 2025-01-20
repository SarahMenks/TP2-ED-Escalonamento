#include "Procedure.hpp"

Procedure::Procedure(){
        this->duration = 0;
        this->num_units = 0;
        this->units = nullptr;
}
Procedure::~Procedure(){
        delete this->units;
}

void Procedure::Inicialize(float t, int quant){
        this->duration = t;
        this->num_units = quant;
        this->units = new Unit[quant];
}

void Procedure::UpdateIdle(int num, float present_time){
        //o tempo ocioso é  (tempo total - tempo em serviço)
        if(present_time > this->units[num].service_ended)
                this->units[num].occupied_time += (present_time - this->units[num].service_ended);
}

void Procedure::PerformProcedure(Patiant *p){
        //verificar se tem unidade disponivel
        for(int i = 0 ; i < this->num_units ; i++){
                if(this->units[i].isEmpty){
                        //ocupa unidade e atualiza tempo de serviço, data de saida e status do paciente
                        this->units[i].isEmpty = false;
                        this->units[i].service_ended = p->total_time + this->duration;
                        p->out_date->tm_hour += this->duration;
                        p->time_in_treatment += this->duration;
                        p->status++;
                        break;
                }
        }
}