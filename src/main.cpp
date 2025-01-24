#include <iostream>
#include <fstream>
#include <ctime>
#include "System.hpp"
#include "Patiant.hpp"
#include "Procedure.hpp"
#include "Scheduler.hpp"
#include "Queue.hpp"

using namespace std;

void InitializePatiants(ifstream &file, Patiant *pacientes, int size){
    int config_month, config_year;
    
    for(int pos=0; pos < size ; pos++){
        file >> pacientes[pos].id >> pacientes[pos].discharge >> config_year >> config_month >> pacientes[pos].entry_date->tm_mday >> pacientes[pos].entry_date->tm_hour >> pacientes[pos].urgency >> pacientes[pos].num_hosp_mesures >> pacientes[pos].num_tests >> pacientes[pos].num_exams >> pacientes[pos].num_medications;
        pacientes[pos].ConfigDate(config_month, config_year);
    }
}

int main(int argc, char const *argv[]){
    ifstream file(argv[1]);
    if (!(file.is_open())){
        cout << "Cannot open file" << endl;
        exit(1);
    }
    
    //cria as variaveis do sistema
    System *system = new System();
    int num_patiants;
    double timekeeper = 0; //horario , em minutos
    
    //Inicializa 5 procedimentos
    for(int i=0 ; i < 6 ; i++){
        float time;
        int quant;
        file >> time >> quant;
        system->SetProcedures(i, time, quant);
    }
    
    //registra pacientes
    file >> num_patiants;
    Patiant *patiants = new Patiant[num_patiants]();
    Scheduler escalonador = Scheduler(num_patiants);

    InitializePatiants(file, patiants, num_patiants);
    timekeeper = (patiants[0].entry_date->tm_hour*60)+patiants[0].entry_date->tm_min;

    //fila de triagem por ordem de chegada, ja que a prioridade é definida depois
    for(int i = 0 ; i < num_patiants ; i++){
        system->CheckAndEnqueue(&patiants[i]);
    }
    system->ProcessQueue(ARRIVING, timekeeper, escalonador);

    while(!(escalonador.isEmpty() && system->EmptyQueues())){
        try{
            Patiant *p = escalonador.RemoveNext();
            if((p->discharge || p->status == DISCHARGE) && p->status != TRIAGE){
                continue;
            }
            
            system->CheckAndEnqueue(p);

            if(escalonador.isEmpty()){
                system->ProcessQueue(HIGH_PRIORITY, timekeeper, escalonador);
                system->ProcessQueue(MEDIUM_PRIORITY, timekeeper, escalonador);
                system->ProcessQueue(LOW_PRIORITY, timekeeper, escalonador);
            }
        } catch(const char* msg) {cerr << "Erro: " << msg << endl; continue;}
    }

    system->PrintStatistics(patiants, num_patiants);

    delete[] patiants;

    file.close();

    return 0;
}