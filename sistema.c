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
    char cpf[15];
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

void escreverBinario(PLAYER jogadores[], int numJogadores){
    FILE *file;
    file = fopen("sistema.dat", "rb+");
    if(file == NULL){
        printf("O arquivo não foi aberto ;(");
    }
    int qtsRegEscritos = fwrite(jogadores, sizeof(PLAYER), numJogadores, file);
    printf("\nFoi escrito %d registro(s) de jogador(es)!\n", qtsRegEscritos);
    fclose(file);
}

void lerBinario(PLAYER jogadores[], int numJogadores){
    FILE *file;
    file = fopen("sistema.dat", "rb");
    if(file == NULL){
        printf("O arquivo não foi aberto ;(");
    }
    int qtdRegLidos;
    qtdRegLidos = fread(jogadores, sizeof(PLAYER), numJogadores, file); 
    printf("\nForam lidos %d registro(s) de jogador(es)!\n", qtdRegLidos);
    fclose(file);
    return;
}

void cadastrarJogador(PLAYER jogadores[], int numJogadores) {
    int cont = 0;
        for(int i = 0; i < numJogadores; i++){
            // Nome
            printf("\nNome do jogador: ");
            fflush(stdin);
            gets(jogadores[i].nome);
            fflush(stdin);

            // Data de nascimento
            printf("\nDigite a sua data de nascimento\n");
            printf("O dia: ");
            scanf("%d", &jogadores[i].dataNascimento.dia);
            printf("O mes (em numero): ");
            scanf("%d", &jogadores[i].dataNascimento.mes);
            printf("O ano: "); 
            scanf("%d", &jogadores[i].dataNascimento.ano);

            // CPF
            printf("\nCPF (11 digitos): ");
            fflush(stdin);
            gets(jogadores[i].cpf);
            fflush(stdin);

            // Genero
            printf("\nGenero: ");
            fflush(stdin);
            gets(jogadores[i].genero);
            fflush(stdin);

            // Estado Civil
            printf("\nEstado civil: ");
            fflush(stdin);
            gets(jogadores[i].estado_civil);
            fflush(stdin);

            // Equipe
            printf("\nNome da equipe: ");
            fflush(stdin);
            gets(jogadores[i].equipe.nome);
            fflush(stdin);
            printf("O username DA EQUIPE no Instagram: @");
            fflush(stdin);
            gets(jogadores[i].equipe.nicknameRedeSocial);
            fflush(stdin);
            printf("Quantidade de seguidores DA EQUIPE no Instagram: ");
            fflush(stdin);
            scanf("%d", &jogadores[i].equipe.seguidores);
            fflush(stdin);

            // Patrocinador
            printf("\nO principal patrocinador deste jogador: ");
            fflush(stdin);
            gets(jogadores[i].patrocinador);
            fflush(stdin);

            // Rede social
            printf("\nNome de usuario do Instagram do jogador: @");
            fflush(stdin);
            gets(jogadores[i].rede_social_username);
            fflush(stdin);
            printf("Digite a quantidade de seguidores nessa mesma rede social: ");
            scanf("%d", &jogadores[i].seguidores_rede_social);

            // Hardware
            printf("\nQual o modelo do computador/notebook usado: ");
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
            printf("\nDigite a quantidade de VITORIAS do jogador: ");
            scanf("%d", &jogadores[i].campeonato.vitorias);
            int vitoria = jogadores[i].campeonato.vitorias;
            printf("Digite a quantidade de EMPATES do jogador: ");
            scanf("%d", &jogadores[i].campeonato.empates);
            int empate = jogadores[i].campeonato.empates;
            printf("Digite a quantidade de DERROTAS do jogador: ");
            scanf("%d", &jogadores[i].campeonato.derrotas);

            int pontos = vitoria*3 + empate*1; 
            jogadores[i].campeonato.pontuacao = pontos;

            // Quantidade de titulos
            printf("\nDigite quantos titulos esse jogador ja ganhou: ");
            scanf("%d", &jogadores[i].titulos);

            // Posicao no rank 
            printf("\nDigite a posicao que esse jogador se encontra no ranque mundial: ");
            scanf("%d", &jogadores[i].posicaoRank);

            printf("\nO %d jogador foi cadastrado\n\n", i+1);
            cont++; 

            escreverBinario(jogadores, numJogadores);
        }
    printf("\nForam cadastrados %d jogadores!", cont);
}

