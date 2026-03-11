
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Minimax.h"
#include "4enratlla.h"
#define JUGADOR '1'
#define BUIT '0'
#define ORDINADOR '2'

int calculaNumFills(char taulell[DIMENSIO][DIMENSIO]) { // We will have as many children as possible moves we can make.
    int n_fills = 0;   // There is no need to check whether a whole column is full; we only need to
    for (int i = 0; i < DIMENSIO; i++) { // check whether there are pieces in the top row of the board.
        if (taulell[0][i] == BUIT) {
            n_fills++;
        }
    }
    return n_fills;
}



int introduirfitxa(char taulell[DIMENSIO][DIMENSIO], int col, char jugador) {
    if (col < 0 || col >= DIMENSIO) {
        printf("Has introdu�t una fitxa fora del rang especificat!\n");
        return 0; // 0 indicates that the move could not be made
    }
    for (int i = DIMENSIO - 1; i >= 0; i--) {
        if (taulell[i][col] == BUIT) { // Starting from the bottom of the board, we check whether that position is occupied
            taulell[i][col] = jugador; // If the position is not occupied, we place the piece there
            return 1; // 1 indicates that the move was made successfully
        }
    }
    printf("Columna plena. Intenta de nou.\n");
    return 0;
}


// Function that copies one board into another.
void copiaTauler(char desti[DIMENSIO][DIMENSIO], char origen[DIMENSIO][DIMENSIO]) {
    for (int i = 0; i < DIMENSIO; i++) {
        for (int j = 0; j < DIMENSIO; j++) {
            desti[i][j] = origen[i][j];
        }
    }
}

void crear1Nivell(Node *pare, char jugador) {
    if (pare == NULL) return; // If the pointer does not point to any memory position and, therefore,
    // we do not have a node, we return
    // Given our node, we calculate the number of children from its board
    pare->n_fills = calculaNumFills(pare->tauler);

    // We allocate memory space for the child nodes
    pare->fills = (Node **)malloc(pare->n_fills * sizeof(Node *));
    if (pare->fills == NULL) {
        printf("Error al assignar memoria als fills\n");
        return;
    }
    int indexfill = 0; // We have one child node for each possible move we can make (which
    for (int col = 0; col < DIMENSIO; col++) { // depends on whether the column is full or not)
        if (pare->tauler[0][col] == BUIT) { // We check whether the column is not full
            Node *fill = (Node *)malloc(sizeof(Node)); // We allocate memory space for our
            if (fill == NULL) {                      // child node
                printf("Error al assignar memoria al fill.\n");
            }
            copiaTauler(fill->tauler, pare->tauler); // We copy the parent board to the child node
            introduirfitxa(fill->tauler, col, jugador); // We make the corresponding move in the child node
            fill->fills = NULL; // We initialize the child attributes
            fill->n_fills = 0;
            fill->valor = 0;
            pare->fills[indexfill] = fill; // We assign the child node pointer to the pointer we
            indexfill++; // defined before
        }
    }
}


int verifiacio(char taulell[DIMENSIO][DIMENSIO], char jugador) { // Function that checks whether someone has achieved four in a row
    for (int i = 0; i < DIMENSIO; i++) { // We check whether four in a row has been achieved horizontally. We perform the check over the 8x4 submatrix, because
        for (int j = 0; j <= DIMENSIO - 4; j++) { // a point with j>4 (counting from 0 to 7) cannot have
            if (taulell[i][j] == jugador && taulell[i][j + 1] == jugador && // 4 horizontal pieces, because there is not enough
                taulell[i][j + 2] == jugador && taulell[i][j + 3] == jugador) { // space on the board
                return 1; // 1 indicates that four in a row has been achieved
            }
        }
    }

    for (int i = 0; i <= DIMENSIO - 4; i++) { // We check whether four in a row has been achieved vertically. We perform the check over the 4x8 submatrix, because a point
        for (int j = 0; j < DIMENSIO; j++) { // with i>4 (counting from 0 to 7) cannot have
            if (taulell[i][j] == jugador && taulell[i + 1][j] == jugador && // 4 vertical pieces, because there is not enough
                taulell[i + 2][j] == jugador && taulell[i + 3][j] == jugador) { // space on the board
                return 1;
            }
        }
    }

    for (int i = 0; i <= DIMENSIO - 4; i++) { // We check whether four in a row has been achieved diagonally (from bottom-left to top-right)
        for (int j = 0; j <= DIMENSIO - 4; j++) { // We perform the diagonal check over the 4x4 submatrix
            if (taulell[i][j] == jugador && taulell[i + 1][j + 1] == jugador && // because a point with
                taulell[i + 2][j + 2] == jugador && taulell[i + 3][j + 3] == jugador) { // i>4 cannot have 4 vertical positions
                return 1; // and a point with j>4 cannot have 4 horizontal positions
            }
        }
    }
    for (int i = 0; i <= DIMENSIO - 4; i++) { // We check whether four in a row has been achieved diagonally (from top-left to bottom-right)
        for (int j = 3; j < DIMENSIO; j++) { // We perform the diagonal check over the
            if (taulell[i][j] == jugador && taulell[i + 1][j - 1] == jugador && // 4x4 submatrix, because a point with j<3 cannot
                taulell[i + 2][j - 2] == jugador && taulell[i + 3][j - 3] == jugador) { // have a diagonal down to the right
                return 1;
            }
        }
    }

    return 0; // Otherwise, we return 0 indicating that no condition has been met.
}

