#include <iostream>
#include <fstream>

using namespace std;

struct Pessoa{
    int a, b, c;

    void imprimePessoa();
};

void Pessoa::imprimePessoa(){
    cout << a << " " << b << " " << c << endl;
}

int teste(int *a, int b){
    *a = 10;
    b = 10;
}

int main(){
    int *a = new int;
    int b=0;
    teste(a, b);
    cout << *a << " " << b << endl;
    
    // string linha;
    // ifstream arquivo("teste.csv");

    // getline(arquivo, linha);
    // int tam = stoi(linha);

    // Pessoa* p = new Pessoa[tam];
    // int pos = 0;

    // while(arquivo >> p[pos].a >> p[pos].b >> p[pos].c){
    //     pos++;
    // }

    // for(int i = 0 ; i < tam ; i++){
    //     p[i].imprimePessoa();
    // }
    
    return 0;
}


