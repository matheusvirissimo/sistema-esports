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

// FUNÇÕES BASES

void escreverBinario(PLAYER jogadores[], int numJogadores, int qtdJogadores){ 
    FILE *file;
    file = fopen("sistema.dat", "ab+"); // queremos escrever jogadores além dos que já temos, por isso AB+
    if(file == NULL){
        printf("O arquivo não foi aberto ;(");
    }
    int teste = sizeof(PLAYER)*30 + (qtdJogadores--);
    int cadastro = ftell(file)/teste;
    fseek(file, teste, SEEK_SET);
    fread(jogadores, sizeof(PLAYER), numJogadores, file);
    int qtsRegEscritos = fwrite(jogadores, sizeof(PLAYER), qtdJogadores, file);
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

int buscaBinaria(int vetor[], int chave, int INI, int FIM){
    int MEIO = (INI+FIM)/2;
    if(INI>FIM){
        return (0);
    }else{
        if(chave == vetor[MEIO]){
            return (1);
        }else{
            if(chave > vetor[MEIO]){
                return (buscaBinaria(vetor, chave, MEIO+1, FIM));
            }else{
                if(chave < vetor[MEIO]){
                    return (buscaBinaria(vetor, chave, INI, MEIO-1));
                }
            }
        }
    }
}

// FUNÇÕES PROGRAMA

void cadastrarJogador(PLAYER jogadores[], int numJogadores) {
    int cont = 0, qtdJogadores;
    printf("\t\n\n*** CADASTRO DE JOGADORES ***\n\n");
    printf("Digite quantos jogadores você deseja cadastrar: ");
    scanf("%d", &qtdJogadores);
        for(int i = 0; i < qtdJogadores; i++){
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

            escreverBinario(jogadores, numJogadores, qtdJogadores);
        }
    printf("Foram cadastrados %d jogadores!\n\n", cont);
}

void lerInformacoesJogadorES(PLAYER jogadores[], int numJogadores){
    FILE *file;
    file = fopen("sistema.dat", "rb"); // rb == leitura e somente leitura
        if(file == NULL){
            printf("O arquivo nao foi aberto >:(");
        }
    fseek(file, 0, SEEK_END); // coloca o ponteiro no fim
    int tamArquivo = ftell(file)/sizeof(PLAYER); // diz o tamanho total do arquivo (incluindo outras informações que possa conter)
    fseek(file, 0, SEEK_SET); // coloca o ponteiro novamente no inicio
    // tem que ser com 0, não pode ser 0*PLAYER(jogadores) porque não vai :(
    fread(jogadores, sizeof(PLAYER), tamArquivo, file);
    printf("\n------------------------------------\n"); 
        for(int i = 0; i < numJogadores; i++){ // tem que mudar o FOR
            if(jogadores[i].nome[0] == '\0'){
                // Sai do FOR se o próximo nome for vazio
                break;
            }
            
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
    fclose(file);
}

void lerInformacoesUnicoJogador(PLAYER jogadores[], int tamArquivo, int numeroDoJogador){ // para não precisar ficar repetindo 3 vezes
    FILE *file;
    file = fopen("sistema.dat", "rb"); // rb == leitura e somente leitura
        if(file == NULL){
            printf("O arquivo nao foi aberto >:(");
        }
    fread(jogadores, sizeof(PLAYER), tamArquivo, file);
    printf("\n------------------------------------\n"); 
        for(int i = 0; i < tamArquivo; i++){ 

            if(i == numeroDoJogador){
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
    fclose(file);
}

void correcaoDadosJogador(PLAYER jogadores, int numJogadores){
    FILE *file;
    file = fopen("sistema.c", "wb");
        if(file == NULL){
            printf("O arquivo nao foi aberto nooooooo :(");
        }
    
}

void inserirVitoriaEmpateDerrota(int numJogadores) { // BUGADO
    FILE *file;
    file = fopen("sistema.dat", "rb+"); // faz a leitura e escreve no fim
    if (file == NULL) {
        printf("O arquivo nao foi aberto aff");
        return;
    }
    int posicaoJogador;
    fseek(file, 0, SEEK_END);
    int tamArquivo = ftell(file)/sizeof(PLAYER); 
    rewind(file); // == fseek(file, 0, seek_set)
    PLAYER jogadores[tamArquivo];
    fread(jogadores, sizeof(PLAYER), tamArquivo, file);

    printf("\n\nVoce deve selecionar a numeracao do jogador conforme a sua inscricao na lista\n");
    printf("Por exemplo: o jogador MAVINCAS foi o 1 jogador a ser inscrito, logo, se voce deseja atualizar ele, digite 1\n");
    printf("Digite a numeracao do jogador a ser alterado: ");
    scanf("%d", &posicaoJogador);
    posicaoJogador--; // é computação, a numeração não começa no 1, mas sim no 0. 
    PLAYER vetorAux[1];
    printf("Digite as VITORIAS atualizadas: ");
    scanf("%d", &vetorAux[0].campeonato.vitorias);
    printf("Digite os EMPATES atualizados: ");
    scanf("%d", &vetorAux[0].campeonato.empates);
    printf("Digite as DERROTAS atualizadas: ");
    scanf("%d", &vetorAux[0].campeonato.derrotas);

    vetorAux[0].campeonato.pontuacao = vetorAux[0].campeonato.vitorias * 3 + vetorAux[0].campeonato.empates;

    fwrite(vetorAux, sizeof(PLAYER), 1, file);
    fclose(file);
    }

void listagemAlfabetica(){
}

void listagemRank(){

}

void listagemVitoria(){

}

void buscaPorNome(char nome[100]){
    FILE *file;
    file = fopen("sistema.dat", "rb"); // só faz leitura, é uma busca afinal
        if(file == NULL){
            printf("O arquivo nao foi abertoooo");
        }
    fseek(file, 0, SEEK_END); // é importante sempre colocar o ponteiro no fim, porque fazemos várias manipulações e o tamanho pode variar
    int tamStruct = sizeof(PLAYER); // se usa comumente 36, mas cada struct pode variar
    int tamArquivo = ftell(file)/tamStruct;
    PLAYER jogadores[tamArquivo];
    fseek(file, 0, SEEK_SET); // volta o ponteiro no inicio para sua manipulação
    fread(jogadores, sizeof(PLAYER), tamArquivo, file);
    int i = 0;
        for(i = 0; i < tamArquivo; i++){
            if(strcmp(jogadores[i].nome, nome) == 0){
                int numeroDoJogador = i;
                lerInformacoesUnicoJogador(jogadores, tamArquivo, numeroDoJogador);
            }else{
                printf("\n\nEsse jogador nao existe em nosso banco de dados!\n\n");
            }
        }
    fclose(file);
    return;
}

void buscaPorRank(int rank){
FILE *file;
    file = fopen("sistema.dat", "rb"); // só faz leitura, é uma busca afinal
        if(file == NULL){
            printf("O arquivo nao foi abertoooo");
        }
    fseek(file, 0, SEEK_END); 
    int tamArquivo = ftell(file)/sizeof(PLAYER);
    PLAYER jogadores[tamArquivo];
    fseek(file, 0, SEEK_SET); // volta o ponteiro no inicio para sua manipulação
    fread(jogadores, sizeof(PLAYER), tamArquivo, file);
    int i = 0;
        for(i = 0; i < tamArquivo; i++){
            if(jogadores[i].posicaoRank == rank){
                int numeroDoJogador = i;
                lerInformacoesUnicoJogador(jogadores, tamArquivo, numeroDoJogador);
                break; 
            }else{
                printf("\n\nEsse jogador nao existe em nosso banco de dados!\n\n");
            }
        }
    fclose(file);
    return;
}

void mediaSeguidores(PLAYER jogadores[], int numJogadores){
    FILE *file;
    file = fopen("sistema.dat", "rb"); // não vamos escrever no arquivo, vamos ler os dados e depois transpor eles
        if(file == NULL){
            printf("O arquivo nao foi aberto :/");
        }
    fseek(file, 0, SEEK_END);
    int tamArquivo = ftell(file)/sizeof(PLAYER);
    rewind(file);
    float seguidoresTotal = 0;
    fread(jogadores, sizeof(PLAYER), tamArquivo, file);
        for(int i = 0; i < tamArquivo; i++){
            seguidoresTotal += jogadores[i].seguidores_rede_social; // += é a mesma coisa que x = x + y, só fica mais elegante :)
        }
    float seguidoresMedia = seguidoresTotal/tamArquivo;
    printf("A quantidade MEDIA dos seguidores do campeonato e de: %.2f\n", seguidoresMedia);
    printf("\n------------------------------------\n");
}

int main() {
    int opcao, numJogadores = MAX_PLAYERS, rank;
    char nome[100];
    PLAYER jogadores[numJogadores];
    printf("\n\tSistema de competicao de E-Sports\n\n");
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
                        lerInformacoesJogadorES(jogadores, numJogadores);
                        lerBinario(jogadores, numJogadores);
                        break;
                    case 3:
                        break;
                    case 4:
                        inserirVitoriaEmpateDerrota(numJogadores);
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
                        printf("\t\n\n*** BUSCA POR NOME ***\n\n");
                        printf("Digite o nome do jogador igual a como esta listado: ");
                        fflush(stdin);
                        gets(nome);
                        fflush(stdin);
                        buscaPorNome(nome);
                        break;
                    case 12:
                        printf("\t\n\n*** BUSCA POR RANK ***\n\n");
                        printf("Digite o ranque do jogador que voce busca: ");
                        scanf("%d", &rank);
                        buscaPorRank(rank);
                        break;
                    case 13:
                        printf("\t\n\n*** MEDIA DE SEGUIDORES ***\n\n");
                        mediaSeguidores(jogadores, numJogadores);
                        break;
                    case 14:
                        return 0;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                }
        }

    return 0;
}
