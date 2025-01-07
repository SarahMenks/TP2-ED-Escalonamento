#include <iostream>
#include <fstream>
#include <ctime>
#include "Paciente.hpp"
#include "Procedimento.hpp"
#include "Escalonador.hpp"
#include "Fila.hpp"

using namespace std;

void InicializaProcedimentos(ifstream &arquivo, Procedimento &triagem, Procedimento &atendimento, Procedimento &medhosp, Procedimento &teste, Procedimento &exame, Procedimento &medic){
    float tempo;
    int quant;
    
    arquivo >> tempo >> quant;
    triagem.Inicializa(tempo, quant);
    
    arquivo >> tempo >> quant;
    atendimento.Inicializa(tempo, quant);

    arquivo >> tempo >> quant;
    medhosp.Inicializa(tempo, quant);

    arquivo >> tempo >> quant;
    teste.Inicializa(tempo, quant);

    arquivo >> tempo >> quant;
    exame.Inicializa(tempo, quant);

    arquivo >> tempo >> quant;
    medic.Inicializa(tempo, quant);

}

int main(int argc, char const *argv[]){

    Procedimento triagem, atendimento, medhosp, teste, exame, medic;
    Escalonador esc;

    ifstream arquivo(argv[1]);
    if (!(arquivo.is_open())){
        cout << "Cannot open file" << endl;
        exit(1);
    }

    InicializaProcedimentos(arquivo, triagem, atendimento, medhosp, teste, exame, medic);
    
    //registra pacientes
    int tam;
    arquivo >> tam;
    Paciente *pacientes = new Paciente[tam];
    esc.Inicializa(tam);

    for(int pos=0; pos < tam ; ++pos){
        //arquivo >> pacientes[pos].id >> pacientes[pos].alta >> pacientes[pos].ano >> pacientes[pos].mes >> pacientes[pos].dia >> pacientes[pos].hora >> pacientes[pos].urgencia >> pacientes[pos].medidas_hosp >> pacientes[pos].testes >> pacientes[pos].exames >> pacientes[pos].medicamentos;
        
        
        esc.CriaEvento(&pacientes[pos]);
    }

//cada procedimento vai ter uma fila
/*
Inicializa Condição de Término para FALSO
Inicializa as variáveis de estado do sistema
Inicializa o Relógio (usualmente zero)
Escalona a chegada de pacientes
Enquanto houver eventos ou filas não vazias
    Remove o próximo evento do escalonador
    Avança o relógio para o instante do próximo evento
    Verifica o próximo estado do paciente
    Se houver mais serviços para paciente
        Enfileira o paciente na fila adequada
    Senão
        Finaliza o atendimento (Alta Hospitalar)
        
    Para cada fila de espera que tenha pacientes
        Se há unidade disponível para execução
            Escalonar o evento de execução do serviço
    Atualizar as estatísticas
Fim 
Gerar relatórios de estatísticas
*/

    


    arquivo.close();

    return 0;
}


//time_t t
//cout << ctime(&t) << endl;