#include "Escalonador.hpp"

Evento::Evento(){
    this->p = nullptr;
    this->ano = 0;
    this->mes = 0;
    this->dia = 0;
    this->hora = 0;
    this->estado = 0;
}

Evento::Evento(Paciente *temp){
    this->p = temp;
    this->ano = temp->ano;
    this->mes = temp->mes;
    this->dia = temp->dia;
    this->hora = temp->hora;
    this->estado = 0;
}

void Escalonador::Inicializa(int maxsize){
    this->heap = new Evento[maxsize];
    this->tamanho = 0;
}

void Escalonador::CriaEvento(Paciente *temp){
    Evento novo(temp);
    InsereEvento(novo);
}

void Escalonador::InsereEvento(Evento e){
    this->heap[this->tamanho] = e;
    this->tamanho++;
    HeapfyPorBaixo(this->tamanho-1);    
}

Evento Escalonador::RetiraProximoEvento(){
    Evento aux = this->heap[0];
    this->heap[0] = this->heap[this->tamanho-1];
    this->tamanho--;
    HeapfyPorCima(0);
    return aux;
}

int Escalonador::GetAncestral(int posicao){
    return (posicao-1)/2;
}

int Escalonador::GetSucessorEsq(int posicao){
    return (posicao*2)+1;
}

int Escalonador::GetSucessorDir(int posicao){
    return (posicao*2)+2;
}

void Escalonador::HeapfyPorBaixo(int posicao){
    if(posicao == 0)
        return;

    int posicao_pai = GetAncestral(posicao);
    //se o evento pai tiver um paciente com maior urgencia, mantes
    if(this->heap[posicao_pai].p->urgencia < this->heap[posicao].p->urgencia){
        return;
    }   
    //se o filho tiver maior urgencia ou o menor tempo, troca
    else if(this->heap[posicao].p->urgencia < this->heap[posicao_pai].p->urgencia || this->heap[posicao] < this->heap[posicao_pai]){
        Evento aux = this->heap[posicao];
        this->heap[posicao] = this->heap[posicao_pai];
        this->heap[posicao_pai] = aux;
        HeapfyPorBaixo(posicao_pai);
    }
}

void Escalonador::HeapfyPorCima(int posicao){
    int esq = GetSucessorEsq(posicao);
    int dir = GetSucessorDir(posicao);
    int pos_menor = posicao;

    if((dir < this->tamanho) && (this->heap[dir] < this->heap[pos_menor]) && (this->heap[dir] < this->heap[esq]) && (this->heap[dir].p->urgencia > this->heap[pos_menor].p->urgencia))
        pos_menor = dir;
    
    if((esq < this->tamanho) && (this->heap[esq] < this->heap[pos_menor]) && (this->heap[esq] < this->heap[dir]) && (this->heap[esq].p->urgencia > this->heap[pos_menor].p->urgencia))
        pos_menor = esq;

    if(pos_menor != posicao){
        Evento aux = this->heap[posicao];
        this->heap[posicao] = this->heap[pos_menor];
        this->heap[pos_menor] = aux; //talvez nao saiba copiar pacientes

        HeapfyPorCima(pos_menor);
    }
}

void Escalonador::Finaliza(){
//Gerar estatisticas
}

/*
void escalonarPaciente(Unidade& unidade, double momento_atual, double duracao_atendimento) {
    atualizarOciosidade(unidade, momento_atual);
    unidade.tempo_ocupado_total += duracao_atendimento;
    unidade.fim_atendimento = momento_atual + duracao_atendimento;
}
*/