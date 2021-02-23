//INCLUDES
    #include "../board.h"
    #include <stdio.h>
    #include <string.h>
//MACROS
    #define ROUGE "\e[91m"
    #define BLEU "\e[94m"
    #define CLEAR "\e[0m"
    #define ERROR "\e[95m"
    #define BOLD "\e[1m"
    #define BLINK "\e[5m" //NE MARCHE PAS DANS LE SHELL VSC MAIS MARCHE DANS TERMINAL

#ifndef H_DEF
#define H_DEF
//AFFICHAGE
    char size_to_piece(size sized);
    char *player_to_color(player holding);
    void tour(int joueur);
    void plateau(board game, int joueur);
    void inventaire(board game, int i);
    void grille(int compteur);
    void grille_fin();
//VERIFICATIONS
    int selection_action();
    size selection_taille(board game, player joueur);
    int selection_ligne_source();
    int selection_colonne_source();
    int selection_case(board game, player joueur);
    int fin_abandon(player joueur);
    int selection_ligne();
    int selection_colonne();
    int verif_choix(board game, player *joueur);   
    void verif_action(int test, player *joueur);
    int playerPresent(board game, player *joueur);
    void annonce_winner_partie(board game, int status, player joueur);
    int verif_continuer();
//BUFFER
    void BufferErase();
    int saisieInt(char *message, char *consigne);
#endif