#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#define true 1
#define false 0

#define MAX_LINHA 1024
#define DELIMITADOR ","

// Estrutura dos pedidos
typedef struct Pedidos
{
    int item;
    int opcaoCeia;
    char *nome_cliente;
    int ano;
    int dia;
    int mes;
    int hora;
    int min;
    int seg;
    int id;
    int altura;
    int balancingFactor;
    struct Pedidos *left;
    struct Pedidos *right;
} Pedidos;


// Estrutura das entregas
typedef struct Entregas{

    int idPedido;
    int idEntregador;
    int item;
    int balancingFactor;
    int ano;
    int mes;
    int dia;
    int hora;
    int min;
    int seg;
    struct Entregas *left;
    struct Entregas *right;

}Entregas;


//=========================== PEDIDOS =====================================
// função para criar um novo nó da arvore AVL de pedidos
Pedidos *CriarNo(int key, int opcaoCeia, char *nome_cliente, int ano, int mes, int dia, int hora, int min, int seg, int aux)
{
    Pedidos *novo = malloc(sizeof(Pedidos));
    novo->nome_cliente = malloc(sizeof(char));
   
    novo->left = NULL;
    novo->right = NULL;
    novo->altura = 0;
    novo->item = key;
    novo->opcaoCeia = opcaoCeia;
    novo->ano = ano;
    novo->mes = mes;
    novo->dia = dia;
    novo->hora = hora;
    novo->min = min;
    novo->seg = seg;
    novo->id = aux;
    novo->nome_cliente = nome_cliente;
     

    return novo;
}
//rotações a esquerda usada para balancear a arvore
Pedidos *rotateLeft(Pedidos *tree)
{
    Pedidos *child = tree->left, *child2;

    if (child->balancingFactor == 1)
    {
        //rotação Left-Left (LL)
        tree->left = child->right;
        child->right = tree;
        tree = child;
    }
    else
    {
        //rotação Left-Right (LR)
        child = tree->left;
        child2 = child->right;
        child->right = child2->left;
        child2->left = child;
        tree->left = child2->right;
        child2->right = tree;

        if (child2->balancingFactor == 1)
        {
            tree->balancingFactor = -1;
        }
        else
        {
            tree->balancingFactor = 0;
        }

        if (child2->balancingFactor == -1)
        {
            tree->balancingFactor = 1;
        }
        else
        {
            child->balancingFactor = 0;
        }

        tree = child2;
    }

    return tree;
}

//Realizar rotação a direita
Pedidos *rotateRight(Pedidos *tree)
{
    Pedidos *child = tree->right, *child2;

    if (child->balancingFactor == -1)
    {
        //Rotação Right-Right (RR)
        tree->right = child->left;
        child->left = tree;
        tree = child;
    }
    else
    {
        //Rotação Right-Left (RL)
        child = tree->right;
        child2 = child->left;
        child->left = child2->right;
        child2->right = child;
        tree->right = child2->left;
        child2->left = tree;

        if (child2->balancingFactor == -1)
        {
            tree->balancingFactor = 1;
        }
        else
        {
            tree->balancingFactor = 0;
        }

        if (child2->balancingFactor == 1)
        {
            tree->balancingFactor = -1;
        }
        else
        {
            child->balancingFactor = 0;
        }

        tree = child2;
    }

    return tree;
}
//inserir na estrtutura de pedidos
Pedidos *Inserir(Pedidos *tree, int key, int grown, int opcaoCeia, char *nome_cliente, int ano, int mes, int dia, int hora, int min, int seg, int aux)
{
    
      if (tree == NULL)
    {
        tree = CriarNo(key, opcaoCeia , nome_cliente, ano, mes, dia, hora, min, seg, aux);
         
        grown = true; //ter controle caso a árvore crescer
    }
    else if (key < tree->id)
    {
        tree->left = Inserir(tree->left, key, grown, opcaoCeia , nome_cliente, ano, mes, dia, hora, min, seg, aux);

        if (grown == true)
        {
            //verificar o fator de balanceamento
            switch (tree->balancingFactor)
            {
            case -1:
                tree->balancingFactor = 0;
                grown = false;
                break; //árvore balanceada
            case 0:
                tree->balancingFactor = 1;
                break; //árvore balanceada
            case 1:
                tree = rotateLeft(tree);
                tree->balancingFactor = 0;
                grown = false;
            }
        }
    }
    else if (key > tree->id)
    {
        tree->right = Inserir(tree->right, key, grown, opcaoCeia , nome_cliente, ano, mes, dia, hora, min, seg, aux);

        if (grown == true)
        {
            switch (tree->balancingFactor)
            {
            case 1:
                tree->balancingFactor = 0;
                grown = false;
                break; //árvore balanceada
            case 0:
                tree->balancingFactor = -1;
                break; //árvore balanceada
            case -1:
                tree = rotateRight(tree);
                tree->balancingFactor = 0;
                grown = false;
            }
        }
    }
    return tree;
}

