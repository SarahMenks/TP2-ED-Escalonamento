#include <iostream>
#include <algorithm> //só é usado para remover o \n de uma string, na funcao Print().
#include "Patiant.hpp"

// void Patiant::Initialize(int id, bool alta, int ano, int mes, int dia, int hora, int urgencia, int medidas_hosp, int testes, int exames, int medicamentos){
//     this->id = id;
//     this->discharge = alta;
//     this->date->tm_year = ano - 1900;
//     this->date->tm_mon = mes -;
//     this->date->tm_mday = dia;
//     this->date->tm_hour = hora;
//     this->urgency = urgencia;
//     this->hosp_mesures = medidas_hosp;
//     this->tests = testes;
//     this->exams = exames;
//     this->medications = medicamentos;
//     this->status= status;
// };	

Patiant::Patiant(){
    this->id = 0;
    this->discharge = false;
    this->entry_date = new tm;
    this->urgency = 0;
    this->num_hosp_mesures = 0;
    this->num_tests = 0;
    this->num_exams = 0;
    this->num_medications = 0;
    this->status = 0;
    this->time_in_queue = 0;
    this->time_in_treatment = 0;
    this->total_time = 0; //total em minutos
}

Patiant::~Patiant(){
    delete this->entry_date;
}

void Patiant::ConfigDate(int month, int year){    
    this->entry_date->tm_year = year - 1900;
    this->entry_date->tm_mon = month - 1;
    this->total_time = (entry_date->tm_hour*60) + entry_date->tm_min; //total em minutos
};

void Patiant::Print(){
    struct tm out_date = *this->entry_date;
    out_date.tm_hour = this->total_time/60;
    out_date.tm_min = (int)(this->total_time)%60;

    mktime(this->entry_date);
    mktime(&out_date);

    std::string entry = asctime(this->entry_date); 
    std::string out = asctime(&out_date);
    
    //funcoes que dependem de <algorithm>
    entry.erase(std::remove(entry.begin(), entry.end(), '\n'), entry.end());
    out.erase(std::remove(out.begin(), out.end(), '\n'), out.end());

    //quanto tempo o paciente passou em tratamento e na fila, tirando o horario de entrada
    total_time -= ((entry_date->tm_hour*60) + entry_date->tm_min);
    
    std::cout << this->id << " "
              << entry << " "
              << out << " "
              << (total_time/60) << " "
              << (time_in_treatment/60) << " "
              << (time_in_queue/60) << std::endl;
}

double Patiant::GetPatiantTime(int id){
    return this->total_time;
}

 int Patiant::GetProcedureTime(){
    //Funcao que retorna quantas vezes o paciente deve realizar o procedimento
    switch (this->status){
        case TRIAGE:
            return 1;
        case ATENDANCE:
            return 1;
        case MEDICAL_HOSPITALIZATION:
            return num_hosp_mesures;
        case TEST:
            return num_tests;
        case EXAM:
            return num_exams;
        case MEDICATION:
            return num_medications;
        default:
            throw "Status inválido";
            return 0;
    }
 }



/*quais e quantos procedimentos deve realizar, estado atual e as estatísticas de atendimento do paciente*/
//COlcoar int tempo na fila?