#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TAM 7

//DISCIPLINA : CONSTRUÇÃO DE ALGORÍTMOS
//DOCENTE : EUGENIO DA SILVA
//DISCENTES : JOÃO PEDRO VALÉRIO CORRÊA & ANA CLARA FERNANDES MALVINO
//TAREFA : PUZZLE RESTA UM / PEG SOLITAIRE

//Criação da matriz fora da main(), tornando global e mais fácil de manipular
int tab[TAM][TAM];
int isel, jsel;
isel = 1;
jsel = 3;

// Monta tabuleiro já com um espaço vazio no meio
void monta_tabuleiro() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if ((i == 0 || i == 1 || i == 5 || i == 6) && (j == 0 || j == 1 || j == 5 || j == 6)) {
                tab[i][j] = 0;
            } else if (i == 3 && j == 3) {
                tab[i][j] = 2;
            } else {
                tab[i][j] = 1;
            }
        }
    }
}

//Exibe o tabuleiro
void exibir (){
    system("cls");
    int linha=0;
    printf("     1   2   3   4   5   6   7\n");
    printf("   _____________________________\n  |                             |\n");
    for (int i=0; i < 7; i++)
    {
        linha += 1;
        printf(" %d|", linha);
            for (int j= 0; j < 7; j++)
            {
                if (tab[i][j] == 0)
                   printf("    ");
                else
                    if (isel == i && jsel == j){
                        if (tab[i][j] == 1)
                            printf(" [%c]", 'O');
                        if (tab[i][j] == 3)
                            printf(" [%c]", 155);
                        if (tab[i][j] == 2)
                            printf(" [%c]", 240);
                    }
                    else if (tab[i][j] == 1)
                        printf("  %c ", 'O');
                    else if (tab[i][j] == 3)
                        printf("  %c ", 155);
                    else if (tab[i][j] == 2)
                        printf("  %c ", 240);

            }
        if (linha == 7)
            printf(" |\n  |");
        else
            printf(" |\n  |                             |\n");
    }
    printf("_____________________________|\n\n");
}

// Insere tecla das setinhas
int tecla() {
    int seta;

    while (1) {
        printf("          APERTE UMA SETA\n");
        seta = getch();
        if (seta == 0 || seta == 224) {
            seta = getch(); // lê o código estendido da tecla
            return seta;
        }
    }
}

//Seleciona a peça
int selpont() {
    int ponteiro;
    int enterKeyPressed = 0;

    while (!enterKeyPressed) {
        printf("    APERTE ENTER PARA CONFIRMAR");
        ponteiro = getch();

        if (ponteiro == 13) { // Código ASCII para a tecla ENTER
            enterKeyPressed = 1;
        } else if (ponteiro == 0 || ponteiro == 224) {
            ponteiro = getch(); // lê o código estendido da tecla
            switch (ponteiro) {
            case 72: // seta para cima
                if(tab[isel-1][jsel]!= 0 && isel>0)
                    isel--;
                break;
            case 80: // seta para baixo
                if(tab[isel+1][jsel]!= 0 && isel<6)
                    isel++;
                break;
            case 75: // seta para esquerda
                if(tab[isel][jsel-1]!= 0 && jsel>0)
                    jsel--;
                break;
            case 77: // seta para direita
                if(tab[isel][jsel+1]!= 0 && jsel<6)
                    jsel++;
                break;
            }
        }
    exibir();
    }
     return -1;
}




// Mostra peças elegíveis de jogada
void elegiveis() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 3) {
                tab[i][j] = 1; // Reinicia o estado das peças elegíveis
            }
        }
    }

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if(tab[i][j] != 0 && tab[i][j] != 2){
                // verifica se tem jogada pra direita
                if (j <= 4 && (tab[i][j+1] == 1 || tab[i][j+1] == 3) && tab[i][j+2] == 2) {
                    tab[i][j] = 3;
                }
                // se tem pra esquerda
                if (j >= 2 && (tab[i][j-1] == 1 || tab[i][j-1] == 3) && tab[i][j-2] == 2) {
                    tab[i][j] = 3;
                }
                // se tem pra baixo
                if (i <= 4 && (tab[i+1][j] == 1 || tab[i+1][j] == 3) && tab[i+2][j] == 2) {
                    tab[i][j] = 3;
                }
                // se tem pra cima
                if (i >= 2 && (tab[i-1][j] == 1 || tab[i-1][j] == 3) && tab[i-2][j] == 2) {
                    tab[i][j] = 3;
                }
            }
        }
    }
}

