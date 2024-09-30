//Bibliotecas necessárias
#include <cstdio>
#include <cstdlib>
#include "Fila.h"

TipoCelula *Frente, *Tras; //Variáveis utilizadas para manter o controle do estado atual da Fila
                           //Como a Fila é implementada em memória dinâmica,
                           //Frente e Tras devem ser ponteiros para as células da Fila


int Contador;  //Variável utilizada para armazenar a quantidade de elementos na Fila

//Um construtor é um método que deve ser executado obrigatoriamente antes da fila ser utilizada
void Fila_Construtor()
{


  Frente = Tras = NULL;  //estado inicial da fila.
                         //Tanto Frente quanto Tras devem apontar para NULL
                         //indicando que nenhum elemento foi enfileirado
                         //Frente e Tras [nos métodos a seguir] sempre são
                         //utilizados na manipulação da Fila dinâmica

  Contador = 0;   //Armazena a quantidade de elementos na Fila
                  //Como a Fila está sendo construída, não há elementos
}

//Método para recuperar a memória dinâmica alocada para a Fila
//Ao contrário de um construtor, o destrutor é um método que deve ser executado
//depois da fila ser utilizada
void Fila_Destrutor()
{


   TipoCelula *Temp;  //Ponteiro temporário utilizado para desalocar a memória

   while(Frente != NULL)  //Enquanto Frente não chegar em Nulo (Enquanto a Fila não estiver vazia)
   {
     Temp = Frente;  //o ponteiro temporário deve apontar para o mesmo endereço que Frente
     Frente = Frente -> Prox; //Frente avança para a célula seguinte

     Temp->Prox = NULL; //desliga a célula a ser excluída da Fila
     free(Temp);  //desaloca o espaço de memória (célula) apontado por Temp
   }

   Tras = NULL;
   Contador = 0;
}

//Função para indicar se a Fila está ou não vazia (se exite ou não algum elemento armazenado)
bool Fila_Vazia()
{

   return Frente == NULL;  //Pela forma como os elementos são Enfileirados e Desenfileirados (métodos a seguir)
                           //tem-se que a Fila está vazia se um dos ponteiros (nesse caso, Frente)
                           //aponta para NULL

                           //se Frente apontar para NULL, a função retorna verdadeiro
                           //caso contrário, será retornado falso (operador de comparação ==)

                          //Esse comando poderia também ser substituído por Contador == 0
                          //uma vez que essa variável indica a quantidade de elementos
                          //armazenados na Fila
}


//Função para retornar a quantidade de elementos armazenados na Fila
int Fila_Tamanho()
{
    return Contador;  //É retornado o contador de elementos, manipulado nos métodos de Enfileirar e Desenfileirar
}



//Método para adicionar elementos na Fila (Enfileirar)
//Se o elemento for Enfileirado (armazenado na Fila), o método retorna verdadeiro
//caso contrário, retorna falso
//Esse método também é conhecido como Enqueue
bool Fila_Enfileirar(TipoDado Elemento)
{

   TipoCelula *Nova;  //Ponteiro temporário utilizado para apontar para a nova célula a ser criada
   Nova = (TipoCelula *) malloc(sizeof(TipoCelula));

   if(Nova==NULL)  //tenta alocar dinâmicamente na memória a primeira célula da Fila
   {                                                             //e Nova deve apontar para esse endereço de memória

       //caso não for possível alocar mais uma célula na memória (Nova aponta para NULL e torna a condição do if verdadeira)
       //Retona falso, indicando que nenhum elemento foi Enfileirado (não foi possível alocar mais memória)
       return false;
   }
   else
   {
          Nova->Item = Elemento; //Como Nova aponta para um espaço de memória disponível, guardamos o Elemento a ser armazenado nesse espaço
          Nova->Prox = NULL;  //Sendo Nova a última celula que será adicionada na Fila,
                              //seu ponteiro Prox deve apontar para NULL (Fim da Fila)

          if(Fila_Vazia())  //Caso a Fila esteja em seu estado inicial
            Frente = Nova;  //Corrige o ponteiro Frente, que deve apontar para a nova (e única) célula da Fila
          else Tras->Prox = Nova;  //caso a Fila não esteja no estado inicial,
                                   //Faz a ligação entre a última célula encadeada na Fila, com a Nova célula criada

          Tras = Nova;  //Tras deve sempre apontar para a nova célula criada
          Contador++;       //Um elemento foi enfileirado, portanto deve-se incrementar o contador de elementos da Fila

          return true;            //Retona verdadeiro, indicando que o elemento foi Enfileirado (inserido na Fila)
   }
}


//Método para remover elementos da Fila
//Se o elemento for Desenfileirado (removido da Fila), o método retorna verdadeiro
//caso contrário, retorna falso
//O Elemento na Frente da Fila é removido e retornado por referência pelo parâmetro da função
//Esse método também é conhecido como Dequeue
bool Fila_Desenfileirar(TipoDado &Elemento)
{

     if(!Fila_Vazia()){  //Se a Fila não estiver vazia, podemos remover algum elemento

        TipoCelula *Temp = Frente;//Cria um ponteiro temporário (Temp) e faz apontar para o mesmo endereço de Frente
                                  //Essa célula será excluída da Fila

        Elemento = Frente->Item;  //Como Frente deve apontar para uma célula com o primeiro valor
                                  //a ser desenfileirado, deve ser retornado o Elemento dentro da célula
                                  //apontada por Frente

        Frente = Frente->Prox;  //Faz o ponteiro de Frente da Fila apontar para a célula seguinte
                                //Esse procedimento define a célula eleita como sendo a primeira da Fila

        Temp->Prox = NULL;  //Remove a ligação entre a célula a ser excluída e a célula de frente da Fila (Segurança)

        free(Temp);         //Desaloca o espaço de memória reservado pela célula apontada por Temp
                            //(devolve esse espaço de memória ao sistema operacional)

        if(Frente == NULL) //Se Frente, ao apontar para célula seguinte, for igual a NULL, significa que a Fila só tinha um elemento armzenado e este foi excluído (A Fila agora está vazia)
          Tras = NULL;  //No caso de Fila vazia, Tras também deve apontar para NULL (Estado inicial da Fila)

        Contador--;  //"Contador" é decrementado para indicar que um elemento foi removido da Fila (desenfileirado)

        return true;   //Retona verdadeiro, indicando que o elemento foi desenfileirado
     }
     else //caso a Fila esteja vazia
       return false;  //Retona falso, indicando que nenhum elemento foi desenfileirado (a Fila está vazia)
}

//Método para retornar o elemento na frente da Fila sem reemovê-lo
//O elemento é retornado por referência pelo parâmetro da função
bool Fila_Frente(TipoDado &Elemento)
{
     if(!Fila_Vazia())  //primeiro deve-se conferir se a Fila não está vazia
     {
        Elemento = Frente->Item;  //assim como no método Desenfileirar, a primeira célula
                                  //na Fila apontada por Frente possui um valor válido

                                  //Repare que aqui a variável Frente não avança na Fila,
                                  //o que iria "remover" o elemento da Fila
        return true;  //retorna verdadeiro indicando que um elemento foi retornado
     }
     else //caso a Fila esteja vazia
          return false;  //retorna falso, indicando que não foi possível retornar um elemento
}