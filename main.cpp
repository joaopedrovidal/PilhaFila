#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include "Fila.h"

using namespace std;

void verificaPosicao(float nota1, float nota2, Aluno aluno, int mat1, int mat2) {
    Aluno temp;
    if (nota1 < nota2) {
        Pilha_Desempilhar(aluno);
        Fila_Enfileirar(aluno);
        Fila_Frente(aluno);
        Pilha_Topo(aluno);
        nota2 = aluno.nota;
        if (nota2 < nota1) {
            Fila_Desenfileirar(aluno);
            Pilha_Empilhar(aluno);
        } else {
            verificaPosicao(nota1, nota2, aluno, mat1, mat2);
        }
    } else if (nota1 > nota2) {
        Fila_Frente(aluno);
        Fila_Desenfileirar(aluno);
        Pilha_Empilhar(aluno);
    } else {
        if (mat1 > mat2) {
            Fila_Desenfileirar(aluno);
            Pilha_Empilhar(aluno);
        } else {
            Pilha_Desempilhar(aluno);
            temp = aluno;
            Fila_Desenfileirar(aluno);
            Pilha_Empilhar(aluno);
            Pilha_Empilhar(temp);
        }
    }
}

int main() {
    int opcao;
    float notaFrente, notaTopo;
    int matriculaFrente, matriculaTopo;
    Aluno aluno;
    Fila_Construtor();
    Pilha_Construtor();

    cout << "Instruções para utilizar o programa:";
    cout << "\n1- Você deve incluir obrigatoriamente a matrícula e a nota do aluno.";
    cout << "\n2- A matrícula não poderá repetir em mais de um aluno.\n";

    do {
        cout << "\nDigite a matrícula do aluno: ";
        cin >> aluno.matricula;
        cout << "Digite a nota do aluno: ";
        cin >> aluno.nota;
        cout << "\nPara continuar adicionando, digite 1, para sair digite qualquer outro valor: ";
        cin >> opcao;

        Fila_Enfileirar(aluno);
    } while (opcao == 1);

    // Empilha o primeiro aluno e retira da lista
    Fila_Frente(aluno);
    Pilha_Empilhar(aluno);
    Fila_Desenfileirar(aluno);

    // Faz as necessárias verificações para ordenar enquanto a lista não estiver vazia
    while (Fila_Tamanho() != 0) {
        if (Fila_Frente(aluno)) {
            Fila_Frente(aluno);
            notaFrente = aluno.nota;
            matriculaFrente = aluno.matricula;
            Pilha_Topo(aluno);
            notaTopo = aluno.nota;
            matriculaTopo = aluno.matricula;
            // Chama a função recursiva
            verificaPosicao(notaFrente, notaTopo, aluno, matriculaFrente, matriculaTopo);
        }
    }

    // Imprime a pilha da ordem maior para o menor
    while (Pilha_Tamanho() != 0) {
        Pilha_Topo(aluno);
        cout << "Matrícula: " << aluno.matricula << " Nota: " << aluno.nota << endl;
        Pilha_Desempilhar(aluno);
    }

    return 0;
}
