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
	struct nodarb* left, * right;
} nodarb;

typedef struct 
{
	student inf;
	struct nodlista* next, * prev;
} nodlista;

typedef struct 
{
	student inf;
	struct nodstiva* next;
} nodstiva;

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
				if (aux->left != NULL) aux = aux->left;
				else
				{
					aux->left = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->right != NULL) aux = aux->right;
					else
					{
						aux->right = creare(s, NULL, NULL);
						return rad;
					}
				else
				{
					printf("\nNod existent!");
					return rad;
				}
		}
}

void inordine(nodarb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nStudentul %s are codul %d si media %5.2f", rad->inf.nume, rad->inf.cod, rad->inf.medie);
		inordine(rad->right);
	}
}

void preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		printf("\nStudentul %s are codul %d si media %5.2f", rad->inf.nume, rad->inf.cod, rad->inf.medie);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nStudentul %s are codul %d si media %5.2f", rad->inf.nume, rad->inf.cod, rad->inf.medie);
	}
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b) max = b;
	return max;
}

int nr_niveluri(nodarb* rad)
{
	if (rad != NULL)
		return 1 + maxim(nr_niveluri(rad->left),
			nr_niveluri(rad->right));
	else return 0;
}

nodarb* cautare(nodarb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.cod) return rad;
		else if (cheie < rad->inf.cod)
			return cautare(rad->left, cheie);
		else return cautare(rad->right, cheie);
	}
	else return NULL;
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
			while (temp->right != NULL)
				temp = temp->right;
			temp->right = aux->right;
		}
	}
	else
		if (aux->right != NULL)
			rad = aux->right;
		else rad = NULL;
	free(aux->inf.nume);
	free(aux);
	return rad;
}

nodarb* stergeNod(nodarb* rad, int cheie)
{
	if (rad == NULL) return NULL;
	else
		if (rad->inf.cod == cheie)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
		{
			nodarb* aux = rad;
			nodarb* auxS = aux->left;
			nodarb* auxD = aux->right;
			while (1)
			{
				if (cheie < aux->inf.cod)
					if (aux->left == NULL) break;
					else if (auxS->inf.cod == cheie)
						aux->left = stergeRad(aux->left);
					else
						aux = aux->left;
				else
					if (cheie > aux->inf.cod)
						if (aux->right == NULL) break;
						else if (auxD->inf.cod == cheie)
							aux->right = stergeRad(aux->right);
						else aux = aux->right;
			}
			return rad;
		}
}

void dezalocare(nodarb* rad)
{
	if (rad != NULL)
	{
		nodarb* st = rad->left;
		nodarb* dr = rad->right;
		printf("\nAm dezalocat %d", rad->inf.cod);
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

nodlista* inserareLista(nodlista* cap, student s)
{
	nodlista* nou = (nodlista*)malloc(sizeof(nodlista));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodlista* temp = cap;
		while (temp->next) temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
	}
	return cap;
}

void conversieArboreLista(nodarb* rad, nodlista** cap)
{
	if (rad != NULL)
	{
		*cap = inserareLista(*cap, rad->inf);
		conversieArboreLista(rad->left, cap);
		conversieArboreLista(rad->right, cap);
	}
}

void afisare_lista(nodlista* cap)
{
	nodlista* aux = cap;
	while (aux != NULL)
	{
		printf("\nStudentul %s are codul %d si media %5.2f", aux->inf.nume, aux->inf.cod, aux->inf.medie);
		aux = aux->next;
	}
}

void conversie_arbore_vector(nodarb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		vect[*nr] = rad->inf;
		(*nr)++;
		conversie_arbore_vector(rad->left, vect, nr);
		conversie_arbore_vector(rad->right, vect, nr);
	}
}

void inserare_stiva(nodstiva** varf, student s)
{
	nodstiva* nou = (nodstiva*)malloc(sizeof(nodstiva));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	if (*varf == NULL)
	{
		nou->next = NULL;
		*varf = nou;
	}
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

void conversie_arbore_stiva(nodarb* rad, nodstiva** varf)
{
	if (rad != NULL)
	{
		inserare_stiva(varf, rad->inf);
		conversie_arbore_stiva(rad->left, varf);
		conversie_arbore_stiva(rad->right, varf);
	}
}

void afisare_stiva(nodstiva* varf)
{
	nodstiva* aux = varf;
	while (aux != NULL)
	{
		printf("\nStudentul %s are codul %d si media %5.2f", aux->inf.nume, aux->inf.cod, aux->inf.medie);
		aux = aux->next;
	}
}

void main()
{
	int n;

	FILE* f = fopen("fisier.txt", "r");

	//printf("Nr. studenti: ");
	fscanf(f, "%d", &n);

	nodarb* rad = NULL;
	student s;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		//printf("\nCod: ");
		fscanf(f, "%d", &s.cod);
		//printf("\nNume: ");
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		//printf("\nMedie: ");
		fscanf(f, "%f", &s.medie);

		rad = inserare(s, rad);
	}
	fclose(f);

	printf("\n-------------inordine");
	inordine(rad);
	printf("\n-------------preordine");
	preordine(rad);
	printf("\n-------------postordine");
	postordine(rad);

	printf("\nArborele are %d niveluri", nr_niveluri(rad));

	nodarb* nodCautat = cautare(rad, 7);
	printf("\nStudentul cu cheia 7 se numeste %s", nodCautat->inf.nume);

	//rad = stergeRad(rad);
	//rad = stergeNod(rad, 7);
	//inordine(rad);

	//dezalocare(rad);

	nodlista* cap = NULL;
	conversieArboreLista(rad, &cap);
	afisare_lista(cap);

	printf("\n-------------vector------");
	student* vector = (student*)malloc(n * sizeof(student));
	n = 0;
	conversie_arbore_vector(rad, vector, &n);
	for (int i = 0; i < n; i++)
		printf("\nStudentul %s are codul %d si media %5.2f", vector[i].nume, vector[i].cod, vector[i].medie);

	printf("\n-------------stiva------");
	nodstiva* varf = NULL;
	conversie_arbore_stiva(rad, &varf);
	afisare_stiva(varf);
}