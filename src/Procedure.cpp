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
        //ocupa unidade e atualiza tempo de serviço, data de saida e status do paciente
        int position = FindEmptyUnit();
        if (position == -1) {
                throw "Nenhuma unidade disponível!";
        }
        this->units[position].isEmpty = false;
        this->units[position].service_ended = p->total_time + this->duration;
        
        p->out_date->tm_hour += p->GetProcedureTime()*this->duration;
        mktime(p->out_date); //formata a data

        p->status++;
        p->time_in_treatment += p->GetProcedureTime()*this->duration;
}

int Procedure::FindEmptyUnit() {
        for (int i = 0; i < this->num_units ; i++) {
            if(this->units[i].isEmpty)
                return i;
        }
        return -1; // Nenhuma unidade disponível
}

int Procedure::GetTime(){
        return this->duration;
}

void Procedure::CheckServiceEnded(double const &time){
        for(int i = 0 ; i < this->num_units ; i++){
                if(this->units[i].service_ended < time){
                        units[i].isEmpty = true;
                }
        }
}