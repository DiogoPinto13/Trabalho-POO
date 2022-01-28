#include "Comandos.h"
#include "Ilha.h"
#include "Recursos.h"
#include "Edificios.h"
#include "Jogo.h"
#include "Trabalhadores.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <tuple>


Interface& Comandos::execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) {
	return interface;
}

Comandos::Comandos(const Comandos& outro) {

}

Interface& Constroi::execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) {
    int linha, coluna;
    string tipo_construcao;

    comand >> tipo_construcao >> linha >> coluna;

    if (comand.fail()) {
        interface.setMessage("Erro, comando invalido : cons <tipo> <linha> <coluna>");
        return interface;
    }
    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas() )) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }
    
    auto it = jogo.getTipos().find(tipo_construcao);
    if (it == jogo.getTipos().end()) {
        interface.setMessage("Erro, tipo de construcao nao existe");
        return interface;
    }

    if (ilha.getZona(linha, coluna)->getEdificio() == nullptr) {

        bool constroi {true};
        vector<tuple<Recursos*,float>> removidos;
        for(auto m : it->second->getCusto()){
            if(get<0>(m.first)->getRecurso() >= get<0>(m.second)){
                get<0>(m.first)->setRecurso((get<0>(m.first)->getRecurso()) - get<0>(m.second));
                removidos.emplace_back(get<0>(m.first),get<0>(m.second));
            }
            else{
                if(get<1>(m.first) != nullptr){


                    if(get<1>(m.first)->getRecurso() >= (get<1>(m.second) * (get<0>(m.second) - get<0>(m.first)->getRecurso()))){
                        get<1>(m.first)->setRecurso((get<1>(m.first)->getRecurso()) - (get<1>(m.second) * (get<0>(m.second) - get<0>(m.first)->getRecurso())));
                        get<0>(m.first)->setRecurso(get<0>(m.first)->getRecurso() - (get<1>(m.second) * get<0>(m.second) - (get<1>(m.second) * (get<0>(m.second) - get<0>(m.first)->getRecurso())))/get<1>(m.second));

                        removidos.emplace_back(get<1>(m.first),get<1>(m.second));
                        removidos.emplace_back(get<0>(m.first),(get<1>(m.second) * get<0>(m.second) - (get<1>(m.second) * (get<0>(m.second)) - get<0>(m.first)->getRecurso()))/get<1>(m.second));
                        continue;
                    }
                }
                constroi = false;
                break;
            }
        }
        if(!constroi){
            for(auto m : removidos){
                get<0>(m)->setRecurso(get<0>(m)->getRecurso() + get<1>(m));
            }
            interface.setMessage("Recursos insuficientes para construir edificio");
            return interface;
        }
        (ilha.getZona(linha, coluna))->setEdificio((it->second)->cloneEdificios());
        (ilha.getZona(linha, coluna))->getEdificio()->MudaZona(ilha.getZona(linha, coluna));
        interface.setMessage("Edificio construido com sucesso");
        return interface;


    }
    interface.setMessage("Ja existe um edificio nesse sitio");
    return interface;
}
Interface& Contrata::execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) {

	string tipo_trabalhador;

	comand >> tipo_trabalhador;
	if (comand.fail()) {
        interface.setMessage("Erro, comando invalido : cont <tipo>");
		return interface;
	}

	auto it = jogo.getTiposTrabalhadores().find(tipo_trabalhador);
	if (it == jogo.getTiposTrabalhadores().end()) {
		interface.setMessage("Tipo de trabalhador invalido");
		return interface;
	}

	if(jogo.getListarecursos()[6]->getRecurso() >= it->second->getPagamento()){
        for(int i=1;i<=ilha.getLinhas();i++){
            for(int j=1;i<=ilha.getColunas();j++){
                if(ilha.getZona(i,j)->getNomeZona()=="pas"){
                    Trabalhadores* novoTrabalhador{(it->second)->cloneTrabalhador(0,nDia)};
                    novoTrabalhador->setZona(ilha.getZona(i, j));
                    (ilha.getZona(i, j))->setTrabalhador(novoTrabalhador);
                    jogo.getListarecursos()[6]->setRecurso(jogo.getListarecursos()[6]->getRecurso() - it->second->getPagamento());
                    interface.setMessage("Trabalhador contratado com sucesso");
                    return interface;
                }
            }
        }
    }

    interface.setMessage("Dinheiro insuficiente");
	return interface;
}


