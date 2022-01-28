#include "Armazem.h"
Armazem::Armazem(const int capacidade, const int armazenamento):capacidade(capacidade),armazenamento(armazenamento) {}
bool Armazem::removeRecurso(const float quant) {
    if(armazenamento+quant>=0) {
        armazenamento -= quant;
        return true;
    }
    return false;
}

float Armazem::getArmazenado() const{
    return armazenamento;
}

bool Armazem::aumentaArmazenado(const float quant) {
    if(capacidade>0) { // se a capacidade for menor ou igual a 0 então é infinita
        if (armazenamento + quant <= capacidade) {
            armazenamento += quant;
            return true;
        }
        return false;
    }
    else{
        armazenamento += quant;
        return true;
    }
}

float Armazem::getCapacidade() {
    return capacidade;
}

void Armazem::setCapacidade(float novaCapacidade) {
    capacidade = novaCapacidade;
}