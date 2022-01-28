#include "Zona.h"
#include "Recursos.h"
#include "Ilha.h"
// "dsr","pas","flr","mnt","pnt","znZ"

Zona::~Zona() {

    for(auto & t : tipoTrabalhadores){
        delete t;
    }
    tipoTrabalhadores.clear();
    destroiEdificio(getEdificio());
}

void Zona::setEdificio(Edificios* edificio) {
	this->edificio = edificio;
	
}

void Zona::addRecursos(const array<Recursos*, 7> recursos){}

void Zona::setTrabalhador(Trabalhadores* trabalhador) {
    tipoTrabalhadores.push_back(trabalhador);
    nTrabalhadores++;
}

Edificios* Zona::getEdificio() const{
    return edificio;
}


vector<Trabalhadores*> Zona::getTipoTrabalhadores(){
    return tipoTrabalhadores;
}

int Zona::getNTrabalhadores() const{
    return nTrabalhadores;
}

void Zona::setlocalizacao(int linha, int coluna) {
    this->linha=linha;
    this->coluna=coluna;
}

Zona::Zona(string nome, const array<Recursos*, 7> recursos,Ilha& ilha,int capacidade, int armazenamento): Armazem(capacidade,armazenamento),nomeZona(nome),ilha(&ilha),nTrabalhadores(0),edificio(nullptr),recursos(recursos){}

Floresta::Floresta(string nome, const array<Recursos*, 7> recursos,Ilha& ilha):Zona(nome, recursos,ilha,100,0), nLenhadores(0), maxArvores(100) {
    std::random_device rd;
    uniform_int_distribution<> d(20, 40);
    mt19937 gen{rd()};
    nArvores = d(gen);
}
Floresta::Floresta(const Floresta& outro):Zona(outro), nLenhadores(outro.nLenhadores), maxArvores(outro.maxArvores) {
    std::random_device rd;
    uniform_int_distribution<> d(20, 40);
    mt19937 gen{rd()};
    nArvores = d(gen);

}
Pastagem::Pastagem(string nome, const array<Recursos*, 7> recursos,Ilha& ilha):Zona(nome, recursos,ilha,100,0) {}
Montanha::Montanha(string nome, const array<Recursos*, 7> recursos,Ilha& ilha):Zona(nome, recursos,ilha,100,0) {}
Deserto::Deserto(string nome, const array<Recursos*, 7> recursos,Ilha& ilha):Zona(nome, recursos,ilha,100,0) {}
Pantano::Pantano(string nome, const array<Recursos*, 7> recursos,Ilha& ilha):Zona(nome, recursos,ilha,100,0) {}
ZonaX::ZonaX(string nome, const array<Recursos*, 7> recursos,Ilha& ilha):Zona(nome, recursos,ilha,100,0) {}

Zona* Zona::cloneZona() {return new Zona(*this);}
Floresta* Floresta::cloneZona() {return new Floresta(*this);}
void Floresta::addRecursos(const array<Recursos*, 7> recursos){
    recursos[3]->setRecurso(recursos[3]->getRecurso() + armazenamento);
}

void Floresta::extrai() {
    for(auto i : getTipoTrabalhadores()){
        nLenhadores=0;
        if(i->getSimbolo() == 'L' && !i->isDescanso()) {
            nLenhadores++;
        }
    }
    if(nArvores>0) {
        if (getEdificio() == nullptr) {
            if (nLenhadores) {
                aumentaArmazenado(1 * nLenhadores);

            }
        }
        else{
            nArvores--;
            if (nLenhadores) {
                aumentaArmazenado(1 * nLenhadores);
            }
        }

    }
}
void Floresta::cresceArvore(int nDia) {
    if(nArvores + 1 <= maxArvores){
        if(nDia%2 == 0)
            nArvores++;
    }
}
void Montanha::extrai() {
    aumentaArmazenado(0.1 * getNTrabalhadores());
}
Pastagem* Pastagem::cloneZona() {return new Pastagem(*this);}
void Pastagem::addRecursos(const array<Recursos*, 7> recursos){
}
Deserto* Deserto::cloneZona() {return new Deserto(*this);}
void Deserto::addRecursos(const array<Recursos*, 7> recursos){
}

float Zona::getMultiplier(Recursos* recursoExtraido) { return 0; }

float Pastagem::getMultiplier(Recursos *recursoExtraido) {
    return 1.0;
}

float Pastagem::getMultiplerDemissao(Trabalhadores *trabalhador) {
    static map<char ,float> multipliers{
            {'L', trabalhador->getProbIrEmbora() * 0},
            {'O',trabalhador->getProbIrEmbora() * 0},
            {'M',trabalhador->getProbIrEmbora() * 0}
    };
    auto it = multipliers.find((trabalhador->getSimbolo()));
    if(it != multipliers.end())
        return it->second;
    else
        return trabalhador->getProbIrEmbora();
}

float Floresta::getMultiplier(Recursos *recursoExtraido) {
    return 1.0;
}

void Floresta::efeito(int nDia) {
    cresceArvore(nDia);
}

float Pantano::getMultiplier(Recursos *recursoExtraido) {
    return 1.0;
}

float ZonaX::getMultiplier(Recursos *recursoExtraido) {
    return 1.0;
}
float Deserto::getMultiplier(Recursos* recursoExtraido) {
    static map<Recursos*, float> multipliers{
            {recursos[0],0.50},
            {recursos[2],0.50}
    };

    auto it = multipliers.find((recursoExtraido));
    if(it != multipliers.end())
        return it->second;
    else
        return 1.0;


}

