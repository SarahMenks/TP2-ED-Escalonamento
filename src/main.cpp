#include <iostream>
#include <fstream>
#include <ctime>
#include "System.hpp"

using namespace std;

void InitializeProcedures(ifstream &file, Procedure &triagem, Procedure &atendimento, Procedure &medhosp, Procedure &teste, Procedure &exame, Procedure &medic){
    float time;
    int quant;
    
    file >> time >> quant;
    triagem.Inicialize(time, quant);
    
    file >> time >> quant;
    atendimento.Inicialize(time, quant);

    file >> time >> quant;
    medhosp.Inicialize(time, quant);

    file >> time >> quant;
    teste.Inicialize(time, quant);

    file >> time >> quant;
    exame.Inicialize(time, quant);

    file >> time >> quant;
    medic.Inicialize(time, quant);
}

int main(int argc, char const *argv[]){

    System S_Hospital;

    ifstream file(argv[1]);
    if (!(file.is_open())){
        cout << "Cannot open file" << endl;
        exit(1);
    }
    

    InitializeProcedures(file, triagem, atendimento, medhosp, teste, exame, medic);
    
    //registra pacientes
    int tam;
    file >> tam;
    Patiant *patiants = new Patiant[tam];
    esc.Initialize(tam);

    for(int pos=0; pos < tam ; ++pos){
        //file >> pacientes[pos].id >> pacientes[pos].alta >> pacientes[pos].ano >> pacientes[pos].mes >> pacientes[pos].dia >> pacientes[pos].hora >> pacientes[pos].urgencia >> pacientes[pos].medidas_hosp >> pacientes[pos].testes >> pacientes[pos].exames >> pacientes[pos].medicamentos;
        
        
        esc.CreateEvent(&patiants[pos]);
    }

//cada Procedure vai ter uma fila
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

    


    file.close();

    return 0;
}


//time_t t
//cout << ctime(&t) << endl;