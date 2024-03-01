#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int *anFabricatie;
	char* marca;
	float consumMediu;
} masina;

typedef struct
{
	masina inf; //informatie utila
	struct nodLS* next;//pointer de legatura
} nodLS;

nodLS* inserareNod(nodLS* cap, masina m)
{
	//alocare memorie nod nou
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	//initializare nod nou
	//nou->inf = m;
	nou->inf.anFabricatie = (int*)malloc(sizeof(int));
	*(nou->inf.anFabricatie) = *(m.anFabricatie);
	nou->inf.marca = (char*)malloc((strlen(m.marca) + 1) *
		sizeof(char));
	strcpy(nou->inf.marca, m.marca);
	nou->inf.consumMediu = m.consumMediu;
	nou->next = NULL;
	//inserare nod
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

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		//prelucrare inf utila
		printf("\nAn fabricatie = %d, Marca = %s, Consum mediu = %5.2f",
			*(temp->inf.anFabricatie), temp->inf.marca, temp->inf.consumMediu);
		temp = temp->next; //deplasare element urmator
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		//stergere nod
		free(temp->inf.marca);
		free(temp->inf.anFabricatie);
		free(temp);
		temp = aux;
	}
}

void salvareMasiniVector(nodLS* cap, masina* vect, 
	int* nrElem, int anFabricatie)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		if (*(temp->inf.anFabricatie) > anFabricatie)
		{
			/*vect[*nrElem].anFabricatie = temp->inf.anFabricatie;
			vect[*nrElem].marca = (char*)malloc((strlen(temp->inf.marca) + 1) 
				* sizeof(char));
			strcpy(vect[*nrElem].marca, temp->inf.marca);
			vect[*nrElem].consumMediu = temp->inf.consumMediu;*/
			vect[*nrElem] = temp->inf;
			(*nrElem)++;
		}
		temp = temp->next;
	}
}

void main()
{
	int nrMasini;
	nodLS* cap = NULL;
	masina m;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		m.anFabricatie = (int*)malloc(sizeof(int));
		fscanf(f, "%d", m.anFabricatie);
		fscanf(f, "%s", buffer);
		m.marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m.marca, buffer);
		fscanf(f, "%f", &m.consumMediu);
		cap = inserareNod(cap, m);
		free(m.marca);
		free(m.anFabricatie);
	}
	fclose(f);

	traversareLista(cap);

	printf("\n------------------\n");
	int nrElem = 0;
	masina* vect = (masina*)malloc(nrMasini * sizeof(masina));
	salvareMasiniVector(cap, vect, &nrElem, 2020);
	for (int i = 0; i < nrElem; i++)
		printf("\nAn fabricatie = %d, Marca = %s, Consum mediu = %5.2f",
			*(vect[i].anFabricatie), vect[i].marca, vect[i].consumMediu);
	/*for (int i = 0; i < nrElem; i++)
		free(vect[i].marca);*/
	free(vect);

	dezalocareLS(cap);
}