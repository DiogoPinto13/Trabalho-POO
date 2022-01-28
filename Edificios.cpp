#include "Edificios.h"
#include "Recursos.h"
#include "Zona.h"
#include <algorithm>
// #################################### CONSTRUTORES #######################################

Edificios::Edificios(const string& nome, const array<Recursos*, 7> recursos,const float capacidade,const float armazenamento,bool upgradable) : Armazem(capacidade,armazenamento),nome(nome),ligado(0),podeMelhorar(upgradable), recursos(recursos),nivel(0){
}


MinaFerro::MinaFerro(const string& nome, const array<Recursos*, 7> recursos) : Edificios(nome, recursos,100,0, true),probDesabar(15){
    custo = {
            {{recursos[4],recursos[6]},{10,10}}
    };

    upgradeCusto={ { recursos[6],15} ,{recursos[4],1}};
}

MinaCarvao::MinaCarvao(const string& nome, const array<Recursos*, 7> recursos) : Edificios(nome, recursos,100,0, true),probDesabar(10) {
    custo = {
            {{recursos[4],recursos[6]},{10,10}}
    };
    upgradeCusto={ { recursos[6],10} ,{recursos[4],1}};
}

CentralEletrica::CentralEletrica(const string& nome, const array<Recursos*, 7> recursos) : Edificios(nome, recursos,100,0, false){
    custo = {
            {{recursos[6],nullptr},{15,NULL}}
    };

}

Bateria::Bateria(const string& nome, const array<Recursos*, 7> recursos) : Edificios(nome, recursos,100,0,false){
    custo = {
            {{recursos[6],nullptr},{10,NULL}},
            {{recursos[4],nullptr},{10,NULL}}
    };
    upgradeCusto={ { recursos[6],5}};

}

Fundicao::Fundicao(const string& nome, const array<Recursos*, 7> recursos) : Edificios(nome, recursos,100,0,false) {
    custo = {
            {{recursos[6],nullptr},{10,NULL}}
    };

}

EdificioX::EdificioX(const string& nome, const array<Recursos*, 7> recursos) : Edificios(nome, recursos,100,0,false) {

}

/*
pair< map<Recursos*, float>, map<Recursos*, float> > Edificios::getCusto() {
    return make_pair(custoConstruir,custoSubstitui);
}
*/

void Edificios::MudaZona(Zona* novaZona) {
    zona=novaZona;
}
string Edificios::getNome() const {
    return nome;
}

void Edificios::setLigado(const bool estado) {
    ligado = estado;
}

const map<tuple<Recursos *, Recursos *>, tuple<float, float>> &Edificios::getCusto() const {
    return custo;
}

const vector<tuple<Recursos *, float> > &Edificios::getUpgradeCusto() const {
    return upgradeCusto;
}

bool Edificios::upgrade() {
    if(podeMelhorar && nivel < 5){ // and nivel < nivelmax
        nivel++;
        capacidade+=10;
        return true;
    }
    return false;
}

bool Edificios::setCusto(int euro) {
    for(auto& i : custo){
        if(get<0>(i.first) == recursos[6] ){
            i.second = tuple<float,float>{euro,get<1>(i.second)};
            return true;
        }
        else{
           if(get<1>(i.first) == recursos[6]){
               i.second = tuple<float,float>{get<0>(i.second),euro};

               return true;
           }
        }
    }
    return false;
}

bool Edificios::isLigado() const {
    return ligado;
}

void Edificios::evento(int ndia) {

}

void Edificios::setListaRecursos(const array<Recursos*, 7>& listarecursos) {
    recursos = listarecursos;
}

void Edificios::updatecusto(array<Recursos *, 7> listarecursos) {
    map<tuple<Recursos*,Recursos*>, tuple<float,float>> recursostemp;
    for(int i{0};i< listarecursos.size();i++){
        for(auto& j : custo){
            if(get<0>(j.first) != nullptr)
            {
                if (get<0>(j.first)->getAbreviatura() == listarecursos[i]->getAbreviatura()) {
                    recursostemp.emplace(tuple<Recursos*, Recursos*>(listarecursos[i],get<1>(j.first)), tuple<float, float>(get<0>(j.second),get<1>(j.second)));
                }
                else{
                    if(get<1>(j.first) != nullptr){
                        if(get<1>(j.first)->getAbreviatura() == listarecursos[i]->getAbreviatura()){
                            recursostemp.emplace(tuple<Recursos*, Recursos*>(get<0>(j.first),listarecursos[i]), tuple<float, float>(get<0>(j.second),get<1>(j.second)));
                        }
                    }
                }
            }
        }
    }
    vector<tuple<Recursos*, float>> upgradetemp;

        for(auto& j : upgradeCusto){
            for(int i{0};i<listarecursos.size();i++){
                if(get<0>(j)->getAbreviatura() == listarecursos[i]->getAbreviatura()){
                    upgradetemp.emplace_back(tuple<Recursos*, float>(listarecursos[i],get<1>(j)));
                }
            }
        }

    custo = recursostemp;
    upgradeCusto= upgradetemp;
}

