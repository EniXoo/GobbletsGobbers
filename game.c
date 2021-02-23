#include <stdio.h>
#include "./Fonctions/definitions.h"
#include "board.h"

int main(int argc, char *argv[]){
    int menu=0;
	do{
		board game=new_game();
		player joueur=1;
		player *p_joueur=&joueur;
		int status=0, cpt=0;
		char *message="Choix non-conforme";

		do{
			if(cpt>0)
				printf("%s%s%s\n", ERROR, message, CLEAR);
			menu = saisieInt(message, "		MENU\n	1-Nouvelle partie\n	2-Règles\n	3-Quitter\n");
			cpt++;
		} while(menu!=1 && menu!=2 && menu!=3);
	
		switch (menu){ //
			case 1: //
				do{
					tour(joueur);
					plateau(game, joueur); 
					status = verif_choix(game,p_joueur);
				} while(get_winner(game)==NO_PLAYER && status==0);
				annonce_winner_partie(game,status,joueur);
				printf("-------------------------------------------\n");
				destroy_game(game);
				break;
			case 2:
				printf("Ce jeu se joue à deux joueurs sur un plateau constitué d’un damier de trois cases par trois cases, comme le morpion. Chaque joueur dispose au début de six pièces de jeu dans sa maison. Les pièces peuvent être de trois tailles : petite, moyenne ou grosse, et chaque joueur possède deux pièces de chaque taille au début de la partie.\nLes joueurs exécutent chacun leur tour une action parmi les deux actions suivantes :\n\n        —  Un joueur peut placer une pièce de sa maison sur une case du plateau.\n\n        —  Un joueur peut déplacer l’une de ses pièces présentes sur le plateau (et visible) vers une autre case du plateau.\n\nPour placer (ou déplacer) une pièce sur le plateau, il est nécessaire que la case d’arrivée soit libre ou ne contienne que des pièces plus petites que la pièce placée. Dans le cas où une pièce est posée sur une case occupée, celle-ci couvre alors les pièces déjà présentes, les rendant invisibles. On peut donc couvrir une petite pièce avec une pièce moyenne ou une grande, ou couvrir une pièce moyenne avec une pièce grande.Il est possible de couvrir indifféremment une pièce de l’adversaire ou l’une de ses propres pièces. Une case peut donc comporter au plus trois pièces en même temps, une petite,une moyenne et une grande. Seule la plus grande pièce présente sur la case est alors visible.\n\nLorsque l’on déplace une pièce qui en couvrait une autre, la pièce précédemment cachée redevient alors visible. Si on déplace une grande pièce qui couvrait une pièce petite et une moyenne, seule la pièce moyenne devient visible.%s%sUn joueur remporte la partie lorsqu’il parvient à ce que toutes les pièces visibles d’une ligne, d’une colonne ou d’une diagonale lui appartiennent%s. Dans le cas peu probable où les deux joueurs satisfont la condition de victoire lors d’un même mouvement, la partie continue jusqu’à ce qu’un seul joueur soit en position gagnante. Ce cas peut arriver quand lors d’un déplacement, la pièce déplacée révèle une ligne gagnante dans la position quittée en même temps qu’elle en crée une avec la case atteinte.\n",ROUGE,BOLD,CLEAR);
				printf("-------------------------------------------\n");
				break;
			case 3:
				printf("Fermeture du programme\n");
				break;
		}
	} while(menu!=3);
	return 0;
}
