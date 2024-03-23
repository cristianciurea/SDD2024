#include<stdio.h>
#include<malloc.h>

typedef struct
{
	char* numeAngajat;
	char* departament;
	float salariu;
	char* functie;
} Angajat;

typedef struct
{
	Angajat inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

typedef struct
{
	struct nodLS** vect;
	int nrElem;
} hashT;

int functieHash(char cheie[20], hashT tabela)
{
	return cheie[0] % tabela.nrElem;
}

void inserareLS(nodLS** capLS, Angajat a)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.numeAngajat = (char*)malloc((strlen(a.numeAngajat) + 1) *
		sizeof(char));
	strcpy(nou->inf.numeAngajat, a.numeAngajat);
	nou->inf.departament = (char*)malloc((strlen(a.departament) + 1) *
		sizeof(char));
	strcpy(nou->inf.departament, a.departament);
	nou->inf.salariu = a.salariu;
	nou->inf.functie = (char*)malloc((strlen(a.functie) + 1) *
		sizeof(char));
	strcpy(nou->inf.functie, a.functie);
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

void inserareHash(hashT tabela, Angajat a)
{
	int poz = functieHash(a.numeAngajat, tabela);
	inserareLS(&tabela.vect[poz], a);
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\nNume = %s, Departament = %s, Salariu = %5.2f, Functie = %s",
			temp->inf.numeAngajat, temp->inf.departament,
			temp->inf.salariu, temp->inf.functie);
		temp = temp->next;
	}
}

void traversareHash(hashT tabela)
{
	for(int i=0;i<tabela.nrElem;i++)
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitie: %d", i);
			traversareLS(tabela.vect[i]);
		}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* aux = temp->next;
		free(temp->inf.numeAngajat);
		free(temp->inf.departament);
		free(temp->inf.functie);
		free(temp);
		temp = aux;
	}
}

void dezalocareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
			dezalocareLS(tabela.vect[i]);
	free(tabela.vect);
}

void determinareAngajatiFunctie(hashT tabela, char* functie, int* nr)
{
	for(int i=0;i<tabela.nrElem;i++)
		if (tabela.vect[i] != NULL)
		{
			nodLS* temp = tabela.vect[i];
			while (temp)
			{
				if (strcmp(temp->inf.functie, functie) == 0)
					(*nr)++;
				temp = temp->next;
			}
		}
}

void salvareAngajatiFunctie(hashT tabela, Angajat *vect, char* functie, int* nr)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
		{
			nodLS* temp = tabela.vect[i];
			while (temp)
			{
				if (strcmp(temp->inf.functie, functie) == 0)
				{
					vect[*nr] = temp->inf;
					(*nr)++;
				}
				temp = temp->next;
			}
		}
}

void main()
{
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	Angajat a;
	char buffer[30];
	int nrAngajati;

	FILE* f = fopen("angajati.txt", "r");
	fscanf(f, "%d", &nrAngajati);
	for (int i = 0; i < nrAngajati; i++)
	{
		fscanf(f, "%s", buffer);
		a.numeAngajat = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.numeAngajat, buffer);
		fscanf(f, "%s", buffer);
		a.departament = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.departament, buffer);
		fscanf(f, "%f", &a.salariu);
		fscanf(f, "%s", buffer);
		a.functie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(a.functie, buffer);

		inserareHash(tabela, a);

		free(a.numeAngajat);
		free(a.departament);
		free(a.functie);
	}
	fclose(f);

	traversareHash(tabela);

	printf("\n---------------------\n");

	int nr = 0;
	determinareAngajatiFunctie(tabela, "Programator", &nr);
	printf("Nr. angajati functie = %d", nr);

	printf("\n---------------------\n");
	Angajat* vect = (Angajat*)malloc(nrAngajati * sizeof(Angajat));
	nr = 0;
	salvareAngajatiFunctie(tabela, vect, "Tester", &nr);
	for (int i = 0; i < nr; i++)
		printf("\nNume = %s, Departament = %s, Salariu = %5.2f, Functie = %s",
			vect[i].numeAngajat, vect[i].departament,
			vect[i].salariu, vect[i].functie);
	free(vect);

	dezalocareHash(tabela);
}