Edificios::Edificios(const Edificios &outro) : Armazem(outro) {
    podeMelhorar = outro.podeMelhorar;
    nivel = outro.nivel;
    ligado = outro.ligado;
    nome = outro.nome;
    recursos = outro.recursos;
    upgradeCusto = outro.upgradeCusto;
    custo = outro.custo;
    zona = outro.zona;
}

const int Edificios::getNivel() const {
    return nivel;
}

/*
Edificios* Edificios::cloneEdificios() {
	return new Edificios(*this);
}
void Edificios::addRecursos(const array<Recursos*, 7> recursos){}
*/
/*
Edificios* EdificiosUp::cloneEdificios() {
	return new EdificiosUp(*this);
}

void EdificiosUp::addRecursos(const array<Recursos*, 7> recursos){}
*/
Edificios* MinaFerro::cloneEdificios() {
    return new MinaFerro(*this);
}

Recursos * MinaFerro::addRecursos(const array<Recursos*, 7> recursos){
    recursos[0]->setRecurso(recursos[0]->getRecurso() + armazenamento);
    armazenamento=0;
    return recursos[0];
}


Edificios* MinaCarvao::cloneEdificios() {
    return new MinaCarvao(*this);
}
Recursos * MinaCarvao::addRecursos(const array<Recursos*, 7> recursos){
    recursos[2]->setRecurso(recursos[2]->getRecurso() + armazenamento);
    armazenamento=0;
    return recursos[2];
}


Edificios* CentralEletrica::cloneEdificios() {
    return new CentralEletrica(*this);
}
Recursos * CentralEletrica::addRecursos(const array<Recursos*, 7> recursos){
    recursos[2]->setRecurso(recursos[2]->getRecurso() + armazenamento);
    armazenamento=0;
    return recursos[2];
}


Edificios* Bateria::cloneEdificios() {
    return new Bateria(*this);
}
Recursos * Bateria::addRecursos(const array<Recursos*, 7> recursos){
    recursos[5]->setRecurso(recursos[5]->getRecurso() + armazenamento);
    armazenamento=0;
    return recursos[5];
}




map<string,bool(Armazem::*)(const float)> CentralEletrica::funcs{
        {"bat",&Armazem::aumentaArmazenado},
        {"flr",&Armazem::removeRecurso},
};
map<string,string> CentralEletrica::relacoes{
        {"bat","flr"},
};
map<string,float> CentralEletrica::funcs_parameters{
        {"bat", 1},
        {"flr", 1},
};

map<string,bool(Armazem::*)(const float)> Fundicao::funcs{
        {"mnC",&Armazem::removeRecurso},
        {"elec",&Armazem::removeRecurso},
        {"mnF",&Armazem::removeRecurso}
};

map<string,string> Fundicao::relacoes{
        {"mnC","elec"},
        {"mnF",""}

};
map<string,float> Fundicao::funcs_parameters{
        {"mnC", 1},
        {"mnF", 1.5},
};

map<string,bool(Armazem::*)(const float)> Serraria::funcs{
        {"flr",&Armazem::removeRecurso},
};

map<string,string> Serraria::relacoes{
        {"flr",""},

};
map<string,float> Serraria::funcs_parameters{
        {"flr", 1},
};

Edificios* Fundicao::cloneEdificios() {
    return new Fundicao(*this);
}
Recursos * Fundicao::addRecursos(const array<Recursos*, 7> recursos){
    recursos[1]->setRecurso(recursos[1]->getRecurso() + armazenamento);
    armazenamento=0;
    return recursos[1];
}



Edificios* EdificioX::cloneEdificios() {
    return new EdificioX(*this);
}

