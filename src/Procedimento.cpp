#include "Procedimento.hpp"
    
void Procedimento::Inicializa(float t, int quant){
        this->duracao = t;
        this->quant_unidades = quant;
        this->unidades = new Unidade[quant];
};

void Procedimento::AtualizaOciosidade(int num, float momento_atual){
    if(momento_atual > this->unidades[num].fim_atendimento)
        this->unidades[num].tempo_ocioso += (momento_atual - this->unidades[num].fim_atendimento);
}