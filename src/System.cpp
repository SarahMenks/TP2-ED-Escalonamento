#include <iostream>
#include "System.hpp"

void System::SetProcedures(int option, float time, int quant){
    switch(option){
        case 0:
            this->triagem.Inicialize(time, quant);
            break;

        case 1:
            this->atendimento.Inicialize(time, quant);
            break;

        case 2:
            this->medhosp.Inicialize(time, quant);
            break;

        case 3:
            this->teste.Inicialize(time, quant);
            break;

        case 4:
            this->exame.Inicialize(time, quant);
            break;

        case 5:
            this->medic.Inicialize(time, quant);
            break;

        default:
            std::cout << "Impossível inicializar, procedimento invalido" << std::endl;
            throw "Procedimento invalido";
    }
}

Procedure* System::GetProcedure(Patiant *p){
    //retorna o procedimento correspondente à fila em que o paciente esta
    switch(p->status){
        case TRIAGE_QUEUE:
            return &this->triagem;
        
        case ATTENDANCE_QUEUE:
            return &this->atendimento;

        case MEDICAL_HOSPITALIZATION_QUEUE:
            return &this->medhosp;

        case TEST_QUEUE:
            return &this->teste;

        case EXAM_QUEUE:
            return &this->exame;

        case MEDICATION_QUEUE:
            return &this->medic;

        case DISCHARGE:
            std::cout << "System - GetProcedure ta falando q o paciente ta liberado" << std::endl;
            return nullptr;

        default:
            std::cout << "GetProcedure no System ta errado: " << p->status << std::endl;
            return nullptr;
            throw "Status de processo inválido";
    }
    return nullptr;
}

Queue* System::GetQueue(int priority){
    switch(priority){
        case LOW_PRIORITY:
            return &this->baixa;

        case MEDIUM_PRIORITY:
            return &this->media;

        case HIGH_PRIORITY:
            return &this->alta;

        default:
            throw "Prioridade inválida";
    }
    std::cout << "Deu ruim no Get Queue" << std::endl;
    return nullptr;
}

void System::CheckAndEnqueue(Patiant *p, double time){
    //enfileira de acordo com prioridade
    p->entry_queue = time;
    if(p->urgency == LOW_PRIORITY || p->status == ARRIVING)
        this->baixa.Enqueue(p, time);

    else if(p->urgency == MEDIUM_PRIORITY)
        this->media.Enqueue(p, time);
    
    else if(p->urgency == HIGH_PRIORITY)
        this->alta.Enqueue(p, time);
}

bool System::EmptyQueues(){
    if(this->alta.isEmpty() && this->media.isEmpty() && this->baixa.isEmpty())
        return true;
    
    return false;
}

/* Meu
void System::ProcessQueue(int priority, double &timekeeper, Scheduler &escalonador){
    //passa pela fila de atendimento
    while(!GetQueue(priority)->isEmpty()){
        try{
            Patiant *p = GetQueue(priority)->First();

            if(p->status == DISCHARGE){
                GetQueue(priority)->Remove();
                continue;
            }

            Procedure *procedure = this->GetProcedure(GetQueue(priority)->First());

            //procura uma unidade vazia. Se for o caso, faz o procedimento
            if(procedure->CheckEmptyUnit(timekeeper) != -1){
                procedure->PerformProcedure(p, timekeeper);
                escalonador.InsertEvent(p);
                timekeeper = p->total_time;
                GetQueue(priority)->Remove();
            } else{
                p->time_in_queue++;
                p->total_time++; 
                timekeeper++;
            }

            procedure->CheckEmptyUnit(timekeeper);
        } catch(const char* msg) {std::cout << msg << '\n'; std::cerr << "Erro:" << msg << std::endl; continue;}
    }
}
*/
 
void System::ProcessQueue(int priority, double timekeeper, Scheduler &escalonador){
    //while( !escalonador.isEmpty() ){
        Queue *queue = GetQueue(HIGH_PRIORITY);
        while( !queue->isEmpty() ){
            try{
                //Pega a unidade disponivel do procedimento correspondente ao primeiro da fila
                Patiant *p = queue->Remove(timekeeper);       
                Procedure *procedure = this->GetProcedure(p);       
                double procedure_time = 0;        
                
                if(procedure->CheckEmptyUnit(timekeeper) != -1){
                    procedure_time = this->GetProcedure(p)->GetTime() * p->GetProcedureTime();
                    p->time_in_queue = (timekeeper - p->entry_queue);
                    this->GetProcedure(p)->PerformProcedure(p, timekeeper);
                } 
                escalonador.CreateEvent(p, (timekeeper+procedure_time));

            } catch(const char* msg) {std::cerr << "Erro: " << msg << std::endl; continue;}
        }
        queue = GetQueue(MEDIUM_PRIORITY);
        while( !queue->isEmpty() ){
            try{
                //Pega a unidade disponivel do procedimento correspondente ao primeiro da fila
                Patiant *p = queue->Remove(timekeeper);       
                Procedure *procedure = this->GetProcedure(p);       
                double procedure_time = 0;        
                
                if(procedure->CheckEmptyUnit(timekeeper) != -1){
                    procedure_time = this->GetProcedure(p)->GetTime() * p->GetProcedureTime();
                    p->time_in_queue = (timekeeper - p->entry_queue);
                    this->GetProcedure(p)->PerformProcedure(p, timekeeper);
                } 
                escalonador.CreateEvent(p, (timekeeper+procedure_time));

            } catch(const char* msg) {std::cerr << "Erro: " << msg << std::endl; continue;}
        }
        queue = GetQueue(LOW_PRIORITY);
        while( !queue->isEmpty() ){
            try{
                //Pega a unidade disponivel do procedimento correspondente ao primeiro da fila
                Patiant *p = queue->Remove(timekeeper);       
                Procedure *procedure = this->GetProcedure(p);       
                double procedure_time = 0;        
                
                if(procedure->CheckEmptyUnit(timekeeper) != -1){
                    procedure_time = this->GetProcedure(p)->GetTime() * p->GetProcedureTime();
                    p->time_in_queue = (timekeeper - p->entry_queue);
                    this->GetProcedure(p)->PerformProcedure(p, timekeeper);
                } 
                escalonador.CreateEvent(p, (timekeeper+procedure_time));

            } catch(const char* msg) {std::cerr << "Erro: " << msg << std::endl; continue;}
        }

    //}
}
//duas coisas:
//o escalonador ja manda pra processar a fila direto. Os pacientes normais dão erro
//o timekeeper ta errado. Ele é o tempo do evento, nao o tempo atual

void System::PrintStatistics(Patiant *p, int position){
    //printar estatisticas
    for(int i = 0 ; i < position ; i++){
        p[i].PrintStatistics();
    }
}


