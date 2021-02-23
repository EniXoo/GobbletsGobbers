#include "board.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author You?
 */

/**
 * @brief The board of the game, define it as you wish.
 */


void verif_ligne(int i, int j,player *winner, player *winner2, board game );
void verif_colonne(int i, int j,player *winner, player *winner2, board game );

struct board_s {
	player PetiteCase[DIMENSIONS][DIMENSIONS];
	player MoyenneCase[DIMENSIONS][DIMENSIONS];
	player GrandeCase[DIMENSIONS][DIMENSIONS];
};

player next_player(player current_player){
	if(current_player==PLAYER_1)
		current_player=PLAYER_2;
	else
		current_player=PLAYER_1;
	return current_player;
}
board new_game(){ 
	// memory allocation for the board (leave it as is)
	board new_board = malloc(sizeof(struct board_s));
	// TODO: Insérer les traitements que vous voudriez faire.
	for(int i=0;i<DIMENSIONS;i++){
		for(int j=0;j<DIMENSIONS;j++){
			new_board->PetiteCase[i][j]=NO_PLAYER;
			new_board->MoyenneCase[i][j]=NO_PLAYER;
			new_board->GrandeCase[i][j]=NO_PLAYER;
		}	
	}
	return new_board;
}
board copy_game(board original_game){
	board copy_board = malloc(sizeof(struct board_s));
	for(int i=0;i<DIMENSIONS;i++){
		for(int j=0;j<DIMENSIONS;j++){
			copy_board->PetiteCase[i][j]=original_game->PetiteCase[i][j];
			copy_board->MoyenneCase[i][j]=original_game->MoyenneCase[i][j];
			copy_board->GrandeCase[i][j]=original_game->GrandeCase[i][j];
		}	
	}
	return copy_board;
}
void destroy_game(board game){
	// freeing memory, necessary for memory allocated with malloc (leave as is)
	free(game);
}

