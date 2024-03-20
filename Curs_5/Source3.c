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

//definire nod lista simpla secundara (sublista)
typedef struct 
{
	int coloana, valoare;
	struct nodLS* next;
} nodLS;

//definire nod lista simpla principala
typedef struct 
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

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

//functia pentru crearea unei subliste simple cu elementele de pe o anumita linie a matricei
nodLS* transform_lista(nodLS* cap, int** a, int nrlin, int nrcol, int lin)
{
	nodLS* p;
	for (int j = 0; j < nrcol; j++)
	{
		if (a[lin][j] && rara(a, nrlin, nrcol))
		{
			nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
			nou->valoare = a[lin][j];
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

//inserare nod in lista simpla principala
nodLP* inserare(nodLP* capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next= NULL;
	if (capLP == NULL)
	{
		return nou;
	}
	else
	{
		nodLP* p;
		for (p = capLP; p->next; p = p->next);
		p->next = nou;
		return capLP;
	}
}

//traversare lista simpla secundara (sublista)
void traversare(nodLS* cap)
{
	nodLS* p = cap;
	while (p)
	{
		printf("%d (%d) ", p->valoare, p->coloana);
		p = p->next;
	}
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

//dezalocare lista secundara (sublista)
void dezaloc_lista_sec(nodLS* cap)
{
	nodLS* p = cap, * q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
}

//dezalocare lista de liste
void dezaloc_lista_liste(nodLP* capLP)
{
	nodLP* p = capLP, * q;
	while (p)
	{
		q = p->next;
		if (p->inf) 
			dezaloc_lista_sec(p->inf);
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

	nodLP* capLP = NULL;
	for (int i = 0; i < m; i++)
	{
		nodLS* capLS = NULL;
		capLS = transform_lista(capLS, mat1, m, n, i);
		capLP = inserare(capLP, capLS);
	}

	printf("\nMatricea rara reprezentata prin lista de liste:\n");
	nodLP* p = capLP;
	int i = 0;
	while (p)
	{
		printf("\nSublista aferenta liniei %d\n", i);
		traversare(p->inf);
		p = p->next;
		i++;
	}

	//dezalocari
	dezaloc_matrice(mat1, m, n);
	dezaloc_vectori(a);
	dezaloc_lista_liste(capLP);
}