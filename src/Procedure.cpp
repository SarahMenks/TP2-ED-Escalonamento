#include "Procedure.hpp"
#include <iostream>

Procedure::Procedure(){
        this->duration = 0;
        this->num_units = 0;
}

Procedure::~Procedure(){
        delete[] this->units;
}

int Procedure::GetTime(){
        return this->duration;
}

void Procedure::Inicialize(float t, int quant){
        this->duration = (t*60);
        this->num_units = quant;
        this->units = new Unit[quant];
        for(int i=0 ; i<quant ; i++){
                units[i].isEmpty = true;
                units[i].service_ended = 0;
        }
}
// void Procedure::UpdateIdle(int num, float present_time){
//         //o tempo ocioso é  (tempo total - tempo em serviço)
//         if(present_time > this->units[num].service_ended)
//                 this->units[num].occupied_time += (present_time - this->units[num].service_ended);
// }

void Procedure::PerformProcedure(Patiant *p, float const timekeeper){
        //ocupa unidade e atualiza tempo de serviço, data de saida e status do paciente
        int position = CheckEmptyUnit(timekeeper);
        if (position == -1) {
                std::cout <<"Nenhuma unidade disponível!"; 
                throw "Nenhuma unidade disponível!";
        }
        this->units[position].service_ended = timekeeper + this->duration;
        
        p->status++;
        p->time_in_treatment += (p->GetProcedureTime()*this->duration);
        p->total_time += p->time_in_treatment;
}

int Procedure::CheckEmptyUnit(double const &time){
        for(int i = 0 ; i < this->num_units ; i++){
                if(this->units[i].service_ended <= time){
                        units[i].isEmpty = true;
                        //this->units[i].service_ended = time;  //Libera a unidade
                        return i;   
                }
        }
        return -1;
}