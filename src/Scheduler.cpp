#include "Scheduler.hpp"

Event::Event(){
    this->p = nullptr;
    this->event_date = 0;
}

Event::Event(Patiant *temp){
    this->p = temp;
    this->event_date = p->date;
}

void Scheduler::Initialize(int maxsize){
    this->heap = new Event[maxsize];
    this->size = 0;
}

void Scheduler::CreateEvent(Patiant *temp){
    Event new_event(temp);
    InsertEvent(new_event);
}

void Scheduler::InsertEvent(Event e){
    this->heap[this->size] = e;
    this->size++;
    LowHeapfy(this->size-1);    
}

Event Scheduler::RemoveNext(){
    Event aux = this->heap[0];
    this->heap[0] = this->heap[this->size-1];
    this->size--;
    HighHeapfy(0);
    return aux;
}

int Scheduler::GetParent(int position){
    return (position-1)/2;
}

int Scheduler::GetLeftSucessor(int position){
    return (position*2)+1;
}

int Scheduler::GetRightSucessor(int position){
    return (position*2)+2;
}

void Scheduler::LowHeapfy(int position){
    if(position == 0)
        return;

    int position_parent = GetParent(position);
    //se o evento parent tiver um paciente com maior urgencia, mantes
    if(this->heap[position_parent].p->urgency < this->heap[position].p->urgency){
        return;
    }   
    //se o filho tiver maior urgencia ou o menor tempo, troca
    else if(this->heap[position].p->urgency < this->heap[position_parent].p->urgency || this->heap[position] < this->heap[position_parent]){
        Event aux = this->heap[position];
        this->heap[position] = this->heap[position_parent];
        this->heap[position_parent] = aux;
        LowHeapfy(position_parent);
    }
}

void Scheduler::HighHeapfy(int position){
    int esq = GetLeftSucessor(position);
    int dir = GetRightSucessor(position);
    int pos_menor = position;

    if((dir < this->size) && (this->heap[dir] < this->heap[pos_menor]) && (this->heap[dir] < this->heap[esq]) && (this->heap[dir].p->urgency > this->heap[pos_menor].p->urgency))
        pos_menor = dir;
    
    if((esq < this->size) && (this->heap[esq] < this->heap[pos_menor]) && (this->heap[esq] < this->heap[dir]) && (this->heap[esq].p->urgency > this->heap[pos_menor].p->urgency))
        pos_menor = esq;

    if(pos_menor != position){
        Event aux = this->heap[position];
        this->heap[position] = this->heap[pos_menor];
        this->heap[pos_menor] = aux; //talvez nao saiba copiar pacientes

        HighHeapfy(pos_menor);
    }
}

void Scheduler::Finalize(){
//Gerar estatisticas
}

/*
void escalonarPaciente(Unidade& unidade, double momento_atual, double duracao_atendimento) {
    atualizarOciosidade(unidade, momento_atual);
    unidade.tempo_ocupado_total += duracao_atendimento;
    unidade.fim_atendimento = momento_atual + duracao_atendimento;
}
*/