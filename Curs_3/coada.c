#include <stdio.h>
#include <malloc.h>

typedef struct 
{
	int varsta;
	char* nume;
	float medie;
	//int nrNote;
	//int *vectNote;
} student;

typedef struct 
{
	student inf;
	struct nodCoada* next;
} nodCoada;

void put(nodCoada** prim, nodCoada** ultim, student s)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.varsta = s.varsta;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
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
		(*s).varsta = (*prim)->inf.varsta;
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).medie = (*prim)->inf.medie;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux->inf.nume);
		free(aux);
		return 0;
	}
	else
		if (*prim == NULL) {
			*ultim = NULL;
			return -1;
		}
}

void traversare(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		printf("\nVarsta = %d, Nume = %s, Medie = %5.2f", temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
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

void main()
{
	int n;
	printf("Nr. studenti=");
	scanf("%d", &n);

	nodCoada* prim = NULL, * ultim = NULL;
	student s;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nVarsta=");
		scanf("%d", &s.varsta);
		printf("\nNume=");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s.medie);
		put(&prim, &ultim, s);
	}
	traversare(prim);

	student s1;
	get(&prim, &ultim, &s1);
	printf("\nStudentul extras se numeste %s ", s1.nume);
	free(s1.nume);

	/*while (get(&prim, &ultim, &s1)==0)
		free(s1.nume);*/

	printf("\n----vector---------\n");

	student* vect = (student*)malloc(n * sizeof(student));
	int nr = 0;
	conversieCoadaVector(&prim, &ultim, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nVarsta = %d, Nume = %s, Medie = %5.2f", vect[i].varsta, vect[i].nume, vect[i].medie);
	for (int i = 0; i < nr; i++)
		free(vect[i].nume);
	free(vect);
}