void crearArbre(Node *node, char jugador, int profunditat) {  // Function that creates a tree from a given node.
    // The `jugador` parameter indicates which player is making the move at the current level.
    // `profunditat` controls up to which level the tree must be generated.
    if (node == NULL || profunditat <= 0) return;  // Base condition of the recursion:
    if (verifiacio(node->tauler, jugador) == 1) return;
    // If the board of the current node already represents a winning situation for the player,
    // we stop generating more levels along this branch.

    crear1Nivell(node, jugador);  // We generate one level of children for the current node
    // We determine the player who will make the next move:
    // If the current player is JUGADOR, the next one is ORDINADOR.
    // If the current player is ORDINADOR, the next one is JUGADOR.
    char jugadorseg;
    if (jugador == JUGADOR) {
        jugadorseg = ORDINADOR;
    } else {
        jugadorseg = JUGADOR;
    }
    for (int i = 0; i < node->n_fills; i++) {
        // We go through all the children generated for the current node and generate trees for them
        crearArbre(node->fills[i], jugadorseg, profunditat - 1);
        // Recursive call to generate the tree for each child:
        // The player alternates between JUGADOR and ORDINADOR.
    }
}

// Transforms the index of a child into a valid column
int transformaFillAColumna(char tauler[DIMENSIO][DIMENSIO], int numDeFill) {
    int contador = 0;
    for (int i = 0; i < DIMENSIO; i++) {
        if (tauler[0][i] == BUIT) { // If the column is not full
            if (contador == numDeFill) {
                return i;
            }
            contador++;
        }
    }
    return -1;
}


int heurifuncio(char pos[4]) {
    int puntuacio=0;
    int nordinador = 0;  // computer pieces
    int njugador = 0;   // opponent pieces
    int nbuit = 0; // empty positions

    for (int i = 0; i < 4; i++) {
        if (pos[i] == ORDINADOR) nordinador++;
        else if (pos[i] == JUGADOR) njugador++;
        else nbuit++;
    }
    // Evaluate conditions for "nordinador"
    if (nordinador == 4) {
        puntuacio += 50000000;
    } else {
            if (nordinador == 3 && nbuit == 1) {
            puntuacio += 10;
            } else {
                if (nordinador == 2 && nbuit == 2) {
                puntuacio += 1;
                }
            }
        }
    if (njugador == 4) {
        puntuacio -=50000000;
    } else {
        if (njugador == 3 && nbuit == 1) {
        puntuacio -= 10;
        } else {
            if (njugador == 2 && nbuit == 2) {
                puntuacio -= 1;
            }
        }
    }

return puntuacio;

}


int puntTauler(char taulell[DIMENSIO][DIMENSIO]) {
    int puntuacio = 0;
    char pos[4];
// For each situation on the board within the 8x4 submatrix, we analyze the 4 horizontal positions (to the right)
// We call a function that evaluates the situation of the 4 pieces and assigns a score to them
// based on the heuristic function
    for (int i = 0; i < DIMENSIO; i++) {
        for (int j = 0; j <= DIMENSIO - 4; j++) {
            for (int q = 0; q < 4; q++) {
                pos[q] = taulell[i][j + q];
            }
            puntuacio += heurifuncio(pos);
        }
    }
// For each situation on the board within the 4x8 submatrix, we analyze the 4 vertical positions
// We call a function that evaluates the situation of the 4 pieces and assigns a score to them
// based on the heuristic function
    for (int j = 0; j < DIMENSIO; j++) {
        for (int i = 0; i <= DIMENSIO - 4; i++) {
            for (int q = 0; q < 4; q++) {
                pos[q] = taulell[i + q][j];
            }
            puntuacio += heurifuncio(pos);
        }
    }
// For each situation on the board within the 4x4 submatrix, we analyze the 4 positions corresponding to the
// diagonal from left to right, bottom to top
    for (int i = 0; i <= DIMENSIO - 4; i++) {
        for (int j = 0; j <= DIMENSIO - 4; j++) {
            for (int q = 0; q < 4; q++) {
                pos[q] = taulell[i + q][j + q];
            }
            puntuacio += heurifuncio(pos);
        }
    }
// For each situation on the board within the 4x4 submatrix, we analyze the 4 positions corresponding to the
// diagonal from right to left, top to bottom
    for (int i = 0; i <= DIMENSIO - 4; i++) {
        for (int j = 3; j < DIMENSIO; j++) {
            for (int q = 0; q < 4; q++) {
                pos[q] = taulell[i + q][j - q];
            }
            puntuacio += heurifuncio(pos);
        }
    }
   // printf("puntuacio: %d",puntuacio);

    return puntuacio;
}

