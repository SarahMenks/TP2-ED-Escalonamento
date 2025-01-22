#include <iostream>
#include <fstream>
#include <ctime>
#include "Patiant.hpp"
#include "Procedure.hpp"
#include "Scheduler.hpp"
#include "Queue.hpp"

using namespace std;

void InitializeProcedures(ifstream &file, Procedure &triagem, Procedure &atendimento, Procedure &medhosp, Procedure &teste, Procedure &exame, Procedure &medic){
    float time;
    int quant;
    
    file >> time >> quant;
    triagem.Inicialize(time, quant);
    
    file >> time >> quant;
    atendimento.Inicialize(time, quant);

    file >> time >> quant;
    medhosp.Inicialize(time, quant);

    file >> time >> quant;
    teste.Inicialize(time, quant);

    file >> time >> quant;
    exame.Inicialize(time, quant);

    file >> time >> quant;
    medic.Inicialize(time, quant);

    /* Fazer com set?
void InitializeProcedures(ifstream &file, System *H){
    float time;
    int quant;
    
    file >> time >> quant;
    H->SetTriagem(time, quant);
    
    file >> time >> quant;
    H->SetAtendimento(time, quant);

    file >> time >> quant;
    H->SetMedHosp(time, quant);
    
    file >> time >> quant;
    H->SetTeste(time, quant);

    file >> time >> quant;
    H->SetExame(time, quant);

    file >> time >> quant;
    H->SetMedic(time, quant);
}
*/
}

void InitializePatiants(ifstream &file, Patiant *pacientes, int size){
    int config_month, config_year;
    
    for(int pos=0; pos < size ; pos++){
        file >> pacientes[pos].id >> pacientes[pos].discharge >> config_year >> config_month >> pacientes[pos].entry_date->tm_mday >> pacientes[pos].entry_date->tm_hour >> pacientes[pos].urgency >> pacientes[pos].num_hosp_mesures >> pacientes[pos].num_tests >> pacientes[pos].num_exams >> pacientes[pos].num_medications;
        pacientes[pos].ConfigDate(config_month, config_year);
    }
}

void CheckAndEnqueue(Patiant *p, Queue &high, Queue &medium, Queue &low){
    if(p->urgency == LOW_PRIORITY)
        low.Enqueue(p);

    else if(p->urgency == MEDIUM_PRIORITY)
        medium.Enqueue(p);
    
    else if(p->urgency == HIGH_PRIORITY)
        high.Enqueue(p);
}

//Só se precisar
void CheckAndDequeue(Patiant *p, Queue &high, Queue &medium, Queue &low){
    if(p->urgency == LOW_PRIORITY)
        low.Remove();

    else if(p->urgency == MEDIUM_PRIORITY)
        medium.Remove();
    
    else if(p->urgency == HIGH_PRIORITY)
        high.Remove();
}

void PrintStatistics(Patiant *p, int num_patiants){
    //printar estatisticas
    for(int i = 0 ; i < num_patiants ; i++){
        p[i].PrintStatistics();
    }
}

void ProcessQueue(Queue &queue, Procedure &procedure, Scheduler &escalonador, double &system_time){
    //passa pela fila de atendimento
    if(queue.isEmpty()){
        cout << "Nao dá pra processar, a fila está vazia!" << endl;
        return;
    }
    else{
        while(!queue.isEmpty()){
            try{
                Patiant *p = queue.First();
                
                //procura uma unidade vazia. Se for o caso, faz o procedimento
                if(procedure.FindEmptyUnit(system_time) != -1){
                    procedure.PerformProcedure(p, system_time);
                    escalonador.InsertEvent(p);
                    system_time = p->total_time;
                    queue.Remove();
                }

                else if(procedure.FindEmptyUnit(system_time) == -1) {
                    p->time_in_queue++;
                    p->total_time++; 
                    system_time++;
                }

                procedure.CheckServiceEnded(system_time);
            } catch(const char* msg) {cerr << "Erro:" << msg << endl; continue;}
        }
    } 
}

