#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP
#include "Paciente.hpp"
#include <fstream>

struct Evento{
    int ano, mes, dia;
    float hora;
    int estado; //0 ao 13
    Paciente *p;

    Evento();
    Evento(Paciente *temp);

    bool operator < (Evento &e) const{
        return (this->ano <= e.ano, this->mes<= e.mes, this->dia <= e.dia && this->hora < e.hora);
    }
};

class Escalonador{
    private:
        Evento *heap;
        int tamanho;
        void HeapfyPorBaixo(int posicao);
        void HeapfyPorCima(int posicao); 

    public:
        void CriaEvento(Paciente *temp);
        void Inicializa(int maxsize);
        void InsereEvento(Evento evento);
        Evento RetiraProximoEvento();
        int GetAncestral(int posicao); 
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);
        void Finaliza();
};

#endif