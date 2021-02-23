GobbletsGobbers: game.o board.o ./Fonctions/affichage.o ./Fonctions/verifications.o
	gcc game.o board.o ./Fonctions/affichage.o ./Fonctions/verifications.o -o GobbletsGobbers -Wall

game.o: game.c
	gcc game.c -c -Wall

board.o: board.c board.h
	gcc board.c -c -Wall

verifications.o: verifications.c 
	gcc ./Fonctions/verifications.c -c -Wall

affichage.o: affichage.c definitions.h
	gcc ./Fonctions/affichage.c -c -Wall

clean:
	rm -f [!board]*.o
	rm -f *~
	rm -f ./Fonctions/*.o
	rm -f ./Fonctions/*~

oprof:
	cp boardprof.o board.o
	
