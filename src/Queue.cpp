#include "Queue.hpp"

Queue::Queue(){
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

Node_F::Node_F(Patiant *aux){
    this->p = aux;
    this->next = nullptr;
}

void Queue::Enqueue(Patiant *p){
    Node_F *nova = new Node_F(p);
    if(this->size == 0){
        this->head = nova;
        this->tail = nova;
    }
    else{
        this->tail->next = nova;
        this->tail = nova;
    }
    this->size++;
    p->status++;
}

void Queue::Remove(){
    if (this->size == 0)
        throw "Erro ao remover, a fila está vazia!";

    Node_F *aux = this->head;
    this->head = head->next;
    this->size--;

    if (this->size == 0){
        this->tail = nullptr; // Atualiza tail quando a fila se torna vazia
    }

    delete aux;  
}

bool Queue::isEmpty(){
    return size == 0; 
}
void Queue::Finalize(){}

Patiant* Queue::First(){
    return this->head->p;
}