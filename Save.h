#ifndef RATINHOCORPORATION_SAVE_H
#define RATINHOCORPORATION_SAVE_H
#include <iostream>
#include <vector>

using namespace std;
class Jogo;

class Save{
public:
    Save() = default;
    string savegame(const string& name, Jogo& jogo);
    string loadgame(const string& name, Jogo& jogo);
    string deletesave(const string& name);

private:
    static vector<tuple<string,Jogo*>> saves;
};


#endif //RATINHOCORPORATION_SAVE_H
