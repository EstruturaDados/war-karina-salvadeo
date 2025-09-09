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
void limparBufferEntrada();
void inicializarTerritorios(Territorio *mapa, int tamanho);
void exibirMapa(const Territorio *mapa, int tamanho);
void exibirMenuPrincipal();

// --- Função Principal (main) ---
int main() {
    setlocale(LC_ALL, "Portuguese");  // Configura idioma para português (acentos)

    Territorio mapa[MAX_TERRITORIOS]; // Declara um vetor estático de 5 territórios

    printf("=== PROJETO WAR ESTRUTURADO ===\n");

    // Cadastro inicial dos territórios
    inicializarTerritorios(mapa, MAX_TERRITORIOS);

    int opcao;
    // Loop principal do jogo
    do {
        exibirMenuPrincipal();        // Mostra opções ao jogador
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);          // Lê a opção escolhida
        limparBufferEntrada();        // Evita problemas com \n no buffer

        switch (opcao) {              // Escolhe o que fazer com base na opção
            case 1:
                exibirMapa(mapa, MAX_TERRITORIOS); // Exibe o estado do mapa
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);  // Repete até o jogador escolher sair (0)

    return 0;
}

// --- Implementação das Funções ---

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê caracteres até encontrar ENTER ou fim do arquivo
}


void inicializarTerritorios(Territorio *mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {                  // Percorre todos os territórios
        printf("\nCadastro do Território %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);            // Lê o nome do território
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;   // Remove o \n no final da string

        printf("Cor do exército: ");
        fgets(mapa[i].cor, MAX_COR, stdin);              // Lê a cor do exército
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;     // Remove o \n

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);                    // Lê o número de tropas
        limparBufferEntrada();                           // Limpa o buffer para evitar bugs
    }
}


void exibirMapa(const Territorio *mapa, int tamanho) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < tamanho; i++) {                  // Percorre todos os territórios
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);              // Exibe nome
        printf("Cor: %s\n", mapa[i].cor);                // Exibe cor
        printf("Tropas: %d\n", mapa[i].tropas);          // Exibe tropas
        printf("-------------------------\n");
    }
}

void exibirMenuPrincipal() {
    printf("\n=== Menu Principal ===\n");
    printf("1 - Exibir mapa\n");
    printf("0 - Sair\n");
}