Interface& List::execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) {
	int linha, coluna;

	int contador;
	comand >> linha >> coluna;

	if (comand.fail()) {
		printTab(ilha,jogo);
		return interface;
	}
    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas())) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }

    cout << "*********************ZONA***************************" << endl;
    cout << "Nome: " << ilha.getZona(linha, coluna)->getNomeZona() << endl;
    cout << "Armazenamento: " << ilha.getZona(linha,coluna)->getArmazenado() << endl;
    cout << "Numero de trabalhadores: " << ilha.getZona(linha,coluna)->getNTrabalhadores() << endl;
    cout << "*****************************************************" << endl;
    if (ilha.getZona(linha, coluna)->getEdificio() != nullptr) {
        cout << "*********************Edificio************************" << endl;
        cout << "Nome: "<<ilha.getZona(linha,coluna)->getEdificio()->getNome() << endl;
        cout << "Armazenado: " << ilha.getZona(linha,coluna)->getEdificio()->getArmazenado() << endl;
        std::cout << std::boolalpha;
        cout << "Ligado: " << ilha.getZona(linha,coluna)->getEdificio()->isLigado() << endl;
        cout << "Nivel: " << ilha.getZona(linha,coluna)->getEdificio()->getNivel() << endl;
        cout << "*****************************************************" << endl;
    }
    cout << "*********************Trabalhador*********************" << endl;
    for(auto i : ilha.getZona(linha,coluna)->getTipoTrabalhadores()){
        cout << "Nome: " << i->getSimbolo() << endl;
        cout << "Probabilidade de se despedir: " << ilha.getZona(linha,coluna)->getMultiplerDemissao(i) << endl;
        std::cout << std::boolalpha;
        cout << "A descansar: " << i->isDescanso() << endl;
        cout << "Id: " << i->getId() << endl;
        cout << "Dia contrato: " << i->getDiaContrato() << endl;
    }
    cout << "*****************************************************" << endl;
    interface.setMessage("");
    return interface;
}

void List::printTab(Ilha& ilha, Jogo& jogo) {
	int linhas{ ilha.getLinhas() };
	int colunas{ ilha.getColunas() };

	double contador;
	cout << endl;
	for (int i = 1; i <= linhas; i++) {
		for (int j = 1; j <= colunas; j++)
			cout << "******";
		cout << endl;
		for (int j = 1; j <= colunas; j++) {
			cout << setw(5);

			cout << ilha.getZona(i, j)->getNomeZona();
			cout << "|";


		}
		cout << '\n';

		for (int j = 1; j <= colunas; j++) {
			if (ilha.getZona(i, j)->getEdificio() != nullptr) {
				cout << setw(5);
				cout << ilha.getZona(i, j)->getEdificio()->getNome();
			}
			else {
				cout << setw(6);
			}
			cout << "|";


		}
		cout << '\n';

		for (int j = 1; j <= colunas; j++) {

			for (contador = 0; contador < (ilha.getZona(i, j)->getNTrabalhadores()); contador++) {
				if (contador < 5)
					cout << (ilha.getZona(i, j)->getTipoTrabalhadores()[contador])->getSimbolo();
			}
			cout << setw(6 - contador);
			cout << "|";
			contador = 0;

		}
		cout << '\n';
		for (int j = 1; j <= colunas; j++) {
			cout << setw(5);
			cout << ilha.getZona(i, j)->getNTrabalhadores();
			cout << "|";


		}
		cout << '\n';
	}
	for (int j = 1; j <= colunas; j++)
		cout << "******";
	cout << "\n\n";
    for(auto i : jogo.getListarecursos()){
        cout << i->getAbreviatura() << ": " << i->getRecurso() << endl;
    }

}

