// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
// Karina Salvadeo Pereira - Engenharia de Software (Estrutura de Dados)       
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 20


// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;


// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.

// Funções de setup e memória
Territorio* alocarMapa(int tamanho);         // Aloca dinamicamente vetor de territórios
void liberarMapa(Territorio* mapa);          // Libera memória do vetor de territórios

// Funções de inicialização
void inicializarTerritorios(Territorio* mapa, int tamanho); // Cadastra os territórios

// Funções de interface
void exibirMenu();                                         // Mostra opções do jogador
void exibirMapa(const Territorio* mapa, int tamanho);     // Exibe todos os territórios
void exibirMissao(int idMissao);                          // Mostra a missão sorteada

// Funções de mecânica do jogo
void faseDeAtaque(Territorio* mapa, int tamanho);         // Gerencia a fase de ataque
void simularAtaque(Territorio* atacante, Territorio* defensor); // Executa a batalha

// Funções de missões
int sortearMissao();                                      // Sorteia missão aleatória
int verificarMissao(const Territorio* mapa, int tamanho, int idMissao); // Verifica missão

// Função utilitária
void limparBufferEntrada();                                // Limpa buffer de entrada (stdin)

// --- Função Principal (main) ---
int main() {
    setlocale(LC_ALL, "Portuguese");   // Configura idioma para português
    srand(time(NULL));                  // Inicializa o gerador de números aleatórios

    // --- Alocação dinâmica ---
    Territorio* mapa = alocarMapa(MAX_TERRITORIOS);  // Cria vetor de territórios dinamicamente
    if (mapa == NULL) {                             // Verifica se houve erro na alocação
        printf("Erro ao alocar memória!\n");
        return 1;                                   // Encerra o programa caso falhe
    }

    // --- Inicialização ---
    inicializarTerritorios(mapa, MAX_TERRITORIOS); // Cadastra territórios

    // --- Sorteio de missão ---
    int missao = sortearMissao();                  // Sorteia missão aleatória
    printf("\n=== Sua missão foi sorteada! ===\n");
    exibirMissao(missao);                          // Exibe missão para o jogador

    // --- Loop principal do jogo ---
    int opcao;
    do {
        exibirMenu();                              // Mostra opções: atacar, verificar missão, sair
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();                      // Limpa buffer para evitar problemas com fgets

        switch (opcao) {
            case 1:                                 // Opção: atacar
                faseDeAtaque(mapa, MAX_TERRITORIOS);
                break;
            case 2:                                 // Opção: verificar missão
                if (verificarMissao(mapa, MAX_TERRITORIOS, missao)) {
                    printf("\n🎉 PARABÉNS! Você cumpriu sua missão e venceu o jogo!\n");
                    opcao = 0;                       // Encerra o jogo
                } else {
                    printf("\n⚔️ Sua missão ainda não foi cumprida.\n");
                }
                break;
            case 0:                                 // Opção: sair
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);                          // Repete até o jogador escolher sair

    liberarMapa(mapa);                              // Libera memória alocada
    return 0;
}

// --- Implementação das Funções ---
Territorio* alocarMapa(int tamanho) {
    return (Territorio*) calloc(tamanho, sizeof(Territorio)); // calloc inicializa todos os elementos com 0
}

void liberarMapa(Territorio* mapa) {
    free(mapa);  // Libera memória
}

void inicializarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {                     // Percorre todos os territórios
        printf("\nCadastro do Território %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);               // Lê nome
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;     // Remove \n do final

        printf("Cor do exército: ");
        fgets(mapa[i].cor, MAX_COR, stdin);                 // Lê cor
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;       // Remove \n do final

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);                       // Lê número de tropas
        limparBufferEntrada();                               // Limpa buffer para próximas leituras
    }
}

void exibirMenu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar missão\n");
    printf("0 - Sair\n");
}

void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território %d | Nome: %s | Exército: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(int idMissao) {
    printf("\n=== MISSÃO ===\n");
    if (idMissao == 1) {
        printf("Destruir todo o exército Verde.\n");
    } else if (idMissao == 2) {
        printf("Conquistar 3 territórios.\n");
    }
}

void faseDeAtaque(Territorio* mapa, int tamanho) {
    exibirMapa(mapa, tamanho);                              // Mostra o mapa

    int idAtacante, idDefensor;
    printf("\nEscolha o território atacante (1 a %d): ", tamanho);
    scanf("%d", &idAtacante);
    printf("Escolha o território defensor (1 a %d): ", tamanho);
    scanf("%d", &idDefensor);
    limparBufferEntrada();                                   // Limpa buffer

    // Validação de entradas
    if (idAtacante < 1 || idAtacante > tamanho ||
        idDefensor < 1 || idDefensor > tamanho ||
        idAtacante == idDefensor) {
        printf("\n Escolha inválida!\n");
        return;
    }

    simularAtaque(&mapa[idAtacante - 1], &mapa[idDefensor - 1]); // Executa batalha
}

void simularAtaque(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 1) {                             // Verifica se há tropas suficientes
        printf("\n O território atacante não tem tropas suficientes!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;                       // Dado atacante (1-6)
    int dadoDefensor = rand() % 6 + 1;                       // Dado defensor (1-6)

    printf("\n🎲 Dados rolados! Atacante: %d | Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {                      // Atacante vence ou empate
        defensor->tropas -= 1;                               // Defensor perde 1 tropa
        printf("O ataque foi bem-sucedido! O defensor perdeu 1 tropa.\n");

        if (defensor->tropas <= 0) {                        // Defensor derrotado
            printf("Território %s foi conquistado pelo exército %s!\n",
                   defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);           // Muda cor do território
            defensor->tropas = 1;                            // O defensor "ocupado" recebe 1 tropa
            atacante->tropas -= 1;                           // Atacante perde 1 tropa para ocupar
        }
    } else {                                                 // Defensor vence
        atacante->tropas -= 1;                               // Atacante perde 1 tropa
        printf("O defensor resistiu! O atacante perdeu 1 tropa.\n");
    }
}

int sortearMissao() {
    return (rand() % 2) + 1;                                 // Retorna 1 ou 2
}

int verificarMissao(const Territorio* mapa, int tamanho, int idMissao) {
    if (idMissao == 1) {                                     // Missão: destruir exército Verde
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                return 0;                                     // Ainda existe território verde
            }
        }
        return 1;                                            // Todos destruídos → missão cumprida
    } else if (idMissao == 2) {                              // Missão: conquistar 3 territórios
        char corJogador[MAX_COR];
        strcpy(corJogador, mapa[0].cor);                     // Considera cor do jogador como primeira cor

        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                count++;
            }
        }
        return count >= 3;                                   // Verdadeiro se possuir >= 3 territórios
    }
    return 0;                                                // Missão não cumprida
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);            // Lê até ENTER ou EOF
}