Recursos * EdificioX::addRecursos(const array<Recursos*, 7> recursos){
    recursos[6]->setRecurso(13);
    return recursos[6];
}



// ###################   EXTRACAO DE RECURSOS ######################
void MinaFerro::extrai() {
    if(ligado){
        auto trabalhadores = zona->getTipoTrabalhadores();
        auto it = find_if(trabalhadores.begin(), trabalhadores.end(),[](const Trabalhadores *trabalhador) {
            return ('M' == trabalhador->getSimbolo());
        });

        if (it != zona->getTipoTrabalhadores().end()) {
            aumentaArmazenado((2 + nivel * 1) * zona->getMultiplier(recursos[0]));
        }
    }


}

void MinaFerro::evento(int ndia) {
    desabar();
}

void MinaFerro::desabar() {
    random_device rd;
    uniform_int_distribution<> d(1, 100);
    mt19937 gen{rd()};
    if(d(gen) <= probDesabar){
        zona->destroiEdificio(this);
    }
}
void MinaCarvao::evento(int ndia) {
    desabar();
}

void MinaCarvao::desabar() {
    random_device rd;
    uniform_int_distribution<> d(1, 100);
    mt19937 gen{rd()};
    if(d(gen) <= probDesabar){
        zona->destroiEdificio(this);
    }
}

void MinaCarvao::extrai() {
    if(ligado){
        auto trabalhadores = zona->getTipoTrabalhadores();
        auto it = find_if(trabalhadores.begin(), trabalhadores.end(),[](const Trabalhadores *trabalhador) {
            return ('M' == trabalhador->getSimbolo());
        });

        if (it != zona->getTipoTrabalhadores().end()) {
            aumentaArmazenado((2 + nivel * 1) * zona->getMultiplier(recursos[2]));
        }
    }
}

void CentralEletrica::extrai(){

    if(ligado){
        if(armazenamento + 1 * zona->getMultiplier(recursos[3]) <= capacidade) {
            auto trabalhadores = zona->getTipoTrabalhadores();
            auto it = find_if(trabalhadores.begin(), trabalhadores.end(),
                              [](const Trabalhadores *trabalhador) {
                                  return ('O' == trabalhador->getSimbolo());
                              });

            if (it != zona->getTipoTrabalhadores().end()) {
                auto zonasAdjacentes = zona->getAdjacente();
                auto funcs_copy = funcs;
                auto relacoes_copy = relacoes;
                vector<Zona*> removidos;
                //loop de removes
                for(auto zona : zonasAdjacentes){
                    if(zona != nullptr){
                        if(zona->getEdificio()!= nullptr){
                            auto func_edificio = funcs_copy.find(zona->getEdificio()->getNome()); // encontrar edificio no mapa
                            if(func_edificio!=funcs_copy.end() && func_edificio->second == &Armazem::removeRecurso){ // ver se a funcao é de remove e se existe
                                auto func_parameter = funcs_parameters.find(zona->getEdificio()->getNome()); // quantidade para remover
                                if(zona->getEdificio()->getArmazenado() >= func_parameter->second){
                                    (zona->getEdificio()->*(func_edificio->second))(func_parameter->second); // chamar funçao no mapa(remove neste caso)
                                    removidos.emplace_back(zona);
                                    funcs_copy.erase(zona->getEdificio()->getNome());
                                    for(auto it{relacoes_copy.begin()};it != relacoes_copy.end(); ) { // iterar mapa para encontrar sitio onde se remove
                                        if (it->second == zona->getEdificio()->getNome() || it->first == zona->getEdificio()->getNome()) {
                                            it = relacoes_copy.erase(it);
                                        }
                                        else{
                                            ++it;
                                        }

                                    }
                                }
                            }
                        }
                        auto func_zona = funcs_copy.find(zona->getNomeZona());
                        if(func_zona != funcs_copy.end() && func_zona->second == &Armazem::removeRecurso) {
                            auto func_parameter = funcs_parameters.find(zona->getNomeZona()); // quantidade para remover
                            if(zona->getArmazenado() >= func_parameter->second){
                                //armazenamento += 1 * zona->getMultiplier(recursos[3]); // adicionar 1 kg de carvao sempre que se remove de algum lado
                                (zona->*(func_zona->second))(func_parameter->second); // chamar funçao no mapa(remove neste caso)
                                funcs_copy.erase(zona->getNomeZona());
                                removidos.emplace_back(zona);
                                for(auto it{relacoes_copy.begin()};it != relacoes_copy.end(); ) { // iterar mapa para encontrar sitio onde se remove
                                    if (it->second == zona->getNomeZona() || it->first == zona->getNomeZona()) {
                                        it = relacoes_copy.erase(it);
                                    }
                                    else{
                                        ++it;
                                    }
                                }
                            }
                        }
                    }
                }

                if(!relacoes_copy.empty()){
                    for(auto zona : removidos){
                        if(zona->getEdificio() != nullptr) {
                            zona->getEdificio()->aumentaArmazenado((funcs_parameters.find(zona->getEdificio()->getNome()))->second);
                        }
                        zona->aumentaArmazenado(funcs_parameters.find(zona->getNomeZona())->second);
                    }
                }
                else {
                    aumentaArmazenado(1 * zona->getMultiplier(recursos[3]));
                    // loop de adds
                    for (auto zona: zonasAdjacentes) {
                        if (zona != nullptr) {
                            if (zona->getEdificio() != nullptr) {
                                auto func_edificio = funcs_copy.find(zona->getEdificio()->getNome());
                                if (func_edificio != funcs_copy.end() && func_edificio->second == &Armazem::aumentaArmazenado) {
                                    auto func_parameter = funcs_parameters.find(zona->getEdificio()->getNome());
                                    auto existe = relacoes_copy.find(zona->getEdificio()->getNome());
                                    if (existe == relacoes_copy.end()) { // se chegou ao fim das relacoes entao o remove foi sucessfull
                                        (zona->getEdificio()->*(func_edificio->second))(func_parameter->second);
                                        funcs_copy.erase(func_edificio);
                                    }
                                }
                            }
                            auto func_zona = funcs_copy.find(zona->getNomeZona());
                            if (func_zona != funcs_copy.end() && func_zona->second == &Armazem::aumentaArmazenado) {
                                auto func_parameter = funcs_parameters.find(zona->getNomeZona());
                                auto existe = relacoes_copy.find(zona->getNomeZona());
                                if (existe == relacoes_copy.end()) { // se chegou ao fim das relacoes entao o remove foi sucessfull
                                    (zona->getEdificio()->*(func_zona->second))(func_parameter->second);
                                    funcs_copy.erase(func_zona);
                                }
                            }

                        }
                    }
                }

            }
        }
    }

}

