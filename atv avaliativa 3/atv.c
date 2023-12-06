#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct produto{

      int codigo;
      char descricao[100];
      int quantidade;
      double valorProduto;
      struct Produto *prox;
}Produto;

Produto* criarListaVazia(){
    return NULL;
}

Produto* adicionarProduto(){
    Produto *novoProduto = (Produto*)malloc(sizeof(Produto));  
    if(novoProduto == NULL){
        printf("erro de alocacao");
        exit(EXIT_FAILURE);
    }
    novoProduto->prox = NULL;
    return novoProduto;
}

Produto* cadastrar(Produto *lista){
    Produto *novoProduto = adicionarProduto();
    srand(time(NULL));
    printf("\nDigite o codigo: ");
    scanf("%d", &novoProduto->codigo);
    printf("\nDigite a descricao: ");
    fflush(stdin);
    fgets(novoProduto->descricao, sizeof(novoProduto->descricao), stdin);
    novoProduto->descricao[strcspn(novoProduto->descricao, "\n")] = '\0';
    printf("\nDigite a quantidade: ");
    fflush(stdin);
    scanf("%d", &novoProduto->quantidade);
    fflush(stdin);
    printf("\nDigite o valor: ");
    scanf("%lf", &novoProduto->valorProduto);
    fflush(stdin);

    if(lista == NULL){
        return novoProduto;
    }else{
        Produto *atual = lista;
        while(atual->prox!=NULL){
            atual = atual->prox;
        }
        atual->prox = novoProduto;
        return lista;
    }

}

void gerarRelatorio(Produto *lista){
    if(lista == NULL){
        printf("\nProduto inexistente\n");
        return;
    }else{
        Produto *atual = lista;
        while(atual != NULL){
            printf("\nCodigo do Produto: %d", atual->codigo);
            printf("\nDescricao: %s", atual->descricao);
            printf("\nQuantida: %d", atual->quantidade);
            printf("\nValor do Produto: %lf", atual->valorProduto);
            atual = atual->prox;
        }
    }

}

Produto* consultarProduto(Produto *lista, int codigoBusca){
    if(lista == NULL){
        printf("Produto inexistente");
        return;
    }else{
        Produto *atual = lista;
        while(atual != NULL){
            if(atual->codigo == codigoBusca){
                printf("\nCodigo do Produto: %d", atual->codigo);
                printf("\nDescricao: %s", atual->descricao);
                printf("\nQuantida: %d", atual->quantidade);
                printf("\nValor do Produto: %lf", atual->valorProduto);
                return atual;
                }
                atual = atual->prox;
            }
            printf("\nProduto nao encontrado");
            return NULL;
    }
}

Produto* removerProduto(Produto *lista, int codigoBusca){
    Produto *anterior = NULL;
    Produto *atual = lista;

    while(atual != NULL && atual->codigo != codigoBusca){
        anterior = atual;
        atual = atual->prox;
    }
    if(atual != NULL){
        if(anterior != NULL){

            anterior->prox = atual->prox;

        }else{
            lista = atual->prox;
        }
        free(atual);
        printf("\nProduto excluido");

    }else{
         printf("\nPRODUTO NAO CADASTRADO!\n");
    }
    return lista;

}

void liberarLista(Produto *lista){
    Produto *atual = lista;
    Produto *proximoProduto;
    while(atual != NULL){
        proximoProduto = atual->prox;
        free(atual);
        atual = proximoProduto;
    }
}

main(){
    int opcao, codigoBusca;
    Produto *lista = criarListaVazia();
    Produto *encontrada;

    do{
       printf("\n        MENU         \n");
       printf("\n|1| - Cadastrar");
       printf("\n|2| - Gerar Relatorio");
       printf("\n|3| - Consultar Produtos");
       printf("\n|4| - Remover Produtos");
       printf("\n|0| - sair\n");
       scanf("%d", &opcao);
       switch(opcao){
            case 1:
                 lista = cadastrar(lista);
            break;
            case 2:
                 gerarRelatorio(lista);
            break;
            case 3:
                 printf("Insira o codigo para consultar produto: ");
                 scanf("%d",&codigoBusca);
                 encontrada = consultarProduto(lista, codigoBusca);
            break;
            case 4:
                 printf("Digite o codigo para buscar: ");
                 scanf("%d",&codigoBusca);
                 lista = removerProduto(lista, codigoBusca);
            break;
       }

    }while(opcao != 0);
    liberarLista(lista);
}