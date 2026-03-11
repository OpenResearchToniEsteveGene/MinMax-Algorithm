#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "4enratlla.h"
#include "Minimax.h"
#define nom_max 50


#define DIMENSIO 8
#define JUGADOR '1'
#define BUIT '0'
#define ORDINADOR '2'


int main() {
    char taulell[DIMENSIO][DIMENSIO];
    char nomjugador[nom_max];
    char nomordinador[] = "C3PO"; // computer name
    int opcio; // control variable
    int profunditat = 6; // default depth (high difficulty)
    int nvjugador = 0; // number of player victories
    int nvordinador = 0; // number of computer victories
    int nempats = 0; // number of player draws
    printf("\n====================================\n");
    printf("   BENVINGUTS AL JOC DEL 4 EN RATLLA   \n");
    printf("======================================\n");
    do {
        // Start menu
    printf("\n=================================\n");
    printf("          MENU PRINCIPAL         \n");
    printf("=================================\n");
    printf("1. Jugar una partida\n");
    printf("2. Veure les regles del joc\n");
    printf("3. Veure el marcador\n");
    printf("4. Reiniciar el marcador\n");
    printf("5. Sortir del joc\n");
    printf("=================================\n");
    printf("Selecciona una opcio (1-5): ");
        scanf("%d", &opcio);

        switch (opcio) {
            case 1: { // Play
                int nivell;
                printf("\n==== Selecciona la dificultat ====\n");
                printf("1. Baixa (Facil)\n");
                printf("2. Mitja \n");
                printf("3. Alta (Dificil)\n");
                printf("===============================\n");
                printf("Selecciona el nivell de dificultat: ");
                scanf("%d", &nivell);

                switch (nivell) {
                    case 1: profunditat = 2; break; // Low
                    case 2: profunditat = 4; break; // Medium
                    case 3: profunditat = 6; break; // High
                    default:
                        printf("Nivell no correcte. Per defecte usarem la dificultat alta.\n");
                        profunditat = 6;
                        break;
                }

                printf("Siusplau, introdueix el teu nom: ");
                scanf("%s", nomjugador);
                printf("\nHola, %s. T'enfrontes a  %s.\n", nomjugador, nomordinador);

                // Select who starts
                int primerTorn;
                printf("\n==== Selecciona qui comen�a ====\n");
                printf("1. Jugador\n");
                printf("2. Ordinador\n");
                printf("===============================\n");
                printf("Selecciona una opcio: ");
                scanf("%d", &primerTorn);

                // Initialize board
                inicialitzartaulell(taulell);
                mostraTauler(taulell);

                // Game loop
                while (1) {
                    if (primerTorn == 1) { // Player turn
                        int colvalida = 0;
                        int coljugador = 0;

                        do {
                            printf("%s, es el teu torn. Tria una columna de 1 a %d: ", nomjugador, DIMENSIO);
                            scanf("%d", &coljugador);
                            coljugador -= 1; // Adjust index
                            if (coljugador < 0 || coljugador >= DIMENSIO) {
                                printf("Columna invalida. Intenta de nou.\n");
                            } else if (!introduirfitxa(taulell, coljugador, JUGADOR)) {
                                printf("Columna plena. Intenta de nou.\n");
                            } else {
                                colvalida = 1; // Valid move
                            }
                        } while (!colvalida);

                        mostraTauler(taulell);

                        if (verifiacio(taulell, JUGADOR)) {
                            printf("Enhorabona, %s! Has guanyat contra %s.\n", nomjugador, nomordinador);
                            nvjugador++;
                            break;
                        }

                        if (taulerPle(taulell)) {
                            printf("El taulell est� ple. Es un empat.\n");
                            nempats++;
                            break;
                        }

                        primerTorn = 2; // Pass turn to the computer
                    } else { // Computer turn
                        printf("Torn de %s...\n", nomordinador);

                        Node *arrel = (Node *)malloc(sizeof(Node));
                        if (arrel == NULL) {
                            printf("Error al assignar memoria al node arrel.\n");
                            return -1000;
                        }

                        copiaTauler(arrel->tauler, taulell);
                        arrel->fills = NULL;
                        arrel->n_fills = 0;
                        arrel->valor = 0;

                        crearArbre(arrel, ORDINADOR, profunditat);
                        asignarValorsFulles(arrel);
                        ferMinimax(arrel, profunditat);

                        int columnaordinador = millorcolumna(arrel);
                        introduirfitxa(taulell, columnaordinador, ORDINADOR);
                        printf("%s ha jugat en la columna %d.\n", nomordinador, columnaordinador + 1);

                        mostraTauler(taulell);

                        if (verifiacio(taulell, ORDINADOR)) {
                            printf("%s t'ha guanyat. Torna-ho a intentar, %s.\n", nomordinador, nomjugador);
                            nvordinador++;
                            esborraArbre(arrel);
                            break;
                        }

                        if (taulerPle(taulell)) {
                            printf("El taulell est� ple. Es un empat.\n");
                            nempats++;
                            break;
                        }

                        esborraArbre(arrel);
                        primerTorn = 1; // Pass turn to the player
                    }
                }
                printf("Joc acabat.\n");
                break;
            }

            case 2: // View instructions
                printf("\n=================================\n");
                printf("          INSTRUCCIONS           \n");
                printf("=================================\n");
                printf("1. Objectiu del joc:\n");
                printf("   Col.loca 4 fitxes consecutives\n");
                printf("   abans que el rival per guanyar.\n");
                printf("---------------------------------\n");
                printf("2. Com jugar:\n");
                printf("   - Introdueix el numero de columna\n");
                printf("     on vols col.locar la teva fitxa.\n");
                printf("   - Prem ENTER per confirmar.\n");
                printf("---------------------------------\n");
                printf("3. Estrategia:\n");
                printf("   - Bloqueja els intents del rival\n");
                printf("     de formar 4 en ratlla.\n");
                printf("   - Planifica les teves jugades.\n");
                printf("---------------------------------\n");
                printf("   Que comenci el joc!\n");
                printf("=================================\n");
                break;

            case 3: // View scoreboard
                    printf("\n=================================\n");
                    printf("             MARCADOR            \n");
                    printf("=================================\n");
                    printf("\n==== Marcador ====\n");
                    printf("Victories de %s: %d\n", nomjugador, nvjugador);
                    printf("Victories de %s: %d\n", nomordinador, nvordinador);
                    printf("---------------------------------\n");
                    printf("Empats: %d\n", nempats);
                    printf("=================================\n");
                break;

            case 4: // Reset scoreboard
                nvjugador = 0;
                nvordinador = 0;
                nempats = 0;
                printf("Marcador reiniciat.\n");
                break;

            case 5: // Exit
                printf("\nGracies per jugar!\n");
                break;

            default: // Invalid option
                printf("Opcio no valida. Selecciona una opcio entre 1-5 \n");
        }
    } while (opcio != 5);

    return 0;
}