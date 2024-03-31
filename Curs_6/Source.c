#include <stdio.h>
#include <malloc.h>

typedef struct 
{
	int cod;
	char* nume;
	float medie;
} student;

typedef struct 
{
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

//functie pentru inserarea unui nod in arborele binar de cautare
nodarb* inserareLista(student s, nodarb* rad)
{
	if (rad != NULL)
	{
		if (s.cod < rad->inf.cod)
		{
			rad->left = inserareLista(s, rad->left);
			return rad;
		}
		else
			if (s.cod > rad->inf.cod)
			{
				rad->right = inserareLista(s, rad->right);
				return rad;
			}
			else
				return rad;
	}
	else
		return creare(s, NULL, NULL);
}

//functie de traversare in preordine
void preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
		preordine(rad->left);
		preordine(rad->right);
	}
}

//functie de traversare in inordine
void inordine(nodarb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
		inordine(rad->right);
	}
}

//functie de traversare in postordine
void postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", rad->inf.cod, rad->inf.nume, rad->inf.medie);
	}
}

//functie pentru dezalocare arbore
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

//functie pentru cautarea unui nod dupa cheie
nodarb* cautare(nodarb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.cod)
			return rad;
		else
			if (cheie < rad->inf.cod)
				return cautare(rad->left, cheie);
			else
				return cautare(rad->right, cheie);
	}
	else
		return NULL;
}

//functie pentru stergerea nodului radacina
nodarb* stergeRad(nodarb* rad)
{
	nodarb* aux = rad;
	if (aux->left != NULL)
	{
		rad = aux->left;
		if (aux->right != NULL)
		{
			nodarb* temp = aux->left;
			while (temp->right)
				temp = temp->right;
			temp->right = aux->right;
		}
	}
	else
		if (aux->right != NULL)
			rad = aux->right;
		else
			rad = NULL;
	free(aux->inf.nume);
	free(aux);
	return rad;
}

//functie pentru stergerea oricarui nod dupa cheie
nodarb* stergeNod(nodarb* rad, int cheie)
{
	if (rad == NULL)
		return NULL;
	else
		if (rad->inf.cod == cheie)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
			if (cheie < rad->inf.cod)
			{
				rad->left = stergeNod(rad->left, cheie);
				return rad;
			}
			else
			{
				rad->right = stergeNod(rad->right, cheie);
				return rad;
			}
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

		rad = inserareLista(s, rad);
	}
	fclose(f);

	inordine(rad);
	printf("\n-------subarbore stang-------------\n");
	inordine(rad->left);
	printf("\n-------subarbore drept-------------\n");
	inordine(rad->right);

	printf("\n-------cautare student-------------\n");
	nodarb* nodCautat = cautare(rad, 6);
	if (nodCautat != NULL)
		printf("\nStudentul cautat se numeste %s", nodCautat->inf.nume);
	else
		printf("\nNu exista!");

	rad = stergeNod(rad, 9);
	printf("\n-------dupa stergere cheie 9-------------\n");
	inordine(rad);

	dezalocare(rad);
}