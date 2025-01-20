#include "Queue.hpp"

Node_F::Node_F(Patiant *aux){
    this->p = aux;
    this->next = nullptr;
}

void Queue::Initialize(){
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
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
}

Patiant* Queue::Remove(){
    if (this->size == 0)
        throw "Fila está vazia!";

    Node_F *aux = this->head;
    this->head = head->next;
    this->size--;

    if (this->size == 0){
        this->tail = nullptr; // Atualiza tail quando a fila se torna vazia
    }

    Patiant* patiant = aux->p;
    delete aux;  

    return patiant;
}

bool Queue::isEmpty(){
    return size == 0; 
}
void Queue::Finalize(){}