//apresentar pedidos prefixo
int prefix(Pedidos*tree, int cont)
{
   
	if (tree != NULL)
	{   cont++;
		 if(tree->item == 1){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao norte", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
             printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
		else if(tree->item == 2){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao centro norte", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
             printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 3){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao extremo norte", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
             printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 4){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao sul", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
             printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 5){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao centro sul", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
             printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 6){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao leste", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
             printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 7){
            printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao oeste", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else {
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao centro oeste", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
		prefix(tree->left, cont);
		prefix(tree->right, cont);
	}
    
}

//apresentar pedidos infixo
int infix(Pedidos*tree, int cont)
{
   
	if (tree != NULL)
	{
        cont++;
		infix(tree->left, cont);

        if(tree->item == 1){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao norte", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
            
        }
		else if(tree->item == 2){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao centro norte", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 3){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao extremo norte", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 4){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao sul", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 5){
             printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao centro sul", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 6){
            printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao leste", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else if(tree->item == 7){
            printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao oeste", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
        else {
            printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d - Regiao centro oeste", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
		infix(tree->right, cont);
	}
    
}
void porRegiao(Pedidos*tree, int conf)
{
	if (tree != NULL)
	{
		if(tree->item == conf)
        {
            printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
        }
		porRegiao(tree->left, conf);
		porRegiao(tree->right, conf);
	}
}

//printar por mes
void porMes(Pedidos *tree, int conf)
{
	if (tree != NULL)
	{
		if(tree->mes == conf)
        {
            printf("\nID do pedido: %d ", tree->id);
            printf("\nRegiao: %d", tree->item);
            printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
            printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        }
		porMes(tree->left, conf);
		porMes(tree->right, conf);
        
	}
   
}
//printar por dia
int porDia(Pedidos *tree,int mes, int dia, int cont)
{
	if (tree != NULL)
	{
		if(tree->mes == mes)
        {
            if(tree->dia == dia){
                printf("\nID do pedido: %d ", tree->id);

                printf("\nRegiao: %d", tree->item);
                printf("\nOpcao de Ceia: %d\n", tree->opcaoCeia);
                printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
                cont++;
            }
            
        }
		porDia(tree->left, mes, dia, cont);
		porDia(tree->right, mes, dia, cont);
        
	}
   return cont;
}

//Função que conta e retorna a quantidade de nós em uma árvore binária

int quantidade_nos(Pedidos *tree){
    if(tree == NULL)
        return 0;
    else
        return 1 + quantidade_nos(tree->left) + quantidade_nos(tree->right);

    // operador ternário
    //return (raiz == NULL)? 0: 1 + quantidade_nos(raiz->esquerda) + quantidade_nos(raiz->direita);
}


//=========================== ENTREGAS =======================
//estrutura para criar uma arvore AVL do tipo Entregas
Entregas *CriarNovaEntregas( int idPedido,int item,int mes,int dia,int hora,int min,int seg, int cont, int ano)
{
   Entregas *n = malloc(sizeof(Entregas));
    n->idPedido = idPedido;
    n->idEntregador = cont;
    n->item = item;
    n->mes= mes;
    n->dia=dia;
    n->hora=hora;
    n->min = min;
    n->seg = seg;
    n->left = NULL;
    n->right = NULL;
    n->ano = ano;

    return n;
}
//Realizar rotação a esquerda usado para balancear a arvore
Entregas *rotateLeftEntregas(Entregas *tree)
{
    Entregas *child = tree->left, *child2;

    if (child->balancingFactor == 1)
    {
        //rotação Left-Left (LL)
        tree->left = child->right;
        child->right = tree;
        tree = child;
    }
    else
    {
        //rotação Left-Right (LR)
        child = tree->left;
        child2 = child->right;
        child->right = child2->left;
        child2->left = child;
        tree->left = child2->right;
        child2->right = tree;

        if (child2->balancingFactor == 1)
        {
            tree->balancingFactor = -1;
        }
        else
        {
            tree->balancingFactor = 0;
        }

        if (child2->balancingFactor == -1)
        {
            tree->balancingFactor = 1;
        }
        else
        {
            child->balancingFactor = 0;
        }

        tree = child2;
    }

    return tree;
}

//Realizar rotação a direita
Entregas *rotateRightEntregas(Entregas *tree)
{
    Entregas *child = tree->right, *child2;

    if (child->balancingFactor == -1)
    {
        //Rotação Right-Right (RR)
        tree->right = child->left;
        child->left = tree;
        tree = child;
    }
    else
    {
        //Rotação Right-Left (RL)
        child = tree->right;
        child2 = child->left;
        child->left = child2->right;
        child2->right = child;
        tree->right = child2->left;
        child2->left = tree;

        if (child2->balancingFactor == -1)
        {
            tree->balancingFactor = 1;
        }
        else
        {
            tree->balancingFactor = 0;
        }

        if (child2->balancingFactor == 1)
        {
            tree->balancingFactor = -1;
        }
        else
        {
            child->balancingFactor = 0;
        }

        tree = child2;
    }

    return tree;
}
// inserir na arvore AVL de entregas
Entregas *inserirEntregas(Entregas *entregas, int regiao, int grown,int opcaoCeia,int ano,int mes,int dia,int hora,int min,int seg,int idPedido, int cont)
{
    if (entregas == NULL)
    {
        entregas = CriarNovaEntregas(idPedido, regiao, mes, dia, hora, min, seg, cont, ano);
        grown = true; //ter controle caso a árvore crescer
    }
    else if (idPedido < entregas->idPedido)
    {
        entregas->left = inserirEntregas(entregas->left, regiao, grown, opcaoCeia, ano, mes, dia, hora, min, seg, idPedido, cont);

        if (grown == true)
        {
            //verificar o fator de balanceamento
            switch (entregas->balancingFactor)
            {
            case -1:
                entregas->balancingFactor = 0;
                grown = false;
                break; //árvore balanceada
            case 0:
                entregas->balancingFactor = 1;
                break; //árvore balanceada
            case 1:
                entregas = rotateLeftEntregas(entregas);
                entregas->balancingFactor = 0;
                grown = false;
            }
        }
    }
    else if (idPedido > entregas->idPedido)
    {
        entregas->right = inserirEntregas(entregas->right, regiao, grown, opcaoCeia, ano, mes, dia, hora, min, seg, idPedido, cont);

        if (grown == true)
        {
            switch (entregas->balancingFactor)
            {
            case 1:
                entregas->balancingFactor = 0;
                grown = false;
                break; //árvore balanceada
            case 0:
                entregas->balancingFactor = -1;
                break; //árvore balanceada
            case -1:
                entregas = rotateRightEntregas(entregas);
                entregas->balancingFactor = 0;
                grown = false;
            }
        }
    }

    return entregas;
}
//imprimir conteudo da arvore Entregas
void ordemEntregas(Entregas*tree)
{
    if (tree != NULL){
        ordemEntregas(tree->left);
        printf("\nID do pedido: %d ", tree->idPedido);
        printf("\nID Entregador: %d", tree->idEntregador);
        printf("\nRegiao: %d", tree->item);
        printf("\nRegistrado em: %d/%d/%d\n Hora: %d:%d:%d\n", tree->dia, tree->mes, tree->ano, tree->hora, tree->min, tree->seg);
        ordemEntregas(tree->right);
    }
        
}
/* funcao auxiliar na destruicao (liberacao da memoria) de uma arvore */
void destruirAux(Pedidos *subRaiz){
	if (subRaiz){
		destruirAux(subRaiz->left);
		destruirAux(subRaiz->right);
		free(subRaiz);
	}
}

/* libera toda memoria de uma arvore e coloca NULL no valor da raiz    */
Pedidos* destruirArvore(Pedidos * raiz){
	destruirAux(raiz);
	raiz = NULL;
    return raiz;
}
/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
Pedidos* delete(Pedidos *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->id == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->left == NULL && raiz->right == NULL) {
                free(raiz);
                printf("Elemento %d removido de pedido, enviado para entrega\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->left != NULL && raiz->right != NULL){
                    Pedidos *aux = raiz->left;
                    while(aux->right != NULL)
                        aux = aux->right;
                    raiz->id = aux->id;
                    aux->id = chave;
                    printf("Elemento %d removido de pedido, enviado para entrega !\n", chave);
                    raiz->left = delete(raiz->left, chave);
                    return raiz;
                }
                else{
                    // delete nós que possuem apenas 1 filho
                    Pedidos *aux;
                    if(raiz->left != NULL)
                        aux = raiz->left;
                    else
                        aux = raiz->right;
                    free(raiz);
                    printf("Elemento %d removido de pedido, enviado para entrega !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->id)
                raiz->left = delete(raiz->left, chave);
            else
                raiz->right = delete(raiz->right, chave);
        }
        /*
        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->left), alturaDoNo(raiz->right)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);
        */
        return raiz;
    }
}


//============================ auxiliares ===================================

// ============================ MAIN =================================

int main(void)
{
    int i=0, escolha, regiao, opcaoCeia, confirm, choice;
    int grown = 0;
    char  *nomeCliente;

    int menu, listChoice, sair =0,  conf , aux1, aux2, aux3, aux4;

    Pedidos *pedidos = NULL;
    Entregas *entregas = NULL;

    //Menu inicial
    printf("\n deseja entrar de qual forma:\n");
    printf("1 - Com insercao manual dos dados\n");
    printf("2 - Gerar dados automaticos\n");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("\n\n====================== M E N U    P E D I D O S ===============================\n");
        do
        {
            do{
                printf("\nInforme a regiao do seu endereco seguindo o exemplo: \n");
                printf("\n1 - Regiao norte");
                printf("\n2 - Regiao centro norte");
                printf("\n3 - Regiao extremo norte");
                printf("\n4 - Regiao sul");
                printf("\n5 - Regiao centro sul");
                printf("\n6 - Regiao leste");
                printf("\n7 - Regiao oeste");
                printf("\n8 - Regiao centro oeste\n");

                scanf("%d", &regiao);
                if(regiao<1||regiao>8)
                {
                    printf("\nRegiao invalida, porfavor informe uma regiao existente\n");
                }
            }while( regiao<1||regiao>8);

            printf("\n\n==========================================================\n");

            nomeCliente = malloc(31);
            printf("\nInforme seu nome: \n");
            scanf("%s", nomeCliente);

            printf("\n\n==========================================================\n");
            
            do{
                printf("\nInforme a sua opcao de ceia: \n");
                printf("\n1 - Opcao 1");
                printf("\n2 - Opcao 2");
                printf("\n3 - Opcao 3");
                printf("\n4 - Opcao 4");
                printf("\n5 - Opcao 5\n");

                scanf("%d", &opcaoCeia);
                if(opcaoCeia<1||opcaoCeia>5)
                {
                    printf("\nOpcao invalida, porfavor informe uma opcao existente\n");
                }
            }while( opcaoCeia<1||opcaoCeia>5);

            //confirmar pedido:
        
            printf("\nOs dados do seu pedido estao corretos?\n");
            printf("Nome: %s\n", nomeCliente);
            printf("Opcao de ceia: %d\n", opcaoCeia);
            printf("Endereco: %d\n", regiao);
            printf("(1 caso sim, 0 caso nao)\n");
            scanf("%d", &confirm);
            if(confirm == 1)
            {
                struct tm *data_hora_atual;
                time_t segundos;
                time(&segundos);
                data_hora_atual = localtime(&segundos); 
                int mes, ano, dia, hora, min, seg;
                dia = data_hora_atual->tm_mday;
                mes = data_hora_atual->tm_mon+1;
                ano = data_hora_atual->tm_year+1900;
                hora = data_hora_atual->tm_hour;
                min = data_hora_atual->tm_min;
                seg = data_hora_atual->tm_sec;
                int hash = regiao*100-(rand()%100);
                pedidos = Inserir(pedidos, regiao, grown, opcaoCeia, nomeCliente, ano, mes, dia, hora, min, seg, hash);

            }
            
            printf("\nDeseja fazer um novo pedido? (1 caso sim 0 caso nao): \n");
            scanf("%d", &escolha);
            
        } while (escolha != 0);
    }
    else{

        // abre arquivo
        //TOME CUIDADO PARA INSERIR O CAMINHO CORRETO DO ARQUIVO NO SEU COMPUTADOR, CAMINHO ERRADO RESULTARA EM ERROS
        // MOCK_DATA.CVS = 1000 pedidos
        // MOCK_DATA(1).CVS = 100 pedidos

        FILE* fp = fopen("C:/Users/user/Desktop/ajuda/MOCK_DATA(1).csv", "r");
        if (fp == NULL) 
        {
            printf("Falha ao abrir o arquivo");
            return(1);
        }
        char aux[10];
        nomeCliente = malloc(31);
        while(fscanf(fp, "%d,%d,%s,", &regiao,  &opcaoCeia, nomeCliente)!= EOF){
            
            struct tm *data_hora_atual;
            time_t segundos;
            time(&segundos);
            data_hora_atual = localtime(&segundos); 
            int mes, ano, dia, hora, min, seg;
            dia = 1+rand()%30;
            mes = 1+rand()%12;
            ano = 2022;
            hora = rand()%23;
            min = rand()%59;
            seg = rand()%59;

            int hash = regiao*100-(rand()%100);
           
            pedidos = Inserir(pedidos, regiao, grown, opcaoCeia, nomeCliente, ano, mes, dia, hora, min, seg, hash);
           

        }

    }

    do
    {
        
        printf("\n================== Selecione o que deseja fazer ==========================\n");
        printf("\n1 - Listar Pedidos a serem entregues");
        printf("\n2 - Listar pedidos por regiao");
        printf("\n3 - Listar pedidos por mes");
        printf("\n4 - Listar pedidos por dia");
        printf("\n5 - Listar entregas\n");
        printf("\n6 - Fazer entregas");
        scanf("%d", &menu);

        if(menu == 1)
        {
           
            do{
                printf("\n================== Que tipo de listagem deseja ==========================\n");
                printf("\n1 - Prefixo");
                printf("\n2 - Infixo");
                scanf("%d", &listChoice);
                if(listChoice<1 || listChoice>2){
                    printf("Opcao invalida, porfavor selecione uma opcao:");
                }
                
            }while (listChoice<1 || listChoice>2);
            int ajuda = 0;
            if(listChoice == 1)
            {
                printf("\n\n====================== P E D I D O S ===============================\n");
                
                    ajuda = prefix(pedidos, ajuda);
                    if(ajuda!=0){
                        printf("\nNao existe pedidos a serem entregues!\n");
                    }
            }
            else{
                printf("\n\n====================== P E D I D O S ===============================\n");
             
                ajuda =infix(pedidos, ajuda);
                if(ajuda!=0){
                        printf("\nNao existe pedidos a serem entregues!\n");
                }

                
            }
            
        }
        else if(menu == 2){
            do{
                printf("\nSelecione a regiao que deseja mostrar:\n");
                printf("\n1 - Regiao norte");
                printf("\n2 - Regiao centro norte");
                printf("\n3 - Regiao extremo norte");
                printf("\n4 - Regiao sul");
                printf("\n5 - Regiao centro sul");
                printf("\n6 - Regiao leste");
                printf("\n7 - Regiao oeste");
                printf("\n8 - Regiao centro oeste\n");

                scanf("%d", &aux1);
                if(aux1<1||aux1>8)
                {
                    printf("\nOpcao invalida, porfavor informe uma opcao existente\n");
                }
            }while( aux1<1||aux1>8);
            
            printf("\n\n================= P E D I D O S    R E G I A O =====================\n");

            porRegiao(pedidos, aux1);

        }
        else if(menu == 3){

             do{
                printf("\nInsira o mes que deseja consultar:\n");
                scanf("%d", &aux2);
                if(aux2<1||aux2>12)
                {
                    printf("\nOpcao invalida, porfavor informe uma opcao existente\n");
                }
            }while( aux2<1||aux2>12);
            
            printf("\n\n================= P E D I D O S   P O R   M E S =====================\n");

            porMes(pedidos, aux2);

            
        }
        else if(menu == 4){
            int cont =0;
             do{
                printf("\nInsira o MES que deseja consultar:\n");
                scanf("%d", &aux3);
                if(aux3<1||aux3>12)
                {
                    printf("\nOpcao invalida, porfavor informe uma opcao existente\n");
                }
            }while( aux3<1||aux3>12);
            do{
                printf("\nInsira o DIA que deseja consultar:\n");
                scanf("%d", &aux4);
                if(aux4<1||aux4>31)
                {
                    printf("\nOpcao invalida, porfavor informe uma opcao existente\n");
                }
            }while( aux4<1||aux4>31);
            
            printf("\n\n================= P E D I D O S   P O R   D I A =====================\n");

            cont = porDia(pedidos, aux3, aux4, cont);
            if(cont == 0)
            {
                printf("\nNao existe pedido no dia de consulta!");
            }
            
            
        }
      
        else if(menu == 5){

             printf("\n\n====================== E N T R E G A S ===============================\n");
            if(entregas == NULL)
            {
                printf("\nNao existe entregas feitas!\n");
            }
            else{
                ordemEntregas(entregas);
            }
            
            
        }
        else if(menu == 6){

            int qtdGadores, col;
           
            printf("\n\n============ E N T R E G A S    R E A L I Z A D A S  =====================\n");
            int qtdMaxEntrega, i, id=1, cont=1;

            //TOME CUIDADO PARA INSERIR O CAMINHO CORRETO DO ARQUIVO NO SEU COMPUTADOR, CAMINHO ERRADO RESULTARA EM ERROS
            FILE* fp2 = fopen("C:/Users/user/Desktop/ajuda/MOCK_DATA(1).csv", "r");
            if (fp2 == NULL) 
            {
                printf("Falha ao abrir o arquivo");
                return(1);
            }
            char aux[10];
            nomeCliente = malloc(31);

            while(fscanf(fp2, "%d,%d,%s,", &regiao,  &opcaoCeia, nomeCliente)!= EOF){
                    
                int mes, ano, dia, hora, min, seg, cont=1;
                dia = 24;
                mes = 12;
                ano = 2022;
                hora = rand()%23;
                min = rand()%59;
                seg = rand()%59;
                cont += rand()%8;

                int hash = regiao*100-(rand()%100);
                
                entregas = inserirEntregas(entregas, regiao, grown, opcaoCeia, ano, mes, dia, hora, min, seg, hash, cont);
               
            
            }
             pedidos = destruirArvore(pedidos);

        }
        printf("\nDeseja sair da aplicacao? (1 caso sim)");
        scanf("%d", &sair);
        
    } while (sair != 1);
    


    return 0;
}