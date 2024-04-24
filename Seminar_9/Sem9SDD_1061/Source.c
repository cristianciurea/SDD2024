#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int nrMatricol;
	char* nume;
	float medie;
} student;

typedef struct
{
	student inf;
	struct nodArb *stanga, *dreapta;
} nodArb;

nodArb* creareNod(student s, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) *
		sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(nodArb* rad, student s)
{
	if (rad != NULL)
	{
		if (s.nrMatricol < rad->inf.nrMatricol)
		{
			rad->stanga = inserareNod(rad->stanga, s);
			return rad;
		}
		else
			if (s.nrMatricol > rad->inf.nrMatricol)
			{
				rad->dreapta = inserareNod(rad->dreapta, s);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(s, NULL, NULL);
}

void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			rad->inf.nrMatricol, rad->inf.nume,
			rad->inf.medie);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{
		/*nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);*/

		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->inf.nume);
		free(rad);
	}
}

//salvare in vector studenti din noduri frunza
void salvareVectorFrunze(nodArb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		salvareVectorFrunze(rad->stanga, vect, nr);
		salvareVectorFrunze(rad->dreapta, vect, nr);
	}
}

void nrStudentiMediePrag(nodArb* rad, int* nr, float prag)
{
	if (rad != NULL)
	{
		if (rad->inf.medie >= prag)
			(*nr)++;
		nrStudentiMediePrag(rad->stanga, nr, prag);
		nrStudentiMediePrag(rad->dreapta, nr, prag);
	}
}

void main()
{
	student s;
	nodArb* rad = NULL;
	char buffer[20];

	int nrStud;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserareNod(rad, s);
		free(s.nume);
	}
	fclose(f);

	preordine(rad);

	printf("\n-----------------\n");
	int nr = 0;
	student* vect = (student*)malloc(nrStud * sizeof(student));
	salvareVectorFrunze(rad, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			vect[i].nrMatricol, vect[i].nume, vect[i].medie);
	free(vect);

	printf("\n-----------------\n");
	nr = 0;
	nrStudentiMediePrag(rad, &nr, 9);
	printf("\nNr. studenti cu media > 9 este %d", nr);

	dezalocare(rad);
}