#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct 
{
	int cod;
	char* nume;
	float medie;
} student;

//structura nodului include si gradul de echilibru (BF)
typedef struct 
{
	int BF;
	student inf;
	struct nodarb* left, * right;
} nodarb;

//functie pentru initializarea unui nod
nodarb* creare(student s, nodarb* st, nodarb* dr)
{
	nodarb* nou = (nodarb*)malloc(sizeof(nodarb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->left = st;
	nou->right = dr;
	return nou;
}

//functie de inserare nod in arbore binar de cautare
nodarb* inserare(student s, nodarb* rad)
{
	nodarb* aux = rad;
	if (rad == NULL)
	{
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (1)
		{
			if (s.cod < aux->inf.cod)
				if (aux->left != NULL)
					aux = aux->left;
				else
				{
					aux->left = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->right != NULL)
						aux = aux->right;
					else
					{
						aux->right = creare(s, NULL, NULL);
						return rad;
					}
				else
					return rad;
		}
}

//functie de traversare preordine
void preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		preordine(rad->left);
		preordine(rad->right);
	}
}

//functie de traversare inordine
void inordine(nodarb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		inordine(rad->right);
	}
}

//functie de traversare postordine
void postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
	}
}

//functie de dezalocare arbore
void dezalocare(nodarb* rad)
{
	if (rad != NULL)
	{
		nodarb* st = rad->left;
		nodarb* dr = rad->right;
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

//functie pentru calcul inaltime arbore
int nrNiveluri(nodarb* rad)
{
	if (rad != NULL)
		return 1 + maxim(nrNiveluri(rad->left), nrNiveluri(rad->right));
	else
		return 0;
}

//functie pentru initializare grad de echilibru la nivelul fiecarui nod
void calculBF(nodarb* rad)
{
	if (rad != NULL)
	{
		rad->BF = nrNiveluri(rad->right) - nrNiveluri(rad->left);
		calculBF(rad->left);
		calculBF(rad->right);
	}
}

//functie pentru implementare rotatie dreapta
nodarb* rotatie_dreapta(nodarb* rad)
{
	printf("\nRotatie dreapta\n");
	nodarb* nod1 = rad->left;
	rad->left = nod1->right;
	nod1->right = rad;
	rad = nod1;
	return rad;
}

//functie pentru implementare rotatie stanga
nodarb* rotatie_stanga(nodarb* rad)
{
	printf("\nRotatie stanga\n");
	nodarb* nod1 = rad->right;
	rad->right = nod1->left;
	nod1->left = rad;
	rad = nod1;
	return rad;
}

//functie pentru implementare rotatie dreapta-stanga
nodarb* rotatie_dreapta_stanga(nodarb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodarb* nod1 = rad->right;
	nodarb* nod2 = nod1->left;
	nod1->left = nod2->right;
	nod2->right = nod1;
	rad->right = nod2->left;
	nod2->left = rad;
	rad = nod2;
	return rad;
}

//functie pentru implementare rotatie stanga-dreapta
nodarb* rotatie_stanga_dreapta(nodarb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodarb* nod1 = rad->left;
	nodarb* nod2 = nod1->right;
	nod1->right = nod2->left;
	nod2->left = nod1;
	rad->left = nod2->right;
	nod2->right = rad;
	rad = nod2;
	return rad;
}

//functie pentru reechilibrare arbore in situatia aplicarii celor 4 rotatii
nodarb* reechilibrare(nodarb* rad)
{
	calculBF(rad);
	nodarb* stanga = rad->left;
	nodarb* dreapta = rad->right;
	if (rad->BF <= -2 && stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF >= 2 && dreapta->BF >= 1)
		{
			rad = rotatie_stanga(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && dreapta->BF <= -1)
			{
				rad = rotatie_dreapta_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF <= -2 && stanga->BF >= 1)
				{
					rad = rotatie_stanga_dreapta(rad);
					calculBF(rad);
				}
	return rad;
}

void main()
{
	int n;
	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &n);

	nodarb* rad = NULL;
	student s;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserare(s, rad);

		rad = reechilibrare(rad);
	}
	fclose(f);

	inordine(rad);
	printf("\n------------------------\n");
	inordine(rad->left);
	printf("\n------------------------\n");
	inordine(rad->right);
	printf("\n------------------------\n");

	printf("\nInaltime arbore este %d", nrNiveluri(rad));
	printf("\nInaltime subarbore stang este %d", nrNiveluri(rad->left));
	printf("\nInaltime subarbore drept este %d", nrNiveluri(rad->right));

	dezalocare(rad);
}