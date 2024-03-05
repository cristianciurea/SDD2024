#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct
{
	int cod; //4B
	char* den; //4B
	float pret;  //4B
	float cant; //4B
} produs;

typedef struct {

	produs info; //16B
	struct nodLs* next; //pointer de legatura, 4B

} nodLs; //20B

nodLs* inserare(nodLs* cap, produs p) {
	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	//nou->info = p;
	//initializarea informatiei utile
	nou->info.cod = p.cod;
	nou->info.den = (char*)malloc((strlen(p.den) + 1) * sizeof(char));
	strcpy(nou->info.den, p.den);
	nou->info.pret = p.pret;
	nou->info.cant = p.cant;
	//initializarea pointerului de legatura
	nou->next = NULL;
	if (cap == NULL)
	{
		cap = nou;
		nou->next = cap;
	}
		
	else {
		nodLs* aux = cap;
		while (aux->next != cap)
			aux = aux->next;

		aux->next = nou;
		nou->next = cap;
	}
	return cap;
}

void traversare(nodLs* cap) {
	nodLs* aux = cap;

	while (aux->next != cap) {
		printf("Cod = %d", aux->info.cod);
		printf(", Denumire = %s", aux->info.den);
		printf(", Pret = %5.2f", aux->info.pret);
		printf(", Cant = %5.2f", aux->info.cant);
		printf("\n");
		aux = aux->next;

	}
	printf("Cod = %d", aux->info.cod);
	printf(", Denumire = %s", aux->info.den);
	printf(", Pret = %5.2f", aux->info.pret);
	printf(", Cant = %5.2f", aux->info.cant);
	printf("\n");
}

void dezalocare(nodLs* cap) {
	nodLs* aux = cap;
	while (aux->next != cap) {
		nodLs* temp = aux->next;
		free(aux->info.den);
		free(aux);
		aux = temp;
	}
	free(aux->info.den);
	free(aux);
}

void main() {

	int n;//nr produse

	//printf("Nr produse: ");
	//scanf("%d", &n);

	nodLs* cap = NULL;
	produs p;
	char buffer[20];

	/*for (int i = 0; i < n; i++)
	{
		printf("Codul: ");
		scanf("%d", &p.cod);

		printf("Denumire: ");
		scanf("%s", buffer);

		p.den = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.den, buffer);

		printf("Pretul: ");
		scanf("%f", &p.pret);

		printf("Cantitatea: ");
		scanf("%f", &p.cant);

		cap = inserare(cap, p);
		free(p.den);
	}*/

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		//printf("Codul: ");
		fscanf(f, "%d", &p.cod);

		//printf("Denumire: ");
		fscanf(f, "%s", buffer);

		p.den = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.den, buffer);

		//printf("Pretul: ");
		fscanf(f, "%f", &p.pret);

		//printf("Cantitatea: ");
		fscanf(f, "%f", &p.cant);

		cap = inserare(cap, p);
		free(p.den);

	}
	fclose(f);

	traversare(cap);
	dezalocare(cap);
}