void lerInformacoesJogador(PLAYER jogadores[], int numJogadores){
    FILE *file;
    file = fopen("sistema.dat", "rb"); // rb == leitura e somente leitura
        if(file == NULL){
            printf("O arquivo nao foi aberto >:(");
        }
    fseek(file, 0, SEEK_END); // coloca o ponteiro no fim
    int tamArquivo = ftell(file); // diz o tamanho total do arquivo (incluindo outras informações que possa conter)
    fseek(file, 0, SEEK_SET); // coloca o ponteiro novamente no inicio
    // tem que ser com 0, não pode ser 0*PLAYER(jogadores) porque não vai :(
    fread(jogadores, sizeof(PLAYER), tamArquivo, file);
    printf("\n------------------------------------\n"); 
        for(int i = 0; i < numJogadores; i++){
            printf("%d Jogador:\n\n", i + 1);

            //Dados gerais
            printf("Nome: %s\n", jogadores[i].nome);
            printf("Data de Nascimento: %d/%d/%d\n", jogadores[i].dataNascimento.dia, jogadores[i].dataNascimento.mes, jogadores[i].dataNascimento.ano);
            printf("CPF: %s\n", jogadores[i].cpf);
            printf("Genero: %s\n", jogadores[i].genero);
            printf("Estado Civil: %s\n\n", jogadores[i].estado_civil);

            // Equipe
            printf("Nome da Equipe: %s\n", jogadores[i].equipe.nome);
            printf("Username da equipe: %s\n", jogadores[i].equipe.nicknameRedeSocial);
            printf("Seguidores da equipe: %d\n\n", jogadores[i].equipe.seguidores);

            // Patrocinador
            printf("Patrocinador principal: %s\n\n", jogadores[i].patrocinador);

            // Rede social
            printf("Username no Instagram: @%s\n", jogadores[i].rede_social_username);
            printf("Seguidores no Instagram: %d\n\n", jogadores[i].seguidores_rede_social);

            // Hardware
            printf("Modelo da maquina: %s\n", jogadores[i].hardware.modeloMaquinario);
            printf("Processador: %s\n", jogadores[i].hardware.processador);
            printf("Placa de video: %s\n", jogadores[i].hardware.placaDeVideo);
            printf("Quantidade de memoria RAM: %dGB\n\n", jogadores[i].hardware.memoriaRAM);

            // Campeonato
            printf("Pontuacao no campeonato: %d\n", jogadores[i].campeonato.pontuacao);
            printf("Vitorias: %d\n", jogadores[i].campeonato.vitorias);
            printf("Empates: %d\n", jogadores[i].campeonato.empates);
            printf("Derrotas: %d\n\n", jogadores[i].campeonato.derrotas);

            // Titulos
            printf("Quantidade de titulos: %d\n", jogadores[i].titulos);

            // Posicao no rank
            printf("Posicao no rank mundial: %d", jogadores[i].posicaoRank);

            printf("\n------------------------------------\n");
            
            system("pause");
        }
}
/* 
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
}*/

int main() {
    int opcao, numJogadores;
    printf("\n\tSistema de competicao de E-Sports\n\n");
    printf("Digite a quantidade de jogadres\n");
    printf("A quantidade de jogadores DEVE ser MAIOR OU IGUAL a 30 e MENOR OU IGUAL a 50: ");
    scanf("%d", &numJogadores);
        if(numJogadores<=0){
            do{ // observar formas de melhorar
                printf("Digite um numero maior que 0\n");
                printf("Digite a quantidade de jogadores: ");
                scanf("%d", &numJogadores);
            }while(numJogadores <= 0);
        }
    PLAYER jogadores[numJogadores];
        while (1) {
            printf("\n1. Cadastrar jogador\n");
            printf("2. Listar TODOS os jogadores\n");
            printf("3. Alteracao de dados do jogador\n");
            printf("4. Atualizacao dos jogos e pontuacao\n");
            printf("5. Listagem ALFABELTICA dos jogadores\n");
            printf("6. Listagem POR POSICAO dos jogadores\n");
            printf("7. Listagem POR VITORIA dos jogadores\n");
            printf("8. Classificacao do campeonato\n");
            printf("9. Listagem de jogadores com pontuacao MAIOR que certa pontuacao\n");
            printf("10. Listagem de jogadores com pontuacao MENOR que certa pontuacao\n");
            printf("11. Busca de jogador POR NOME\n");
            printf("12. Busca de jogador POR POSICAO no rank\n");
            printf("13. Media de seguidores de um jogador\n");
            printf("14. Sair\n");
            printf("Escolha a opcao: ");
            scanf("%d", &opcao);
                switch (opcao) {
                    case 1:
                        cadastrarJogador(jogadores, numJogadores);
                        break;
                    case 2:
                        lerBinario(jogadores, numJogadores);
                        lerInformacoesJogador(jogadores, numJogadores);
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
                        break;
                    case 14:
                        return 0;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                }
        }

    return 0;
}
