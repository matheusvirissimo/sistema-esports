#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MIN_PLAYERS 30

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
        for(int i = 0; i < *numJogadores; i++){
            printf("Nome do jogador: ");
            fflush(stdin);
            gets(jogadores[i].nome);
            fflush(stdin);
            printf("Digite a sua idade de nascimento\n(dd/mm/aaaa): ");
            fflush(stdin);
            gets(jogadores[i].data_nascimento);
            fflush(stdin);
            printf("CPF (11 digitos): ");
            scanf("%d", &jogadores[i].cpf);
            printf("Genero: ");
            fflush(stdin);
            gets(jogadores[i].genero);
            fflush(stdin);
            printf("Estado civil: ");
            fflush(stdin);
            gets(jogadores[i].estado_civil);
            fflush(stdin);
            printf("Nome da equipe: ");
            fflush(stdin);
            gets(jogadores[i].equipe_nome);
            fflush(stdin);
            printf("Nome de usuario da rede social: ");
            fflush(stdin);
            gets(jogadores[i].rede_social_username);
            fflush(stdin);
            printf("Digite a quantidade de seguidores nas redes sociais do jogador: ");
            scanf("%d", &jogadores[i].seguidores_rede_social);
            printf("\nO %d jogador foi cadastrado\n\n");
        }
    printf("Foram cadastrados %d jogadores!", numJogadores);
}

void listarJogadores(struct Player jogadores[], int numJogadores) {
    if (numJogadores > 0) {
        printf("Lista de Jogadores:\n");
        for (int i = 0; i < numJogadores; i++) {
            printf("%d Jogador:\n", i + 1);
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
    int numJogadores = 0;
    int opcao;
    char cpf[12];
    printf("\n\tSistema de competicao de E-Sports\n\n");
    printf("Digite a quantidade de jogadores\n(DEVE SER MAIOR que 30: ");
    scanf("%d", &numJogadores);
        do{
            printf("A quantidade de jogadores deve ser maior que 30!");
            printf("\nDigite novamente a quantidade: ");
            scanf("%d", &numJogadores);
        }while(numJogadores < MIN_PLAYERS);
    struct Player jogadores[numJogadores];
    while (1) {
        printf("\n1. Cadastrar jogador\n");
        printf("2. Listar jogadores\n");
        printf("3. Remover jogador\n");
        printf("4. Sair\n\n");
        printf("Escolha a opção: ");
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
