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
void limparBufferEntrada();
Territorio* alocarMapa(int tamanho);
void inicializarTerritorios(Territorio *mapa, int tamanho);
void liberarMemoria(Territorio *mapa);
void exibirMapa(const Territorio *mapa, int tamanho);
void exibirMenuPrincipal();
void faseDeAtaque(Territorio *mapa, int tamanho);
void simularAtaque(Territorio *atacante, Territorio *defensor);

// --- Função Principal (main) ---
int main() {
    setlocale(LC_ALL, "Portuguese");  // Configura idioma para português (acentos)
    srand(time(NULL)); // Inicializa gerador de números aleatórios (rand)

    // Aloca dinamicamente os territórios
    Territorio *mapa = alocarMapa(MAX_TERRITORIOS);
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== PROJETO WAR ESTRUTURADO ===\n");
    inicializarTerritorios(mapa, MAX_TERRITORIOS); // Cadastro inicial dos territórios

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
    while ((c = getchar()) != '\n' && c != EOF);
}

Territorio* alocarMapa(int tamanho) {
    return (Territorio*) calloc(tamanho, sizeof(Territorio));
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

// Função para liberar o espaço alocado para o mapa
void liberarMemoria(Territorio *mapa) {
    free(mapa);
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
    printf("2 - Fase de ataque\n");
    printf("0 - Sair\n");
}

// FaseDeAtaque: gerenciar a escolha dos territórios atacante e defensor
//   - Mostra o mapa
//   - Pede para o jogador escolher atacante e defensor
//   - Faz validações básicas
//   - Chama simularAtaque()
void faseDeAtaque(Territorio *mapa, int tamanho) {
    int idAtacante, idDefensor;

    exibirMapa(mapa, tamanho);

    printf("\nEscolha o território atacante (1-%d): ", tamanho);
    scanf("%d", &idAtacante);
    limparBufferEntrada();

    printf("Escolha o território defensor (1-%d): ", tamanho);
    scanf("%d", &idDefensor);
    limparBufferEntrada();

    // Valida entradas
    if (idAtacante < 1 || idAtacante > tamanho ||
        idDefensor < 1 || idDefensor > tamanho ||
        idAtacante == idDefensor) {
        printf("\nEscolha inválida!\n");
        return;
    }

    simularAtaque(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
}

// SimularAtaque: executar a lógica de uma batalha entre dois territórios
//   - Atacante e defensor rolam dados (1 a 6)
//   - Se atacante >= defensor → defensor perde 1 tropa
//   - Se defensor chega a 0 → território conquistado (muda de cor)
//   - Caso contrário, atacante perde 1 tropa
void simularAtaque(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) { // Atacante precisa de pelo menos 2 tropas
        printf("\nO atacante não tem tropas suficientes para atacar!\n");
        return;
    }

    // Rola os dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    // Mostra informações da batalha
    printf("\nBatalha: %s (atacante) vs %s (defensor)\n",
           atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n",
           dadoAtacante, dadoDefensor);

    // Aplica regras
    if (dadoAtacante >= dadoDefensor) {
        defensor->tropas--;
        printf("Atacante venceu! Defensor perde 1 tropa.\n");

        if (defensor->tropas <= 0) {
            // Conquista do território
            printf("O território %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);  // Muda cor para a do atacante
            defensor->tropas = 1;                  // Defensor recebe 1 tropa
            atacante->tropas--;                    // Atacante move 1 tropa para ocupar
        }
    } else {
        atacante->tropas--;
        printf("Defensor venceu! Atacante perde 1 tropa.\n");
    }
}