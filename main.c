#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BRANCO 0
#define PRETO 1

// Peças
#define VAZIO 0
#define PEAO 1
#define TORRE 2
#define CAVALO 3
#define BISPO 4
#define RAINHA 5
#define REI 6

// Estrutura para uma peça
typedef struct {
    int tipo;
    int cor;
} Peca;

// Estrutura para posição
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Tabuleiro global
Peca tabuleiro[8][8];
int vez = BRANCO;
int jogo_ativo = 1;

// Protótipos
void inicializar_tabuleiro();
void exibir_tabuleiro();
void limpar_tela();
int mover_peca(Posicao origem, Posicao destino);
int eh_movimento_valido(Posicao origem, Posicao destino);
int movimento_peao(Posicao origem, Posicao destino);
int movimento_torre(Posicao origem, Posicao destino);
int movimento_cavalo(Posicao origem, Posicao destino);
int movimento_bispo(Posicao origem, Posicao destino);
int movimento_rainha(Posicao origem, Posicao destino);
int movimento_rei(Posicao origem, Posicao destino);
int caminho_livre(Posicao origem, Posicao destino);
int esta_em_xeque(int cor);
int posicao_sob_ataque(Posicao pos, int cor_atacante);
int converter_coordenada(char *coord, Posicao *pos);
char peca_para_char(Peca peca);
int eh_movimento_seguro(Posicao origem, Posicao destino, int cor);

int main() {
    char entrada[100];
    Posicao origem, destino;
    
    inicializar_tabuleiro();
    
    printf("=== JOGO DE XADREZ ===\n");
    printf("Comandos: 'e2 e4' para mover, 'sair' para encerrar\n");
    printf("Pressione Enter para continuar...\n");
    getchar();
    
    while (jogo_ativo) {
        limpar_tela();
        exibir_tabuleiro();
        
        printf("\n%s joga (ex: e2 e4): ", vez == BRANCO ? "BRANCAS" : "PRETAS");
        fgets(entrada, 100, stdin);
        entrada[strcspn(entrada, "\n")] = 0;
        
        if (strcmp(entrada, "sair") == 0) {
            printf("Jogo encerrado.\n");
            break;
        }
        
        char coord1[3], coord2[3];
        if (sscanf(entrada, "%2s %2s", coord1, coord2) != 2) {
            printf("Comando inválido! Use formato: 'e2 e4'\n");
            printf("Pressione Enter para continuar...\n");
            getchar();
            continue;
        }
        
        if (!converter_coordenada(coord1, &origem) || !converter_coordenada(coord2, &destino)) {
            printf("Coordenadas inválidas! Use letras a-h e números 1-8\n");
            printf("Pressione Enter para continuar...\n");
            getchar();
            continue;
        }
        
        if (mover_peca(origem, destino)) {
            vez = !vez;
        } else {
            printf("Movimento inválido! Tente novamente.\n");
            printf("Pressione Enter para continuar...\n");
            getchar();
        }
    }
    
    return 0;
}

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void inicializar_tabuleiro() {
    // Inicializa tudo vazio
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tabuleiro[i][j].tipo = VAZIO;
            tabuleiro[i][j].cor = -1;
        }
    }
    
    // Peças pretas (linhas 0 e 1)
    tabuleiro[0][0].tipo = TORRE; tabuleiro[0][0].cor = PRETO;
    tabuleiro[0][1].tipo = CAVALO; tabuleiro[0][1].cor = PRETO;
    tabuleiro[0][2].tipo = BISPO; tabuleiro[0][2].cor = PRETO;
    tabuleiro[0][3].tipo = RAINHA; tabuleiro[0][3].cor = PRETO;
    tabuleiro[0][4].tipo = REI; tabuleiro[0][4].cor = PRETO;
    tabuleiro[0][5].tipo = BISPO; tabuleiro[0][5].cor = PRETO;
    tabuleiro[0][6].tipo = CAVALO; tabuleiro[0][6].cor = PRETO;
    tabuleiro[0][7].tipo = TORRE; tabuleiro[0][7].cor = PRETO;
    
    for (int i = 0; i < 8; i++) {
        tabuleiro[1][i].tipo = PEAO;
        tabuleiro[1][i].cor = PRETO;
    }
    
    // Peças brancas (linhas 6 e 7)
    for (int i = 0; i < 8; i++) {
        tabuleiro[6][i].tipo = PEAO;
        tabuleiro[6][i].cor = BRANCO;
    }
    
    tabuleiro[7][0].tipo = TORRE; tabuleiro[7][0].cor = BRANCO;
    tabuleiro[7][1].tipo = CAVALO; tabuleiro[7][1].cor = BRANCO;
    tabuleiro[7][2].tipo = BISPO; tabuleiro[7][2].cor = BRANCO;
    tabuleiro[7][3].tipo = RAINHA; tabuleiro[7][3].cor = BRANCO;
    tabuleiro[7][4].tipo = REI; tabuleiro[7][4].cor = BRANCO;
    tabuleiro[7][5].tipo = BISPO; tabuleiro[7][5].cor = BRANCO;
    tabuleiro[7][6].tipo = CAVALO; tabuleiro[7][6].cor = BRANCO;
    tabuleiro[7][7].tipo = TORRE; tabuleiro[7][7].cor = BRANCO;
}

