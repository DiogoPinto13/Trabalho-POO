#include "UI.h"
#include "Jogo.h"
#include <iostream>
UI::UI(Jogo &novoJogo) : jogo(novoJogo) {
    jogo.addObserver(*this);
}

void UI::update(Interface& interface) {
    std::cout << interface.getMessage() << endl;

}