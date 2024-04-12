#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct 
{
	int cod;
	char* nume;
	float medie;
} student;

typedef struct 
{
	int BF;
	student inf;
	struct nodarb* left, * right;
} nodarb;

nodarb* creare(student s, nodarb* st, nodarb* dr)
{
	nodarb* nou = (nodarb*)malloc(sizeof(nodarb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodarb* inserare(student s, nodarb* rad)
{
	nodarb* aux = rad;
	if (rad == NULL)
	{
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (1)
		{
			if (s.cod < aux->inf.cod)
				if (aux->left != NULL)
					aux = aux->left;
				else
				{
					aux->left = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->right != NULL)
						aux = aux->right;
					else
					{
						aux->right = creare(s, NULL, NULL);
						return rad;
					}
				else
					return rad;
		}
}

void preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void inordine(nodarb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		inordine(rad->right);
	}
}

void postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
	}
}

void dezalocare(nodarb* rad)
{
	if (rad != NULL)
	{
		nodarb* st = rad->left;
		nodarb* dr = rad->right;
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

//nodarb* cautare(nodarb* rad, int cheie)
//{
//	if (rad != NULL)
//	{
//		if (cheie == rad->inf.cod)
//			return rad;
//		else
//			if (cheie < rad->inf.cod)
//				return cautare(rad->left, cheie);
//			else
//				return cautare(rad->right, cheie);
//	}
//	else
//		return NULL;
//}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int nrNiveluri(nodarb* rad)
{
	if (rad != NULL)
		return 1 + maxim(nrNiveluri(rad->left), nrNiveluri(rad->right));
	else
		return 0;
}

void conversieArboreVector(nodarb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		/*vect[*nr] = rad->inf;
		(*nr)++;
		conversieArboreVector(rad->left, vect, nr);
		conversieArboreVector(rad->right, vect, nr);*/

		vect[*nr].cod = rad->inf.cod;
		vect[*nr].nume = (char*)malloc((strlen(rad->inf.nume) + 1) * sizeof(char));
		strcpy(vect[*nr].nume, rad->inf.nume);
		vect[*nr].medie = rad->inf.medie;
		(*nr)++;

		nodarb* st = rad->left;
		nodarb* dr = rad->right;
		free(rad->inf.nume);
		free(rad);
		conversieArboreVector(st, vect, nr);
		conversieArboreVector(dr, vect, nr);
	}
}

nodarb* stergeRad(nodarb* rad)
{
	nodarb* aux = rad;
	if (aux->left != NULL)
	{
		rad = aux->left;
		if (aux->right != NULL)
		{
			nodarb* temp = aux->left;
			while (temp->right)
				temp = temp->right;
			temp->right = aux->right;
		}
	}
	else
		if (aux->right != NULL)
			rad = aux->right;
		else
			rad = NULL;
	free(aux->inf.nume);
	free(aux);
	return rad;
}

nodarb* stergeNod(nodarb* rad, int cheie)
{
	if (rad == NULL)
		return NULL;
	else
		if (rad->inf.cod == cheie)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
		{
			nodarb* aux = rad;
			while (1)
			{
				if (cheie < aux->inf.cod)
					if (aux->left == NULL)
						break;
					else
					{
						nodarb* stanga = aux->left;
						if (stanga->inf.cod == cheie)
							stanga = stergeRad(stanga);
						else
							aux = stanga;
					}
				else
					if (cheie > aux->inf.cod)
						if (aux->right == NULL)
							break;
						else
						{
							nodarb* dreapta = aux->right;
							if (dreapta->inf.cod == cheie)
								dreapta = stergeRad(dreapta);
							else
								aux = dreapta;
						}
			}
			return rad;
		}
}

void calculBF(nodarb* rad)
{
	if (rad != NULL)
	{
		rad->BF = nrNiveluri(rad->right) - nrNiveluri(rad->left);
		calculBF(rad->left);
		calculBF(rad->right);
	}
}

nodarb* rotatie_dreapta(nodarb* rad)
{
	printf("\nRotatie dreapta\n");
	nodarb* nod1 = rad->left;
	rad->left = nod1->right;
	nod1->right = rad;
	rad = nod1;
	return rad;
}

nodarb* rotatie_stanga(nodarb* rad)
{
	printf("\nRotatie stanga\n");
	nodarb* nod1 = rad->right;
	rad->right = nod1->left;
	nod1->left = rad;
	rad = nod1;
	return rad;
}

nodarb* rotatie_dreapta_stanga(nodarb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodarb* nod1 = rad->right;
	nodarb* nod2 = nod1->left;
	nod1->left = nod2->right;
	nod2->right = nod1;
	rad->right = nod2->left;
	nod2->left = rad;
	rad = nod2;
	return rad;
}

nodarb* rotatie_stanga_dreapta(nodarb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodarb* nod1 = rad->left;
	nodarb* nod2 = nod1->right;
	nod1->right = nod2->left;
	nod2->left = nod1;
	rad->left = nod2->right;
	nod2->right = rad;
	rad = nod2;
	return rad;
}

nodarb* reechilibrare(nodarb* rad)
{
	calculBF(rad);
	nodarb* stanga = rad->left;
	nodarb* dreapta = rad->right;
	if (rad->BF <= -2 && stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF >= 2 && dreapta->BF >= 1)
		{
			rad = rotatie_stanga(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && dreapta->BF <= -1)
			{
				rad = rotatie_dreapta_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF <= -2 && stanga->BF >= 1)
				{
					rad = rotatie_stanga_dreapta(rad);
					calculBF(rad);
				}
	return rad;
}

//functia de afisare noduri de pe un anumit nivel
void afisareNivel(nodarb* rad, int level)
{
	if (rad == NULL)
		return;
	if (level == 1)
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
	else if (level > 1)
	{
		afisareNivel(rad->left, level - 1);
		afisareNivel(rad->right, level - 1);
	}
}

//functie pentru traversare arbore pe niveluri
void traversareNiveluri(nodarb* rad)
{
	int h = nrNiveluri(rad);
	for (int i = 1; i <= h; i++)
		afisareNivel(rad, i);
}

// functia care valideaza daca exista drum de la radacina la un anumit nod
int existaDrum(nodarb* rad, int* vector, int* nr, int nod)
{
	if (!rad)
		return 0;

	//se adauga nodul curent in vector
	vector[*nr] = rad->inf.cod;
	(*nr)++;

	//daca nodul primit ca parametru este egal cu radacina returnam true
	if (rad->inf.cod == nod)
		return 1;

	//altfel verificam daca nodul cautat se afla in subarbore stang sau drept
	if (existaDrum(rad->left, vector, nr, nod) || existaDrum(rad->right, vector, nr, nod))
		return 1;

	//daca nu se afla in subarbore stang sau drept se elimina din vector si returnam false
	(*nr)--;
	return 0;
}

// functie care afiseaza drumul de la radacina la un anumit nod
void afiseazaDrum(nodarb* rad, int* vector, int nr, int nod)
{
	if (existaDrum(rad, vector, &nr, nod))
	{
		for (int i = 0; i < nr; i++)
			printf("%d->", vector[i]);
	}
	else
		printf("nu exista drum\n");
}

void spargereAVLdoiArbori(nodarb* rad, nodarb** rad1, nodarb** rad2, int cod)
{
	if (rad != NULL)
	{
		if (rad->inf.cod <= cod)
		{
			*rad1 = inserare(rad->inf, *rad1);
			*rad1 = reechilibrare(*rad1);
		}
		else
		{
			*rad2 = inserare(rad->inf, *rad2);
			*rad2 = reechilibrare(*rad2);
		}
		spargereAVLdoiArbori(rad->left, rad1, rad2, cod);
		spargereAVLdoiArbori(rad->right, rad1, rad2, cod);
	}
}

void main()
{
	int n;
	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &n);

	nodarb* rad = NULL;
	student s;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserare(s, rad);

		rad = reechilibrare(rad);
	}
	fclose(f);

	//calculBF(rad);

	/*preordine(rad);
	printf("\n------------------------\n");
	inordine(rad);
	printf("\n------------------------\n");
	postordine(rad);*/

	/*nodarb *nodCautat = cautare(rad, 6);
	if(nodCautat!=NULL)
		printf("\nStudentul cautat se cheama %s", nodCautat->inf.nume);
	else
		printf("\nNu exista!");*/

	inordine(rad);
	printf("\n------------------------\n");
	inordine(rad->left);
	printf("\n------------------------\n");
	inordine(rad->right);
	printf("\n------------------------\n");

	printf("\nInaltime arbore este %d", nrNiveluri(rad));
	printf("\nInaltime subarbore stang este %d", nrNiveluri(rad->left));
	printf("\nInaltime subarbore drept este %d", nrNiveluri(rad->right));

	//printf("\n--------Vector----------------\n");

	/*student *vect = (student*)malloc(n*sizeof(student));
	int nr = 0;
	conversieArboreVector(rad, vect, &nr);
	for(int i=0;i<nr;i++)
		printf("\nCod=%d, Nume=%s, Medie=%5.2f", vect[i].cod, vect[i].nume, vect[i].medie);
	for(int i=0;i<nr;i++)
		free(vect[i].nume);
	free(vect);*/

	/*rad = stergeRad(rad);
	rad  = stergeNod(rad, 5);*/
	//calculBF(rad);
	//inordine(rad);
	//printf("\n------------------------\n");
	//inordine(rad->left);
	//printf("\n------------------------\n");
	//inordine(rad->right);

	/*printf("\n--------dupa stergere----------------\n");
	rad = stergeNod(rad, 9);
	rad = reechilibrare(rad);
	inordine(rad);
	printf("\n------------------------\n");
	inordine(rad->left);
	printf("\n------------------------\n");
	inordine(rad->right);
	printf("\n------------------------\n");

	printf("\nInaltime arbore este %d", nrNiveluri(rad));
	printf("\nInaltime subarbore stang este %d", nrNiveluri(rad->left));
	printf("\nInaltime subarbore drept este %d", nrNiveluri(rad->right));*/

	printf("\nNoduri de pe nivelul 4: \n");
	afisareNivel(rad, 4);

	printf("\nTraversare pe niveluri: \n");
	traversareNiveluri(rad);

	printf("\nDrumul de la radacina la un anumit nod: \n");
	int* vector = (int*)malloc(n*sizeof(int));
	int nr = 0;
	afiseazaDrum(rad, vector, nr, 7);

	//spargere arbore in doi subarbori binari
	nodarb* rad1 = NULL, *rad2 = NULL;
	spargereAVLdoiArbori(rad, &rad1, &rad2, 8);
	printf("\nPrimul subarbore: \n");
	inordine(rad1);
	printf("\nAl doilea subarbore: \n");
	inordine(rad2);

	dezalocare(rad);
}