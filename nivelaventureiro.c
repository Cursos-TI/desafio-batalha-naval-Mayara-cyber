#include <stdio.h>

#define TAMANHO 10      // Tabuleiro 10x10
#define TAMANHO_NAVIO 3 // Tamanho fixo do navio
#define AGUA 0
#define NAVIO 3

// Protótipo da função de posicionamento
int validar_e_posicionar(int tabuleiro[TAMANHO][TAMANHO], int linha_i, int coluna_i, int tipo_movimento);

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int sucesso_total = 1;

    // Inicialização do Tabuleiro
    printf("Inicializando tabuleiro 10x10.\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posicionamento dos Navios
    printf("\n--- Posicionando Navios Retos ---\n");
    // Navio 1: Horizontal (Tipo 1)
    if (!validar_e_posicionar(tabuleiro, 1, 1, 1)) {
        sucesso_total = 0;
    } 

    // Navio 2: Vertical (Tipo 2)
    if (!validar_e_posicionar(tabuleiro, 5, 8, 2)) {
        sucesso_total = 0;
    }
    
    printf("\n--- Posicionando Navios Diagonais ---\n");
    // Navio 3: Diagonal Principal (Tipo 3: L+, C+)
    if (!validar_e_posicionar(tabuleiro, 7, 3, 3)) {
        sucesso_total = 0;
    } 

    // Navio 4: Diagonal Secundária (Tipo 4: L+, C-)
    if (!validar_e_posicionar(tabuleiro, 0, 9, 4)) {
        sucesso_total = 0;
    } 

    // Exibição do Resultado
    printf("\n--- RESULTADO FINAL ---\n");
    if (sucesso_total) {
        printf("Todos os 4 navios foram posicionados com sucesso!\n");
    } else {
        printf("Houve pelo menos uma falha no posicionamento. Verifique os ERROS acima.\n");
    }

    printf("\n======== TABULEIRO 10x10 ========\n");
    printf("  0 1 2 3 4 5 6 7 8 9 (Coluna)\n");
    
    // Exibir o Tabuleiro
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d", tabuleiro[i][j]); 
        }
        printf("\n");
    }
    printf("(Linha)\n");
    printf("=================================\n");

    return 0;
}

int validar_e_posicionar(int tabuleiro[TAMANHO][TAMANHO], int linha_i, int coluna_i, int tipo_movimento) {
    int l, c;

    // 1. VERIFICAR (Limites e Sobreposição)
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        l = linha_i;
        c = coluna_i;

        // Calcula a nova posição
        if (tipo_movimento == 1) {
            c += k;
        } else if (tipo_movimento == 2) {
            l += k;
        } else if (tipo_movimento == 3) {
            l += k;
            c += k;
        } else if (tipo_movimento == 4) {
            l += k;
            c -= k; 
        }

        // Checagem de Limite OU Sobreposição
        if (l < 0 || l >= TAMANHO || c < 0 || c >= TAMANHO || tabuleiro[l][c] == NAVIO) {
            printf("  Falha ao posicionar Navio em (%d, %d). Motivo: Limite ou Sobreposição.\n", linha_i, coluna_i);
            return 0; // FALHA
        }
    }

    // 2. POSICIONAR
    for (int k = 0; k < TAMANHO_NAVIO; k++) {
        l = linha_i;
        c = coluna_i;

        // Recalcula a nova posição
        if (tipo_movimento == 1) {
            c += k;
        } else if (tipo_movimento == 2) {
            l += k;
        } else if (tipo_movimento == 3) {
            l += k;
            c += k;
        } else if (tipo_movimento == 4) {
            l += k;
            c -= k;
        }
        
        tabuleiro[l][c] = NAVIO;
    }

    printf("  Sucesso: Navio posicionado a partir de (%d, %d).\n", linha_i, coluna_i);
    return 1; // SUCESSO
}