#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Fonctions/definitions.h"
#include "board.h"


int main(int argc, char **argv){
//VARIABLES
    SDL_bool program_launched = SDL_TRUE;
    SDL_Window *window = NULL; 
    SDL_Renderer *renderer = NULL;
    
    TTF_Font * Arial = NULL,* Arial2 = NULL;

    SDL_Surface * message = NULL,* message2 = NULL,* msgMenu = NULL,* msgNewGame = NULL,
    * msgRules = NULL,* msgQuitter = NULL,* rulesText1 = NULL,* rulesText2 = NULL,* rulesText3 = NULL,* rulesText4 = NULL;
    SDL_Texture * text = NULL,* text2 = NULL,* menutext = NULL,* newgame = NULL,
    * rules = NULL,* quitter = NULL,* tRules1 = NULL,* tRules2 = NULL,* tRules3 = NULL,* tRules4 = NULL;
    SDL_Rect textRect, text2Rect, menutextRect, newgameRect, rulesRect, quitterRect, rulesText1Rect, rulesText2Rect, rulesText3Rect, rulesText4Rect;
    SDL_Color textColor, text2Color, textmenuColor;
    int w=0, h=0,statu=0;
    
//INITIALISATION
    textColor.r=0;textColor.g=0;textColor.b=255;
    text2Color.r=255;text2Color.g=0;text2Color.b=0;
    textmenuColor.r=255;textmenuColor.g=255;textmenuColor.b=255;
    //Lancement SDL & TTF
    SDL_Init(SDL_INIT_VIDEO);
    //Création fenêtre + rendu
    window = SDL_CreateWindow("GobbletsGobbers",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000,
        600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    TTF_Init();
    Arial = TTF_OpenFont("Arial.ttf", 20);
    Arial2 = TTF_OpenFont("Arial.ttf", 12);

    message = TTF_RenderText_Solid(Arial, "GOBBLETSGOBBERS", textColor);
    message2 = TTF_RenderText_Solid(Arial2, "Par LEBARBANCHON Valentin & LEMOINE Julien", text2Color);
    msgMenu = TTF_RenderText_Solid(Arial, "MENU", textmenuColor);
    msgNewGame = TTF_RenderText_Solid(Arial, "1 - Nouvelle Partie", textmenuColor);
    msgRules = TTF_RenderText_Solid(Arial, "2 - Regles", textmenuColor);
    msgQuitter = TTF_RenderText_Solid(Arial,"Echap - Quitter", textmenuColor);
    rulesText1 = TTF_RenderUTF8_Blended_Wrapped(Arial2,"Ce jeu se joue à deux joueurs sur un plateau constitué d’un damier de trois cases par trois cases, comme le morpion. Chaque joueur dispose au début de six pièces de jeu dans sa maison. Les pièces peuvent être de trois tailles : petite, moyenne ou grosse, et chaque joueur possède deux pièces de chaque taille au début de la partie. Les joueurs exécutent chacun leur tour une action parmi les deux actions suivantes :",textmenuColor,800);
    rulesText2 = TTF_RenderUTF8_Solid(Arial2,"—  Un joueur peut placer une pièce de sa maison sur une case du plateau.", textmenuColor);
    rulesText3 = TTF_RenderUTF8_Solid(Arial2,"—  Un joueur peut déplacer l’une de ses pièces présentes sur le plateau (et visible) vers une autre case du plateau.", textmenuColor);
    rulesText4 = TTF_RenderUTF8_Blended_Wrapped(Arial2,"Pour placer (ou déplacer) une pièce sur le plateau, il est nécessaire que la case d’arrivée soit libre ou ne contienne que des pièces plus petites que la pièce placée. Dans le cas où une pièce est posée sur une case occupée, celle-ci couvre alors les pièces déjà présentes, les rendant invisibles. On peut donc couvrir une petite pièce avec une pièce moyenne ou une grande, ou couvrir une pièce moyenne avec une pièce grande. Il est possible de couvrir indifféremment une pièce de l’adversaire ou l’une de ses propres pièces. Une case peut donc comporter au plus trois pièces en même temps, une petite,une moyenne et une grande. Seule la plus grande pièce présente sur la case est alors visible. Lorsque l’on déplace une pièce qui en couvrait une autre, la pièce précédemment cachée redevient alors visible. Si on déplace une grande pièce qui couvrait une pièce petite et une moyenne, seule la pièce moyenne devient visible. Un joueur remporte la partie lorsqu’il parvient à ce que toutes les pièces visibles d’une ligne, d’une colonne ou d’une diagonale lui appartiennent. Dans le cas peu probable où les deux joueurs satisfont la condition de victoire lors d’un même mouvement, la partie continue jusqu’à ce qu’un seul joueur soit en position gagnante. Ce cas peut arriver quand lors d’un déplacement, la pièce déplacée révèle une ligne gagnante dans la position quittée en même temps qu’elle en crée une avec la case atteinte.",textmenuColor,800);
    
    text = SDL_CreateTextureFromSurface(renderer, message);
    text2 = SDL_CreateTextureFromSurface(renderer, message2);
    menutext = SDL_CreateTextureFromSurface(renderer, msgMenu);
    newgame = SDL_CreateTextureFromSurface(renderer, msgNewGame);
    rules = SDL_CreateTextureFromSurface(renderer, msgRules);
    quitter = SDL_CreateTextureFromSurface(renderer, msgQuitter);
    tRules1 = SDL_CreateTextureFromSurface(renderer, rulesText1);
    tRules2 = SDL_CreateTextureFromSurface(renderer, rulesText2);
    tRules3 = SDL_CreateTextureFromSurface(renderer, rulesText3);
    tRules4 = SDL_CreateTextureFromSurface(renderer, rulesText4);

    //GLOBAL
    SDL_QueryTexture(text, NULL, NULL, &w, &h);
    textRect.x=(1000-w)/2;textRect.y=0;textRect.w=w;textRect.h=h;
    SDL_QueryTexture(text2, NULL, NULL, &w, &h);
    //MENU
    text2Rect.x=(1000-w)/2;text2Rect.y=25;text2Rect.w=w;text2Rect.h=h;
    SDL_QueryTexture(menutext, NULL, NULL, &w, &h);
    menutextRect.x=(1000-w)/2;menutextRect.y=100;menutextRect.w=w;menutextRect.h=h;
    SDL_QueryTexture(newgame, NULL, NULL, &w, &h);
    newgameRect.x=(1000-w)/2;newgameRect.y=130;newgameRect.w=w;newgameRect.h=h;
    SDL_QueryTexture(rules, NULL, NULL, &w, &h);
    rulesRect.x=(1000-w)/2;rulesRect.y=160;rulesRect.w=w;rulesRect.h=h;
    SDL_QueryTexture(quitter, NULL, NULL, &w, &h);
    quitterRect.x=(1000-w)/2;quitterRect.y=190;quitterRect.w=w;quitterRect.h=h;
    //MENU > 1

    //MENU > 2
    SDL_QueryTexture(tRules1, NULL, NULL, &w, &h);
    rulesText1Rect.x=(1000-w)/2;rulesText1Rect.y=200;rulesText1Rect.w=w;rulesText1Rect.h=h;
    SDL_QueryTexture(tRules2, NULL, NULL, &w, &h);
    rulesText2Rect.x=(1000-w)/2;rulesText2Rect.y=250;rulesText2Rect.w=w;rulesText2Rect.h=h;
    SDL_QueryTexture(tRules3, NULL, NULL, &w, &h);
    rulesText3Rect.x=(1000-w)/2;rulesText3Rect.y=280;rulesText3Rect.w=w;rulesText3Rect.h=h;
    SDL_QueryTexture(tRules4, NULL, NULL, &w, &h);
    rulesText4Rect.x=(1000-w)/2;rulesText4Rect.y=300;rulesText4Rect.w=w;rulesText4Rect.h=h;

//GRILLE
    
//PROGRAMME
    while(program_launched){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT: // Croix de la fenêtre
                    program_launched = SDL_FALSE;
                    break;
                case SDL_KEYDOWN: // Touche du clavier
                    switch(event.key.keysym.sym){
                        case SDLK_1: // Touche 1/&
                        //On efface // ON PEUT FAIRE PLUS SIMPLE UN SEUL MSG ON EVITE DEUX ACTION ET ON REDUIT LE CODE
                            msgMenu = TTF_RenderText_Solid(Arial, "", textmenuColor);
                            msgRules = TTF_RenderText_Solid(Arial, "", textmenuColor);
                            msgNewGame = TTF_RenderText_Solid(Arial, "", textmenuColor);
                            menutext = SDL_CreateTextureFromSurface(renderer, msgMenu);
                            rules = SDL_CreateTextureFromSurface(renderer, msgRules);
                            newgame = SDL_CreateTextureFromSurface(renderer, msgNewGame);
                            SDL_RenderClear(renderer);
                        //On replace
                            SDL_QueryTexture(quitter, NULL, NULL, &w, &h);
                            quitterRect.x=(1000-w)/2;quitterRect.y=600-h;quitterRect.w=w;quitterRect.h=h;
                            SDL_RenderCopy(renderer, quitter, NULL, &quitterRect);
                        //On ajoute
                            SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);
                        //Dessin grille
                            //Colonnes
                            SDL_RenderDrawLine(renderer, 150, 150, 150, 450);
                            SDL_RenderDrawLine(renderer, 250, 150, 250, 450);
                            SDL_RenderDrawLine(renderer, 350, 150, 350, 450);
                            SDL_RenderDrawLine(renderer, 450, 150, 450, 450);
                            //Lignes
                            SDL_RenderDrawLine(renderer, 150, 150, 450, 150);
                            SDL_RenderDrawLine(renderer, 150, 250, 450, 250);
                            SDL_RenderDrawLine(renderer, 150, 350, 450, 350);
                            SDL_RenderDrawLine(renderer, 150, 450, 450, 450);
                        // Croix
                                while(1){
                                    switch (event.type){
                                        case SDL_MOUSEBUTTONDOWN:
                                            if(event.button.button == SDL_BUTTON_LEFT){
                                                int x = event.button.x, y = event.button.y;
                                                if(x>150 && x<250){
                                                    if(y>150 && y<250){
                                                        SDL_RenderDrawLine(renderer, 150, 150, 250, 250);
                                                        SDL_RenderDrawLine(renderer, 250, 150, 150, 250);
                                                    }
                                                    else if(y>250 && y<350){
                                                        SDL_RenderDrawLine(renderer, 150, 250, 250, 350);
                                                        SDL_RenderDrawLine(renderer, 250, 250, 150, 350);
                                                    }
                                                    else if(y>350 && y<450){
                                                        SDL_RenderDrawLine(renderer, 150, 350, 250, 450);
                                                        SDL_RenderDrawLine(renderer, 250, 350, 150, 450);
                                                    }
                                                }
                                                else if(x>250 && x<350){
                                                    if(y>150 && y<250){
                                                        SDL_RenderDrawLine(renderer, 250, 150, 350, 250);
                                                        SDL_RenderDrawLine(renderer, 350, 150, 250, 250);
                                                    }
                                                    else if(y>250 && y<350){
                                                        SDL_RenderDrawLine(renderer, 250, 250, 350, 350);
                                                        SDL_RenderDrawLine(renderer, 350, 250, 250, 350);
                                                    }
                                                    else if(y>350 && y<450){
                                                        SDL_RenderDrawLine(renderer, 250, 350, 350, 450);
                                                        SDL_RenderDrawLine(renderer, 350, 350, 250, 450);
                                                    }
                                                }
                                                else if(x>350 && x<450){
                                                    if(y>150 && y<250){
                                                        SDL_RenderDrawLine(renderer, 350, 150, 450, 250);
                                                        SDL_RenderDrawLine(renderer, 450, 150, 350, 250);
                                                    }
                                                    else if(y>250 && y<350){
                                                        SDL_RenderDrawLine(renderer, 350, 250, 450, 350);
                                                        SDL_RenderDrawLine(renderer, 450, 250, 350, 350);
                                                    }
                                                    else if(y>350 && y<450){
                                                        SDL_RenderDrawLine(renderer, 350, 350, 450, 450);
                                                        SDL_RenderDrawLine(renderer, 450, 350, 350, 450);
                                                    }                      
                                                }
                                            }
                                            SDL_RenderClear(renderer);
                                            SDL_RenderPresent(renderer);   
                                    }
                               }                         
                            break; 
                        case SDLK_2: // Touche 2/é
                        //On efface
                            msgMenu = TTF_RenderText_Solid(Arial, "", textmenuColor);
                            msgRules = TTF_RenderText_Solid(Arial, "", textmenuColor);
                            menutext = SDL_CreateTextureFromSurface(renderer, msgMenu);
                            rules = SDL_CreateTextureFromSurface(renderer, msgRules);
                            SDL_RenderClear(renderer);
                        //On replace
                            SDL_QueryTexture(newgame, NULL, NULL, &w, &h);
                            newgameRect.x=50;newgameRect.y=600-h-30;newgameRect.w=w;newgameRect.h=h;
                            SDL_RenderCopy(renderer, newgame, NULL, &newgameRect);
                            SDL_QueryTexture(quitter, NULL, NULL, &w, &h);
                            quitterRect.x=1000-w-50;quitterRect.y=600-h-30;quitterRect.w=w;quitterRect.h=h;
                            SDL_RenderCopy(renderer, quitter, NULL, &quitterRect);
                        //On ajoute
                            SDL_RenderCopy(renderer, tRules1, NULL, &rulesText1Rect);
                            SDL_RenderCopy(renderer, tRules2, NULL, &rulesText2Rect);
                            SDL_RenderCopy(renderer, tRules3, NULL, &rulesText3Rect);
                            SDL_RenderCopy(renderer, tRules4, NULL, &rulesText4Rect);
                            break;
                        case SDLK_ESCAPE: // Touche Echap/"
                            program_launched = SDL_FALSE;
                            break;
                        default:
                            break;
                }
		SDL_RenderPresent(renderer);
                default:
                // Affichage menu principal
                    SDL_RenderCopy(renderer, text, NULL, &textRect);
                    SDL_RenderCopy(renderer, text2, NULL, &text2Rect);
                    SDL_RenderCopy(renderer, menutext, NULL, &menutextRect);
                    SDL_RenderCopy(renderer, newgame, NULL, &newgameRect);
                    SDL_RenderCopy(renderer, rules, NULL, &rulesRect);
                    SDL_RenderCopy(renderer, quitter, NULL, &quitterRect);
                    break;                
            }
            SDL_RenderPresent(renderer);
        }
    }

    
    // do{
    //     
//FREE MEMORY
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(text);
    TTF_CloseFont(Arial);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
