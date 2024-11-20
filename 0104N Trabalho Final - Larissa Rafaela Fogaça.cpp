#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct tree {
    int num; // Informação
    struct tree* right; // Subárvore à direita
    struct tree* left; // Subárvore à esquerda
} Tree;

/* Função que cria uma árvore */
Tree* createTree() {
    return NULL; // Árvore vazia
}

/* Função que verifica se uma árvore é vazia */
int treeIsEmpty(Tree* t) {
    return t == NULL;
}

/* Função que mostra a informação da árvore */
void showTree(Tree* t) {
    if (!treeIsEmpty(t)) {
        showTree(t->left); // Mostra a subárvore à esquerda
        printf("%d ", t->num); // Mostra o nó atual
        showTree(t->right); // Mostra a subárvore à direita
    }
}

/* Função que insere um dado na árvore */
void insertTree(Tree** t, int num) {
    if (*t == NULL) {
        *t = (Tree*)malloc(sizeof(Tree));
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->num = num;
    } else {
        if (num < (*t)->num) {
            insertTree(&(*t)->left, num);
        } else if (num > (*t)->num) {
            insertTree(&(*t)->right, num);
        } else {
            printf("O número %d já foi inserido na Árvore Binária! \n", num);
        }
    }
}

/* Função que verifica se um elemento pertence ou não à árvore */
int isInTree(Tree* t, int num) {
    if (treeIsEmpty(t)) {
        return 0;
    }
    return t->num == num || isInTree(t->left, num) || isInTree(t->right, num);
}

/* Função auxiliar para encontrar o maior entre dois números */
int maior(int a, int b) {
    return (a > b) ? a : b;
}

/* Função que retorna a altura da árvore */
int height(Tree* t) {
    if (t == NULL || (t->left == NULL && t->right == NULL)) {
        return 0;
    } else {
        return 1 + maior(height(t->left), height(t->right));
    }
}

/* Função que conta o número de folhas */
int countLeaves(Tree* t) {
    if (t == NULL) {
        return 0;
    }
    if (t->left == NULL && t->right == NULL) {
        return 1;
    }
    return countLeaves(t->left) + countLeaves(t->right);
}

/* Função que conta o número total de nós */
int countNodes(Tree* t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + countNodes(t->left) + countNodes(t->right);
}

/* Função recursiva para calcular a análise combinatória: C(n, p) */
int combinatory(int n, int p) {
    if (p == 0 || p == n) {
        return 1; // Base: C(n, 0) = C(n, n) = 1
    }
    return combinatory(n - 1, p - 1) + combinatory(n - 1, p); // Recursão
}

/* Função que remove um elemento da árvore */
void removeTree(Tree** t, int num) {
    if (*t == NULL) {
        printf("Elemento %d não existe na árvore!\n", num);
        return;
    }
    if (num < (*t)->num) {
        removeTree(&(*t)->left, num);
    } else if (num > (*t)->num) {
        removeTree(&(*t)->right, num);
    } else {
        Tree* aux = *t;
        if ((*t)->left == NULL && (*t)->right == NULL) { // Caso 1: Nó folha
            free(aux);
            *t = NULL;
            printf("Elemento %d removido com sucesso!\n", num);
        } else if ((*t)->left == NULL) { // Caso 2: Nó com subárvore direita
            *t = (*t)->right;
            aux->right = NULL;
            free(aux);
            printf("Elemento %d removido com sucesso!\n", num);
        } else if ((*t)->right == NULL) { // Caso 2: Nó com subárvore esquerda
            *t = (*t)->left;
            aux->left = NULL;
            free(aux);
            printf("Elemento %d removido com sucesso!\n", num);
        } else { // Caso 3: Nó com duas subárvores
            Tree* maiorEsq = (*t)->left;
            while (maiorEsq->right != NULL) {
                maiorEsq = maiorEsq->right;
            }
            (*t)->num = maiorEsq->num; // Substitui o valor pelo maior à esquerda
            removeTree(&(*t)->left, maiorEsq->num); // Remove o nó substituído
            printf("Elemento %d removido com sucesso!\n", num);
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    printf("********* Árvore Binária ********\n");
    printf("Disciplina de Estrutura de Dados 2 \n");
    printf("      Larissa Rafaela Fogaca       \n");
    printf("      Trabalho Final 0104N         \n");
    printf("*********************************\n\n");

    Tree* t = NULL; 
    int opcao, novo, elemento, n, p, resultado;

    while (1) {
        printf("\n****************** MENU ******************\n");
        printf("1 - Criar Árvore Binária \n");
        printf("2 - Inserir elemento na Árvore Binária \n");
        printf("3 - Remover elemento na Árvore Binária \n");
        printf("4 - Buscar elemento na Árvore Binária \n");
        printf("5 - Mostrar a Árvore Binária em ordem \n");
        printf("6 - Mostrar altura da Árvore Binária \n");
        printf("7 - Calcular análise combinatória e inserir resultado na árvore \n");
        printf("8 - Contar folhas e nós \n");
        printf("0 - Sair \n");
        printf("******************************************\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                t = createTree();
                printf("Árvore criada!\n");
                break;
            case 2:
                printf("Digite o novo número a ser inserido na árvore: \n");
                scanf("%d", &novo);
                insertTree(&t, novo);
                break;
            case 3:
                printf("Digite o número a ser removido da árvore: \n");
                scanf("%d", &elemento);
                removeTree(&t, elemento);
                break;
            case 4:
                printf("Digite o número a ser buscado na árvore: \n");
                scanf("%d", &elemento);
                if (isInTree(t, elemento)) {
                    printf("O número %d pertence à árvore!\n", elemento);
                } else {
                    printf("O número %d não pertence à árvore!\n", elemento);
                }
                break;
            case 5: 
   			      if (treeIsEmpty(t)) { 
                printf("Árvore está vazia. Favor adicionar um número na árvore.\n");
  				  } else {
       			 showTree(t); 
       			 printf("\n");
   				 }
                break;
            case 6:
                printf("A altura da árvore é: %d\n", height(t));
                break;
            case 7:
                printf("Digite os valores de n e p para calcular a análise combinatória (C(n, p)): \n");
                scanf("%d %d", &n, &p);
                resultado = combinatory(n, p);
                printf("O resultado de C(%d, %d) é: %d\n", n, p, resultado);
                insertTree(&t, resultado); 
                break;
            case 8:
                printf("Número total de folhas: %d\n", countLeaves(t));
                printf("Número total de nós: %d\n", countNodes(t));
                break;
            case 0:
                printf("Saindo do programa...\n");
                exit(0);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}