player get_place_holder(board game, int line, int column){
	player holder=NO_PLAYER;
	if((*game).GrandeCase[line][column]!=NO_PLAYER){
		holder=(*game).GrandeCase[line][column];
	}
	else if((*game).MoyenneCase[line][column]!=NO_PLAYER){
		holder=(*game).MoyenneCase[line][column];
	}
	else if((*game).PetiteCase[line][column]!=NO_PLAYER){
		holder=(*game).PetiteCase[line][column];
	}
	return holder;
}
size get_piece_size(board game, int line, int column){
	size sized=NONE;
	if((*game).GrandeCase[line][column]!=NO_PLAYER){
		sized = LARGE;
	}
	else if((*game).MoyenneCase[line][column]!=NO_PLAYER){
		sized = MEDIUM;
	}
	else if((*game).PetiteCase[line][column]!=NO_PLAYER){
		sized = SMALL;
	}
	return sized;
}
player get_winner(board game){
	int i=0, j=0;
	player temp;
	player winner = NO_PLAYER;
	player winner2 = NO_PLAYER;
	player *win1= &winner;
	player *win2= &winner2;

	verif_ligne(i,j,win1,win2,game);
	i=0;
	verif_colonne(i,j,win1,win2,game);
	j=0;
	//Vérification diagonales
	//Il ne peut pas y avoir une combinaison gagnante pour chaque joueur dans le cas d'une victoire par diagonale
	temp = get_place_holder(game,1,1);
	if(get_place_holder(game,0,0)==temp && get_place_holder(game,2,2)==temp)
		winner=temp; 
	else if(get_place_holder(game,0,2)==temp && get_place_holder(game,2,0)==temp)
		winner=temp;

	if(winner2!=NO_PLAYER)
		winner=NO_PLAYER;
	
	return winner;
}
int get_nb_piece_in_house(board game, player checked_player, size piece_size){
	int compteur=0;
	for(int i=0;i<DIMENSIONS;i++){
		for(int j=0;j<DIMENSIONS;j++){
			switch(piece_size){
				case SMALL : 
					if((*game).PetiteCase[i][j]==checked_player)
						compteur++;
					break;
				case MEDIUM : 
					if((*game).MoyenneCase[i][j]==checked_player)
						compteur++;
					break;
				case LARGE :
					if((*game).GrandeCase[i][j]==checked_player)
						compteur++;
					break;
			}
		}
	}
	if((checked_player!=PLAYER_1 && checked_player!=PLAYER_2) || (piece_size!=SMALL && piece_size!=MEDIUM && piece_size!=LARGE))
		compteur=2;
	return NB_INITIAL_PIECES-compteur;
}
int place_piece(board game, player current_player, size piece_size, int line, int column){
	int retour=0;
	//Test si ligne et colonne entrées correcte
	if((line!=0 && line!=1 && line!=2) || (column!=0 && column!=1 && column!=2)){
		retour=3;
	}
	//Test si pion disponible
	else if(get_nb_piece_in_house(game, current_player, piece_size)==0){
		retour = 1;
	}
	//Test si insertion possible (taille)
	else{
		switch(get_piece_size(game, line, column)){
			case NONE:
				switch(piece_size)
				{
					case SMALL:
						(*game).PetiteCase[line][column]=current_player;
						break;
					case MEDIUM:
						(*game).MoyenneCase[line][column]=current_player;
						break;
					case LARGE:
						(*game).GrandeCase[line][column]=current_player;
						break;
				}
				retour=0;
				break;
			case SMALL:
				switch(piece_size)
				{
					case SMALL:
						retour=2;
						break;
					case MEDIUM:
						(*game).MoyenneCase[line][column]=current_player;
						retour=0;
						break;
					case LARGE:
						(*game).GrandeCase[line][column]=current_player;
						retour=0;
						break;
				}
				break;
			case MEDIUM:
				switch(piece_size)
				{
					case SMALL:
						retour=2;
						break;
					case MEDIUM:
						retour=2;
						break;
					case LARGE:
						(*game).GrandeCase[line][column]=current_player;
						retour=0;
						break;
				}
				break;
			case LARGE:
				retour=2;
				break;
			default:
				retour=3;
				break;
		}
	}
	return retour;
}
int move_piece(board game, int source_line, int source_column, int target_line, int target_column){
	int retour=0;
	if(source_line < 0 || source_line > 2 || source_column < 0 || source_column > 2 || target_line < 0 || target_line > 2 || target_column <0 || target_column > 2) {
		retour=3;
	}
	else if(get_piece_size(game,source_line,source_column)==NONE){
		retour=1;
	}
	else if(get_piece_size(game,source_line,source_column)<=get_piece_size(game,target_line,target_column)){
		retour=2;
	}
	else{ 
		switch(get_piece_size(game, source_line, source_column))
		{
			case NONE: //Impossible car vérification précedente
				break;
			case SMALL:
				(*game).PetiteCase[target_line][target_column]=get_place_holder(game, source_line, source_column);
				(*game).PetiteCase[source_line][source_column]=NO_PLAYER;
				break;
			case MEDIUM:
				(*game).MoyenneCase[target_line][target_column]=get_place_holder(game, source_line, source_column);
				(*game).MoyenneCase[source_line][source_column]=NO_PLAYER;
				break;
			case LARGE:
				(*game).GrandeCase[target_line][target_column]=get_place_holder(game, source_line, source_column);
				(*game).GrandeCase[source_line][source_column]=NO_PLAYER;
				break;
		}
	}
	return retour;
}

void verif_ligne(int i, int j,player *winner, player *winner2,board game){
	player temp;
	do{
		temp = get_place_holder(game,i,j);
		switch(temp)
		{
			case NO_PLAYER:
				i++;
				break;
			default:
				if(get_place_holder(game,i,1)==temp && get_place_holder(game,i,2)==temp){
					if(*winner!=temp && *winner!=NO_PLAYER)
						*winner2=temp;
					else{
						*winner=temp;
						i++;						
					}
				}
				else
					i++;
				break;
		}
	} while(*winner2==NO_PLAYER && i<DIMENSIONS);
}

void verif_colonne(int i, int j,player *winner, player *winner2, board game ){
	player temp;
	do{
		temp = get_place_holder(game,i,j);
		switch (temp)
		{
			case NO_PLAYER:
				j++;
				break;
			default:
				if(get_place_holder(game,1,j)==temp && get_place_holder(game,2,j)==temp){
					if(*winner!=temp && *winner!=NO_PLAYER)
						*winner2=temp;
					else{
						*winner=temp;
						j++;
					}		
				}
				else
					j++;
				break;
		}
	} while(*winner2==NO_PLAYER && j<DIMENSIONS);
}