Interface& Vende::execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) {

    int linha, coluna;
    comand >> linha >> coluna;
	if (comand.fail()) {
        comand.clear();
        string tipo;
        float quantidade;
        comand >> tipo >> quantidade;
        if(comand.fail()){
            interface.setMessage("Erro, comando invalido : vende <tipo> <quantidade> ou vende <linha> <coluna>");
            return interface;
        }

       return vende(tipo,quantidade,jogo);
	}
    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas() )) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }
    if(ilha.getZona(linha,coluna)->getEdificio()!= nullptr){
        float quantidade{ilha.getZona(linha,coluna)->getEdificio()->getArmazenado()};
        vende(ilha.getZona(linha,coluna)->getEdificio()->addRecursos(jogo.getListarecursos())->getAbreviatura(),quantidade,jogo);
        (ilha.getZona(linha,coluna)->destroiEdificio(ilha.getZona(linha,coluna)->getEdificio()));
        return interface;
    }
    return interface;
}

Interface& Vende::vende(string tipo, float quantidade,Jogo& jogo) {
    auto recurso = find_if((jogo.getListarecursos()).begin(),(jogo.getListarecursos()).end(),[&](const Recursos* recurso){
       return recurso->getAbreviatura() == tipo;
    });

    if(recurso != jogo.getListarecursos().end()){
        if(quantidade <= (*recurso)->getRecurso()) {
            jogo.getListarecursos()[6]->setRecurso(jogo.getListarecursos()[6]->getRecurso() + (*recurso)->getValor() * quantidade);
            (*recurso)->setRecurso((*recurso)->getRecurso() - quantidade);
            return interface;
        }
        return interface;
    }
    else{
        interface.setMessage("Erro, tipo de recurso nao existe/ nao pode vender esse tipo de recurso");
        return interface;
    }
}

Interface& Sai::execComando(istringstream& comand, Ilha& ilha, int nDia, Jogo& jogo) {
	exit(0);
}

Interface& Liga::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    int linha, coluna;
    comand >> linha >> coluna;

    if (comand.fail()) {
        interface.setMessage("Erro, comando invalido : liga <linha> <coluna>");
        return interface;
    }
    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas() )) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }
    if(ilha.getZona(linha,coluna)->getEdificio() != nullptr)
        ilha.getZona(linha,coluna)->getEdificio()->setLigado(1);
    else
        interface.setMessage("Erro, nenhum edificio presente para ser ligado");

    return interface;
}

Interface& Desliga::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    int linha, coluna;
    comand >> linha >> coluna;

    if (comand.fail()) {
        interface.setMessage("Erro, comando invalido: des <tipo> <linha> <coluna>");
        return interface;
    }
    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas() )) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }

    if(ilha.getZona(linha,coluna)->getEdificio() != nullptr)
        ilha.getZona(linha,coluna)->getEdificio()->setLigado(0);
    else
        interface.setMessage("Erro, nenhum edificio presente para ser desligado");

    return interface;
}

Interface& Debash::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    float deposito;
    comand >> deposito;
    jogo.getListarecursos()[6]->setRecurso(jogo.getListarecursos()[6]->getRecurso()+deposito);
    interface.setMessage("Dinheiro depositado");
    return interface;
}

Interface& Debed::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    int linha, coluna;
    string tipo;
    int flag = 1;
    comand >> tipo >> linha >> coluna;

    if(comand.fail()) {
        interface.setMessage("Erro, comando invalido: debed <tipo> <linha> <coluna>");
        return interface;
    }
    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas() )) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }

    auto it = jogo.getTipos().find(tipo);
    if (it == jogo.getTipos().end()) {
        interface.setMessage("Erro, tipo de construcao nao existe");
        return interface;
    }

    if (ilha.getZona(linha, coluna)->getEdificio() == nullptr) {
        (ilha.getZona(linha, coluna))->setEdificio((it->second)->cloneEdificios());
        (ilha.getZona(linha, coluna))->getEdificio()->MudaZona(ilha.getZona(linha, coluna));
        interface.setMessage("Edificio construido");
        return interface;
    }
    interface.setMessage("Ja existe um edificio nessa zona");
    return interface;
}

Interface& Debkill::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    int id;
    bool flag = false;
    comand >> id;

    for(int i = 0; i < ilha.getLinhas(); i++){
        for(int j = 0; j < ilha.getColunas(); j++){
            flag = ilha.getZona(i+1,j+1)->killTrabalhador(id);
            if(flag){
                interface.setMessage("O trabalhador id foi morto");
                return interface;
            }
        }
    }

    interface.setMessage("Nao existe um trabalhador com esse id");
    return interface;
}

