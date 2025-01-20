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
        low.Dequeue();

    else if(p->urgency == MEDIUM_PRIORITY)
        medium.Dequeue();
    
    else if(p->urgency == HIGH_PRIORITY)
        high.Dequeue();
}

void PrintStatistics(Patiant *p, int num_patiants){
    //printar estatisticas
    for(int i = 0 ; i < num_patiants ; i++){
        p[i].Print();
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
    struct tm system_time;

    InitializeProcedures(file, triagem, atendimento, medhosp, teste, exame, medic);
    
    //registra pacientes
    file >> num_patiants;
    Patiant *patiants = new Patiant[num_patiants]();
    Scheduler escalonador(num_patiants);


    InitializePatiants(file, patiants, num_patiants);

    //Escalona a chegada de pacientes (cria os eventos)
    for(int i = 0 ; i < num_patiants ; i++){
        escalonador.CreateEvent(&patiants[i]);
    }

    for(int i = 0 ; i < num_patiants ; i++){
        escalonador.RemoveNext()->Print();
    }

    // PrintStatistics(patiants, num_patiants);

    // //passa para a fila de triagem
    // for(int i = 0 ; i < num_patiants ; i++){
    //     triagem.PerformProcedure(escalonador.RemoveNext());
    // }


    // //passa pela fila de atendimento
    // for(int i = 0 ; i < num_patiants ; i++){
    //     atendimento.PerformProcedure(&patiants[i]);
        
    //     if(patiants[i].discharge){
    //         CheckAndDequeue(&patiants[i], high, medium, low);
    //     }
    // }

    // while(!(escalonador.isEmpty() && high.isEmpty() && medium.isEmpty() && low.isEmpty())){
    //     Patiant *p = escalonador.RemoveNext();
    //     system_time = escalonador.GetNextTime();

    //     //checa quem teve alta
    //    if(p->discharge){ //while?
    //         Patiant *aux = p;
    //         p->Print();
    //         p = escalonador.RemoveNext();
    //         delete aux;
    //     }
        
    //     CheckAndEnqueue(p, high, medium, low);
    // }

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

    


    file.close();

    return 0;
}


//time_t t
//cout << ctime(&t) << endl;