void exibir_tabuleiro() {
    printf("\n  +---+---+---+---+---+---+---+---+\n");
    
    for (int i = 0; i < 8; i++) {
        printf("%d ", 8 - i);
        
        for (int j = 0; j < 8; j++) {
            printf("| %c ", peca_para_char(tabuleiro[i][j]));
        }
        printf("|\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    
    printf("    a   b   c   d   e   f   g   h\n");
}

char peca_para_char(Peca peca) {
    if (peca.tipo == VAZIO) return ' ';
    
    char simbolo;
    switch(peca.tipo) {
        case REI: simbolo = 'K'; break;
        case RAINHA: simbolo = 'Q'; break;
        case TORRE: simbolo = 'R'; break;
        case BISPO: simbolo = 'B'; break;
        case CAVALO: simbolo = 'N'; break;
        case PEAO: simbolo = 'P'; break;
        default: return '?';
    }
    
    return (peca.cor == BRANCO) ? simbolo : tolower(simbolo);
}

int mover_peca(Posicao origem, Posicao destino) {
    // Verifica se há peça na origem
    if (tabuleiro[origem.linha][origem.coluna].tipo == VAZIO) {
        printf("Nenhuma peça na posição de origem!\n");
        return 0;
    }
    
    // Verifica se é a vez da peça correta
    if (tabuleiro[origem.linha][origem.coluna].cor != vez) {
        printf("Não é sua vez de jogar!\n");
        return 0;
    }
    
    // Verifica se o movimento é válido
    if (!eh_movimento_valido(origem, destino)) {
        return 0;
    }
    
    // Verifica se o movimento não coloca o próprio rei em xeque
    if (!eh_movimento_seguro(origem, destino, vez)) {
        printf("Este movimento colocaria seu rei em xeque!\n");
        return 0;
    }
    
    // Executa o movimento
    tabuleiro[destino.linha][destino.coluna] = tabuleiro[origem.linha][origem.coluna];
    tabuleiro[origem.linha][origem.coluna].tipo = VAZIO;
    tabuleiro[origem.linha][origem.coluna].cor = -1;
    
    return 1;
}

int eh_movimento_valido(Posicao origem, Posicao destino) {
    Peca peca = tabuleiro[origem.linha][origem.coluna];
    Peca destino_peca = tabuleiro[destino.linha][destino.coluna];
    
    // Não pode capturar peça da mesma cor
    if (destino_peca.tipo != VAZIO && destino_peca.cor == peca.cor) {
        printf("Não pode capturar sua própria peça!\n");
        return 0;
    }
    
    // Verifica movimento específico de cada peça
    switch(peca.tipo) {
        case PEAO: return movimento_peao(origem, destino);
        case TORRE: return movimento_torre(origem, destino);
        case CAVALO: return movimento_cavalo(origem, destino);
        case BISPO: return movimento_bispo(origem, destino);
        case RAINHA: return movimento_rainha(origem, destino);
        case REI: return movimento_rei(origem, destino);
        default: return 0;
    }
}

int movimento_peao(Posicao origem, Posicao destino) {
    int direcao = (tabuleiro[origem.linha][origem.coluna].cor == BRANCO) ? -1 : 1;
    int delta_linha = destino.linha - origem.linha;
    int delta_coluna = abs(destino.coluna - origem.coluna);
    
    // Movimento simples
    if (delta_coluna == 0 && destino.linha == origem.linha + direcao) {
        return (tabuleiro[destino.linha][destino.coluna].tipo == VAZIO);
    }
    
    // Movimento duplo no primeiro movimento
    int linha_inicial = (tabuleiro[origem.linha][origem.coluna].cor == BRANCO) ? 6 : 1;
    if (delta_coluna == 0 && origem.linha == linha_inicial && 
        destino.linha == origem.linha + (2 * direcao)) {
        int meio = origem.linha + direcao;
        return (tabuleiro[destino.linha][destino.coluna].tipo == VAZIO && 
                tabuleiro[meio][origem.coluna].tipo == VAZIO);
    }
    
    // Captura diagonal
    if (delta_coluna == 1 && destino.linha == origem.linha + direcao) {
        return (tabuleiro[destino.linha][destino.coluna].tipo != VAZIO);
    }
    
    return 0;
}

int movimento_torre(Posicao origem, Posicao destino) {
    if (origem.linha != destino.linha && origem.coluna != destino.coluna) {
        return 0;
    }
    return caminho_livre(origem, destino);
}

int movimento_cavalo(Posicao origem, Posicao destino) {
    int delta_linha = abs(destino.linha - origem.linha);
    int delta_coluna = abs(destino.coluna - origem.coluna);
    return (delta_linha == 2 && delta_coluna == 1) || (delta_linha == 1 && delta_coluna == 2);
}

int movimento_bispo(Posicao origem, Posicao destino) {
    if (abs(destino.linha - origem.linha) != abs(destino.coluna - origem.coluna)) {
        return 0;
    }
    return caminho_livre(origem, destino);
}

int movimento_rainha(Posicao origem, Posicao destino) {
    if (origem.linha == destino.linha || origem.coluna == destino.coluna) {
        return caminho_livre(origem, destino);
    }
    if (abs(destino.linha - origem.linha) == abs(destino.coluna - origem.coluna)) {
        return caminho_livre(origem, destino);
    }
    return 0;
}

int movimento_rei(Posicao origem, Posicao destino) {
    int delta_linha = abs(destino.linha - origem.linha);
    int delta_coluna = abs(destino.coluna - origem.coluna);
    return (delta_linha <= 1 && delta_coluna <= 1);
}

int caminho_livre(Posicao origem, Posicao destino) {
    int delta_linha = (destino.linha > origem.linha) ? 1 : (destino.linha < origem.linha) ? -1 : 0;
    int delta_coluna = (destino.coluna > origem.coluna) ? 1 : (destino.coluna < origem.coluna) ? -1 : 0;
    
    int linha = origem.linha + delta_linha;
    int coluna = origem.coluna + delta_coluna;
    
    while (linha != destino.linha || coluna != destino.coluna) {
        if (tabuleiro[linha][coluna].tipo != VAZIO) {
            return 0;
        }
        linha += delta_linha;
        coluna += delta_coluna;
    }
    
    return 1;
}

int eh_movimento_seguro(Posicao origem, Posicao destino, int cor) {
    // Simula o movimento
    Peca peca_temp = tabuleiro[destino.linha][destino.coluna];
    Peca origem_temp = tabuleiro[origem.linha][origem.coluna];
    
    tabuleiro[destino.linha][destino.coluna] = tabuleiro[origem.linha][origem.coluna];
    tabuleiro[origem.linha][origem.coluna].tipo = VAZIO;
    tabuleiro[origem.linha][origem.coluna].cor = -1;
    
    // Verifica se o rei da cor está em xeque
    int em_xeque = esta_em_xeque(cor);
    
    // Desfaz a simulação
    tabuleiro[origem.linha][origem.coluna] = origem_temp;
    tabuleiro[destino.linha][destino.coluna] = peca_temp;
    
    return !em_xeque;
}

int esta_em_xeque(int cor) {
    Posicao rei_pos;
    int encontrou = 0;
    
    // Encontra o rei
    for (int i = 0; i < 8 && !encontrou; i++) {
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j].tipo == REI && tabuleiro[i][j].cor == cor) {
                rei_pos.linha = i;
                rei_pos.coluna = j;
                encontrou = 1;
                break;
            }
        }
    }
    
    // Verifica se alguma peça adversária ataca o rei
    return posicao_sob_ataque(rei_pos, !cor);
}

int posicao_sob_ataque(Posicao pos, int cor_atacante) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j].tipo != VAZIO && tabuleiro[i][j].cor == cor_atacante) {
                Posicao atacante = {i, j};
                
                // Verifica se esta peça pode atacar a posição
                if (eh_movimento_valido(atacante, pos)) {
                    // Para peões, precisa verificar direção correta
                    if (tabuleiro[i][j].tipo == PEAO) {
                        int direcao = (cor_atacante == BRANCO) ? -1 : 1;
                        if (pos.linha == i + direcao && abs(pos.coluna - j) == 1) {
                            return 1;
                        }
                    } else {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int converter_coordenada(char *coord, Posicao *pos) {
    if (strlen(coord) != 2) return 0;
    
    char col = tolower(coord[0]);
    char row = coord[1];
    
    if (col < 'a' || col > 'h') return 0;
    if (row < '1' || row > '8') return 0;
    
    pos->coluna = col - 'a';
    pos->linha = 8 - (row - '0');
    
    return 1;
}