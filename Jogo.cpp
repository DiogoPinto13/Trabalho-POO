#include "Jogo.h"
#include "Dias.h"

void Jogo::addObserver(Observer &o) {
    observers.emplace_back(&o);
}
void Jogo::removeObserver(Observer &o) {
    remove_if(observers.begin(),observers.end(),[&](Observer* observer){
        return observer == &o;
    });
}
void Jogo::notifyObservers(Interface& interface) {
    for(auto& i : observers){
        i->update(interface);
    }
}

void Jogo::comecaJogo() {
	string teste;
	int linha, coluna;
	bool flag{false};
    cout << "Bem vindo ao jogo!" << endl;
	do{
	    flag = false;
        cout << "Por favor digite o numero de linhas e colunas que pretenda que a ilha tenha." << endl;
        cout << "->";
        cin >> linha >> coluna;
        if(cin.fail()){
            cout << "Tem que escrever 2 numeros" << endl;
            flag = true;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            if ((linha < 3 || coluna < 3) || (linha > 8) || (coluna > 16)) {
                cout << "Tamanho do tabuleiro entre 3-8 e 3-16" << endl;
                flag = true;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
	}while(flag);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	ilha.tab = ilha.criaTab(linha, coluna,*this);
	do {
		for(auto& i : dias ){
            i->executa(*this);
        }
	} while (1);
}


Jogo::Jogo(Comandos& comandos) : comando(comandos) {
    dias = {new Manha(ilha,comando), new MeioDia(ilha,comando), new Noite(ilha,comando)};
    listaRecursos={ new Ferro{"ferro",1}, new BarraDeAco{"aco",2}, new Carvao{"carvao",1},
                    new Madeira{"mad",1}, new VigasDeMadeira{"vig",2}, new Eletricidade{"eletr",1.5}, new Dinheiro{"din",0}};
    tipos={
        {"minaf",   new MinaFerro{"mnF", listaRecursos}},
        {"minac",   new MinaCarvao{"mnC", listaRecursos}},
        {"bat",     new Bateria{"bat", listaRecursos}},
        {"central", new CentralEletrica{"elec", listaRecursos}},
        {"fund",    new Fundicao{"fun", listaRecursos}},
        {"serraria",new Serraria{"serr", listaRecursos}},
        {"edx",     new EdificioX{"edx", listaRecursos}}
    };
    tiposTrabalhadores={
            { "oper", new Operario{'O'}},
            { "len", new Lenhador{'L'} },
            { "miner", new Mineiros{'M'}}
    };
}

Jogo::Jogo(const Jogo &outro) {
    if(this==&outro){
        *this = outro;
        return;
    }
    ilha = outro.ilha;


    for(int i=0;i<outro.listaRecursos.size();i++){
        listaRecursos[i] = outro.listaRecursos[i]->cloneRecursos();
    }

    dias.clear();
    for(auto i :outro.dias){
        dias.emplace_back(i->cloneDias());
    }

}

void Jogo::setIlha(Ilha ilha) {
    this->ilha = ilha;
}

Ilha &Jogo::getIlha() {
    return ilha;
}

map<string, Edificios *>& Jogo::getTipos() {
    return tipos;
}

map<string, Trabalhadores*>& Jogo::getTiposTrabalhadores() {
    return tiposTrabalhadores;
}

array<Recursos *, 7>& Jogo::getListarecursos(){
    return listaRecursos;
}

void Jogo::setListaRecursos(array<Recursos*, 7> recursos) {
    for(int i{0};i<recursos.size();i++){
        listaRecursos[i]=recursos[i]->cloneRecursos();
    }
}

void Jogo::updateTipos(array<Recursos *, 7> recursos) {

    for(auto& i : tipos){
        i.second->setListaRecursos(recursos);
        i.second->updatecusto(recursos);

    }
}


