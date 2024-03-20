#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int isbn;
	char* titlu;
	float pret;
} carte;

typedef struct
{
	carte inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

void inserareLS(nodLS** capLS, carte c)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.isbn = c.isbn;
	nou->inf.titlu = (char*)malloc((strlen(c.titlu) + 1) *
		sizeof(char));
	strcpy(nou->inf.titlu, c.titlu);
	nou->inf.pret = c.pret;
	nou->next = NULL;
	if (*capLS == NULL)
		*capLS = nou;
	else
	{
		nodLS* temp = *capLS;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void inserareLP(nodLP** capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if (*capLP == NULL)
		*capLP = nou;
	else
	{
		nodLP* temp = *capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\nISBN = %d, Titlu = %s, Pret = %5.2f",
			temp->inf.isbn, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp)
	{
		printf("\nSublista %d\n", i);
		traversareLS(temp->inf);
		temp = temp->next;
		i++;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.titlu);
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	int nrCarti;
	char buffer[30];
	nodLP* capLP = NULL;
	nodLS* capLS1 = NULL, * capLS2 = NULL;
	carte c;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrCarti);
	for (int i = 0; i < nrCarti; i++)
	{
		fscanf(f, "%d", &c.isbn);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		fscanf(f, "%f", &c.pret);

		if (c.pret >= 100)
			inserareLS(&capLS1, c);
		else
			inserareLS(&capLS2, c);

		free(c.titlu);
	}
	fclose(f);

	inserareLP(&capLP, capLS1);
	inserareLP(&capLP, capLS2);

	traversareLP(capLP);
	dezalocareLP(capLP);
}