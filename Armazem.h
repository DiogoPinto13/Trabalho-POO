#ifndef RATINHOCORPORATION_ARMAZEM_H
#define RATINHOCORPORATION_ARMAZEM_H
class Armazem {
public:
    Armazem(const int capacidade, const int armazenamento);

    bool removeRecurso(const float quant);
    virtual float getArmazenado() const;
    void setCapacidade(float novaCapacidade);
    float getCapacidade();
    bool aumentaArmazenado(const float quant);
protected:
    float armazenamento;
    float capacidade;
private:


};
#endif //RATINHOCORPORATION_ARMAZEM_H
