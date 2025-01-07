#include "Fila.hpp"

Node_F::Node_F(Paciente aux){
    this->p = aux;
    this->next = nullptr;
}


void Fila::Inicializa(){
    Node_F *novo = new Node_F();
    this->head->next = novo;
    this->tail->next = novo;
}

void Fila::Enfileira(){
    Node_F *nova = new Node_F();
    this->tail->next = nova;
    this->tail = nova;
    this->tamanho++;
}

void Fila::Desenfileira(){
    if (this->tamanho == 0)
        throw "Fila está vazia!";

    //int item = aux->id;
    Node_F *aux = this->head;
    this->head = head->next;
    delete aux;
    this->tamanho--;
    //return item;
}

void Fila::FilaVazia(){}
void Fila::Finaliza(){}
