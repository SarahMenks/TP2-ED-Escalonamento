#include "Scheduler.hpp"
#include <iostream>

Event::Event(){
    this->patiant = nullptr;
    this->event_date = 0;
}

Event::Event(Patiant *temp){
    this->patiant = temp;
    this->event_date = patiant->total_time;
}

Scheduler::Scheduler(int maxsize){
    this->heap = new Event[maxsize];
    this->size = 0;
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

void Scheduler::CreateEvent(Patiant *temp){
    Event new_event(temp);
    InsertEvent(new_event);
}

void Scheduler::InsertEvent(Event e){
    this->heap[this->size] = e;
    this->size++;
    LowHeapfy(this->size-1);    
}

Patiant* Scheduler::RemoveNext(){
    if(this->size == 0){
        std::cout << "Heap vazio!" << std::endl;
        throw "Heap vazio!";
    }

    Event aux = this->heap[0];
    this->heap[0] = this->heap[this->size-1];
    this->size--;
    HighHeapfy(0);
    return aux.patiant;
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

int Scheduler::GetNextTime(){
    return this->heap[0].event_date;
}
