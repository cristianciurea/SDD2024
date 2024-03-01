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
	struct nodLS* next; //pointer de legatura
} nodLS;

nodLS* inserareNod(nodLS* cap, student s)
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
	nou->next = NULL;
	//adaugare nod in lista
	if (cap == NULL)
		cap = nou;
	else
	{
		nodLS* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		//prelucrare a inf. utile
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->next; //deplasare pe nod urmator
	}
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		//stergere
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
}

void salvareVector(nodLS* cap, student* vect, int* nrElem, float prag)
{
	nodLS* temp = cap;
	while (temp != NULL)
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
}

void main()
{
	int nrStud;
	nodLS* cap = NULL;
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
		cap = inserareNod(cap, s);
		free(s.nume);
	}
	fclose(f);

	traversare(cap);

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