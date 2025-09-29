#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

typedef struct Territorio Territorio;

Territorio* alocarMapa(int n);
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(const Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio* mapa = alocarMapa(n);

    cadastrarTerritorios(mapa, n);

    printf("\n=== Territórios Iniciais ===\n");
    exibirTerritorios(mapa, n);

    int idxAtacante, idxDefensor;
    printf("\nEscolha o território atacante (1 a %d): ", n);
    scanf("%d", &idxAtacante);
    printf("Escolha o território defensor (1 a %d): ", n);
    scanf("%d", &idxDefensor);

    if (idxAtacante < 1 || idxAtacante > n || idxDefensor < 1 || idxDefensor > n || idxAtacante == idxDefensor) {
        printf("Escolha inválida!\n");
    } else if (strcmp(mapa[idxAtacante - 1].cor, mapa[idxDefensor - 1].cor) == 0) {
        printf("Você não pode atacar um território da mesma cor!\n");
    } else {
        atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);
    }

    printf("\n=== Situação Após Ataque ===\n");
    exibirTerritorios(mapa, n);

    liberarMemoria(mapa);

    return 0;
}

Territorio* alocarMapa(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    return mapa;
}

void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do Território %d\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirTerritorios(const Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n>>> Iniciando ataque de %s contra %s...\n", atacante->nome, defensor->nome);

    int dadoAtacante = (rand() % 6) + 1; // dado de 1 a 6
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas /= 2;
        if (defensor->tropas < 1) defensor->tropas = 1;
    } else {
        printf("O defensor resistiu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}
