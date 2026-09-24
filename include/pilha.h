#ifndef PILHA_H
#define PILHA_H

#include <string>
#include <iostream>
using namespace std;

const int Tmax = 1000;
typedef int Apontador;

typedef struct {
    string palavra;
} TInfo;

typedef struct {
    TInfo Item[Tmax];
    Apontador Topo;
} TPilha;

bool Vazia(TPilha Pilha) {
    return Pilha.Topo == -1;
}

void Cria(TPilha& Pilha) {
    Pilha.Topo = -1;
}

bool Cheia(TPilha Pilha) {
    return Pilha.Topo + 1 == Tmax;
}

void Empilha(TPilha& Pilha, TInfo Item) {
    if (Cheia(Pilha))
        cout << "Erro: A Pilha está cheia" << endl;
    else
        Pilha.Item[++Pilha.Topo] = Item;
}

void Desempilha(TPilha& Pilha) {
    if (Vazia(Pilha))
        cout << "Erro : A Pilha está vazia.\n" << endl;
    else
        Pilha.Topo--;
}

TInfo TopoPilha(TPilha Pilha) {
    if (Vazia(Pilha)) {
        cout << "Erro : A Pilha está vazia.\n" << endl;
        return TInfo();
    } else
        return Pilha.Item[Pilha.Topo];
}

#endif
