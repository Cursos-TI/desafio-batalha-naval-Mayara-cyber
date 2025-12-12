#include <stdio.h>
#include <math.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5
#define CENTRO_HABILIDADE 2
#define MAX_RAIO 2

#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA 5

void construir_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void construir_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void construir_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha_origem, int coluna_origem);
int posicionar_navio_simples(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int l, int c, int tipo);

void construir_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            int dist_horizontal = abs(j - CENTRO_HABILIDADE); 

            if (dist_horizontal <= i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

void construir_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            if (i == CENTRO_HABILIDADE || j == CENTRO_HABILIDADE) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

void construir_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            int dist_v = abs(i - CENTRO_HABILIDADE);
            int dist_h = abs(j - CENTRO_HABILIDADE);

            if ((dist_v + dist_h) <= MAX_RAIO) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha_origem, int coluna_origem) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            int tabuleiro_linha = linha_origem - CENTRO_HABILIDADE + i;
            int tabuleiro_coluna = coluna_origem - CENTRO_HABILIDADE + j;

            if (tabuleiro_linha >= 0 && tabuleiro_linha < TAMANHO_TABULEIRO &&
                tabuleiro_coluna >= 0 && tabuleiro_coluna < TAMANHO_TABULEIRO) 
            {
                if (habilidade[i][j] == 1) {
                    if (tabuleiro[tabuleiro_linha][tabuleiro_coluna] == AGUA) {
                         tabuleiro[tabuleiro_linha][tabuleiro_coluna] = AREA_AFETADA;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
    
    posicionar_navio_simples(tabuleiro, 1, 1, 1);
    posicionar_navio_simples(tabuleiro, 5, 8, 2);
    posicionar_navio_simples(tabuleiro, 7, 3, 3);
    posicionar_navio_simples(tabuleiro, 0, 9, 4);

    construir_cone(habilidade_cone);
    construir_cruz(habilidade_cruz);
    construir_octaedro(habilidade_octaedro);

    sobrepor_habilidade(tabuleiro, habilidade_cone, 1, 7); 
    sobrepor_habilidade(tabuleiro, habilidade_cruz, 5, 5); 
    sobrepor_habilidade(tabuleiro, habilidade_octaedro, 8, 1); 

    printf("================= TABULEIRO FINAL (Nível Mestre) =================\n");
    printf("  0 1 2 3 4 5 6 7 8 9 (Coluna)\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            
            if (tabuleiro[i][j] == AGUA) {
                printf(" ~");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" N");
            } else if (tabuleiro[i][j] == AREA_AFETADA) {
                printf(" *");
            } else {
                printf(" ?");
            }
        }
        printf("\n");
    }
    printf("(Linha)\n");
    printf("\nLegenda: ~ = Água (0), N = Navio (3), * = Área Afetada (5)\n");
    printf("==================================================================\n");

    return 0;
}

int posicionar_navio_simples(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_i, int coluna_i, int tipo_movimento) {
    int l, c;
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        l = linha_i;
        c = coluna_i;

        if (tipo_movimento == 1) c += k;
        else if (tipo_movimento == 2) l += k;
        else if (tipo_movimento == 3) { l += k; c += k; }
        else if (tipo_movimento == 4) { l += k; c -= k; }
        
        if (l < TAMANHO_TABULEIRO && c < TAMANHO_TABULEIRO && l >= 0 && c >= 0) {
            tabuleiro[l][c] = NAVIO;
        }
    }
    return 1;
}