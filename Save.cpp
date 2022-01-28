#include "Save.h"
#include "Jogo.h"

vector<tuple<string,Jogo*>> Save::saves;

string Save::savegame(const string& name, Jogo& jogo) {
    bool flag{false};
    for(auto i : saves){
        if(get<0>(i) == name){
            flag = true;
            break;
        }
    }
    if(!flag) {
        saves.emplace_back(name, new Jogo(jogo));
        return "Jogo salvo com sucesso";
    }
    else{
        return "Nome de save ja existe";
    }



}

string Save::loadgame(const string& name, Jogo& jogo) {
    
    for(int i = 0; i < saves.size(); i++){
        if(get<0>(saves[i]) == name){
            jogo.setIlha(get<1>(saves[i])->getIlha());
            jogo.setListaRecursos(get<1>(saves[i])->getListarecursos());
            jogo.updateTipos(jogo.getListarecursos());
            for(int k{1};k<=get<1>(saves[i])->getIlha().getLinhas();k++){
                for(int j{1};j<=get<1>(saves[i])->getIlha().getColunas();j++){
                    if(get<1>(saves[i])->getIlha().getZona(k,j)->getEdificio()!= nullptr){
                        get<1>(saves[i])->getIlha().getZona(k,j)->getEdificio()->updatecusto(jogo.getListarecursos());
                        get<1>(saves[i])->getIlha().getZona(k,j)->getEdificio()->setListaRecursos(jogo.getListarecursos());
                    }
                }
            }
            return "Jogo carregado com sucesso";
        }
    }
    return "Nao foi possivel encontrar o save";

}

string Save::deletesave(const string &name) {
    auto savestemp = saves;
    bool flag{false};
    for(auto i{saves.begin()}; i != saves.end(); ){
        if(get<0>(*i) == name) {
            delete get<1>(*i);
            i = saves.erase(i);
            flag=true;
            break;
        }
        else{
            i++;
        }
    }
    if(flag){
        return "Save apagado com sucesso";
    }
    else{
        return "Save nao encontrado";
    }

}
