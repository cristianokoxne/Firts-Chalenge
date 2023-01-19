#include <stdio.h>
#include <stdlib.h>

typedef struct Pedidos{
    int id;
    struct Pedidos *left, *direito;
    short altura;
}Pedidos;

/*
    Função que cria um Pedidosvo nó
    x -> id a ser inserido Pedidos nó
    Retorna: o endereço do nó criado
*/
Pedidos* PedidosvoPedidos(int x){
    Pedidos *Pedidosvo = malloc(sizeof(Pedidos));

    if(Pedidosvo){
        Pedidosvo->id = x;
        Pedidosvo->left = NULL;
        Pedidosvo->direito = NULL;
        Pedidosvo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em PedidosvoPedidos!\n");
    return Pedidosvo;
}

/*
    Retorna o maior dentre dois ides
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b){
    return (a > b)? a: b;
}


//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoPedidos(Pedidos *Pedidos){
    if(Pedidos == NULL)
        return -1;
    else
        return Pedidos->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(Pedidos *Pedidos){
    if(Pedidos)
        return (alturaDoPedidos(Pedidos->left) - alturaDoPedidos(Pedidos->direito));
    else
        return 0;
}

// --------- ROTAÇÕES ---------------------------

// função para a rotação à esquerda
Pedidos* rotacaoEsquerda(Pedidos *r){
    Pedidos *y, *f;

    y = r->direito;
    f = y->left;

    y->left = r;
    r->direito = f;

    r->altura = maior(alturaDoPedidos(r->left), alturaDoPedidos(r->direito)) + 1;
    y->altura = maior(alturaDoPedidos(y->left), alturaDoPedidos(y->direito)) + 1;

    return y;
}

// função para a rotação à direita
Pedidos* rotacaoDireita(Pedidos *r){
    Pedidos *y, *f;

    y = r->left;
    f = y->direito;

    y->direito = r;
    r->left = f;

    r->altura = maior(alturaDoPedidos(r->left), alturaDoPedidos(r->direito)) + 1;
    y->altura = maior(alturaDoPedidos(y->left), alturaDoPedidos(y->direito)) + 1;

    return y;
}

Pedidos* rotacaoEsquerdaDireita(Pedidos *r){
    r->left = rotacaoEsquerda(r->left);
    return rotacaoDireita(r);
}

Pedidos* rotacaoDireitaEsquerda(Pedidos *r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a Pedidosva raiz após o balanceamento
*/
Pedidos* balancear(Pedidos *raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->left) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->left) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

/*
    Insere um Pedidosvo nó na árvore
    raiz -> raiz da árvore
    x -> id a ser inserido
    RetorPedidos: endereço do Pedidosvo nó ou Pedidosva raiz após o balanceamento
*/
Pedidos* inserir(Pedidos *raiz, int x){
    if(raiz == NULL) // árvore vazia
        return PedidosvoPedidos(x);
    else{ // inserção será à esquerda ou à direita
        if(x < raiz->id)
            raiz->left = inserir(raiz->left, x);
        else if(x > raiz->id)
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInsercao nao realizada!edidos elemento %d a existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o Pedidosvo nó inserido
    raiz->altura = maior(alturaDoPedidos(raiz->left), alturaDoPedidos(raiz->direito)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
Pedidos* remover(Pedidos *raiz, int chave) {
    if(raiz == NULL){
        printf("id nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->id == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->left == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->left != NULL && raiz->direito != NULL){
                    Pedidos *aux = raiz->left;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    raiz->id = aux->id;
                    aux->id = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->left = remover(raiz->left, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    Pedidos *aux;
                    if(raiz->left != NULL)
                        aux = raiz->left;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->id)
                raiz->left = remover(raiz->left, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o Pedidosvo nó inserido
        raiz->altura = maior(alturaDoPedidos(raiz->left), alturaDoPedidos(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimir(Pedidos *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->id);
        imprimir(raiz->left, nivel + 1);
    }
}

int main(){

    int opcao, id;
    Pedidos *raiz = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("Saindo!!!");
            break;
        case 1:
            printf("\tDigite o id a ser inserido: ");
            scanf("%d", &id);
            raiz = inserir(raiz, id);
            break;
        case 2:
            printf("\tDigite o id a ser removido: ");
            scanf("%d", &id);
            raiz = remover(raiz, id);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        default:
            printf("\Pedidoscao invalida!!!\n");
        }

    }while(opcao != 0);

    return 0;
}