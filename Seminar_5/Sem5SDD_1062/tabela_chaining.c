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
	struct nodLS** vect;
	int nrElem;
} hashT;

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.nrElem;
}

int functieHash2(char titlu[20], hashT tabela)
{
	return titlu[0] % tabela.nrElem;
}

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

void inserareHash(hashT tabela, carte c)
{
	//int poz = functieHash(c.isbn, tabela);
	int poz = functieHash2(c.titlu, tabela);
	inserareLS(&tabela.vect[poz], c);
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

void traversareHash(hashT tabela)
{
	for(int i=0;i<tabela.nrElem;i++)
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitia: %d", i);
			traversareLS(tabela.vect[i]);
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

void dezalocareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
			dezalocareLS(tabela.vect[i]);
	free(tabela.vect);
}

void main()
{
	hashT tabela;
	tabela.nrElem = 23;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	int nrCarti;
	char buffer[30];
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

		inserareHash(tabela, c);
		free(c.titlu);
	}
	fclose(f);

	traversareHash(tabela);
	dezalocareHash(tabela);
}