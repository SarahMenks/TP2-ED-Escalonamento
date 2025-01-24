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
            std::cout << "Status no System ta errado: " << p->status << std::endl;
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
    }
    std::cout << "Deu ruim no Get Queue" << std::endl;
    return nullptr;
}

void System::CheckAndEnqueue(Patiant *p){
    //enfileira de acordo com prioridade
    if(p->urgency == LOW_PRIORITY || p->status == ARRIVING)
        this->baixa.Enqueue(p);

    else if(p->urgency == MEDIUM_PRIORITY)
        this->media.Enqueue(p);
    
    else if(p->urgency == HIGH_PRIORITY)
        this->alta.Enqueue(p);
}

bool System::EmptyQueues(){
    if(this->alta.isEmpty() && this->media.isEmpty() && this->baixa.isEmpty())
        return true;
    
    return false;
}

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
            if(procedure->FindEmptyUnit(timekeeper) != -1){
                procedure->PerformProcedure(p, timekeeper);
                escalonador.InsertEvent(p);
                timekeeper = p->total_time;
                GetQueue(priority)->Remove();
            }

            else if(procedure->FindEmptyUnit(timekeeper) == -1) {
                p->time_in_queue++;
                p->total_time++; 
                timekeeper++;
            }

            procedure->CheckServiceEnded(timekeeper);
        } catch(const char* msg) {std::cout << msg << '\n'; std::cerr << "Erro:" << msg << std::endl; continue;}
    }
} 

void System::PrintStatistics(Patiant *p, int position){
    //printar estatisticas
    for(int i = 0 ; i < position ; i++){
        p[i].PrintStatistics();
    }
}


