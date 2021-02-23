#include "definitions.h"

char size_to_piece(size sized){
    switch(sized){
        case SMALL:
            return 'x';
        case MEDIUM:
            return 'X';
        case LARGE:
            return '#';
        case NONE:
            return ' ';
    }
}
char *player_to_color(player holding){
    switch (holding){
    case PLAYER_1:
        return ROUGE;
        break;
    case PLAYER_2:
        return BLEU;
        break;
    case NO_PLAYER:
        return "";
        break;
    }
}
void tour(int joueur){
    printf("-------------------------------------------\n\n");
    if(joueur==1)
        printf("%sJoueur%d%s, à vous de jouer :\n\n", ROUGE, joueur, CLEAR);
    else
        printf("%sJoueur%d%s, à vous de jouer :\n\n", BLEU, joueur, CLEAR);
}
void plateau(board game, int joueur){
    for(int i=0;i<3;i++){
        grille(i+1);
        for(int j=0;j<3;j++){
            player holding = get_place_holder(game, i, j); //Variable stockant à qui appartient la case
            size sized = get_piece_size(game,i,j); //Variable stockant la taille de la pièce présente à la case
            char piece=size_to_piece(sized);
            char *color=player_to_color(holding);
            printf("│%s %c %s",color,piece,CLEAR);
        }
        inventaire(game, i);
    }
    grille_fin();
}
void inventaire(board game, int i){
    switch(i){
        case 0:
            printf("│       Contenu des maisons");
            break;
        case 1:
            printf("│       %s",ROUGE);
            for(int sizes=1;sizes<4;sizes++){
                for(int each=1; each<=get_nb_piece_in_house(game,PLAYER_1,sizes); each++)
                    printf("%c ",size_to_piece(sizes));
            }
            break;
        case 2:
            printf("│       %s",BLEU);
            for(int sizes=1;sizes<4;sizes++){
                for(int each=1; each<=get_nb_piece_in_house(game,PLAYER_2,sizes); each++)
                    printf("%c ",size_to_piece(sizes));
            }
            break;
    }   
    printf("%s\n",CLEAR);
}
void grille(int compteur){
    switch (compteur){
        case 1:
            printf("    ┌───┬───┬───┐\n");
            printf("    ");
            break;
        case 2:
            printf("    ├───┼───┼───┤\n");
            printf("    ");
            break;
        case 3:
            printf("    ├───┼───┼───┤\n");
            printf("    ");
            break;
    }
}
void grille_fin(){
    printf("    └───┴───┴───┘\n\n"); 
}