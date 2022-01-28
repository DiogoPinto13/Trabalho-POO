#include <iostream>
#include <string>
#include "Zona.h"
#include "Jogo.h"
#include "UI.h"
#include "Jogo.h"
#include <fstream>
#include <sstream>
using namespace std;

int main(){
    Comandos comandos;
    Jogo jogo(comandos);
    UI ui(jogo);
    jogo.comecaJogo();

    return 0;
}
