#include "Queue.hpp"

Node_F::Node_F(Patiant *aux){
    this->p = aux;
    this->next = nullptr;
}

void Queue::Initialize(){
    Patiant aux;  //provavelmente tirar
    Node_F *novo = new Node_F(&aux);
    this->head->next = novo;
    this->tail->next = novo;
}

void Queue::Enqueue(Patiant *p){
    Node_F *nova = new Node_F(p);
    this->tail->next = nova;
    this->tail = nova;
    this->size++;
}

void Queue::Dequeue(){
    if (this->size == 0)
        throw "Fila está vazia!";

    //int item = aux->id;
    Node_F *aux = this->head;
    this->head = head->next;
    delete aux;
    this->size--;
    //return item;
}

bool Queue::isEmpty(){
    return size == 0; 
}
void Queue::Finalize(){}
