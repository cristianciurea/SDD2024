#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int cod;
	char* nume;
	int varsta;
	float venit;
} persoana;

typedef struct
{
	persoana inf;
	struct nodArb* stanga, * dreapta;
} nodArb;

nodArb* creareNod(persoana p, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.cod = p.cod;
	nou->inf.nume = (char*)malloc((strlen(p.nume) + 1) *
		sizeof(char));
	strcpy(nou->inf.nume, p.nume);
	nou->inf.varsta = p.varsta;
	nou->inf.venit = p.venit;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(nodArb* rad, persoana p)
{
	if (rad != NULL)
	{
		if (p.cod < rad->inf.cod)
		{
			rad->stanga = inserareNod(rad->stanga, p);
			return rad;
		}
		else
			if (p.cod > rad->inf.cod)
			{
				rad->dreapta = inserareNod(rad->dreapta, p);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(p, NULL, NULL);
}

void preordine(nodArb* rad)//RSD
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Nume=%s, Varsta=%d, Venit=%5.2f",
			rad->inf.cod, rad->inf.nume, rad->inf.varsta,
			rad->inf.venit);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void inordine(nodArb* rad)//SRD
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nCod=%d, Nume=%s, Varsta=%d, Venit=%5.2f",
			rad->inf.cod, rad->inf.nume, rad->inf.varsta,
			rad->inf.venit);
		inordine(rad->dreapta);
	}
}

void postordine(nodArb* rad)//SDR
{
	if (rad != NULL)
	{
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nCod=%d, Nume=%s, Varsta=%d, Venit=%5.2f",
			rad->inf.cod, rad->inf.nume, rad->inf.varsta,
			rad->inf.venit);
	}
}

void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{
		/*nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);*/

		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->inf.nume);
		free(rad);
	}
}

void nrPersVenitPrag(nodArb* rad, int* nr, float venitPrag)
{
	if (rad != NULL)
	{
		if (rad->inf.venit >= venitPrag)
			(*nr)++;
		nrPersVenitPrag(rad->stanga, nr, venitPrag);
		nrPersVenitPrag(rad->dreapta, nr, venitPrag);
	}
}

void sumaVenituriPersoane(nodArb* rad, float* suma)
{
	if (rad != NULL)
	{
		*suma += rad->inf.venit;
		sumaVenituriPersoane(rad->stanga, suma);
		sumaVenituriPersoane(rad->dreapta, suma);
	}
}

void salvareVectorNoduriFrunza(nodArb* rad, persoana* vect, int* nr, float venitPrag)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			if (rad->inf.venit >= venitPrag)
			{
				vect[*nr] = rad->inf;
				(*nr)++;
			}
		}
		salvareVectorNoduriFrunza(rad->stanga, vect, nr, venitPrag);
		salvareVectorNoduriFrunza(rad->dreapta, vect, nr, venitPrag);
	}
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int inaltimeArbore(nodArb* rad)
{
	if (rad != NULL)
		return 1 + maxim(inaltimeArbore(rad->stanga),
			inaltimeArbore(rad->dreapta));
	else
		return 0;
}

nodArb* cautare(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.cod)
			return rad;
		else
			if (cheie < rad->inf.cod)
				return cautare(rad->stanga, cheie);
			else
				return cautare(rad->dreapta, cheie);
	}
	else
		return NULL;
}

void main()
{
	nodArb* rad = NULL;
	persoana p;
	char buffer[20];

	int nrPers;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrPers);
	for (int i = 0; i < nrPers; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.nume, buffer);
		fscanf(f, "%d", &p.varsta);
		fscanf(f, "%f", &p.venit);

		rad = inserareNod(rad, p);

		free(p.nume);
	}
	fclose(f);

	preordine(rad);
	printf("\n-----------------\n");
	preordine(rad->stanga);
	//inordine(rad);
	printf("\n-----------------\n");
	preordine(rad->dreapta);
	//postordine(rad);

	int nr = 0;
	nrPersVenitPrag(rad, &nr, 2000);
	printf("\nNr. persoane cu venit peste 2000 = %d", nr);

	float suma = 0;
	sumaVenituriPersoane(rad, &suma);
	printf("\nSuma veniturilor este = %5.2f", suma);

	printf("\n-----------------\n");

	persoana* vect = (persoana*)malloc(nrPers * sizeof(persoana));
	int nrP = 0;
	salvareVectorNoduriFrunza(rad, vect, &nrP, 5000);
	for (int i = 0; i < nrP; i++)
		printf("\nCod=%d, Nume=%s, Varsta=%d, Venit=%5.2f",
			vect[i].cod, vect[i].nume, vect[i].varsta,
			vect[i].venit);

	free(vect);

	printf("\nInaltime arbore = %d", inaltimeArbore(rad));
	printf("\nInaltime subarbore stang = %d", inaltimeArbore(rad->stanga));
	printf("\nInaltime subarbore drept = %d", inaltimeArbore(rad->dreapta));

	nodArb* nodCautat = NULL;
	nodCautat = cautare(rad, 400);
	if (nodCautat != NULL)
		printf("\nNumele persoanei cautate este %s", nodCautat->inf.nume);
	else
		printf("\Persoana nu exista!");

	dezalocare(rad);
}