//Tratamento de erro
int tratamento(int erro, int i, int j) {
    switch (erro) {
        case 72: // seta para cima
            if (i >= 2 && (tab[i-1][j] == 1 || tab[i-1][j] == 3) && tab[i-2][j] == 2)
                return erro;
            break;
        case 80: // seta para baixo
            if (i <= 4 && (tab[i+1][j] == 1 || tab[i+1][j] == 3) && tab[i+2][j] == 2)
                return erro;
            break;
        case 75: // seta para esquerda
            if (j >= 2 && (tab[i][j-1] == 1 || tab[i][j-1] == 3) && tab[i][j-2] == 2)
                return erro;
            break;
        case 77: // seta para direita
            if (j <= 4 && (tab[i][j+1] == 1 || tab[i][j+1] == 3) && tab[i][j+2] == 2)
                return erro;
            break;
    }
    return 0; // Retorna 0 caso o movimento não seja possível
}


// Seleção de peça
void selecao() {
    int linha, coluna;
    linha = isel;
    coluna = jsel;

    if (tab[linha][coluna] != 3) {
        printf("PECA INVALIDA POR FAVOR TENTE NOVAMENTE...\n\n");
        system("pause");
        return;
    } else {
        int setinha;
        int trata = 0;

        while (trata != 72 && trata != 80 && trata != 75 && trata != 77) {
            setinha = tecla();
            trata = tratamento(setinha, linha, coluna);
            if (trata == 0) {
                printf("TECLA INVALIDA POR FAVOR TENTE NOVAMENTE...\n\n");
            }
        }

        movimenta(setinha, linha, coluna);
    }
}

// Movimenta efetivamente uma peça
void movimenta(int opcao, int i, int j) {
    switch (opcao) {
        case 72: // seta para cima
            tab[i][j] = 2;
            tab[i-1][j] = 2;
            tab[i-2][j] = 1;
            break;
        case 80: // seta para baixo
            tab[i][j] = 2;
            tab[i+1][j] = 2;
            tab[i+2][j] = 1;
            break;
        case 75: // seta para esquerda
            tab[i][j] = 2;
            tab[i][j-1] = 2;
            tab[i][j-2] = 1;
            break;
        case 77: // seta para direita
            tab[i][j] = 2;
            tab[i][j+1] = 2;
            tab[i][j+2] = 1;
            break;
    }
}

//Fim de jogo
int endgame() {
    int contagem = 0;
    int fim = 0;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 1)
                ++contagem;
            if (tab[i][j] == 3)
                ++fim;
        }
    }

    if (fim == 0) {
        if (contagem == 1){
            system("cls");
            printf("VOCE VENCEU!!!\n\n");
            system("pause");
            return 5;
        }
        else{
            system("cls");
            printf("VOCE PERDEU COM %d PECAS RESTANTES!!!\n\n", contagem);
            system("pause");
            return 7;
        }
    }
}

void arte() {
    printf("                                                                                                              .         .           \n");
    printf("8 888888888o.   8 8888888888     d888888o. 8888888 8888888888   .8.                    8 8888      88        ,8.       ,8.          \n");
    printf("8 8888    `88.  8 8888         .`8888:' `88.     8 8888        .888.                   8 8888      88       ,888.     ,888.         \n");
    printf("8 8888     `88  8 8888         8.`8888.   Y8     8 8888       :88888.                  8 8888      88      .`8888.   .`8888.        \n");
    printf("8 8888     ,88  8 8888         `8.`8888.         8 8888      . `88888.                 8 8888      88     ,8.`8888. ,8.`8888.       \n");
    printf("8 8888.   ,88'  8 888888888888  `8.`8888.        8 8888     .8. `88888.                8 8888      88    ,8'8.`8888,8^8.`8888.      \n");
    printf("8 888888888P'   8 8888           `8.`8888.       8 8888    .8`8. `88888.               8 8888      88   ,8' `8.`8888' `8.`8888.     \n");
    printf("8 8888`8b       8 8888            `8.`8888.      8 8888   .8' `8. `88888.              8 8888      88  ,8'   `8.`88'   `8.`8888.    \n");
    printf("8 8888 `8b.     8 8888        8b   `8.`8888.     8 8888  .8'   `8. `88888.             ` 8888     ,8P ,8'     `8.`'     `8.`8888.   \n");
    printf("8 8888   `8b.   8 8888        `8b.  ;8.`8888     8 8888 .888888888. `88888.              8888   ,d8P ,8'       `         `8.`8888.  \n");
    printf("8 8888     `88. 8 888888888888 `Y8888P ,88P'     8 8888.8'       `8. `88888.              `Y88888P' ,8'         `         `8.`8888. \n");
    printf("\n\n");
}

int main() {
    arte();
    system("pause");
    monta_tabuleiro();
    elegiveis();
    int jogoAcabou = 0;
    while (1) {
        elegiveis();
        exibir();
        int op = selpont();
        if (op == -1) {
            selecao();
            system("cls");
        }
        elegiveis();
        jogoAcabou = endgame();
        if (jogoAcabou == 5 || jogoAcabou == 7)
            break;
    }
    system("cls");
    printf("\nOBRIGADO POR JOGAR\n\n");
    return 0;
}

