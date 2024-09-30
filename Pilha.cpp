
//Bibliotecas necessárias
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"



TipoCelulaP *Topo; //Variável utilizada para manter o controle do estado atual da pilha
                  //Como a pilha é implementada em memória dinâmica,
                  //Topo deve ser um ponteiro para a célula no topo da Pilha

int ContadorP;  //Variável para contar o número de elementos armazenados na Pilha


//Um construtor é um método que deve ser executado obrigatoriamente antes da pilha ser utilizada
void Pilha_Construtor()
{

  Topo = NULL;  //O construtor da Pilha deve iniciar uma Pilha vazia, sem memória alocada
                //para essa estrutura de dados (não há ainda elementos armazenados)
                //Portanto, o ponteiro Topo deve apontar para NULL

  ContadorP = 0;  //Inicia a variável para indicar a quantidade de elementos armazenados na Pilha
}

//Método para recuperar a memória dinâmica alocada para a Pilha
//Ao contrário de um construtor, o destrutor é um método que deve ser executado
//depois da pilha ser utilizada
void Pilha_Destrutor()
{

   TipoCelulaP *Temp;  //Ponteiro temporário utilizado para desalocar a memória

   while(Topo != NULL)  //Enquanto Topo não chegar em Nulo (Enquanto a Pilha não estiver vazia)
   {
     Temp = Topo;  //o ponteiro temporário deve apontar para o mesmo endereço que Topo
     Topo = Topo -> Prox; //Topo avança para a célula seguinte

     Temp->Prox = NULL; //Para quebrar o vínculo que existia entre as células da Pilha (segurança)
     free(Temp);  //desaloca o espaço de memória (célula) apontado por Temp
   }

   ContadorP = 0;
}

//Função para indicar se a Pilha está ou não vazia (se exite ou não algum elemento armazenado)
bool Pilha_Vazia()
{
   return Topo == NULL;   //Pela forma como os elementos são Empilhados e Desempilhados (métodos a seguir)
                          //a Pilha está vazia se Topo apontar para NULL


                          //se Topo for igual a NULL, a função retorna verdadeiro
                          //caso contrário, será retornado falso (operador de comparação ==)

                          //Esse comando poderia também ser substituído por ContadorP == 0
                          //uma vez que essa variável indica a quantidade de elementos
                          //armazenados na Pilha
}

//Função para retornar a quantidade de elementos armazenados na Pilha
int Pilha_Tamanho()
{

    return ContadorP;   //É retornado o ContadorP de elementos, manipulado nos métodos de Empilhar e Desempilhar
}


//Método para adicionar elementos do topo da Pilha
//Se o elemento for Empilhado (armazenado na Pilha), o método retorna verdadeiro
//caso contrário, retorna falso
//Esse método também é conhecido como Push
bool Pilha_Empilhar(TipoDadoP Elemento)
{

   TipoCelulaP *Nova;  //Ponteiro temporário utilizado para apontar para a nova célula a ser criada
   Nova = (TipoCelulaP *) malloc(sizeof(TipoCelulaP));

   if(Nova==NULL)  //tenta alocar dinâmicamente na memória umam nova célula da Pilha
   {                                                             //e Nova deve apontar para esse endereço de memória

       //caso não for possível alocar mais uma célula na memória (Nova aponta para NULL e torna a condição do if verdadeira)
       //Retona falso, indicando que nenhum elemento foi empilhado (não foi possível alocar mais memória)
       return false;
   }
   else
   {
       Nova->Item = Elemento;  //Como Nova aponta para um espaço de memória disponível, guardamos o Elemento a ser armazenado nesse espaço
       Nova->Prox = Topo;      //Para fazer a ligação entre as células da Pilha, o novo espaço de memória reservado
                               //e apontado por Nova possui um ponteiro Prox que deve apontar para célua seguinte
                               //Nesse caso, o ponteiro Prox deve apontar para o mesmo endereço que Topo aponta
                               //Resumindo: O Prox do Nova aponta agora para Topo

       Topo = Nova;            //Como a Pilha possui agora um novo topo apontado por Nova e o ponteiro Topo está um nível abaixo
                               //deve-se fazer com que Topo aponte para a nova célula criada

       ContadorP++;             //Como foi armazenado um novo Elemento, o ContadorP deve ser incrementado

       return true;            //Retorna verdadeiro, indicando que o elemento foi empilhado (inserido na Pilha)
   }
}


//Método para remover elementos da Pilha
//Se o elemento for Desempilhado (removido da Pilha), o método retorna verdadeiro
//caso contrário, retorna falso
//O Elemento no topo da Pilha é removido e retornado por referência pelo parâmetro da função
//Esse método também é conhecido como Pop
bool Pilha_Desempilhar(TipoDadoP &Elemento)
{

   if(!Pilha_Vazia())  //primeiro deve-se conferir se a Pilha não está vazia
   {

      TipoCelulaP *Temp = Topo;  //Cria um ponteiro temporário (Temp) e faz apontar para o mesmo endereço de Topo
                                //Essa célula será excluída da Pilha

      Topo = Topo->Prox; //Faz o topo apontar para a célula seguinte
                         //Esse procedimento define a célula eleita como topo da Pilha

      Elemento = Temp->Item;  //O Elemento a ser retornado está na célula que será excluída
                              //Esse elemento é o último que foi empilhado (inserido na Pilha)

      Temp->Prox = NULL;  //Remove a ligação entre a célula a ser excluída e a célula de topo da Pilha (segurança)

      free(Temp);         //Desaloca o espaço de memória reservado pela célula apontada por Temp
                          //(devolve esse espaço de memória ao sistema)

      ContadorP--;          //Como foi removido um Elemento, o ContadorP deve ser decrementado

      return true;        //Retona verdadeiro, indicando que o elemento foi removido
   }
   else  //caso a Pilha esteja vazia
     return false;      //Retona falso, indicando que nenhum elemento foi removido (Não há Elemento para ser removido, a Pilha está vazia)
}


//Método para retornar o elemento no topo da Pilha sem removê-lo
//O elemento é retornado por referência pelo parâmetro da função
bool Pilha_Topo(TipoDadoP &Elemento)
{

     if(!Pilha_Vazia())  //primeiro deve-se conferir se a Pilha não está vazia
     {
        Elemento = Topo->Item;  //Topo aponta uma célula com o último elemento empilhado

        return true;  //retorna verdadeiro indicando que o último elemento da Pilha foi retornado (mas não desempilhado)
     }
     else //caso a Pilha esteja vazia
     return false;  //retorna falso, indicando que não foi possível retornar o elemento
}
