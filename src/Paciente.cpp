#include <iostream>
#include "Paciente.hpp"

void Paciente::Inicializa(int id, bool alta, int ano, int mes, int dia, int hora, int urgencia, int medidas_hosp, int testes, int exames, int medicamentos){
    this->id = id;
    this->alta = alta;
    this->data->tm_year = ano;
    this->data->tm_mon = mes;
    this->data->tm_mday = dia;
    this->data->tm_hour = hora;
    this->urgencia = urgencia;
    this->medidas_hosp = medidas_hosp;
    this->testes = testes;
    this->exames = exames;
    this->medicamentos = medicamentos;
    this->estado = estado;
};	

void Paciente::Imprime(){
    std::cout << "ID: " << this->id << std::endl;
    std::cout << "Alta: " << this->alta << std::endl;
    std::cout << "Ano: " << this->ano << std::endl;
    std::cout << "Mes: " << this->mes << std::endl;
    std::cout << "Dia: " << this->dia << std::endl;
    std::cout << "Hora: " << this->hora << std::endl;
}

/*quais e quantos procedimentos deve realizar, estado atual e as estatísticas de atendimento do paciente*/
//COlcoar int tempo na fila?