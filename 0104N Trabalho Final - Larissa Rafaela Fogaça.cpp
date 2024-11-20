#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct tree {
    int num; // Informa��o
    struct tree* right; // Sub�rvore � direita
    struct tree* left; // Sub�rvore � esquerda
} Tree;

/* Fun��o que cria uma �rvore */
Tree* createTree() {
    return NULL; // �rvore vazia
}

/* Fun��o que verifica se uma �rvore � vazia */
int treeIsEmpty(Tree* t) {
    return t == NULL;
}

/* Fun��o que mostra a informa��o da �rvore */
void showTree(Tree* t) {
    if (!treeIsEmpty(t)) {
        showTree(t->left); // Mostra a sub�rvore � esquerda
        printf("%d ", t->num); // Mostra o n� atual
        showTree(t->right); // Mostra a sub�rvore � direita
    }
}

/* Fun��o que insere um dado na �rvore */
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
            printf("O n�mero %d j� foi inserido na �rvore Bin�ria! \n", num);
        }
    }
}

/* Fun��o que verifica se um elemento pertence ou n�o � �rvore */
int isInTree(Tree* t, int num) {
    if (treeIsEmpty(t)) {
        return 0;
    }
    return t->num == num || isInTree(t->left, num) || isInTree(t->right, num);
}

/* Fun��o auxiliar para encontrar o maior entre dois n�meros */
int maior(int a, int b) {
    return (a > b) ? a : b;
}

/* Fun��o que retorna a altura da �rvore */
int height(Tree* t) {
    if (t == NULL || (t->left == NULL && t->right == NULL)) {
        return 0;
    } else {
        return 1 + maior(height(t->left), height(t->right));
    }
}

/* Fun��o que conta o n�mero de folhas */
int countLeaves(Tree* t) {
    if (t == NULL) {
        return 0;
    }
    if (t->left == NULL && t->right == NULL) {
        return 1;
    }
    return countLeaves(t->left) + countLeaves(t->right);
}

/* Fun��o que conta o n�mero total de n�s */
int countNodes(Tree* t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + countNodes(t->left) + countNodes(t->right);
}

/* Fun��o recursiva para calcular a an�lise combinat�ria: C(n, p) */
int combinatory(int n, int p) {
    if (p == 0 || p == n) {
        return 1; // Base: C(n, 0) = C(n, n) = 1
    }
    return combinatory(n - 1, p - 1) + combinatory(n - 1, p); // Recurs�o
}

/* Fun��o que remove um elemento da �rvore */
void removeTree(Tree** t, int num) {
    if (*t == NULL) {
        printf("Elemento %d n�o existe na �rvore!\n", num);
        return;
    }
    if (num < (*t)->num) {
        removeTree(&(*t)->left, num);
    } else if (num > (*t)->num) {
        removeTree(&(*t)->right, num);
    } else {
        Tree* aux = *t;
        if ((*t)->left == NULL && (*t)->right == NULL) { // Caso 1: N� folha
            free(aux);
            *t = NULL;
            printf("Elemento %d removido com sucesso!\n", num);
        } else if ((*t)->left == NULL) { // Caso 2: N� com sub�rvore direita
            *t = (*t)->right;
            aux->right = NULL;
            free(aux);
            printf("Elemento %d removido com sucesso!\n", num);
        } else if ((*t)->right == NULL) { // Caso 2: N� com sub�rvore esquerda
            *t = (*t)->left;
            aux->left = NULL;
            free(aux);
            printf("Elemento %d removido com sucesso!\n", num);
        } else { // Caso 3: N� com duas sub�rvores
            Tree* maiorEsq = (*t)->left;
            while (maiorEsq->right != NULL) {
                maiorEsq = maiorEsq->right;
            }
            (*t)->num = maiorEsq->num; // Substitui o valor pelo maior � esquerda
            removeTree(&(*t)->left, maiorEsq->num); // Remove o n� substitu�do
            printf("Elemento %d removido com sucesso!\n", num);
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    printf("********* �rvore Bin�ria ********\n");
    printf("Disciplina de Estrutura de Dados 2 \n");
    printf("      Larissa Rafaela Fogaca       \n");
    printf("      Trabalho Final 0104N         \n");
    printf("*********************************\n\n");

    Tree* t = NULL; 
    int opcao, novo, elemento, n, p, resultado;

    while (1) {
        printf("\n****************** MENU ******************\n");
        printf("1 - Criar �rvore Bin�ria \n");
        printf("2 - Inserir elemento na �rvore Bin�ria \n");
        printf("3 - Remover elemento na �rvore Bin�ria \n");
        printf("4 - Buscar elemento na �rvore Bin�ria \n");
        printf("5 - Mostrar a �rvore Bin�ria em ordem \n");
        printf("6 - Mostrar altura da �rvore Bin�ria \n");
        printf("7 - Calcular an�lise combinat�ria e inserir resultado na �rvore \n");
        printf("8 - Contar folhas e n�s \n");
        printf("0 - Sair \n");
        printf("******************************************\n");
        printf("Op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                t = createTree();
                printf("�rvore criada!\n");
                break;
            case 2:
                printf("Digite o novo n�mero a ser inserido na �rvore: \n");
                scanf("%d", &novo);
                insertTree(&t, novo);
                break;
            case 3:
                printf("Digite o n�mero a ser removido da �rvore: \n");
                scanf("%d", &elemento);
                removeTree(&t, elemento);
                break;
            case 4:
                printf("Digite o n�mero a ser buscado na �rvore: \n");
                scanf("%d", &elemento);
                if (isInTree(t, elemento)) {
                    printf("O n�mero %d pertence � �rvore!\n", elemento);
                } else {
                    printf("O n�mero %d n�o pertence � �rvore!\n", elemento);
                }
                break;
            case 5: 
   			      if (treeIsEmpty(t)) { 
                printf("�rvore est� vazia. Favor adicionar um n�mero na �rvore.\n");
  				  } else {
       			 showTree(t); 
       			 printf("\n");
   				 }
                break;
            case 6:
                printf("A altura da �rvore �: %d\n", height(t));
                break;
            case 7:
                printf("Digite os valores de n e p para calcular a an�lise combinat�ria (C(n, p)): \n");
                scanf("%d %d", &n, &p);
                resultado = combinatory(n, p);
                printf("O resultado de C(%d, %d) �: %d\n", n, p, resultado);
                insertTree(&t, resultado); 
                break;
            case 8:
                printf("N�mero total de folhas: %d\n", countLeaves(t));
                printf("N�mero total de n�s: %d\n", countNodes(t));
                break;
            case 0:
                printf("Saindo do programa...\n");
                exit(0);
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}

