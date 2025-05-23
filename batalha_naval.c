#include <stdio.h>

#define TAM_TAB 10
#define TAM_HAB 5
#define TAM_NAVIO 3

// Função para verificar sobreposição ao posicionar o navio
int estaOcupado(int tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna) {
    return tabuleiro[linha][coluna] == 3;
}

// Função para criar matriz de habilidade em forma de Cone
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Condição: j entre centro - i e centro + i
            if (j >= (TAM_HAB / 2) - i && j <= (TAM_HAB / 2) + i) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em forma de Cruz
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em forma de Octaedro (losango)
void criarOctaedro(int oct[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2) {
                oct[i][j] = 1;
            } else {
                oct[i][j] = 0;
            }
        }
    }
}

// Função para sobrepor matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int habilidade[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int lin = origem_linha - TAM_HAB / 2 + i;
                int col = origem_coluna - TAM_HAB / 2 + j;

                if (lin >= 0 && lin < TAM_TAB && col >= 0 && col < TAM_TAB) {
                    if (tabuleiro[lin][col] == 0) {
                        tabuleiro[lin][col] = 5; // Marca área afetada
                    }
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ "); // água
            else if (tabuleiro[i][j] == 3)
                printf("N "); // navio
            else if (tabuleiro[i][j] == 5)
                printf("* "); // área afetada
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB] = {0};  // Inicializa com água

    // Posicionando dois navios (horizontal e vertical)
    int linhaH = 2, colunaH = 2;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = 3;
    }

    int linhaV = 6, colunaV = 4;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = 3;
    }

    // Posicionando dois navios diagonais
    int linhaD1 = 0, colunaD1 = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
    }

    int linhaD2 = 7, colunaD2 = 2;
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaD2 + i][colunaD2 - i] = 3;
    }

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Definindo pontos de origem das habilidades
    int origemCone_linha = 4, origemCone_coluna = 4;
    int origemCruz_linha = 7, origemCruz_coluna = 7;
    int origemOct_linha = 2, origemOct_coluna = 7;

    // Aplicando habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemCone_linha, origemCone_coluna);
    aplicarHabilidade(tabuleiro, cruz, origemCruz_linha, origemCruz_coluna);
    aplicarHabilidade(tabuleiro, octaedro, origemOct_linha, origemOct_coluna);

    // Exibir resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
