#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP

struct Unidade{
    float tempo_ocupado;
    float tempo_ocioso;
    float fim_atendimento;
};

class Procedimento{
    private:
        float duracao;
        int quant_unidades;
        Unidade* unidades;
    
    public:
        void Inicializa(float t, int quant);
        void AtualizaOciosidade(int num, float tempo);
};
//registrar a utilização de cada unidade de cada procedimento
//e/ou seu tempo ocioso. 
//manter a data hora até a qual cada unidade está ocupada.

#endif