#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int anFabricatie;
	char* marca;
	float pret;
} masina;

typedef struct
{
	masina** vect;
	int nrElem;
} hashT;

int functieHash(hashT tabela, char* cheie)
{
	return cheie[0] % tabela.nrElem;
}

void inserareHash(hashT tabela, masina* m)
{
	int poz = functieHash(tabela, (*m).marca);
	if (tabela.vect[poz] == NULL)
		tabela.vect[poz] = m;
	else
	{
		int index = 1;
		while (poz + index < tabela.nrElem)
		{
			if (tabela.vect[poz + index] == NULL)
			{
				poz += index;
				tabela.vect[poz] = m;
				break;
			}
			else
				index++;
		}
	}
}

void traversareHash(hashT tabela)
{
	for(int i=0;i<tabela.nrElem;i++)
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitia = %d", i);
			printf("\nAn fabricatie = %d, Marca = %s, Pret = %5.2f",
				tabela.vect[i]->anFabricatie,
				tabela.vect[i]->marca,
				tabela.vect[i]->pret);
		}
}

void dezalocareHash(hashT tabela)
{
	for(int i=0;i<tabela.nrElem;i++)
		if (tabela.vect[i] != NULL)
		{
			free(tabela.vect[i]->marca);
			free(tabela.vect[i]);
		}
	free(tabela.vect);
}

void main()
{
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (masina**)malloc(tabela.nrElem *
		sizeof(masina*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	FILE* f = fopen("fisier.txt", "r");
	char buffer[20];
	masina* m;
	int nrMasini;
	fscanf(f, "%d", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		m = (masina*)malloc(sizeof(masina));
		fscanf(f, "%d", &m->anFabricatie);
		fscanf(f, "%s", buffer);
		m->marca = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(m->marca, buffer);
		fscanf(f, "%f", &m->pret);

		inserareHash(tabela, m);
	}
	fclose(f);

	traversareHash(tabela);
	dezalocareHash(tabela);
}