int main(int argc, char const *argv[]){
    ifstream file(argv[1]);
    if (!(file.is_open())){
        cout << "Cannot open file" << endl;
        exit(1);
    }
    
    //cria as variaveis do sistema
    //System s_hospital;
    Procedure triagem, atendimento, medhosp, teste, exame, medic;
    Queue high, medium, low;
    int num_patiants;
    double system_time = 0; //horario do sistema, em minutos

    InitializeProcedures(file, triagem, atendimento, medhosp, teste, exame, medic);
    
    //registra pacientes
    file >> num_patiants;
    Patiant *patiants = new Patiant[num_patiants]();
    Scheduler escalonador(num_patiants);

    InitializePatiants(file, patiants, num_patiants);
    system_time = (patiants[0].entry_date->tm_hour*60)+patiants[0].entry_date->tm_min;

    //fila de triagem por ordem de chegada, ja que a prioridade é definida depois
    for(int i = 0 ; i < num_patiants ; i++){
        high.Enqueue(&patiants[i]);
    }
    
    ProcessQueue(high, triagem, escalonador, system_time);

    while(!(escalonador.isEmpty() && high.isEmpty() && medium.isEmpty() && low.isEmpty())){
        Patiant *p = escalonador.RemoveNext();

        try{
            if(p->discharge || p->status == DISCHARGE){
                p->PrintStatistics();
                continue;
            }
            
            CheckAndEnqueue(p, high, medium, low);

            if(escalonador.isEmpty()){
                if(!high.isEmpty()){
                    switch(high.First()->status){
                        case ATTENDANCE_QUEUE:
                            ProcessQueue(high, atendimento, escalonador, system_time);
                        break;
                        case MEDICAL_HOSPITALIZATION_QUEUE:
                            ProcessQueue(high, medhosp, escalonador, system_time);
                        break;
                        
                        case TEST_QUEUE:
                            ProcessQueue(high, teste, escalonador, system_time);
                        break;
                        
                        case EXAM_QUEUE:
                            ProcessQueue(high, exame, escalonador, system_time);                    
                        break;
                        
                        case MEDICATION_QUEUE:
                            ProcessQueue(high, medic, escalonador, system_time);
                        break;
                        case DISCHARGE:
                            p->PrintStatistics();
                        break;
                        
                        default:
                            cout << p->status << endl;
                            throw "Status de processo inválido";
                    }
                }
                if(!medium.isEmpty()){
                    switch(medium.First()->status){
                    case ATTENDANCE_QUEUE:
                        if(!medium.isEmpty())
                        ProcessQueue(medium, atendimento, escalonador, system_time);
                    break;
                    case MEDICAL_HOSPITALIZATION_QUEUE:
                        ProcessQueue(medium, medhosp, escalonador, system_time);
                    break;
                    
                    case TEST_QUEUE:
                        ProcessQueue(medium, teste, escalonador, system_time);
                    break;
                    
                    case EXAM_QUEUE:
                        ProcessQueue(medium, exame, escalonador, system_time);
                    break;
                    
                    case MEDICATION_QUEUE:
                        ProcessQueue(medium, medic, escalonador, system_time);
                    break;
                    case DISCHARGE:
                        p->PrintStatistics();
                    break;
                    
                    default:
                        cout << p->status << endl;
                        throw "Status de processo inválido";
                }
                }
                if(!low.isEmpty()){
                    switch (low.First()->status){
                    case ATTENDANCE_QUEUE:
                        ProcessQueue(low, atendimento, escalonador, system_time);
                    break;
                    case MEDICAL_HOSPITALIZATION_QUEUE:
                        ProcessQueue(low, medhosp, escalonador, system_time);
                    break;
                    
                    case TEST_QUEUE:
                        ProcessQueue(low, teste, escalonador, system_time);
                    break;
                    
                    case EXAM_QUEUE:
                        ProcessQueue(low, exame, escalonador, system_time);
                    break;
                    
                    case MEDICATION_QUEUE:
                        ProcessQueue(low, medic, escalonador, system_time);
                    break;
                    case DISCHARGE:
                        p->PrintStatistics();
                    break;
                    
                    default:
                        cout << "Status: " << p->status << endl;
                        throw "Status de processo inválido";
                    }
                }
            }
        } catch(const char* msg) {cerr << "Erro: " << msg << endl; continue;}
    }

    // for(int i=0 ; i < num_patiants ; i++){
    //     patiants[i].PrintStatistics();
    // }


    file.close();

    return 0;
}

//cada Procedure vai ter uma fila
/*
Inicializa Condição de Término para FALSO
Inicializa as variáveis de estado do sistema
Inicializa o Relógio (usualmente zero)
Escalona a chegada de pacientes
Enquanto houver eventos ou filas não vazias
    Remove o próximo evento do escalonador
    Avança o relógio para o instante do próximo evento
    Verifica o próximo estado do paciente
    Se houver mais serviços para paciente
        Enfileira o paciente na fila adequada
    Senão
        Finaliza o atendimento (Alta Hospitalar)
        
    Para cada fila de espera que tenha pacientes
        Se há unidade disponível para execução
            Escalonar o evento de execução do serviço
    Atualizar as estatísticas
Fim 
Gerar relatórios de estatísticas
*/