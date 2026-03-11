#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Minimax.h"
#include "4enratlla.h"
#define JUGADOR '1'
#define BUIT '0'
#define ORDINADOR '2'
void inicialitzartaulell(char taulell[DIMENSIO][DIMENSIO]) { // We initialize the board with all 0s
    for (int i = 0; i < DIMENSIO; i++) {
        for (int j = 0; j < DIMENSIO; j++) {
            taulell[i][j] = BUIT;
        }
    }
}


// We print the board in a visually static way
void mostraTauler(char taulell[DIMENSIO][DIMENSIO]) {
    printf("  "); // We print an initial space so that the numbers are properly aligned with the columns
    for (int i = 0; i < DIMENSIO; i++) {
        printf("  %d ", i + 1);   // We print the column number adding 1, so that the indices go from
    }                            //  1 up to DIMENSIO
    printf("\n");

    // The first line of the board is printed, delimiting the cells with +
    printf("  +");
    for (int i = 0; i < DIMENSIO; i++) {
        printf("---+");
    }
    printf("\n");

    // We print the rows of the board
    for (int i = 0; i < DIMENSIO; i++) {
        printf("  |"); // For one row, we start by introducing the left separator of the first column
        for (int j = 0; j < DIMENSIO; j++) {
            if (taulell[i][j] == BUIT) { // We traverse all the cells of the row in question, printing
                printf("   |"); // "  ", O, X depending on whether it is BUIT, a JUGADOR piece, or an ORDINADOR piece
            } else if (taulell[i][j] == JUGADOR) {
                printf(" \033[1;34m%c\033[0m |", 'O'); // BLUE for JUGADOR
            } else if (taulell[i][j]==ORDINADOR){
                printf(" \033[1;31m%c\033[0m |", 'X'); // RED for ORDINADOR
            }   // note: we introduce an ANSI escape sequence
        }
        printf("\n");
        // the last row of the board is introduced in the same way as the first one for aesthetics
        printf("  +");
        for (int k = 0; k < DIMENSIO; k++) {
            printf("---+");
        }
        printf("\n");
    }
}



// Function that checks whether the board is FULL
int taulerPle(char taulell[DIMENSIO][DIMENSIO]) {
    for (int col = 0; col < DIMENSIO; col++) { // We check whether the board is empty or not depending on whether
        if (taulell[0][col] == BUIT) { // the last row of the board is empty or not
            return 0; // we return 0 if the board is not empty
        }
    }
    return 1; // we return 1 if the board is empty
}