void asignarValorsFulles(Node *node) {
    if (node == NULL) return; // It has no assigned memory position
    if (node->n_fills == 0) { // If we have already reached the maximum depth and have no children
        node->valor = puntTauler(node->tauler); // Given a board, we evaluate it and assign
        return; // a score based on the heuristic function
    }
    // If we do not have a leaf node, we traverse the different children to assign a value
    for (int i = 0; i < node->n_fills; i++) {
        asignarValorsFulles(node->fills[i]);
    }
}

int ferMinimax(Node *node, int profunditat) {
    if (node == NULL) return 0; // If the node points nowhere, we return 0

    if (node->n_fills == 0) {
        return node->valor; // If it is a leaf node, we return its heuristic value
    }

    // Determine whether the level is maximizing (even) or minimizing (odd)
    int max = (profunditat % 2 == 0);

    if (max) { // Maximizing turn
        int maxvalor = -1000000000; // We initialize the maximum with a very low value
        for (int i = 0; i < node->n_fills; i++) {
            int valor = ferMinimax(node->fills[i], profunditat - 1);
            if (valor > maxvalor) {
                maxvalor = valor;
            }
        }
        node->valor = maxvalor; // We assign the maximum value to the node
        return maxvalor; // We return the maximum value
    } else { // Minimizing turn
        int minvalor = 1000000000; // We initialize the minimum with a very high value
        for (int i = 0; i < node->n_fills; i++) {
            int valor = ferMinimax(node->fills[i], profunditat-1);
            if (valor < minvalor) {
                minvalor = valor;
            }
        }
        node->valor = minvalor; // We assign the minimum value to the node
        return minvalor; // We return the minimum value
    }
}

int millorcolumna(Node *arrel) {
    // Given a root node, we check which column corresponds to its maximum value
    // assigned by the minimax algorithm.

    if (arrel == NULL || arrel->n_fills == 0) {
        // We check whether the root is NULL or whether it has no children.
        // If so, no column can be determined, and we return -1.
        printf("Error: L'arrel es NULL o no te fills.\n");
        return -1;
    }

    int valormax = arrel->valor; // We store the maximum value assigned to the root.
    int millorcolumna = -1; // We initialize the best column with an invalid value (-1).
    int columnacentre = DIMENSIO / 2; // We determine the central column of the board.

    for (int i = 0; i < arrel->n_fills; i++) {
        // We go through all the children of the root.
        if (arrel->fills[i] != NULL) {
            // We check whether the board of the current child represents a win for the computer.
            if (verifiacio(arrel->fills[i]->tauler, ORDINADOR) == 1) {
                // If it is a winning move, we directly return the corresponding column.
                return transformaFillAColumna(arrel->tauler, i);
            }

            int valorara = arrel->fills[i]->valor; // We get the value of the current child.
            int columnara = transformaFillAColumna(arrel->tauler, i); // We get the column corresponding to the child.

            // We check whether the value of the current child is equal to the maximum value.
            // In case of a tie, priority is given to the column closest to the center.
            if (valorara == valormax && abs(columnara - columnacentre) < abs(millorcolumna - columnacentre)) {
                valormax = valorara; // We update the maximum value.
                millorcolumna = columnara; // We update the best column.
            }
        }
    }

    // We return the best column found, prioritizing the most central ones in case of a tie.
    return millorcolumna;
}

void esborraArbre(Node *arrel) {
    if (arrel == NULL) {
        return; // If the node is NULL, we do nothing
    }
    for (int i = 0; i < arrel->n_fills; i++) {
        esborraArbre(arrel->fills[i]); // We apply recursion to free
    }                                  // the child nodes
    free(arrel->fills);

    free(arrel); // we free the current node as well
}
