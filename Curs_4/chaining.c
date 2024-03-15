#include <stdio.h>
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
	struct nodLS* next;
} nodLS;

typedef struct 
{
	struct nodLS** vect;
	int size;
} hashT;

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.size;
}

int inserare(hashT tabela, student s)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(s.cod, tabela);
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->inf.cod = s.cod;
		nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
		strcpy(nou->inf.nume, s.nume);
		nou->inf.medie = s.medie;
		nou->next = NULL;
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next)
				temp = temp->next;
			temp->next = nou;
		}
	}
	return pozitie;
}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		printf("\nCod: %d, nume: %s, medie: %5.2f",
			temp->inf.cod, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie: %d", i);
				traversareLista(tabela.vect[i]);
			}
		}
	}
}

void traversare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie=%d", i);
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					printf("\nCod=%d, Nume=%s, Medie=%5.2f",
						temp->inf.cod, temp->inf.nume, temp->inf.medie);
					temp = temp->next;
				}
			}
	}
}

void dezalocareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				dezalocareLista(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}

void dezalocare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					nodLS* temp2 = temp->next;
					free(temp->inf.nume);
					free(temp);
					temp = temp2;
				}
			}
		free(tabela.vect);
	}
}

void stergeNod(nodLS* nod)
{
	free(nod->inf.nume);
	free(nod);
}

int stergere(hashT tabela, int cod)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(cod, tabela);
		nodLS* temp = tabela.vect[pozitie];
		if (temp == NULL)
			return -1;
		else
		{
			if (temp->inf.cod == cod)
			{
				if (temp->next == NULL)
				{
					stergeNod(temp);
					tabela.vect[pozitie] = NULL;
				}
				else
				{
					nodLS* temp2 = temp;
					tabela.vect[pozitie] = temp->next;
					stergeNod(temp2);
				}
			}
			else
			{
				while (temp->next != NULL) {
					nodLS* temp2 = temp->next;
					if (temp2->inf.cod != cod)
						temp = temp->next;
					else
						break;
				}
				nodLS* p = temp->next;
				if (p != NULL)
				{
					if (p->next != NULL)
					{
						temp->next = p->next;
						stergeNod(p);
					}
					else
					{
						temp->next = NULL;
						stergeNod(p);
					}
				}
				else
					return -1;
			}
		}
	}
	return pozitie;
}

void main()
{
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (nodLS**)malloc(tabela.size * sizeof(nodLS*));
	for (int i = 0; i < tabela.size; i++)
		tabela.vect[i] = NULL;

	int n;
	/*printf("Nr. studenti=");
	scanf("%d", &n);
	student s;
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

		inserare(tabela, s);
	}*/

	FILE*f = fopen("fisier.txt", "r");
	student s;
	char buffer[20];
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		inserare(tabela, s);
	}
	fclose(f);

	traversare(tabela);

	stergere(tabela, 305);

	printf("\n------dupa stergere-------");

	traversare(tabela);

	dezalocare(tabela);
}