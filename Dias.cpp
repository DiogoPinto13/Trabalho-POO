#include "Dias.h"
#include "Ilha.h"
#include <string>
#include <fstream>
#include "Jogo.h"
#include "UI.h"

int Dias::nDia{1};
Dias::Dias(Ilha& ilha,Comandos& comandos): ilha(ilha),comandos(comandos) {

}

void Manha::executa(Jogo& jogo) {

    for(int i{1};i<=ilha.getLinhas();i++){
        for(int j{1};j<=ilha.getColunas();j++){
            for(auto a : ilha.getZona(i,j)->getTipoTrabalhadores()){
                a->evento(nDia);
            }
        }
    }

    for(int i{1};i<=ilha.getLinhas();i++){
        for(int j{1};j<=ilha.getColunas();j++){
            ilha.getZona(i,j)->efeito(nDia);
            if(ilha.getZona(i,j)->getEdificio()!= nullptr){
                ilha.getZona(i,j)->getEdificio()->evento(nDia);
            }
        }
    }
}

Manha::Manha(Ilha &ilha, Comandos &comandos) : Dias(ilha, comandos) {

}

void MeioDia::executa(Jogo& jogo) {
    string input;
    do {
        cout << "Comando: ";
        getline(cin, input);
        istringstream iss(input);
        jogo.notifyObservers(executa_comando(iss,jogo));

    } while (input != "next");
}

Interface& MeioDia::executa_comando(istringstream &comand,Jogo& jogo) {
    string comandoNome;
    bool result{};
    comand >> comandoNome;

    static map<string, Comandos*> comandos{
            {"cont",new Contrata},
            {"cons",new Constroi},
            {"list", new List},
            {"vende", new Vende},
            {"liga", new Liga},
            {"des", new Desliga},
            {"sai", new Sai},
            {"debcash", new Debash},
            {"debkill", new Debkill},
            {"debed", new Debed},
            {"move", new Move},
            {"upgrade", new Upgrade},
            {"config", new Config},
            {"save",new Savegame},
            {"load", new Loadgame},
            {"apaga", new Deletesave}
    };
    auto it = comandos.find(comandoNome);
    if (it != comandos.end()) {
        return (it->second)->execComando(comand, ilha,nDia,jogo);
    }
    if(comandoNome == "next"){
        handler.setMessage("Proximo dia");
        return handler;
    }
    else{
        if(comandoNome == "exec"){
            executa_fich(comand,jogo);
        }
    }
    handler.setMessage("Esse comando nao existe");
    return handler;
}

MeioDia::MeioDia(Ilha &ilha, Comandos &comandos) : Dias(ilha, comandos) {

}

void Noite::executa(Jogo& jogo) {
    for(int i{1};i<=jogo.getIlha().getLinhas();i++){
        for(int j{1};j<=jogo.getIlha().getColunas();j++){
            jogo.getIlha().getZona(i,j)->extrai();
        }
    }
    for(int i{1};i<=jogo.getIlha().getLinhas();i++){
        for(int j{1};j<=jogo.getIlha().getColunas();j++){
            if(jogo.getIlha().getZona(i,j)->getEdificio()!= nullptr){
                jogo.getIlha().getZona(i,j)->getEdificio()->extrai();
            }
        }
    }
    for(int i{1};i<=jogo.getIlha().getLinhas();i++){
        for(int j{1};j<=jogo.getIlha().getColunas();j++){
            jogo.getIlha().getZona(i,j)->addRecursos(jogo.getListarecursos());
            if(jogo.getIlha().getZona(i,j)->getEdificio()!= nullptr){
                jogo.getIlha().getZona(i,j)->getEdificio()->addRecursos(jogo.getListarecursos());
            }
        }
    }
    nDia++;
}

Noite::Noite(Ilha &ilha, Comandos &comandos) : Dias(ilha, comandos) {}

int Dias::getNDia() {
    return nDia;
}

void Dias::setNDia(int nDia) {
    Dias::nDia = nDia;
}

Manha *Manha::cloneDias() {
    return new Manha(*this);
}
MeioDia *MeioDia::cloneDias() {
    return new MeioDia(*this);
}

void MeioDia::executa_fich(istringstream &comand, Jogo &jogo) {
    string filename;
    comand >> filename;

    if(comand.fail()){
        //return interface;
    }

    ifstream file(filename);

    if(!file.is_open()){
       cout << "Falha na abertura do ficheiro";
    }
    istringstream configLine;
    string input;

    while(file){
        getline(file,input);
        istringstream configLine(input);
        jogo.notifyObservers(executa_comando(configLine,jogo));

    }

}

Noite *Noite::cloneDias() {
    return new Noite(*this);
}