float Montanha::getMultiplier(Recursos *recursoExtraido) {
    static map<Recursos*, float> multipliers{
            {recursos[0],2.0},
            {recursos[2],2.0}
    };

    auto it = multipliers.find((recursoExtraido));
    if(it != multipliers.end())
        return it->second;
    else
        return 1.0;


}

Montanha* Montanha::cloneZona() {return new Montanha(*this);}

void Montanha::addRecursos(const array<Recursos*, 7> recursos){
	recursos[0]->setRecurso(recursos[0]->getRecurso()+armazenamento);
}

void Montanha::efeito(int nDia) {
    aumentaArmazenado(0.1 * getNTrabalhadores());
}
float Montanha::getMultiplerDemissao(Trabalhadores *trabalhador) {
    static map<char ,float> multipliers{
            {'L', trabalhador->getProbIrEmbora() + 5},
            {'O',trabalhador->getProbIrEmbora() + 5},
            {'M',trabalhador->getProbIrEmbora() + 5}
    };
    auto it = multipliers.find((trabalhador->getSimbolo()));
    if(it != multipliers.end())
        return it->second;
    else
        return trabalhador->getProbIrEmbora();
}

Pantano* Pantano::cloneZona() {return new Pantano(*this);}
void Pantano::addRecursos(const array<Recursos*, 7> recursos){
}

void Pantano::efeito(int nDia) {
    if(nDia%10 == 0){
        destroiEdificio(getEdificio());
        bool found{false};
        for(auto& i : getTipoTrabalhadores()){
            sendPurgatorio(i,nDia);
        }
    }
}

ZonaX* ZonaX::cloneZona() {return new ZonaX(*this);}
void ZonaX::addRecursos(const array<Recursos*, 7> recursos){
}

void ZonaX::extrai() {
    aumentaArmazenado(5 * getNTrabalhadores());
}

string Zona::getNomeZona() const{
    return nomeZona;
}

vector<Zona *> Zona::getAdjacente() {
    vector<Zona*> zonasAdjacentes;
    std::cout << linha << coluna;
    if(ilha->getZona(linha-1,coluna) != nullptr)
        zonasAdjacentes.emplace_back(ilha->getZona(linha-1,coluna)); // cima
    if(ilha->getZona(linha+1,coluna) != nullptr)
        zonasAdjacentes.emplace_back(ilha->getZona(linha+1,coluna));// baixo
    if(ilha->getZona(linha,coluna+1) != nullptr)
        zonasAdjacentes.emplace_back(ilha->getZona(linha,coluna+1)); // direita
    if(ilha->getZona(linha,coluna-1) != nullptr)
        zonasAdjacentes.emplace_back(ilha->getZona(linha,coluna-1)); // esquerda

    return zonasAdjacentes;
}

float Zona::getMultiplerDemissao(Trabalhadores *trabalhador) {
    return trabalhador->getProbIrEmbora();
}

void Zona::destroiEdificio(Edificios* novoEdificio) {
    delete novoEdificio;
    edificio = nullptr;
}

bool Zona::killTrabalhador(int id) {
    auto trabalhador = find_if(tipoTrabalhadores.begin(),tipoTrabalhadores.end(),[=](const Trabalhadores* tra){
        return tra->getId() == id;
    });
    if(trabalhador != tipoTrabalhadores.end()){
        delete *trabalhador;
        tipoTrabalhadores.erase(trabalhador);
        nTrabalhadores--;
        return true;
    }
    return false;
}

Trabalhadores* Zona::getTrabalhador(int id) const {
    auto trabalhador = find_if(tipoTrabalhadores.begin(),tipoTrabalhadores.end(),[=](const Trabalhadores* tra){
        return tra->getId() == id;
    });
    if(trabalhador != tipoTrabalhadores.end()){
        return *trabalhador;
    }
    return nullptr;
}

void Zona::efeito(int nDia) {

}

void Zona::sendPurgatorio(Trabalhadores* trabalhador,int nDia) {
    bool found{false};
    for(int j{1} ; j < ilha->getLinhas();j++){
        for(int k{1}; k < ilha->getColunas();k++){
            if(ilha->getZona(j,k)->getNomeZona() == "pur"){
                Trabalhadores* clone {trabalhador->cloneTrabalhador(1,nDia)};
                ilha->getZona(j,k)->setTrabalhador(clone);
                clone->setZona(ilha->getZona(j,k));
                killTrabalhador(trabalhador->getId());
                found=true;
                break;
            }
        }
        if(found)
            break;
    }
}


Zona::Zona(const Zona& outro): Armazem(outro) {
    if(this==&outro){
        *this = outro;
        return;
    }
    linha = outro.linha;
    coluna = outro.coluna;
    nomeZona = outro.nomeZona;
    nTrabalhadores = outro.nTrabalhadores;
    recursos = outro.recursos;
    ilha = outro.ilha;

    if(outro.edificio != nullptr){
        edificio = outro.edificio->cloneEdificios(); // clona edificio
        edificio->MudaZona(this); // mete o a apontar para a zona copiada
    }
    else{
        edificio = nullptr;
    }
    tipoTrabalhadores.clear();
    for(auto& i : outro.tipoTrabalhadores){
        tipoTrabalhadores.emplace_back(i->cloneTrabalhador(1,i->getDiaContrato()));
    }
    for(auto& i : tipoTrabalhadores){
        i->setZona(this);
    }
}

void Zona::setIlha(Ilha& ilha) {
    this->ilha = &ilha;
}


