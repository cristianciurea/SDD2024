#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int zi, luna, an;
} dataPrimire;

typedef struct
{
	dataPrimire data;
	char* expeditor;
	float dimensiune;
} email;

typedef struct
{
	email inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	email inf;
	struct nodCoada* next;
} nodCoada;

//fct de inserare nod in stiva
void push(nodStiva** varf, email e)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.data.zi = e.data.zi;
	nou->inf.data.luna = e.data.luna;
	nou->inf.data.an = e.data.an;
	nou->inf.expeditor = (char*)malloc((strlen(e.expeditor) + 1) *
		sizeof(char));
	strcpy(nou->inf.expeditor, e.expeditor);
	nou->inf.dimensiune = e.dimensiune;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

//fct de extragere nod din stiva
int pop(nodStiva** varf, email* val)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*val).data.zi = (*varf)->inf.data.zi;
		(*val).data.luna = (*varf)->inf.data.luna;
		(*val).data.an = (*varf)->inf.data.an;
		(*val).expeditor = (char*)malloc((strlen((*varf)->inf.expeditor) + 1) *
			sizeof(char));
		strcpy((*val).expeditor, (*varf)->inf.expeditor);
		(*val).dimensiune = (*varf)->inf.dimensiune;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.expeditor);
		free(temp);
		return 0;
	}
}

//fct de afisare stiva
void afisareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nData: %d/%d/%d, Expeditor: %s, Dimensiune: %5.2f",
			temp->inf.data.zi, temp->inf.data.luna, temp->inf.data.an,
			temp->inf.expeditor, temp->inf.dimensiune);
		temp = temp->next;
	}
}

//fct inserare nod in coada
void put(nodCoada** prim, nodCoada** ultim, email e)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.data.zi = e.data.zi;
	nou->inf.data.luna = e.data.luna;
	nou->inf.data.an = e.data.an;
	nou->inf.expeditor = (char*)malloc((strlen(e.expeditor) + 1) *
		sizeof(char));
	strcpy(nou->inf.expeditor, e.expeditor);
	nou->inf.dimensiune = e.dimensiune;
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

//fct extragere nod din coada
int get(nodCoada** prim, nodCoada** ultim, email* val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*val).data.zi = (*prim)->inf.data.zi;
		(*val).data.luna = (*prim)->inf.data.luna;
		(*val).data.an = (*prim)->inf.data.an;
		(*val).expeditor = (char*)malloc((strlen((*prim)->inf.expeditor) + 1) *
			sizeof(char));
		strcpy((*val).expeditor, (*prim)->inf.expeditor);
		(*val).dimensiune = (*prim)->inf.dimensiune;
		nodStiva* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.expeditor);
		free(temp);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

//fct de afisare coada
void afisareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nData: %d/%d/%d, Expeditor: %s, Dimensiune: %5.2f",
			temp->inf.data.zi, temp->inf.data.luna, temp->inf.data.an,
			temp->inf.expeditor, temp->inf.dimensiune);
		temp = temp->next;
	}
}

void salvareStivaVector(nodStiva* varf, email* vect, int* nr)
{
	email e;
	while (pop(&varf, &e) == 0)
	{
		vect[*nr] = e;
		(*nr)++;
	}
}

void salvareStivaCoada(nodStiva* varf, nodCoada** prim, nodCoada** ultim)
{
	email e;
	while (pop(&varf, &e) == 0)
		put(prim, ultim, e);
}

void determinareEmailuriExpeditor(nodCoada* prim, nodCoada* ultim, email* vect, int* nr, char* expeditor)
{
	email e;
	while (get(&prim, &ultim, &e) == 0)
	{
		if (strcmp(e.expeditor, expeditor) == 0)
		{
			vect[*nr] = e;
			(*nr)++;
		}
	}
}

void main()
{
	int nrEmailuri;
	nodStiva* varf = NULL;
	nodCoada* prim = NULL, * ultim = NULL;
	email e;
	char buffer[30];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrEmailuri);
	for (int i = 0; i < nrEmailuri; i++)
	{
		fscanf(f, "%d", &e.data.zi);
		fscanf(f, "%d", &e.data.luna);
		fscanf(f, "%d", &e.data.an);
		fscanf(f, "%s", buffer);
		e.expeditor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.expeditor, buffer);
		fscanf(f, "%f", &e.dimensiune);
		push(&varf, e);
		//put(&prim, &ultim, e);
		free(e.expeditor);
	}
	fclose(f);

	printf("\n---------stiva-----------\n");
	afisareStiva(varf);

	//printf("\n---------coada-----------\n");
	//afisareCoada(prim);

	//printf("\n---------stiva in vector-----------\n");
	//int nr = 0;
	//email* vect = (email*)malloc(nrEmailuri * sizeof(email));
	//salvareStivaVector(varf, vect, &nr);
	//for(int i=0;i<nr;i++)
	//	printf("\nData: %d/%d/%d, Expeditor: %s, Dimensiune: %5.2f",
	//		vect[i].data.zi, vect[i].data.luna, vect[i].data.an,
	//		vect[i].expeditor, vect[i].dimensiune);

	////dezalocare vector
	//for (int i = 0; i < nr; i++)
	//	free(vect[i].expeditor);
	//free(vect);

	//dezalocare stiva
	/*while (pop(&varf, &e) == 0)
		free(e.expeditor);*/

	printf("\n---------stiva in coada-----------\n");
	salvareStivaCoada(varf, &prim, &ultim);
	afisareCoada(prim);

	printf("\n---------coada in vector-----------\n");
	int nr = 0;
	email* vect = (email*)malloc(nrEmailuri * sizeof(email));
	determinareEmailuriExpeditor(prim, ultim, vect, &nr, "dorel@gmail.com");
	for (int i = 0; i < nr; i++)
			printf("\nData: %d/%d/%d, Expeditor: %s, Dimensiune: %5.2f",
				vect[i].data.zi, vect[i].data.luna, vect[i].data.an,
				vect[i].expeditor, vect[i].dimensiune);
	for (int i = 0; i < nr; i++)
		free(vect[i].expeditor);
	free(vect);

	//dezalocare coada
	/*while (get(&prim, &ultim, &e) == 0)
		free(e.expeditor);*/
}