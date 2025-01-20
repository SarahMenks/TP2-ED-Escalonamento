#include <iostream>
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
    this->out_date = new tm;
    this->urgency = 0;
    this->num_hosp_mesures = 0;
    this->num_tests = 0;
    this->num_exams = 0;
    this->num_medications = 0;
    this->status = 0;
    this->time_in_queue = 0;
    this->time_in_treatment = 0;
    this->total_time = 0;
}

Patiant::~Patiant(){
    delete this->entry_date;
    delete this->out_date;
}

void Patiant::ConfigDate(int month, int year){    
    this->entry_date->tm_year = year - 1900;
    this->entry_date->tm_mon = month - 1;
    this->out_date = this->entry_date;
};

void Patiant::Print(){
    std::mktime(this->entry_date);
    std::mktime(this->out_date);
    std::cout << this->id << " "
              << asctime(this->entry_date)
              << asctime(this->out_date)
              << total_time << " "
              << time_in_treatment << " "
              << time_in_queue << std::endl;
    
//tem q olhar o incremento do out_date, pode ser q esteja errado
}

struct tm Patiant::GetPatiantTime(int id){
    return *this->out_date;
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