#include "definitions.h"

int selection_action(){
    int choix, cpt=0;
    char *message = "Choix renseigné non-valide";
    do{
        if(cpt>0)
            printf("%s%s%s\n",ERROR,message,CLEAR);
        choix = saisieInt(message, "Voulez-vous ajouter (0) ou déplacer (1) une pièce? ");
        cpt++;
    }while(choix!=0 && choix!=1);
    return choix;
}
int saisieInt(char *message, char *consigne){
    int res=0, choix, erreur=0;
    while(res==0){
        if(erreur==1)
            printf("%s%s%s\n", ERROR, message, CLEAR);
        printf("%s",consigne);
        res = scanf("%d",&choix);
        if(res==0)
            getchar();
        BufferErase();
        erreur=1;
    }
    return choix;
}
void BufferErase(){
    char c;
    while(( c = getchar())!='\n' && c!=EOF){
        
    }
}
size selection_taille(board game, player joueur){
    int taille, cpt=0;
    char *message = "Taille renseignée non-valide ou indisponible";
    do{
        if(cpt>0)
            printf("%s%s%s\n", ERROR, message, CLEAR);
        taille = saisieInt(message,"Quelle taille voulez-vous jouer?\n(1: petit, 2: moyen, 3: grand) ");
        cpt++;
    } while ((taille!=1 && taille!=2 && taille!=3) || get_nb_piece_in_house(game,joueur,taille)==0);
    return taille;
}
int selection_ligne_source(){
    int ligne_source, cpt=0;
    char *message = "Ligne renseignée non-valide";
        do{
            if(cpt>0)
                printf("%s%s%s\n", ERROR, message, CLEAR);
            ligne_source = saisieInt(message, "Sur quelle ligne se trouve la pièce ? ");
            cpt++;
        } while (ligne_source!=1 && ligne_source!=2 && ligne_source!=3);
        return ligne_source-1;
}
int selection_colonne_source(){
    int colonne_source, cpt=0;
    char *message="Colonne renseignée non-valide";
    do{
        if(cpt>0)
            printf("%s%s%s\n", ERROR, message, CLEAR);
        colonne_source = saisieInt(message, "Sur quelle colonne se trouve la pièce ?");
        cpt++;
    } while (colonne_source!=1 && colonne_source!=2 && colonne_source!=3);
    return colonne_source-1;
}
int selection_case(board game, player joueur){
    int holder_issue=0, colonne_source, ligne_source, ligne, colonne;
    do{
        if(holder_issue)
            printf("%sLa case est vide ou ne vous appartient pas%s\n", ERROR, CLEAR);
        ligne_source=selection_ligne_source();
        colonne_source=selection_colonne_source();
        holder_issue=1;
    } while(get_place_holder(game, ligne_source, colonne_source)!=joueur);
    ligne=selection_ligne();
    colonne=selection_colonne();
    return move_piece(game,ligne_source,colonne_source, ligne, colonne);
}
int fin_abandon(player joueur){
    char confirmation[100];
    int abandon=0;
    printf("Voulez-vous vraiment quitter? Oui pour confirmer\n");
    scanf("%s",confirmation);
    BufferErase();
    if(!strcmp(confirmation,"Oui")){
        printf("%sLe Joueur %d a abandonné%s\n",ERROR,joueur,CLEAR);
        abandon=1;
    }
    else{
        printf("%sVous continuez la partie%s\n",ERROR,CLEAR);
    }
    return abandon;
}
int selection_ligne(){
    int ligne, cpt=0;
    char *message = "Ligne renseignée non-valide ";
    do{
        if(cpt>0)
            printf("%s%s%s\n", ERROR, message, CLEAR);
        ligne = saisieInt(message, "Sur quelle ligne voulez-vous jouer? ");
        cpt++;
    } while (ligne!=1 && ligne!=2 && ligne!=3);
    return ligne-1;
}
int selection_colonne(){
    int colonne, cpt=0;
    char *message = "Colonne renseignée non-valide ";
    do{
        if(cpt>0)
            printf("%s%s%s\n", ERROR, message, CLEAR);
        colonne = saisieInt(message, "Sur quelle colonne voulez-vous jouer? ");
        cpt++;
    } while (colonne!=1 && colonne!=2 && colonne!=3); 
    return colonne-1; 
}
int verif_choix(board game, player *joueur){
    int test, ligne, colonne, status=0, choix=0;
    size taille;
    switch(verif_continuer()){
        case 0:
            if(playerPresent(game,joueur))
                choix=selection_action();
            switch (choix){
                case 0:
                    taille = selection_taille(game, *joueur);
                    ligne = selection_ligne();
                    colonne= selection_colonne();
                    test = place_piece(game,*joueur,taille, ligne, colonne);
                    verif_action(test, joueur);
                    break;
                case 1:
                    test = selection_case(game, *joueur);
                    verif_action(test, joueur);
                    break;
            }
            break;
        case 1:
            status=fin_abandon(*joueur);
            break;
    }
    return status;
}
int verif_continuer(){
    char confirmation;
    int retour, confirmation_issue=0;
    do{
        if(confirmation_issue)
            printf("%sChoix renseigné non-valide %s\n", ERROR, CLEAR);
        printf("Voulez vous abandonner? O/N? ");
        scanf("%c",&confirmation);
        BufferErase();
        if(confirmation=='O')
            retour=1;
        else if(confirmation=='N')
            retour=0;
        confirmation_issue=1;
    } while(confirmation!='O' && confirmation!='N');
    return retour;
}
void verif_action(int test, player *joueur){
    switch(test){
        case 1:
            printf("%sPièce indisponible dans la réserve.%s\n",ERROR,CLEAR);
            break;
        case 2:
            printf("%sLa pièce est trop petite pour être insérée ici.%s\n",ERROR,CLEAR);
            break;
        //Théoriquement impossible car déjà vérifié auparavant lors de la saisie.
        case 3:
            printf("%sEmplacement inexistant.%s\n",ERROR,CLEAR);
            break;
        default:
            printf("La pièce a été placée avec succès.\n");
            *joueur = next_player(*joueur);
            break;
    }
}
int playerPresent(board game, player *joueur){
    int retour=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            player holding = get_place_holder(game, i, j);
            if(holding==*joueur){
                retour=1;
            }
        }
    }
    return retour;
}
void annonce_winner_partie(board game, int status, player joueur){
    plateau(game,joueur);
    if(status==1){
        player gagnant = next_player(joueur);
        printf("%s%sBRAVO Joueur %d, vous avez GAGNÉ!%s\n",player_to_color(gagnant),BLINK,gagnant,CLEAR);
    }
    else{
        player gagnant = get_winner(game);
        printf("%s%sLe gagnant est le joueur %d%s\n",player_to_color(gagnant),BLINK,gagnant,CLEAR);
    }     
}