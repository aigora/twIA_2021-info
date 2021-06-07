#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <string.h>
#include <malloc.h>

#define N 25

typedef struct {

	char palab[N];
	char vpalab[N];

}PAL;

void administrador();
void ingresoPalabra(PAL*, int, char*);
void jugador(int, char*, char*);
void empezarJuego(char*, char*);
void dibujo(int);
void perdido(int, char*, char*);
void ganado(int, char*, char*);

void guardar(char*, char*, int);

int main() {
	
	system("mode con cols=90 lines=30");
	
	administrador();

	system("PAUSE");
}

void administrador() {
	
	PAL* c;

	int op;
	char cat[N];

	c = (PAL*)malloc(sizeof(PAL));

	if (c == NULL) printf("\n\nNo se ha podido realizar la reserva\n\n");
	else printf("\n\nMemoria reservada con exito\n\n");

	getchar();

	if (c) {
		
		do {

			system("CLS");

			printf("\n\t\t\t\tJUEGO DEL AHORCADO\n\t\t\t\t(Administrador)\n\n");
			printf(" CATEGORIAS\n\n");
			printf(" 1. Frutas\n");
			printf(" 2. Animales\n");
			printf(" 3. Paises\n");
			printf(" 4. Objetos\n");
			printf(" 5. Otra\n\n");
			printf(" 6. Salir\n\n");
			printf(" Ingresa una opcion: ");
			scanf_s("%d", &op);

		} while (op != 1 && op != 6 && op != 2 && op != 3 && op != 4 && op != 5);

		if (op == 1) ingresoPalabra(c, op, 0);
		if (op == 2) ingresoPalabra(c, op, 0);
		if (op == 3) ingresoPalabra(c, op, 0);
		if (op == 4) ingresoPalabra(c, op, 0);
		if (op == 5) {

			system("CLS");

			printf("Introduzca el nombre de la categoria: ");
			scanf_s("%s", cat, sizeof(cat));

			system("CLS");

			ingresoPalabra(c, op, cat);
		}
		if (op == 6) {

			system("CLS");

			printf("Cerrando Juego\n\n\n");

			system("PAUSE");

			exit(0);
		}
	}

	free(c);
}

void ingresoPalabra(PAL* c, int op, char* cat) {

	int in = 1, cor = 0, i;
	char pal[N];

	system("CLS");

	printf("Introduzca una palabra para jugar: ");
	scanf_s("%s", c[0].palab, sizeof(c[0].palab));

	system("CLS");

	printf("Repita la palabra a jugar para confirmar: ");
	scanf_s("%s", c[0].vpalab, sizeof(c[0].vpalab));

	system("CLS");

	for (i = 0; i < N; i++) {

		if (c[0].palab[i] >= 'a' && c[0].palab[i] <= 'z') {

			if (c[0].vpalab[i] == c[0].palab[i] - 32) c[0].vpalab[i] = c[0].palab[i];
		}

		if (c[0].palab[i] >= 'A' && c[0].palab[i] <= 'Z') {

			if (c[0].vpalab[i] == c[0].palab[i] + 32) c[0].vpalab[i] = c[0].palab[i];
		}
	}

	if (strcmp(c[0].palab, c[0].vpalab) == 0) cor = 1;

	while ((cor == 0) && (in < 3)) {

		in++;

		printf("Palabra incorrecta. Le quedan %d intentos: ", 4 - in);
	    scanf_s("%s", c[0].vpalab, sizeof(c[0].vpalab));

		system("CLS");

		if (strcmp(c[0].palab, c[0].vpalab) == 0) cor = 1;
	}

	if (cor == 0) {

		printf("Se han excedido el numero de intentos.\n\n");
		printf("Intoruzca una nueva palabra\n\n\n");

		system("PAUSE");
		system("CLS");

		ingresoPalabra(c, op, cat);
	}

	else {

		printf("Palabra guardada.\n\n");

		system("PAUSE");

		strcpy_s(pal, c[0].vpalab);

		jugador(op, cat, pal);
	}
}

void jugador(int op, char* cat, char* pal) {

	char nombrecat[4][N] = {"Frutas", "Animales", "Paises", "Objetos"};

	switch (op) {

		case 1:
			empezarJuego(pal, nombrecat[op - 1]);
		break;
		case 2:
			empezarJuego(pal, nombrecat[op - 1]);
		break;
		case 3:
			empezarJuego(pal, nombrecat[op - 1]);
		break;
		case 4:
			empezarJuego(pal, nombrecat[op - 1]);
		break;
		case 5:
			empezarJuego(pal, cat);
		break;
	}
}

void empezarJuego(char* pal, char* cat) {
	
	int i, j, longitud, espacios;
	int x = 0, puntos = 1200, aciertos = 0, intentos = 0, ganar = 0;
	char letra;
	char frase[10], letrapal[N];

	longitud = strlen(pal);

	for (i = 0; i < longitud; i++) {
		
		frase[i] = '_';
	}

	do {

		aciertos = 0;

		system("CLS");

		printf("\n\t\t\t\tJUEGO EL AHORCADO\n\t\t\t\t(Jugador)\n\n");
		printf(" CATEGORIA: %s\n\n", cat);
		printf(" Intentos Disponibles: %i\t\t\t\tPuntuacion: %i\n\n", 6 - intentos, puntos);

		dibujo(intentos);

		printf("\n\n\n");

		for (i = 0; i < longitud; i++) {
			
			if (frase[i] >= 'a' && frase[i] <= 'z') printf(" %c ", frase[i] - 32);
			else printf(" %c ", frase[i]);
		}

		if (intentos == 6) perdido(intentos, pal, cat);

		espacios = 0;

		for (i = 0; i < longitud; i++) {
			
			if (frase[i] == '_') espacios++;
		}

		if (espacios == 0) ganado(intentos, pal, cat);

		printf("\n\n Introduzca una letra: ");
		scanf_s(" %c", &letra, sizeof(letra));

		for (j = 0; j < longitud; j++) {

			if (letra == pal[j] || letra - 32 == pal[j] || letra + 32 == pal[j]) {
				
				frase[j] = letra;
				aciertos++;
			}
		}

		if (aciertos == 0) {
			
			intentos++;
			puntos -= 200;
		}

	} while (intentos != 7);
}

