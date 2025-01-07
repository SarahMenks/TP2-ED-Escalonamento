#ifndef PACIENTE_HPP
#define PACIENTE_HPP

struct Paciente{
        int id;
        bool alta;
        int ano, mes, dia;
        float hora;
        int urgencia; //0 a 2
        int medidas_hosp;
        int testes;
        int exames;
        int medicamentos;

        int estado = 0; //vai de 0 a 13 (1 a 14)
        float tempo_fila, tempo_atendimento, tempo_ocioso; //paciente tem tempo ocioso?

        void Imprime();
};

/*quais e quantos procedimentos deve realizar, estado atual e as estatísticas de atendimento do paciente*/
//COlcoar int tempo na fila?

#endif