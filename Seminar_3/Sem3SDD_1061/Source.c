#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int nrMatricol;
	char* nume;
	float medie;
} student;

typedef struct
{
	student inf; //informatie utila
	struct nodLS* next, *prev; //pointer de legatura
} nodLS;

nodLS* inserareNod(nodLS* cap, nodLS** coada, student s)
{
	//creare nod
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	//initializare nod
	//nou->inf = s;
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) *
		sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	/*nou->next = NULL;
	nou->prev = NULL;*/
	//adaugare nod in lista
	if (cap == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
		(*coada)->next = cap;
		cap->prev = *coada;
	}
	return cap;
}

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		//prelucrare a inf. utile
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->next; //deplasare pe nod urmator
	}
	printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
		temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
}

void traversareInvers(nodLS* coada)
{
	nodLS* temp = coada;
	while (temp->prev != coada)
	{
		//prelucrare a inf. utile
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->prev; //deplasare pe nod anterior
	}
	printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
		temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		//stergere
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
	free(temp->inf.nume);
	free(temp);
}

void salvareVector(nodLS* cap, student* vect, int* nrElem, float prag)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		if (temp->inf.medie > prag)
		{
			//vect[*nrElem] = temp->inf;
			vect[*nrElem].nrMatricol = temp->inf.nrMatricol;
			vect[*nrElem].nume = (char*)malloc((strlen(temp->inf.nume) + 1) *
				sizeof(char));
			strcpy(vect[*nrElem].nume, temp->inf.nume);
			vect[*nrElem].medie = temp->inf.medie;
			(*nrElem)++;
		}
		temp = temp->next;
	}
	if (temp->inf.medie > prag)
	{
		//vect[*nrElem] = temp->inf;
		vect[*nrElem].nrMatricol = temp->inf.nrMatricol;
		vect[*nrElem].nume = (char*)malloc((strlen(temp->inf.nume) + 1) *
			sizeof(char));
		strcpy(vect[*nrElem].nume, temp->inf.nume);
		vect[*nrElem].medie = temp->inf.medie;
		(*nrElem)++;
	}
}

void main()
{
	int nrStud;
	nodLS* cap = NULL, *coada = NULL;
	student s;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		cap = inserareNod(cap, &coada, s);
		free(s.nume);
	}
	fclose(f);

	traversare(cap);

	printf("\n---------------------\n");

	traversareInvers(coada);

	printf("\n---------------------\n");
	int nrElem = 0;
	student* vect = (student*)malloc(nrStud * sizeof(student));
	salvareVector(cap, vect, &nrElem, 9.5f);
	for (int i = 0; i < nrElem; i++)
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			vect[i].nrMatricol, vect[i].nume, vect[i].medie);
	for (int i = 0; i < nrElem; i++)
		free(vect[i].nume);
	free(vect);

	dezalocare(cap);
}