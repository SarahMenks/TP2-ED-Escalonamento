#include "Scheduler.hpp"
#include <iostream>

Event::Event(){
    this->patiant = nullptr;
    this->event_time = 0;
}

Event::Event(Patiant *p, double time){
    this->patiant = p;
    this->type = p->status;
    this->event_time = time;
}

Scheduler::Scheduler(){
    this->heap = new Event[0];
    this->size = 0;
}

Scheduler::Scheduler(int maxsize){
    this->heap = new Event[maxsize];
    this->size = maxsize;
}

Scheduler::~Scheduler(){
    delete[] this->heap;
}

void Scheduler::ResizeHeap(int newsize) {
    Event* newheap = new Event[newsize];
    for (int i = 0; i < this->size; i++) {
        newheap[i] = this->heap[i];
    }
    delete[] this->heap;
    this->heap = newheap;
    this->size = newsize;
}

void Scheduler::CreateEvent(Patiant *p, double time){
    Event new_event(p, time);
    this->heap[this->size] = new_event;
    this->size++;
    LowHeapfy(this->size-1); 
}

Event Scheduler::RemoveNext(){
    if(this->size <= 0){
        throw "Heap vazio!";
    }

    Event aux = this->heap[0];
    this->heap[0] = this->heap[this->size-1];
    this->size--;
    HighHeapfy(0);
    return aux;
}

int Scheduler::GetParent(int position){
    if(this->size == 1)
        return 0;

    return (position-1)/2;
}

int Scheduler::GetLeftSucessor(int position){
    if(this->size == 1)
        return 0;
    
    return (position*2)+1;
}

int Scheduler::GetRightSucessor(int position){
    if(this->size == 1)
        return 0;
    
    return (position*2)+2;
}

void Scheduler::LowHeapfy(int position){
    if(position == 0)
        return;

    int position_parent = GetParent(position);
    //se o evento parent tiver um paciente com maior urgencia, mantem
    if(this->heap[position_parent].patiant->urgency > this->heap[position].patiant->urgency){
        return;
    }   
    //se o filho tiver maior urgencia ou o menor tempo, troca
    else if(this->heap[position] < this->heap[position_parent]){
        Event aux = this->heap[position];
        this->heap[position] = this->heap[position_parent];
        this->heap[position_parent] = aux;
        LowHeapfy(position_parent);
    }
}

void Scheduler::HighHeapfy(int position){
    if(GetLeftSucessor(position) >= this->size || GetRightSucessor(position) >= this->size)
        return;
    
    int esq = GetLeftSucessor(position);
    int dir = GetRightSucessor(position);
    int pos_menor = position;

    if((esq < this->size) && (this->heap[esq] < this->heap[pos_menor]) && (this->heap[esq] < this->heap[dir]))
        pos_menor = esq;

    if((dir < this->size) && (this->heap[dir] < this->heap[pos_menor]) && (this->heap[dir] < this->heap[esq]))
        pos_menor = dir;

    if(pos_menor != position){
        Event aux = this->heap[position];
        this->heap[position] = this->heap[pos_menor];
        this->heap[pos_menor] = aux; //talvez nao saiba copiar pacientes

        HighHeapfy(pos_menor);
    }
}

bool Scheduler::isEmpty(){
    return this->size == 0;
}

Event Scheduler::GetNext(){
    return this->heap[0];
}
