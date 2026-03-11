#define DIMENSIO 8

typedef struct node { // We define a structure of type node with a set of variables:
    char tauler[DIMENSIO][DIMENSIO]; // Matrix that will contain the position of the corresponding board.
    struct node **fills; // Variable that will point to the pointers that point to the children of each node
    int n_fills;         // Number of children each node will have, which depends on how many full columns there are
    int valor;           // Value of the node (given by the heuristic function)
} Node;




int calculaNumFills(char taulell[DIMENSIO][DIMENSIO]);
int introduirfitxa(char taulell[DIMENSIO][DIMENSIO], int col, char jugador);
void copiaTauler(char desti[DIMENSIO][DIMENSIO], char origen[DIMENSIO][DIMENSIO]);
void crear1Nivell(Node *pare, char jugador);
int verifiacio(char taulell[DIMENSIO][DIMENSIO], char jugador);
void crearArbre(Node *node, char jugador, int profunditat);
int transformaFillAColumna(char tauler[DIMENSIO][DIMENSIO], int numDeFill);
int heurifuncio(char pos[4]);
int puntTauler(char taulell[DIMENSIO][DIMENSIO]);
void asignarValorsFulles(Node *node);
int ferMinimax(Node *node, int profunditat);
int millorcolumna(Node *arrel);
void esborraArbre(Node *arrel);