#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n--- TABULEIRO ATUAL (0=Agua, 3=Navio) ---\n");
    
    printf("   0 1 2 3 4 5 6 7 8 9\n");
    printf("  ---------------------\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d| ", i); 
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); 
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
}


int main() {
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    inicializar_tabuleiro(tabuleiro);
    
    // --- NAVIO 1: VERTICAL ---
    const int n1_linha = 2;
    const int n1_coluna = 1;
    
    if (n1_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 1; 
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[n1_linha + i][n1_coluna] != AGUA) return 1; 
        tabuleiro[n1_linha + i][n1_coluna] = NAVIO;
    }
    
    
    // --- NAVIO 2: HORIZONTAL ---
    const int n2_linha = 5;
    const int n2_coluna = 5;
    
    if (n2_coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 1; 
    
    for (int j = 0; j < TAMANHO_NAVIO; j++) {
        if (tabuleiro[n2_linha][n2_coluna + j] != AGUA) return 1;
        tabuleiro[n2_linha][n2_coluna + j] = NAVIO;
    }
    
    
    // --- NAVIO 3: DIAGONAL PRINCIPAL (Linha e Coluna aumentam) ---
    const int n3_linha = 1;
    const int n3_coluna = 7;
    
    if (n3_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || n3_coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 1;
    
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int linha_atual = n3_linha + k;
        int coluna_atual = n3_coluna + k;
        
        if (tabuleiro[linha_atual][coluna_atual] != AGUA) return 1;
        tabuleiro[linha_atual][coluna_atual] = NAVIO;
    }
    
    
    // --- NAVIO 4: DIAGONAL SECUNDÁRIA (Linha aumenta, Coluna diminui) ---
    const int n4_linha = 7;
    const int n4_coluna = 2;
    
    if (n4_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || n4_coluna - TAMANHO_NAVIO < -1) return 1;
    
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        int linha_atual = n4_linha + k;
        int coluna_atual = n4_coluna - k;
        
        if (tabuleiro[linha_atual][coluna_atual] != AGUA) return 1;
        tabuleiro[linha_atual][coluna_atual] = NAVIO;
    }

    exibir_tabuleiro(tabuleiro);
    
    return 0;
}