#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_PLAYERS 30

struct Player {
    char nome[100];
    char data_nascimento[11];
    char cpf[12];
    char genero[20];
    char estado_civil[20];
    char equipe_nome[50];
    char rede_social_username[50];
    int seguidores_rede_social;
};

void cadastrarJogador(struct Player jogadores[], int *numJogadores) {
    if (*numJogadores < MAX_PLAYERS) {
        struct Player jogador;
        printf("Nome: ");
        scanf("%s", jogador.nome);
        printf("Data de Nascimento (dd/mm/yyyy): ");
        scanf("%s", jogador.data_nascimento);
        printf("CPF (11 dígitos): ");
        scanf("%s", jogador.cpf);
        printf("Gênero: ");
        scanf("%s", jogador.genero);
        printf("Estado Civil: ");
        scanf("%s", jogador.estado_civil);
        printf("Nome da Equipe: ");
        scanf("%s", jogador.equipe_nome);
        printf("Username da Rede Social: ");
        scanf("%s", jogador.rede_social_username);
        printf("Número de Seguidores na Rede Social: ");
        scanf("%d", &jogador.seguidores_rede_social);

        jogadores[*numJogadores] = jogador;
        (*numJogadores)++;

        printf("\nJogador cadastrado com sucesso!\n");
    } else {
        printf("\nLimite de jogadores atingido.\n");
    }
}

void listarJogadores(struct Player jogadores[], int numJogadores) {
    if (numJogadores > 0) {
        printf("Lista de Jogadores:\n");
        for (int i = 0; i < numJogadores; i++) {
            printf("Jogador %d:\n", i + 1);
            printf("Nome: %s\n", jogadores[i].nome);
            printf("Data de Nascimento: %s\n", jogadores[i].data_nascimento);
            printf("CPF: %s\n", jogadores[i].cpf);
            printf("Gênero: %s\n", jogadores[i].genero);
            printf("Estado Civil: %s\n", jogadores[i].estado_civil);
            printf("Nome da Equipe: %s\n", jogadores[i].equipe_nome);
            printf("Username da Rede Social: %s\n", jogadores[i].rede_social_username);
            printf("Número de Seguidores na Rede Social: %d\n", jogadores[i].seguidores_rede_social);
            printf("\n------------------------------------\n");
        }
    } else {
        printf("Nenhum jogador cadastrado ainda.\n");
    }
}

void removerJogador(struct Player jogadores[], int *numJogadores, char cpf[]) {
    for (int i = 0; i < *numJogadores; i++) {
        if (strcmp(jogadores[i].cpf, cpf) == 0) {
            for (int j = i; j < *numJogadores - 1; j++) {
                jogadores[j] = jogadores[j + 1];
            }
            (*numJogadores)--;
            printf("Jogador com CPF %s removido.\n", cpf);
            return;
        }
    }
    printf("Jogador com CPF %s não encontrado.\n", cpf);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    struct Player jogadores[MAX_PLAYERS];
    int numJogadores = 0;
    int opcao;
    char cpf[12];

    while (1) {
        printf("\nSistema de competição de E-Sports\n");
        printf("\n1. Cadastrar jogador\n");
        printf("2. Listar jogadores\n");
        printf("3. Remover jogador\n");
        printf("4. Sair\n");
        printf("\nEscolha a opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarJogador(jogadores, &numJogadores);
                break;
            case 2:
                listarJogadores(jogadores, numJogadores);
                break;
            case 3:
                printf("Digite o CPF do jogador a ser removido: ");
                scanf("%s", cpf);
                removerJogador(jogadores, &numJogadores, cpf);
                break;
            case 4:
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
