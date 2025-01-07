#ifndef FILA_HPP
#define FILA_HPP
#include "Paciente.hpp"

class Node_F{
    private:
        Paciente p;
        Node_F *next;
    public:
        Node_F(Paciente aux);

        friend class Fila;
};

class Fila{
    private:
        Node_F *head;
        Node_F *tail;
        int tamanho;
        int tempo_espera;

    public:
        void Inicializa();
        void Enfileira();
        void Desenfileira(); //talvez mudar o tipo para retornar o valor do elemento retirado?
        void FilaVazia();
        void Finaliza();
};

#endif