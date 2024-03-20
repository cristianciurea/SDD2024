#include <stdio.h>
#include <malloc.h>

//definire structura matrice rara, reprezentata prin vectori
typedef struct
{
	int* val;
	int* lin;
	int* col;
	int m;
	int n;
	int nrnenule;
} MatriceRara;

//definire nod lista simpla
typedef struct 
{
	int valoare, linie, coloana;
	struct nod* next;
} nod;

//functie pentru citirea unei matrice de la tastatura
int** citiremat(int* nrlin, int* nrcol)
{
	printf("Nr. de linii=");
	scanf("%d", nrlin);
	printf("Nr. de coloane=");
	scanf("%d", nrcol);

	int** a = (int**)malloc((*nrlin) * sizeof(int*));
	for (int i = 0; i < (*nrlin); i++)
		a[i] = (int*)malloc((*nrcol) * sizeof(int));

	for (int i = 0; i < (*nrlin); i++)
		for (int j = 0; j < (*nrcol); j++)
		{
			printf("matr[%d][%d]=", i, j);
			scanf("%d", &a[i][j]);
		}
	return a;
}

//procedura pentru afisarea unei matrice
void afisare(int** a, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		printf("\n");
		for (int j = 0; j < n; j++) 
			printf("%d ", a[i][j]);
	}
}

//functie pentru a verifica daca o matrice este rara
int rara(int** a, int nrlin, int nrcol)
{
	float s = 0;
	for (int i = 0; i < nrlin; i++)
		for (int j = 0; j < nrcol; j++) 
			if (a[i][j] != 0) 
				s++;
	if (s / (float)(nrlin * nrcol) < 0.3) 
		return s;
	else return 0;
}

//functia pentru transformarea unei matrice completa in matrice rara reprezentata prin 3 vectori
MatriceRara transformare(int** a, int nrlin, int nrcol)
{
	MatriceRara b;
	b.m = b.n = b.nrnenule = 0;
	b.col = b.lin = b.val = NULL;
	int k = 0, temp;
	if (temp = rara(a, nrlin, nrcol))
	{
		b.val = (int*)malloc(temp * sizeof(int));
		b.col = (int*)malloc(temp * sizeof(int));
		b.lin = (int*)malloc(temp * sizeof(int));
		b.m = nrlin;
		b.n = nrcol;
		b.nrnenule = rara(a, nrlin, nrcol);
		for (int i = 0; i < nrlin; i++)
			for (int j = 0; j < nrcol; j++)
			{
				if (a[i][j])
				{
					b.val[k] = a[i][j];
					b.lin[k] = i;
					b.col[k] = j;
					k++;
				}
			}
	}
	return b;
}

//functia pentru transformarea unei matrice completa in matrice rara reprezentata prin lista simpla
nod* transform_lista(nod* cap, int** a, int nrlin, int nrcol)
{
	nod* p;
	for (int i = 0; i < nrlin; i++)
		for (int j = 0; j < nrcol; j++)
		{
			if (a[i][j] && rara(a, nrlin, nrcol))
			{
				nod* nou = (nod*)malloc(sizeof(nod));
				nou->valoare = a[i][j];
				nou->linie = i;
				nou->coloana = j;
				if (cap == NULL)
				{
					nou->next = NULL;
					cap = nou;
				}
				else
				{
					for (p = cap; p->next; p = p->next);
					p->next = nou;
					nou->next = NULL;
					p = nou;
				}
			}
		}
	return cap;
}

//procedura pentru afisarea unei matrice rare
void afisareRara(MatriceRara mat)
{
	printf("\n");
	for (int i = 0; i < mat.nrnenule; i++)
		printf("%d (%d,%d) ", mat.val[i], mat.lin[i], mat.col[i]);
}

//functie pentru extragerea elementului de pe linia i si col j a matricei rare
int extrag(MatriceRara a, int i, int j)
{
	for (int k = 0; k < a.nrnenule; k++)
		if ((a.lin[k] == i) && (a.col[k] == j)) 
			return a.val[k];
	return 0;
}

//dezalocare matrice
void dezaloc_matrice(int** a, int nrlin, int nrcol)
{
	for (int i = 0; i < nrlin; i++) 
		free(a[i]);
	free(a);
}

//dezalocare vectori
void dezaloc_vectori(MatriceRara mat)
{
	free(mat.lin);
	free(mat.col);
	free(mat.val);
}

//dezalocare memorie
void dezaloc_lista(nod* cap)
{
	nod* p = cap, * q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
}

void main()
{
	int** mat1;
	int m, n;

	mat1 = citiremat(&m, &n);
	afisare(mat1, m, n);
	MatriceRara a;
	a = transformare(mat1, m, n);
	printf("\nMatricea rara reprezentata prin vectori:\n");
	afisareRara(a);

	nod* cap = NULL;
	cap = transform_lista(cap, mat1, m, n);
	nod* p = cap;
	printf("\nMatricea rara reprezentata prin lista simpla:\n");
	while (p)
	{
		printf("%d (%d,%d) ", p->valoare, p->linie, p->coloana);
		p = p->next;
	}

	//dezalocari
	dezaloc_matrice(mat1, m, n);
	dezaloc_vectori(a);
	dezaloc_lista(cap);
}