void dibujo(int intentos) {
	
	switch (intentos) {

		case 0:
			printf("\n     _______\n    |       |\n    |\n    |\n    |\n    |\n    |\n ----------");
		break;
		case 1:
			printf("\n     _______\n    |       |\n    |       0\n    |\n    |\n    |\n    |\n ----------");
		break;
		case 2:
			printf("\n     _______\n    |       |\n    |       0\n    |       |\n    |\n    |\n    |\n ----------");
		break;
		case 3:
			printf("\n     _______\n    |       |\n    |       0\n    |      /|\n    |\n    |\n    |\n ----------");
		break;
		case 4:
			printf("\n     _______\n    |       |\n    |       0\n    |      /|");
			printf("\\");
			printf("\n");
			printf("    |\n    |\n    |\n ----------");
		break;
		case 5:
			printf("\n     _______\n    |       |\n    |       0\n    |      /|");
			printf("\\");
			printf("\n");
			printf("    |      /\n    |\n    |\n ----------");
		break;
		case 6:
			printf("\n     _______\n    |       |\n    |       0\n    |      /|");
			printf("\\");
			printf("\n");
			printf("    |      / ");
			printf("\\");
			printf("\n");
			printf("    |\n    |\n ----------");
		break;
	}
}

void perdido(int intentos, char* pal, char* cat) {

	char sn;

    printf("\n\n PERDISTE!!\n");
	printf(" LA PALABRA CORRECTA ERA: %s\n\n", pal);

	guardar(pal, cat, intentos);

	system("PAUSE");
	system("CLS");

	printf("Desea jugar otra partida S/N: ");

	getchar();

	scanf_s("%c", &sn, sizeof(sn));

	while (sn != 'n' && sn != 'N' && sn != 's' && sn != 'S') {

		printf("\nSolo validos 'S' o 'N'\n\n");

		system("PAUSE");
		system("CLS");

		printf("Desea jugar otra partida S/N: ");

		getchar();

		scanf_s("%c", &sn, sizeof(sn));
	}

	if (sn == 's' || sn == 'S') administrador();
	if (sn == 'n' || sn == 'N') exit(0);
}

void ganado(int intentos, char* pal, char* cat) {

	char sn;

	printf("\n\n FELICIDADES, GANASTE!!\n\n");

	guardar(pal, cat, intentos);

	system("PAUSE");
	system("CLS");

	printf("Desea jugar otra partida S/N: ");

	getchar();

	scanf_s("%c", &sn, sizeof(sn));

	while (sn != 'n' && sn != 'N' && sn != 's' && sn != 'S') {

		printf("\nSolo validos 'S' o 'N'\n\n");

		system("PAUSE");
		system("CLS");

		printf("Desea jugar otra partida S/N: ");

		getchar();

		scanf_s("%c", &sn, sizeof(sn));
	}

	if (sn == 's' || sn == 'S') administrador();
	if (sn == 'n' || sn == 'N') exit(0);	
}

void guardar(char* pal, char* cat, int intent) {

	FILE* pg;
	errno_t err;

	err = fopen_s(&pg, "datos.txt", "a+");

	if (err == 0) printf(" -- The file was opened\n\n");
	else printf(" -- The file was not opened\n\n");

	if (pg != 0) {

		fprintf(pg, "Palabra: %s\nCategoria: %s\nIntentos sobrantes: %d\n", pal, cat, 6 - intent);
		
		if ((6-intent) == 0) fprintf(pg, "PARTIDA PERDIDA");
		else fprintf(pg, "PARTIDA GANADA");

		switch (intent) {
			
			case 0:
				fprintf(pg, "\n     _______\n    |       |\n    |\n    |\n    |\n    |\n    |\n ----------");
			break;
			case 1:
				fprintf(pg, "\n     _______\n    |       |\n    |       0\n    |\n    |\n    |\n    |\n ----------");
			break;
			case 2:
				fprintf(pg, "\n     _______\n    |       |\n    |       0\n    |       |\n    |\n    |\n    |\n ----------");
			break;
			case 3:
				fprintf(pg, "\n     _______\n    |       |\n    |       0\n    |      /|\n    |\n    |\n    |\n ----------");
			break;
			case 4:
				fprintf(pg, "\n     _______\n    |       |\n    |       0\n    |      /|");
				fprintf(pg, "\\");
				fprintf(pg, "\n");
				fprintf(pg, "    |\n    |\n    |\n ----------");
			break;
			case 5:
				fprintf(pg, "\n     _______\n    |       |\n    |       0\n    |      /|");
				fprintf(pg, "\\");
				fprintf(pg, "\n");
				fprintf(pg, "    |      /\n    |\n    |\n ----------");
			break;
			case 6:
				fprintf(pg, "\n     _______\n    |       |\n    |       0\n    |      /|");
				fprintf(pg, "\\");
				fprintf(pg, "\n");
				fprintf(pg, "    |      / ");
				fprintf(pg, "\\");
				fprintf(pg, "\n");
				fprintf(pg,"    |\n    |\n ----------");
			break;
		}

		fprintf(pg, "\n\n\n");

		fclose(pg);
	}
}