Interface& Move::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    int id,linha,coluna;
    comand >> id >> linha >> coluna;

    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas() )) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }
    for(int i = 1; i <= ilha.getLinhas(); i++){
        for(int j = 1; j <= ilha.getColunas(); j++){
            Trabalhadores* trabalhador{ilha.getZona(i,j)->getTrabalhador(id)};
            if(trabalhador != nullptr){
                if(trabalhador->podeMover()) {
                    Trabalhadores *clone{trabalhador->cloneTrabalhador(1, nDia)};
                    ilha.getZona(linha, coluna)->setTrabalhador(clone);
                    clone->setZona(ilha.getZona(linha, coluna));
                    ilha.getZona(i, j)->killTrabalhador(id);
                    clone->blockMover();
                    interface.setMessage("Trabalhador movido com sucesso");
                    return interface;
                }
                interface.setMessage("Trabalhador ja foi movido este dia, so pode mover 1 vez por dia");
                return interface;
            }

        }
    }
    interface.setMessage("Nao existe um trabalhador com esse id");
    return interface;
}

Interface& Upgrade::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    int linha,coluna;
    comand >> linha >> coluna;

    if(comand.fail()){
        interface.setMessage("Erro, comando invalido: upgrade <linha> <coluna>");
        return interface;
    }

    if ((linha <= 0 || coluna <= 0) || (linha > ilha.getLinhas() || coluna > ilha.getColunas() )) {
        interface.setMessage("Erro, o numero de linhas e colunas invalido");
        return interface;
    }

   auto edificio = ilha.getZona(linha,coluna)->getEdificio();

    if(edificio != nullptr){
        auto upgradeCusto{edificio->getUpgradeCusto()};
        vector<tuple<Recursos*,float>> removidos;
        bool upgrade{true};
        for(auto i : upgradeCusto){
            if(get<0>(i)->getRecurso() >= get<1>(i)){
                get<0>(i)->setRecurso(get<0>(i)->getRecurso()-get<1>(i));
                removidos.emplace_back(i);
                continue;
            }
            upgrade=false;
            break;
        }
        if(upgrade){
            if(edificio->upgrade()){
                interface.setMessage("Edificio upgradado com sucesso");
                return interface;
            }
            interface.setMessage("Edificio nao possui mais upgrades");
            return interface;

        }
        for(auto i : removidos){
            get<0>(i)->setRecurso(get<0>(i)->getRecurso()+get<1>(i));
        }
        interface.setMessage("Recursos insuficientes");
        return interface;
    }
    interface.setMessage("Nenhum edificio nessa zona");
    return interface;



}

Interface& Config::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    string filename;
    comand >> filename;

    if(comand.fail()){
        return interface;
    }

    ifstream file(filename);

    if(!file.is_open()){
        return interface; // failed to open
    }
    istringstream configLine;
    string input;

    while(file){
        getline(file,input);
        istringstream configLine(input);

        string tipo;
        int euro;
        configLine >> tipo >> euro;
        if(configLine.fail()){
            interface.setMessage("Falha na leitura do ficheiro de configuracao");
            return interface;
        }

        auto edificio = jogo.getTipos().find(tipo);
        if(edificio != jogo.getTipos().end()){
            edificio->second->setCusto(euro);
        }
        else{
            auto trabalhador = jogo.getTiposTrabalhadores().find(tipo);
            if(trabalhador != jogo.getTiposTrabalhadores().end()){
                trabalhador->second->setPagamento(euro);
            }
            break;
        }

    }
    interface.setMessage("Ficheiro lido com sucesso");
    return interface;
}


Interface &Savegame::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo& jogo) {
    string nsave;
    comand >> nsave;
    if(comand.fail()){
        return interface;
    }
    interface.setMessage(savess.savegame(nsave,jogo));
    return interface;
}

Interface &Loadgame::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo &jogo) {
    string nsave;
    comand >> nsave;
    if(comand.fail()){
        return interface;
    }
    interface.setMessage(savess.loadgame(nsave,jogo));
    return interface;
}
Interface &Deletesave::execComando(istringstream &comand, Ilha &ilha, int nDia, Jogo &jogo) {
    string nsave;
    comand >> nsave;
    if(comand.fail()){
        return interface;
    }
    interface.setMessage(savess.deletesave(nsave));
    return interface;
}