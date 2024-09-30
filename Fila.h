#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

struct Aluno{
    int matricula;
    float nota;
};

typedef Aluno TipoDado; //Define o tipo de dado que será armazenado na Fila


//Essa estrutura será utilizada como uma célula da Fila

//Item armazena o valor informado pelo usuário
//Nesse exemplo será criada uma fila de inteiros, mas poderia ser
//qualquer outro tipo de dado

//Prox é um ponteiro que aponta para outra célula da Fila
//Esse ponteiro será utilizado para apontar para a célula que contém o próximo
//valor a ser Desenfileirado
struct TipoCelula{

    TipoDado Item;
    TipoCelula *Prox;
};


//Um construtor é um método que deve ser executado obrigatoriamente antes da fila ser utilizada
void Fila_Construtor();

//Método para recuperar a memória dinâmica alocada para a Fila
//Ao contrário de um construtor, o destrutor é um método que deve ser executado
//depois da fila ser utilizada
void Fila_Destrutor();

//Função para indicar se a Fila está ou não vazia (se exite ou não algum elemento armazenado)
bool Fila_Vazia();

//Função para retornar a quantidade de elementos armazenados na Fila
int Fila_Tamanho();

//Método para adicionar elementos na Fila (Enfileirar)
//Se o elemento for Enfileirado (armazenado na Fila), o método retorna verdadeiro
//caso contrário, retorna falso
//Esse método também é conhecido como Enqueue
bool Fila_Enfileirar(TipoDado Elemento);

//Método para remover elementos da Fila
//Se o elemento for Desenfileirado (removido da Fila), o método retorna verdadeiro
//caso contrário, retorna falso
//O Elemento na Frente da Fila é removido e retornado por referência pelo parâmetro da função
//Esse método também é conhecido como Dequeue
bool Fila_Desenfileirar(TipoDado &Elemento);

//Método para retornar o elemento na frente da Fila sem reemovê-lo
//O elemento é retornado por referência pelo parâmetro da função
bool Fila_Frente(TipoDado &Elemento);

#endif // FILA_H_INCLUDED