void Fundicao::extrai() {
    if(ligado){
        if(armazenamento + 1 * zona->getMultiplier(recursos[2]) <= capacidade) {
            auto trabalhadores = zona->getTipoTrabalhadores();
            auto it = find_if(trabalhadores.begin(), trabalhadores.end(),
                              [](const Trabalhadores *trabalhador) {
                                  return ('O' == trabalhador->getSimbolo());
                              });

            if (it != zona->getTipoTrabalhadores().end()) {
                auto zonasAdjacentes = zona->getAdjacente();
                auto funcs_copy = funcs;
                auto relacoes_copy = relacoes;
                vector<Zona*> removidos;
                //loop de removes
                for(auto zona : zonasAdjacentes){
                    if(zona != nullptr){
                        if(zona->getEdificio()!= nullptr){
                            auto func_edificio = funcs_copy.find(zona->getEdificio()->getNome()); // encontrar edificio no mapa
                            if(func_edificio!=funcs_copy.end() && func_edificio->second == &Armazem::removeRecurso){ // ver se a funcao é de remove e se existe
                                auto func_parameter = funcs_parameters.find(zona->getEdificio()->getNome()); // quantidade para remover
                                if(zona->getEdificio()->getArmazenado() >= func_parameter->second){
                                    //armazenamento += 1 * zona->getMultiplier(recursos[3]); // adicionar 1 kg de carvao sempre que se remove de algum lado
                                    (zona->getEdificio()->*(func_edificio->second))(func_parameter->second); // chamar funçao no mapa(remove neste caso)
                                    removidos.emplace_back(zona);
                                    funcs_copy.erase(zona->getEdificio()->getNome());
                                    for(auto it{relacoes_copy.begin()};it != relacoes_copy.end(); ) { // iterar mapa para encontrar sitio onde se remove
                                        if (it->second == zona->getEdificio()->getNome() || it->first == zona->getEdificio()->getNome()) {
                                            it = relacoes_copy.erase(it);
                                        }
                                        else{
                                            ++it;
                                        }

                                    }
                                }
                            }
                        }
                        auto func_zona = funcs_copy.find(zona->getNomeZona());
                        if(func_zona != funcs_copy.end() && func_zona->second == &Armazem::removeRecurso) {
                            auto func_parameter = funcs_parameters.find(zona->getNomeZona()); // quantidade para remover
                            if(zona->getArmazenado() >= func_parameter->second){
                                (zona->*(func_zona->second))(func_parameter->second); // chamar funçao no mapa(remove neste caso)
                                funcs_copy.erase(zona->getNomeZona());
                                removidos.emplace_back(zona);
                                for(auto it{relacoes_copy.begin()};it != relacoes_copy.end(); ) { // iterar mapa para encontrar sitio onde se remove
                                    if (it->second == zona->getNomeZona() || it->first == zona->getNomeZona()) {
                                        it = relacoes_copy.erase(it);
                                    }
                                    else{
                                        ++it;
                                    }
                                }
                            }
                        }
                    }
                }

                if(!relacoes_copy.empty()){
                    for(auto zona : removidos){
                        if(zona->getEdificio() != nullptr) {
                            zona->getEdificio()->aumentaArmazenado((funcs_parameters.find(zona->getEdificio()->getNome()))->second);
                        }
                        zona->aumentaArmazenado(funcs_parameters.find(zona->getNomeZona())->second);
                    }
                }
                else {
                    aumentaArmazenado(1 * zona->getMultiplier(recursos[2]));
                    // loop de adds
                    for (auto zona: zonasAdjacentes) {
                        if (zona != nullptr) {
                            if (zona->getEdificio() != nullptr) {
                                auto func_edificio = funcs_copy.find(zona->getEdificio()->getNome());
                                if (func_edificio != funcs_copy.end() && func_edificio->second == &Armazem::aumentaArmazenado) {
                                    auto func_parameter = funcs_parameters.find(zona->getEdificio()->getNome());
                                    auto existe = relacoes_copy.find(zona->getEdificio()->getNome());
                                    if (existe == relacoes_copy.end()) { // se chegou ao fim das relacoes entao o remove foi sucessfull

                                        (zona->getEdificio()->*(func_edificio->second))(func_parameter->second);
                                        funcs_copy.erase(func_edificio);

                                    }
                                }
                            }
                            auto func_zona = funcs_copy.find(zona->getNomeZona());
                            if (func_zona != funcs_copy.end() && func_zona->second == &Armazem::aumentaArmazenado) {
                                auto func_parameter = funcs_parameters.find(zona->getNomeZona());
                                auto existe = relacoes_copy.find(zona->getNomeZona());
                                if (existe == relacoes_copy.end()) { // se chegou ao fim das relacoes entao o remove foi sucessfull
                                    (zona->getEdificio()->*(func_zona->second))(func_parameter->second);
                                    funcs_copy.erase(func_zona);
                                }
                            }

                        }
                    }
                }

            }
        }
    }
}

