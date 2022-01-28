#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
using namespace std;
class Jogo;

class Interface{
public:
    bool isSuccess() const{return sucess;}
    string getMessage() const{return message;}
    void setMessage(string novaMSG){message = novaMSG;}
    void setSucess(bool novoSucess){sucess = novoSucess;}

private:
    string message;
    bool sucess;

};

class Observer{
public:
    virtual void update(Interface& interface) = 0;
};


class Observable : public Interface {

public:
    virtual void addObserver(Observer&) = 0;
    virtual void removeObserver(Observer&) = 0;
    virtual void notifyObservers(Interface& interface) = 0;
protected:
    std::vector<Observer*> observers;
};

class UI : public Observer{
public:
    UI(Jogo& jogo );
private:
    Jogo& jogo;
    void update(Interface& interface) override;

};

#endif