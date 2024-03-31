#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int memorieRAM;
	char* producator;
	float pret;
} telefon;

typedef struct
{
	telefon** vect;
	int nrElem;
} hashT;

int functieHash(hashT tabela, char* cheie)
{
	return cheie[0] % tabela.nrElem;
}

void inserareHash(hashT tabela, telefon* tel)
{
	int poz = functieHash(tabela, (*tel).producator);
	if (tabela.vect[poz] == NULL)
		tabela.vect[poz] = tel;
	else
	{
		int index = 1;
		while (poz + index < tabela.nrElem)
		{
			if (tabela.vect[poz + index] == NULL)
			{
				poz += index;
				tabela.vect[poz] = tel;
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
			printf("\nMemorie = %d, Producator = %s, Pret = %5.2f",
				tabela.vect[i]->memorieRAM,
				tabela.vect[i]->producator,
				tabela.vect[i]->pret);
		}
}

void dezalocareHash(hashT tabela)
{
	for(int i=0;i<tabela.nrElem;i++)
		if (tabela.vect[i] != NULL)
		{
			free(tabela.vect[i]->producator);
			free(tabela.vect[i]);
		}
	free(tabela.vect);
}

void salvareTelefoanePret(hashT tabela, telefon* vect, int* nr, float pretMin, float pretMax)
{
	for(int i=0;i<tabela.nrElem;i++)
		if (tabela.vect[i] != NULL)
		{
			if (tabela.vect[i]->pret >= pretMin && 
				tabela.vect[i]->pret <= pretMax)
			{
				vect[*nr].memorieRAM = tabela.vect[i]->memorieRAM;
				vect[*nr].producator = (char*)malloc((strlen(tabela.vect[i]->producator) + 1) *
					sizeof(char));
				strcpy(vect[*nr].producator, tabela.vect[i]->producator);
				vect[*nr].pret = tabela.vect[i]->pret;
				(*nr)++;
			}
		}
}

void main()
{
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (telefon**)malloc(tabela.nrElem *
		sizeof(telefon*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	FILE* f = fopen("fisier.txt", "r");

	char buffer[20];
	telefon* tel;
	int nrTel;
	fscanf(f, "%d", &nrTel);
	for (int i = 0; i < nrTel; i++)
	{
		tel = (telefon*)malloc(sizeof(telefon));
		fscanf(f, "%d", &tel->memorieRAM);
		fscanf(f, "%s", buffer);
		tel->producator = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(tel->producator, buffer);
		fscanf(f, "%f", &tel->pret);

		inserareHash(tabela, tel);
		/*free(tel->producator);
		free(tel);*/
	}

	fclose(f);

	traversareHash(tabela);

	printf("\n-----------------\n");

	telefon* vectTel = (telefon*)malloc(nrTel * sizeof(telefon));
	int nr = 0;
	salvareTelefoanePret(tabela, vectTel, &nr, 2000, 4000);
	for (int i = 0; i < nr; i++)
		printf("\nMemorie = %d, Producator = %s, Pret = %5.2f",
			vectTel[i].memorieRAM, vectTel[i].producator,
			vectTel[i].pret);
	for (int i = 0; i < nr; i++)
		free(vectTel[i].producator);
	free(vectTel);

	dezalocareHash(tabela);
}