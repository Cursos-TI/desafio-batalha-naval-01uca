#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM_TAB 10      // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3     // Tamanho fixo dos navios
#define TAM_HAB 5       // Tamanho das matrizes de habilidade (5x5)

// Função para inicializar o tabuleiro com água (0)
void inicializaTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para verificar se é possível posicionar um navio sem sair dos limites e sem sobreposição
bool podePosicionar(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'E') { l += i; c -= i; }
        if (l < 0 || l >= TAM_TAB || c < 0 || c >= TAM_TAB) return false;
        if (tabuleiro[l][c] != 0) return false;
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
void posicionaNavio(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'E') { l += i; c -= i; }
        tabuleiro[l][c] = 3;
    }
}

// Função para exibir o tabuleiro
void exibeTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");      // Água
            else if (tabuleiro[i][j] == 3) printf("N "); // Navio
            else if (tabuleiro[i][j] == 5) printf("* "); // Área de habilidade
            else printf("? ");
        }
        printf("\n");
    }
}

// Função para inicializar matriz de habilidade em cone (ponta para baixo)
void habilidadeCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB/2)-i && j <= (TAM_HAB/2)+i && i <= TAM_HAB/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para inicializar matriz de habilidade em cruz
void habilidadeCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB/2 || j == TAM_HAB/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para inicializar matriz de habilidade em octaedro (losango)
void habilidadeOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB/2) + abs(j - TAM_HAB/2) <= TAM_HAB/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para sobrepor matriz de habilidade ao tabuleiro
void aplicaHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int matriz[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    int offset = TAM_HAB/2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int l = origem_linha + i - offset;
            int c = origem_coluna + j - offset;
            if (l >= 0 && l < TAM_TAB && c >= 0 && c < TAM_TAB) {
                if (matriz[i][j] == 1 && tabuleiro[l][c] == 0)
                    tabuleiro[l][c] = 5; // Marca área de habilidade sem sobrescrever navio
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    inicializaTabuleiro(tabuleiro);

    // --- Nível aventureiro: posicionando 4 navios (2 normais, 2 diagonais) ---
    // Navio 1: horizontal, linha 1, coluna 1
    if (podePosicionar(tabuleiro, 1, 1, TAM_NAVIO, 'H'))
        posicionaNavio(tabuleiro, 1, 1, TAM_NAVIO, 'H');

    // Navio 2: vertical, linha 5, coluna 7
    if (podePosicionar(tabuleiro, 5, 7, TAM_NAVIO, 'V'))
        posicionaNavio(tabuleiro, 5, 7, TAM_NAVIO, 'V');

    // Navio 3: diagonal principal, linha 3, coluna 3
    if (podePosicionar(tabuleiro, 3, 3, TAM_NAVIO, 'D'))
        posicionaNavio(tabuleiro, 3, 3, TAM_NAVIO, 'D');

    // Navio 4: diagonal secundária, linha 0, coluna 9
    if (podePosicionar(tabuleiro, 0, 9, TAM_NAVIO, 'E'))
        posicionaNavio(tabuleiro, 0, 9, TAM_NAVIO, 'E');

    exibeTabuleiro(tabuleiro);

    // --- Nível mestre: habilidades especiais ---
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];
    habilidadeCone(cone);
    habilidadeCruz(cruz);
    habilidadeOctaedro(octaedro);

    // Aplica habilidades em diferentes pontos do tabuleiro
    aplicaHabilidade(tabuleiro, cone, 2, 2);        // Cone centrado em (2,2)
    aplicaHabilidade(tabuleiro, cruz, 7, 7);        // Cruz centrada em (7,7)
    aplicaHabilidade(tabuleiro, octaedro, 5, 2);    // Octaedro centrado em (5,2)

    printf("\nTabuleiro com habilidades especiais:\n");
    exibeTabuleiro(tabuleiro);

    return 0;
}