#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_PLAYERS 50

typedef struct equipe{
    char nome[50];
    char nicknameRedeSocial[20];
    int seguidores;
} EQUIPE;

typedef struct campeonato{
    int pontuacao;
    int vitorias;
    int derrotas;
    int empates;
} CAMPEONATO;

typedef struct hardware{
    char modeloMaquinario[30];
    char processador[20];
    char placaDeVideo[20];
    int memoriaRAM;
} HARDWARE;

typedef struct data{
    int dia;
    int mes;
    int ano;
}DATA;

typedef enum genero {masculino, feminino, prefiroNaoDizer} GENERO;
typedef enum estado_civil {solteiro, divorciado, casado, viuvo, separado} estadoCivil;

typedef struct Player{
    char nome[100];
    DATA dataNascimento;
    char cpf[12];
    GENERO genero[20];
    estadoCivil estado_civil[15];
    EQUIPE equipe;
    char patrocinador[30];
    char rede_social_username[50];
    int seguidores_rede_social;
    HARDWARE hardware;
    CAMPEONATO campeonato;
    int titulos;
    int posicaoRank;
} PLAYER;

void cadastrarJogador(PLAYER jogadores[], int *numJogadores) {
    int cont = 0;
        for(int i = 0; i < *numJogadores; i++){
            // Nome
            printf("Nome do jogador: ");
            fflush(stdin);
            gets(jogadores[i].nome);
            fflush(stdin);

            // Data de nascimento
            printf("Digite a sua data de nascimento\n ");
            printf("O dia: ");
            fflush(stdin);
            gets(jogadores[i].dataNascimento.dia);
            fflush(stdin);
            gets(jogadores[i].dataNascimento.mes);
            fflush(stdin);
            gets(jogadores[i].dataNascimento.ano);
            fflush(stdin);

            // CPF
            printf("CPF (11 digitos): ");
            scanf("%d", &jogadores[i].cpf);

            // Genero
            printf("Genero: ");
            fflush(stdin);
            gets(jogadores[i].genero);
            fflush(stdin);

            // Estado Civil
            printf("Estado civil: ");
            fflush(stdin);
            gets(jogadores[i].estado_civil);
            fflush(stdin);

            // Equipe
            printf("Nome da equipe: ");
            fflush(stdin);
            gets(jogadores[i].equipe.nome);
            fflush(stdin);
            printf("Qual o username da equipe no Instagram? ");
            fflush(stdin);
            gets(jogadores[i].equipe.nicknameRedeSocial);
            fflush(stdin);
            printf("Quantos seguidores essa equipe tem no Instagram?");
            fflush(stdin);
            scanf("%d", &jogadores[i].equipe.seguidores);
            fflush(stdin);

            // Patrocinador
            printf("Qual o principal patrocinador deste jogador?");
            fflush(stdin);
            gets(jogadores[i].patrocinador);
            fflush(stdin);

            // Rede social
            printf("Nome de usuario do Instagram: ");
            fflush(stdin);
            gets(jogadores[i].rede_social_username);
            fflush(stdin);
            printf("Digite a quantidade de seguidores nessa mesma rede social: ");
            scanf("%d", &jogadores[i].seguidores_rede_social);

            // Hardware
            printf("Qual o modelo do computador/notebook usado?");
            fflush(stdin);
            gets(jogadores[i].hardware.modeloMaquinario);
            fflush(stdin);
            printf("O seu processador: ");
            fflush(stdin);
            gets(jogadores[i].hardware.processador);
            fflush(stdin);
            printf("A sua placa de video: ");
            fflush(stdin);
            gets(jogadores[i].hardware.placaDeVideo);
            fflush(stdin);
            printf("A quantidade de Memoria RAM(8/16/24/32/64): ");
            scanf("%d", &jogadores[i].hardware.memoriaRAM);

            // Campeonato
            printf("Digite a quantidade de VITORIAS do jogador");
            scanf("%d", &jogadores[i].campeonato.vitorias);
            printf("Digite a quantidade de EMPATES do jogador");
            scanf("%d", &jogadores[i].campeonato.empates);
            printf("Digite a quantidade de DERROTAS do jogador");
            scanf("%d", &jogadores[i].campeonato.derrotas);

            // Quantidade de titulos
            printf("Digite quantos titulos esse jogador ja ganhou: ");
            scanf("%d", &jogadores[i].titulos);

            // Posicao no rank 
            printf("Digite a posicao que esse jogador se encontra no ranque mundial: ");
            scanf("%d", &jogadores[i].posicaoRank);

            printf("\nO %d jogador foi cadastrado\n\n");
            cont++; 
        }
    printf("Foram cadastrados %d jogadores!", cont);
}

void escreverCadastroJogador(PLAYER jogadores[], int numJogadores){
    FILE *file;
    file = fopen("sistema.dat", "wb");
    if(file == NULL){
        printf("O arquivo nao foi aberto :(");
    }
    int qtdRegistros = fwrite(jogadores, sizeof(PLAYER), numJogadores, file);
    printf("\nForam inscritos %d jogadores!\n", qtdRegistros);
    fclose(file);
}

void listarJogadores(PLAYER jogadores[], int numJogadores) {
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

void removerJogador(PLAYER jogadores[], int *numJogadores, char cpf[]) {
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
    int opcao, numJogadores;
    PLAYER jogadores[MAX_PLAYERS];
    printf("\n\tSistema de competicao de E-Sports\n\n");
    printf("Digite a quantidade de jogaodres\n");
    printf("A quantidade de jogadores DEVE ser MAIOR OU IGUAL a 30 e MENOR OU IGUAL a 50: ");
    scanf("%d", &numJogadores);
        do{
            printf("Digite uma quantidade valida para avancar!\n");
            printf("Lembrando que DEVE ser MAIOR OU IGUAL a 30 e MENOR OU IGUAL a 50: ");
        }while(numJogadores < 30 || numJogadores > 50);
        while (1) {
            printf("\n1. Cadastrar jogador\n");
            printf("2. Alteracao de dados do jogador\n");
            printf("3. Atualização dos jogos e pontuacao\n");
            printf("4. Listagem ALFABELTICA dos jogadores\n");
            printf("5. Listagem POR POSICAO dos jogadores\n");
            printf("6. Listagem POR VITORIA dos jogadores\n");
            printf("7. Classificacao do campeonato\n");
            printf("8. Listagem de jogadores com pontuacao MAIOR que certa pontuacao\n");
            printf("9. Listagem de jogadores com pontuacao MENOR que certa pontuacao\n");
            printf("10. Busca de jogador POR NOME\n");
            printf("11. Busca de jogador POR POSICAO no rank\n");
            printf("12. Media de seguidores de um jogador\n");
            printf("13. Sair");
            printf("Escolha a opcao: ");
            scanf("%d", &opcao);
                switch (opcao) {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                        break;
                    case 9:
                        break;
                    case 10:
                        break;
                    case 11:
                        break;
                    case 12:
                        break;
                    case 13:
                        return 0;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                }
        }

    return 0;
}
