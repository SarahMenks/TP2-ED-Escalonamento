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
    Scheduler escalonador;
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
    Patiant *patiants = new Patiant[num_patiants];

    InitializePatiants(file, patiants, num_patiants);

    //fila de triagem por ordem de chegada, ja que a prioridade é definida depois
    for(int i = 0 ; i < num_patiants ; i++){
        system->CheckAndEnqueue(&patiants[i], timekeeper);
    }
    system->ProcessQueue(ARRIVING, timekeeper, escalonador);

//checar se ja vai pra próxima fila ou se tem q fazer procedimento
    while( !(system->EmptyQueues() && escalonador.isEmpty()) ){
        try{
            Event next = escalonador.RemoveNext();
            //timekeeper = next.event_time;
            Patiant *p = next.patiant;
            //ta errado. O timekeeper é o tempo do evento, nao necessariamente o proximo
            
            if((p->discharge || p->status == DISCHARGE) && p->status != TRIAGE){
                p->discharge = true;
                continue;
            }

            if(){

            }
            
            p->time_in_queue += (timekeeper - p->entry_queue);
            p->total_time += p->time_in_queue;

            Procedure *procedure = system->GetProcedure(p);
            int unit = procedure->CheckEmptyUnit(timekeeper);
            
            
            //procedure->PerformProcedure(p, timekeeper);
            double procedure_end_time = timekeeper + p->GetProcedureTime()*procedure->GetTime();
            escalonador.CreateEvent(p, procedure_end_time);

            system->ProcessQueue(HIGH_PRIORITY, timekeeper, escalonador);
            system->ProcessQueue(MEDIUM_PRIORITY, timekeeper, escalonador);
            system->ProcessQueue(LOW_PRIORITY, timekeeper, escalonador);

        } catch(const char* msg) {cerr << "Erro: " << msg << endl; break;}
    }
    cout << "Chegou no final" << endl;
    system->PrintStatistics(patiants, num_patiants);

    delete[] patiants;

    file.close();

    return 0;
}