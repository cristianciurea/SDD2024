#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int inf; //id nod graf
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	int inf; //id nod graf
	struct nodCoada* next;
} nodCoada;

void push(nodStiva** varf, int idNod)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = idNod;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, int* idNod)
{
	if (*varf == NULL)
		return -1;
	else
	{
		*idNod = (*varf)->inf;
		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
		return 0;
	}
}

void put(nodCoada** prim, nodCoada** ultim, int idNod)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = idNod;
	nou->next = NULL;
	if (*prim == NULL || *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, int* idNod)
{
	if (*prim != NULL && *ultim != NULL)
	{
		*idNod = (*prim)->inf;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void parcurgereAdancime(int** mat, int* vizitate, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitate[i] = 0;

	nodStiva* varf = NULL;

	push(&varf, idNodStart);
	vizitate[idNodStart] = 1;

	while (varf != NULL)
	{
		pop(&varf, &idNodStart);
		printf("%d-", idNodStart+1);
		for(int k=0;k<nrNoduri;k++)
			if (mat[idNodStart][k] == 1 && vizitate[k] == 0)
			{
				push(&varf, k);
				vizitate[k] = 1;
			}
	}
}

void parcurgereLatime(int** mat, int* vizitate, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitate[i] = 0;

	nodCoada* prim = NULL, *ultim = NULL;

	put(&prim, &ultim, idNodStart);
	vizitate[idNodStart] = 1;

	while (prim != NULL)
	{
		get(&prim, &ultim, &idNodStart);
		printf("%d-", idNodStart + 1);
		for (int k = 0; k < nrNoduri; k++)
			if (mat[idNodStart][k] == 1 && vizitate[k] == 0)
			{
				put(&prim, &ultim, k);
				vizitate[k] = 1;
			}
	}
}

void main()
{
	FILE* f = fopen("fisier.txt", "r");

	int nrNoduri;
	fscanf(f, "%d", &nrNoduri);

	int** mat = (int**)malloc(nrNoduri * sizeof(int*));
	for (int i = 0; i < nrNoduri; i++)
		mat[i] = (int*)malloc(nrNoduri * sizeof(int));

	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			mat[i][j] = 0;

	int nrArce, idNodStart, idNodStop;
	fscanf(f, "%d", &nrArce);
	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &idNodStart);
		fscanf(f, "%d", &idNodStop);
		if (idNodStart <= nrNoduri && idNodStop <= nrNoduri)
		{
			mat[idNodStart - 1][idNodStop - 1] = 1;
			mat[idNodStop - 1][idNodStart - 1] = 1;
		}
	}

	fclose(f);

	int* vizitate = (int*)malloc(nrNoduri * sizeof(int));

	printf("Nod de pornire: ");
	scanf("%d", &idNodStart);
	printf("Parcurgere in adancime de la nodul %d\n", idNodStart+1);
	parcurgereAdancime(mat, vizitate, nrNoduri, idNodStart);

	printf("\nParcurgere in latime de la nodul %d\n", idNodStart + 1);
	parcurgereLatime(mat, vizitate, nrNoduri, idNodStart);
}

