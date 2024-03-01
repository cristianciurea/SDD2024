#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
} produs;

typedef struct 
{
    produs* inf;
	struct nodls* next, * prev;
} nodls;

nodls* inserare(nodls* cap, nodls** coada, produs* p)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf = (produs*)malloc(sizeof(produs));
	nou->inf->cod = (int*)malloc(sizeof(int));
	*(nou->inf->cod) = *(p->cod);
	nou->inf->denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
	strcpy(nou->inf->denumire, p->denumire);
	nou->inf->pret = p->pret;
	nou->inf->cantitate = p->cantitate;
	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL)
	{
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodls* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
	return cap;
}

void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->next;
	}
}

void traversareInvers(nodls* coada)
{
	nodls* temp = coada;
	while (temp != NULL)
	{
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
			*(temp->inf->cod), temp->inf->denumire, temp->inf->pret, temp->inf->cantitate);
		temp = temp->prev;
	}
}

void conversieListaVector(nodls* cap, produs** vect, int* nr)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		//vect[*nr] = temp->inf;
		vect[*nr] = (produs*)malloc(1 * sizeof(produs));
		vect[*nr]->cod = (int*)malloc(1 * sizeof(int));
		*(vect[*nr]->cod) = *(temp->inf->cod);
		vect[*nr]->denumire = (char*)malloc((strlen(temp->inf->denumire) + 1)*sizeof(char));
		strcpy(vect[*nr]->denumire, temp->inf->denumire);
		vect[*nr]->pret = temp->inf->pret;
		vect[*nr]->cantitate = temp->inf->cantitate;
		(*nr)++;
		temp = temp->next;
	}
}

void dezalocare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		nodls* temp2 = temp->next;
		free(temp->inf->denumire);
		free(temp->inf->cod);
		free(temp->inf);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	int n;
	printf("Nr produse=");
	scanf("%d", &n);
	nodls* cap = NULL, * coada = NULL;
	produs* p;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		p = (produs*)malloc(sizeof(produs));
		p->cod = (int*)malloc(sizeof(int));
		printf("Cod=");
		scanf("%d", p->cod);
		printf("Denumire=");
		scanf("%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		printf("Pret=");
		scanf("%f", &p->pret);
		printf("Cantitate=");
		scanf("%f", &p->cantitate);
		cap = inserare(cap, &coada, p);
		free(p->denumire);
		free(p->cod);
		free(p);
	}
	traversare(cap);
	traversareInvers(coada);
	
	printf("\n-------conversie-----------");
	produs** vect = (produs**)malloc(n * sizeof(produs*));
	int nr = 0;
	conversieListaVector(cap, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
			*(vect[i]->cod), vect[i]->denumire, vect[i]->pret, vect[i]->cantitate);
	for (int i = 0; i < nr; i++)
	{
		free(vect[i]->denumire);
		free(vect[i]->cod);
		free(vect[i]);
	}
	free(vect);

	dezalocare(cap);
}