//Inchiderea tranzitiva a grafului
#include <stdio.h>

typedef struct 
{
	int inf;
    struct stiva* next;
} stiva;

void push(stiva** varf, int nod)
{
	stiva* tmp = (stiva*)malloc(sizeof(stiva));
	tmp->inf = nod;
	tmp->next = NULL;
	if (*varf == NULL)
	{
		*varf = tmp;
	}
	else
	{
		tmp->next = *varf;
		*varf = tmp;
	}
}

void pop(stiva** varf, int* nod)
{
	if (*varf != NULL)
	{
		stiva* temp = *varf;
		*varf = (*varf)->next;
		(*nod) = temp->inf;
		free(temp);
	}
}

void afisare(int mat[20][20], int n)
{
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			printf("%6d", mat[i][j]);
		printf("\n");
	}
}

void main()
{
	int mat[20][20], mat_tranz[20][20], viz[20], nod, n, i, j, k;

	//varful stivei
	stiva* varf = NULL;

	FILE* f = fopen("fisier1.txt", "r");
	if (f)
	{
		fscanf(f, "%d", &n);
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				fscanf(f, "%d", &mat[i][j]);
	}
	else 
		printf("\nNu exista fisier!");

	printf("\nGraful are %d noduri, matricea sa de adiacenta fiind:\n", n);
	afisare(mat, n);

	//se creeza matricea închiderii tranzitive initialã plecând de la matricea de adiacentã a grafului
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			if (i == j)
				mat_tranz[i][j] = 1;
			else
				mat_tranz[i][j] = mat[i][j];

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++) 
			viz[j] = 0;

		//se viziteaza nodul "i"
		viz[i] = 1;
		push(&varf, i);

		while (varf != NULL)
		{
			//se extrage nodul "nod" din stiva
			pop(&varf, &nod);
			printf("%d-", nod);
			mat_tranz[i][nod] = 1;

			for (int k = 1; k <= n; k++)
			{
				//se pun in stiva toate nodurile adiacente nevizitate
				if (mat[nod][k] == 1 && viz[k] == 0)
				{
					push(&varf, k);
					viz[k] = 1;
				}
			}
		}
		printf("\n");
	}

	//se afiseaza inchiderea tranzitiva a grafului
	printf("\nInchiderea tranzitiva a grafului este:\n", n);
	afisare(mat_tranz, n);
}