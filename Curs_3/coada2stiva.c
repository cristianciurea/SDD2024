#include <stdio.h>
#include <string.h>
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
	struct nodCoada* next;
} nodCoada;

typedef struct 
{
	student inf;
	struct nodStiva* next;
} nodStiva;

void put(nodCoada** prim, nodCoada** ultim, student s)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(nodCoada));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
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

int get(nodCoada** prim, nodCoada** ultim, student* s)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*s).cod = (*prim)->inf.cod;
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).medie = (*prim)->inf.medie;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.nume);
		free(temp);
		return 0;
	}
	else
		if (*prim == NULL)
		{
			*ultim = NULL;
			return -1;
		}
}

void push(nodStiva** varf, student s)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) *
		sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, student* s)
{
	if (*varf == NULL) return -1;
	else
	{
		(*s).cod = (*varf)->inf.cod;
		(*s).nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) *
			sizeof(char));
		strcpy((*s).nume, (*varf)->inf.nume);
		(*s).medie = (*varf)->inf.medie;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.nume);
		free(temp);
		return 0;
	}
}

void traversare(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f",
			temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void conversieCoadaStiva(nodCoada** prim, nodCoada** ultim, nodStiva** varf)
{
	student s;
	while (get(prim, ultim, &s) == 0)
		push(varf, s);
}

void conversieCoadaVector(nodCoada** prim, nodCoada** ultim, student* vect, int* nr)
{
	student s;
	while (get(prim, ultim, &s) == 0)
	{
		vect[*nr] = s;
		(*nr)++;
	}
}

int main()
{
	nodCoada* prim = NULL, * ultim = NULL;
	student s;
	int n;
	printf("Nr studenti=");
	scanf("%d", &n);
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nCod=");
		scanf("%d", &s.cod);
		printf("\nNume=");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s.medie);
		put(&prim, &ultim, s);
	}
	traversare(prim);

	student extras;
	get(&prim, &ultim, &extras);
	printf("\nStudentul extras are numele %s, codul %d si media %5.2f", extras.nume,
		extras.cod, extras.medie);
	free(extras.nume);

	/*student*vect = (student*)malloc(n*sizeof(student));
	int nr = 0;
	conversieCoadaVector(&prim, &ultim, vect, &nr);
	for(int i=0;i<nr;i++)
		printf("\nCod=%d, Nume=%s, Medie=%5.2f",vect[i].cod, vect[i].nume, vect[i].medie);
	for(int i=0;i<nr;i++)
		free(vect[i].nume);
	free(vect);*/

	nodStiva* varf = NULL;
	conversieCoadaStiva(&prim, &ultim, &varf);
	traversareStiva(varf);

	while (pop(&varf, &extras) == 0)
		free(extras.nume);

	return 0;
}