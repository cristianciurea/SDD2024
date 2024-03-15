#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int zi, luna, an;
} dataReceptionare;

typedef struct
{
	dataReceptionare data;
	int prioritate;
	char* aplicatie;
	float durata;
} notificare;

typedef struct
{
	notificare inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	notificare inf;
	struct nodCoada* next;
} nodCoada;

//fct de inserare in stiva
void push(nodStiva** varf, notificare notif)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.data.zi = notif.data.zi;
	nou->inf.data.luna = notif.data.luna;
	nou->inf.data.an = notif.data.an;
	nou->inf.prioritate = notif.prioritate;
	nou->inf.aplicatie = (char*)malloc((strlen(notif.aplicatie) + 1) *
		sizeof(char));
	strcpy(nou->inf.aplicatie, notif.aplicatie);
	nou->inf.durata = notif.durata;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf; //inserare la inceput
		*varf = nou;
	}
}

//fct de extragere din stiva
int pop(nodStiva** varf, notificare* val)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*val).data.zi = (*varf)->inf.data.zi;
		(*val).data.luna = (*varf)->inf.data.luna;
		(*val).data.an = (*varf)->inf.data.an;
		(*val).prioritate = (*varf)->inf.prioritate;
		(*val).aplicatie = (char*)malloc((strlen((*varf)->inf.aplicatie) + 1) *
			sizeof(char));
		strcpy((*val).aplicatie, (*varf)->inf.aplicatie);
		(*val).durata = (*varf)->inf.durata;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.aplicatie);
		free(temp);
		return 0;
	}
}

void afisareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nData: %d/%d/%d, Prioritate: %d, Aplicatie: %s, Durata: %5.2f",
			temp->inf.data.zi, temp->inf.data.luna,
			temp->inf.data.an, temp->inf.prioritate,
			temp->inf.aplicatie, temp->inf.durata);
		temp = temp->next;
	}
}

//fct inserare nod in coada
void put(nodCoada** prim, nodCoada** ultim, notificare notif)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.data.zi = notif.data.zi;
	nou->inf.data.luna = notif.data.luna;
	nou->inf.data.an = notif.data.an;
	nou->inf.prioritate = notif.prioritate;
	nou->inf.aplicatie = (char*)malloc((strlen(notif.aplicatie) + 1) *
		sizeof(char));
	strcpy(nou->inf.aplicatie, notif.aplicatie);
	nou->inf.durata = notif.durata;
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

int get(nodCoada** prim, nodCoada** ultim, notificare* val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*val).data.zi = (*prim)->inf.data.zi;
		(*val).data.luna = (*prim)->inf.data.luna;
		(*val).data.an = (*prim)->inf.data.an;
		(*val).prioritate = (*prim)->inf.prioritate;
		(*val).aplicatie = (char*)malloc((strlen((*prim)->inf.aplicatie) + 1) *
			sizeof(char));
		strcpy((*val).aplicatie, (*prim)->inf.aplicatie);
		(*val).durata = (*prim)->inf.durata;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.aplicatie);
		free(temp);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void afisareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nData: %d/%d/%d, Prioritate: %d, Aplicatie: %s, Durata: %5.2f",
			temp->inf.data.zi, temp->inf.data.luna,
			temp->inf.data.an, temp->inf.prioritate,
			temp->inf.aplicatie, temp->inf.durata);
		temp = temp->next;
	}
}

void salvareStivaVector(nodStiva* varf, notificare* vect, int* nr)
{
	notificare notif;
	while (pop(&varf, &notif) == 0)
	{
		vect[*nr] = notif;
		(*nr)++;
	}
}

void main()
{
	int nrNotif;
	nodStiva* varf = NULL;
	nodCoada* prim = NULL, * ultim = NULL;
	char buffer[20];
	notificare notif;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrNotif);
	for (int i = 0; i < nrNotif; i++)
	{
		fscanf(f, "%d", &notif.data.zi);
		fscanf(f, "%d", &notif.data.luna);
		fscanf(f, "%d", &notif.data.an);
		fscanf(f, "%d", &notif.prioritate);
		fscanf(f, "%s", buffer);
		notif.aplicatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(notif.aplicatie, buffer);
		fscanf(f, "%f", &notif.durata);
		push(&varf, notif);
		put(&prim, &ultim, notif);
		free(notif.aplicatie);
	}
	fclose(f);

	printf("\n------stiva----------\n");
	afisareStiva(varf);

	printf("\n------coada----------\n");
	afisareCoada(prim);

	//dezalocare stiva
	/*while (pop(&varf, &notif) == 0)
		free(notif.aplicatie);*/

	printf("\n------stiva in vector----------\n");
	notificare* vect = (notificare*)malloc(nrNotif * sizeof(notificare));
	int nr = 0;
	salvareStivaVector(varf, vect, &nr);
	for(int i=0;i<nr;i++)
		printf("\nData: %d/%d/%d, Prioritate: %d, Aplicatie: %s, Durata: %5.2f",
			vect[i].data.zi, vect[i].data.luna,
			vect[i].data.an, vect[i].prioritate,
			vect[i].aplicatie, vect[i].durata);
	for (int i = 0; i < nr; i++)
		free(vect[i].aplicatie);
	free(vect);

	//dezalocare coada
	while (get(&prim, &ultim, &notif) == 0)
		free(notif.aplicatie);
}

