#include "System.hpp"

// System::System(){
// }

// System::~System(){

// }



void System::InitializeScheduler(Patiant *p, int num_patiants){
    
}


void System::SetTriagem(float time, int quant){
    this->triagem.Inicialize(time, quant);
}
void System::SetAtendimento(float time, int quant){
    this->atendimento.Inicialize(time, quant);
}
void System::SetMedHosp(float time, int quant){
    this->medhosp.Inicialize(time, quant);
}
void System::SetTeste(float time, int quant){
    this->teste.Inicialize(time, quant);
}
void System::SetExame(float time, int quant){
    this->exame.Inicialize(time, quant);
}
void System::SetMedic(float time, int quant){
    this->medic.Inicialize(time, quant);
}
