#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int* anFabricatie;
	char* marca;
	float consumMediu;
} masina;

typedef struct
{
	masina inf; //informatie utila
	struct nodLS* next, *prev;//pointer de legatura
} nodLS;

nodLS* inserareNod(nodLS* cap, nodLS** coada, masina m)
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
	/*nou->next = NULL;
	nou->prev = NULL;*/
	//inserare nod
	if (cap == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
		(*coada)->next = cap;
		cap->prev = *coada;
	}
	return cap;
}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		//prelucrare inf utila
		printf("\nAn fabricatie = %d, Marca = %s, Consum mediu = %5.2f",
			*(temp->inf.anFabricatie), temp->inf.marca, temp->inf.consumMediu);
		temp = temp->next; //deplasare element urmator
	}
	printf("\nAn fabricatie = %d, Marca = %s, Consum mediu = %5.2f",
		*(temp->inf.anFabricatie), temp->inf.marca, temp->inf.consumMediu);
}

void traversareInversaLista(nodLS* coada)
{
	nodLS* temp = coada;
	while (temp->prev != coada)
	{
		//prelucrare inf utila
		printf("\nAn fabricatie = %d, Marca = %s, Consum mediu = %5.2f",
			*(temp->inf.anFabricatie), temp->inf.marca, temp->inf.consumMediu);
		temp = temp->prev; //deplasare element anterior
	}
	printf("\nAn fabricatie = %d, Marca = %s, Consum mediu = %5.2f",
		*(temp->inf.anFabricatie), temp->inf.marca, temp->inf.consumMediu);
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		nodLS* aux = temp->next;
		//stergere nod
		free(temp->inf.marca);
		free(temp->inf.anFabricatie);
		free(temp);
		temp = aux;
	}
	free(temp->inf.marca);
	free(temp->inf.anFabricatie);
	free(temp);
}

void salvareMasiniVector(nodLS* cap, masina* vect,
	int* nrElem, int anFabricatie)
{
	nodLS* temp = cap;
	while (temp->next != cap)
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
}

void stergeMasinaMarca(nodLS** cap, nodLS** coada, char* marca)
{
	//cazul cand e primul nod
	if (strcmp((*cap)->inf.marca, marca) == 0)
	{
		nodLS* temp = *cap;
		*cap = (*cap)->next;
		if (*cap != NULL)
			(*cap)->prev = NULL;
		free(temp->inf.marca);
		free(temp->inf.anFabricatie);
		free(temp);
		return;
	}else
		//cazul cand e ultimul nod
		if (strcmp((*coada)->inf.marca, marca) == 0)
		{
			nodLS* temp = *coada;
			*coada = (*coada)->prev;
			if (*coada != NULL)
				(*coada)->next = NULL;
			free(temp->inf.marca);
			free(temp->inf.anFabricatie);
			free(temp);
			return;
		}
		else
			//nodul e la jumatatea listei
		{
			nodLS* temp = *cap;
			while (temp != NULL)
			{
				if (strcmp(temp->inf.marca, marca) == 0)
				{
					nodLS* anterior = temp->prev;
					nodLS* urmator = temp->next;
					anterior->next = urmator;
					urmator->prev = anterior;
					free(temp->inf.marca);
					free(temp->inf.anFabricatie);
					free(temp);
					return;
				}
				else
					temp = temp->next;
			}
		}
}

void main()
{
	int nrMasini;
	nodLS* cap = NULL, *coada = NULL;
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
		cap = inserareNod(cap, &coada, m);
		free(m.marca);
		free(m.anFabricatie);
	}
	fclose(f);

	traversareLista(cap);

	printf("\n------------------\n");

	traversareInversaLista(coada);

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


	printf("\n------------------\n");

	//stergeMasinaMarca(&cap, &coada, "Hyundai");
	traversareLista(cap);

	printf("\n------------------\n");

	traversareInversaLista(coada);


	dezalocareLS(cap);
}