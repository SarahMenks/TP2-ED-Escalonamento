#include <iostream>
#include "Patiant.hpp"

void Patiant::Initialize(int id, bool alta, int ano, int mes, int dia, int hora, int urgencia, int medidas_hosp, int testes, int exames, int medicamentos){
    this->id = id;
    this->discharge = alta;
    this->date->tm_year = ano;
    this->date->tm_mon = mes;
    this->date->tm_mday = dia;
    this->date->tm_hour = hora;
    this->urgency = urgencia;
    this->hosp_mesures = medidas_hosp;
    this->tests = testes;
    this->exams = exames;
    this->medications = medicamentos;
    this->status= status;
};	

void Patiant::Print(){
    std::cout << "ID: " << this->id << std::endl;
    std::cout << "Alta: " << this->discharge << std::endl;
    std::cout << "Ano: " << this->date->tm_year << std::endl;
    std::cout << "Mes: " << this->date->tm_mon << std::endl;
    std::cout << "Dia: " << this->date->tm_mday << std::endl;
    std::cout << "Hora: " << this->date->tm_hour << std::endl;
}

struct tm Patiant::GetPatiantTime(int id){
    return *this->date;
}


/*quais e quantos procedimentos deve realizar, estado atual e as estatísticas de atendimento do paciente*/
//COlcoar int tempo na fila?