Serraria::Serraria(const string& nome, const array<Recursos*, 7> recursos) : Edificios(nome, recursos,100,0,false) {
    custo = {
            {{recursos[6],nullptr},{10,NULL}}
    };

}

void Serraria::extrai() {
    if(ligado){
        if(armazenamento + 1 * zona->getMultiplier(recursos[4]) <= capacidade) {
            auto trabalhadores = zona->getTipoTrabalhadores();
            auto it = find_if(trabalhadores.begin(), trabalhadores.end(),
                              [](const Trabalhadores *trabalhador) {
                                  return ('O' == trabalhador->getSimbolo());
                              });

            if (it != zona->getTipoTrabalhadores().end()) {
                auto zonasAdjacentes = zona->getAdjacente();
                auto funcs_copy = funcs;
                auto relacoes_copy = relacoes;
                vector<Zona*> removidos;
                //loop de removes
                for(auto zona : zonasAdjacentes){
                    if(zona != nullptr){
                        if(zona->getEdificio()!= nullptr){
                            auto func_edificio = funcs_copy.find(zona->getEdificio()->getNome()); // encontrar edificio no mapa
                            if(func_edificio!=funcs_copy.end() && func_edificio->second == &Armazem::removeRecurso){ // ver se a funcao é de remove e se existe
                                auto func_parameter = funcs_parameters.find(zona->getEdificio()->getNome()); // quantidade para remover
                                if(zona->getEdificio()->getArmazenado() >= func_parameter->second){
                                    //armazenamento += 1 * zona->getMultiplier(recursos[3]); // adicionar 1 kg de carvao sempre que se remove de algum lado
                                    (zona->getEdificio()->*(func_edificio->second))(func_parameter->second); // chamar funçao no mapa(remove neste caso)
                                    removidos.emplace_back(zona);
                                    funcs_copy.erase(zona->getEdificio()->getNome());
                                    for(auto it{relacoes_copy.begin()};it != relacoes_copy.end(); ) { // iterar mapa para encontrar sitio onde se remove
                                        if (it->second == zona->getEdificio()->getNome() || it->first == zona->getEdificio()->getNome()) {
                                            it = relacoes_copy.erase(it);
                                        }
                                        else{
                                            ++it;
                                        }

                                    }
                                }
                            }
                        }
                        auto func_zona = funcs_copy.find(zona->getNomeZona());
                        if(func_zona != funcs_copy.end() && func_zona->second == &Armazem::removeRecurso) {
                            auto func_parameter = funcs_parameters.find(zona->getNomeZona()); // quantidade para remover
                            if(zona->getArmazenado() >= func_parameter->second){
                                //armazenamento += 1 * zona->getMultiplier(recursos[3]); // adicionar 1 kg de carvao sempre que se remove de algum lado
                                (zona->*(func_zona->second))(func_parameter->second); // chamar funçao no mapa(remove neste caso)
                                funcs_copy.erase(zona->getNomeZona());
                                removidos.emplace_back(zona);
                                for(auto it{relacoes_copy.begin()};it != relacoes_copy.end(); ) { // iterar mapa para encontrar sitio onde se remove
                                    if (it->second == zona->getNomeZona() || it->first == zona->getNomeZona()) {
                                        it = relacoes_copy.erase(it);
                                    }
                                    else{
                                        ++it;
                                    }
                                }
                            }
                        }
                    }
                }

                if(!relacoes_copy.empty()){
                    for(auto zona : removidos){
                        if(zona->getEdificio() != nullptr) {
                            zona->getEdificio()->aumentaArmazenado((funcs_parameters.find(zona->getEdificio()->getNome()))->second);
                        }
                        zona->aumentaArmazenado(funcs_parameters.find(zona->getNomeZona())->second);
                    }
                }
                else {
                    aumentaArmazenado(1 * zona->getMultiplier(recursos[4]));
                    // loop de adds
                    for (auto zona: zonasAdjacentes) {
                        if (zona != nullptr) {
                            if (zona->getEdificio() != nullptr) {
                                auto func_edificio = funcs_copy.find(zona->getEdificio()->getNome());
                                if (func_edificio != funcs_copy.end() && func_edificio->second == &Armazem::aumentaArmazenado) {
                                    auto func_parameter = funcs_parameters.find(zona->getEdificio()->getNome());
                                    auto existe = relacoes_copy.find(zona->getEdificio()->getNome());
                                    if (existe == relacoes_copy.end()) { // se chegou ao fim das relacoes entao o remove foi sucessfull

                                        (zona->getEdificio()->*(func_edificio->second))(func_parameter->second);
                                        funcs_copy.erase(func_edificio);

                                    }
                                }
                            }
                            auto func_zona = funcs_copy.find(zona->getNomeZona());
                            if (func_zona != funcs_copy.end() && func_zona->second == &Armazem::aumentaArmazenado) {
                                auto func_parameter = funcs_parameters.find(zona->getNomeZona());
                                auto existe = relacoes_copy.find(zona->getNomeZona());
                                if (existe == relacoes_copy.end()) { // se chegou ao fim das relacoes entao o remove foi sucessfull
                                    (zona->getEdificio()->*(func_zona->second))(func_parameter->second);
                                    funcs_copy.erase(func_zona);
                                }
                            }

                        }
                    }
                }

            }
        }
    }
}

Edificios* Serraria::cloneEdificios() {
    return new Serraria(*this);
}

Recursos* Serraria::addRecursos(const array<Recursos*, 7> recursos) {
    recursos[4]->setRecurso(recursos[4]->getRecurso() + armazenamento);
    armazenamento=0;
    return recursos[0];
}
