#include <iostream>
#include "Patiant.hpp"

// void Patiant::Initialize(int id, bool alta, int ano, int mes, int dia, int hora, int urgencia, int medidas_hosp, int testes, int exames, int medicamentos){
//     this->id = id;
//     this->discharge = alta;
//     this->date->tm_year = ano;
//     this->date->tm_mon = mes;
//     this->date->tm_mday = dia;
//     this->date->tm_hour = hora;
//     this->urgency = urgencia;
//     this->hosp_mesures = medidas_hosp;
//     this->tests = testes;
//     this->exams = exames;
//     this->medications = medicamentos;
//     this->status= status;
// };	

void Patiant::Print(){
    std::cout << this->id << " "
              << asctime(this->entry_date) << " "
              << asctime(this->out_date) << " "
              << total_time << " "
              << time_in_treatment << " "
              << time_in_queue << std::endl;
}

struct tm Patiant::GetPatiantTime(int id){
    return *this->out_date;
}


/*quais e quantos procedimentos deve realizar, estado atual e as estatísticas de atendimento do paciente*/
//COlcoar int tempo na fila?