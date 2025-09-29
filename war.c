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

void exibirTerritorios(Territorio* territorios, int n) {
    printf("\n==== Territórios ====\n");
    for (int i = 0; i < n; i++) {
        printf("ID %d | Nome: %s | Cor: %s | Tropas: %d\n",
               i, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    printf("\nBatalha: %s (%s) x %s (%s)\n", atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);
    if (dadoAtacante > dadoDefensor) {
        printf(">>> Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;
    } else {
        printf(">>> Defensor resistiu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int index = rand() % totalMissoes;
    strcpy(destino, missoes[index]);
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int cont = 0;
        char corAnterior[10] = "";
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corAnterior) == 0) {
                cont++;
                if (cont >= 3) return 1;
            } else {
                strcpy(corAnterior, mapa[i].cor);
                cont = 1;
            }
        }
        return 0;
    }
    if (strcmp(missao, "Ter mais de 10 tropas em um território") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 10) return 1;
        }
        return 0;
    }
    if (strcmp(missao, "Conquistar todos os territórios de cor azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    }
    if (strcmp(missao, "Manter pelo menos 1 território com 5 tropas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 5) return 1;
        }
        return 0;
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int n;
    printf("Número de territórios: ");
    scanf("%d", &n);

    Territorio* territorios = malloc(n * sizeof(Territorio));

    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Ter mais de 10 tropas em um território",
        "Conquistar todos os territórios de cor azul",
        "Manter pelo menos 1 território com 5 tropas"
    };
    int totalMissoes = 5;

    char* missaoJogador = malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("\nSua missão: %s\n", missaoJogador);

    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d\n", i);
        printf("Nome: ");
        scanf(" %[^\n]", territorios[i].nome);
        printf("Cor: ");
        scanf(" %[^\n]", territorios[i].cor);
        printf("Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    while (1) {
        exibirTerritorios(territorios, n);

        int idAtacante, idDefensor;
        printf("Escolha ID do atacante: ");
        scanf("%d", &idAtacante);
        printf("Escolha ID do defensor: ");
        scanf("%d", &idDefensor);

        if (idAtacante < 0 || idAtacante >= n || idDefensor < 0 || idDefensor >= n) {
            printf("IDs inválidos. Tente novamente.\n");
            continue;
        }

        if (strcmp(territorios[idAtacante].cor, territorios[idDefensor].cor) == 0) {
            printf("Não pode atacar territórios da mesma cor.\n");
            continue;
        }

        atacar(&territorios[idAtacante], &territorios[idDefensor]);

        if (verificarMissao(missaoJogador, territorios, n)) {
            printf("\nParabéns! Você cumpriu sua missão: %s\n", missaoJogador);
            break;
        }
    }

    free(territorios);
    free(missaoJogador);

    return 0;
}
