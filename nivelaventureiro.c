#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Necessário para abs() no Octaedro

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

#define TAMANHO_HABILIDADE 7
#define CENTRO_HABILIDADE (TAMANHO_HABILIDADE / 2)


void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n--- TABULEIRO FINAL (0=Agua, 3=Navio, 5=Habilidade) ---\n");
    
    printf("   0 1 2 3 4 5 6 7 8 9\n");
    printf("  ---------------------\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d| ", i); 
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                printf("N ");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf("X ");
            } else {
                printf("~ ");
            }
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
}


// CONSTRÓI A HABILIDADE CONE
void construir_cone(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = CENTRO_HABILIDADE;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= centro - i && j <= centro + i) {
                matriz_habilidade[i][j] = 1;
            } else {
                matriz_habilidade[i][j] = 0;
            }
        }
    }
}

// CONSTRÓI A HABILIDADE CRUZ
void construir_cruz(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = CENTRO_HABILIDADE;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz_habilidade[i][j] = 1;
            } else {
                matriz_habilidade[i][j] = 0;
            }
        }
    }
}

// CONSTRÓI A HABILIDADE OCTAEDRO/LOSANGO
void construir_octaedro(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = CENTRO_HABILIDADE;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int dist_vertical = abs(i - centro);
            int dist_horizontal = abs(j - centro);
            
            if (dist_vertical + dist_horizontal <= centro) {
                matriz_habilidade[i][j] = 1;
            } else {
                matriz_habilidade[i][j] = 0;
            }
        }
    }
}

// SOBREPOSIÇÃO
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                         int origem_linha, int origem_coluna) {
    
    int centro = CENTRO_HABILIDADE;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            int tab_linha = origem_linha - centro + i;
            int tab_coluna = origem_coluna - centro + j;
            
            if (tab_linha >= 0 && tab_linha < TAMANHO_TABULEIRO &&
                tab_coluna >= 0 && tab_coluna < TAMANHO_TABULEIRO) {
                
                if (matriz_habilidade[i][j] == 1) {
                    
                    if (tabuleiro[tab_linha][tab_coluna] != NAVIO) {
                         tabuleiro[tab_linha][tab_coluna] = HABILIDADE;
                    }
                }
            }
        }
    }
}

int main() {
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int matriz_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    inicializar_tabuleiro(tabuleiro);

    // POSICIONAMENTO DOS NAVIOS
    
    // NAVIO 1: VERTICAL (2, 1)
    const int n1_linha = 2; const int n1_coluna = 1;
    for (int i = 0; i < TAMANHO_NAVIO; i++) { tabuleiro[n1_linha + i][n1_coluna] = NAVIO; }
    
    // NAVIO 2: HORIZONTAL (5, 5)
    const int n2_linha = 5; const int n2_coluna = 5;
    for (int j = 0; j < TAMANHO_NAVIO; j++) { tabuleiro[n2_linha][n2_coluna + j] = NAVIO; }
    
    // NAVIO 3: DIAGONAL PRINCIPAL (1, 7)
    const int n3_linha = 1; const int n3_coluna = 7;
    for (int k = 0; k < TAMANHO_NAVIO; k++) { tabuleiro[n3_linha + k][n3_coluna + k] = NAVIO; }
    
    // NAVIO 4: DIAGONAL SECUNDÁRIA (7, 2)
    const int n4_linha = 7; const int n4_coluna = 2;
    for (int k = 0; k < TAMANHO_NAVIO; k++) { tabuleiro[n4_linha + k][n4_coluna - k] = NAVIO; }
    
    
    // APLICAÇÃO DAS HABILIDADES
    
    // 1. HABILIDADE CONE
    construir_cone(matriz_cone);
    sobrepor_habilidade(tabuleiro, matriz_cone, 0, 5); 

    // 2. HABILIDADE CRUZ
    construir_cruz(matriz_cruz);
    sobrepor_habilidade(tabuleiro, matriz_cruz, 8, 1); 

    // 3. HABILIDADE OCTAEDRO/LOSANGO
    construir_octaedro(matriz_octaedro);
    sobrepor_habilidade(tabuleiro, matriz_octaedro, 4, 8); 
    
    exibir_tabuleiro(tabuleiro);
    
    return 0;
}