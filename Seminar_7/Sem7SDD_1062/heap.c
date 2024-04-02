#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int urgenta;
	char* descriere;
	float oreAsteptare;
} spitalizare;

typedef struct
{
	spitalizare* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt<h.nrElem && h.vect[indexSt].urgenta>
		h.vect[indexRad].urgenta)
		indexRad = indexSt;

	if (indexDr<h.nrElem && h.vect[indexDr].urgenta>
		h.vect[indexRad].urgenta)
		indexRad = indexDr;

	if (index != indexRad)
	{
		spitalizare aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, spitalizare noua)
{
	spitalizare* vectNou = (spitalizare*)malloc((h.nrElem + 1) *
		sizeof(spitalizare));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	h.nrElem++;
	vectNou[h.nrElem - 1] = noua;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, spitalizare* extras)
{
	spitalizare* vectNou = (spitalizare*)malloc((h.nrElem - 1) *
		sizeof(spitalizare));

	spitalizare aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;

	*extras = h.vect[h.nrElem - 1];

	h.nrElem--;
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

void afisareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		printf("\nUrgenta=%d, Descriere=%s, Durata=%5.2f",
			h.vect[i].urgenta,
			h.vect[i].descriere,
			h.vect[i].oreAsteptare);
}

void dezalocareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		free(h.vect[i].descriere);
	free(h.vect);
}

void main()
{
	heap h;
	char buffer[30];

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	h.vect = (spitalizare*)malloc(h.nrElem * sizeof(spitalizare));
	for (int i = 0; i < h.nrElem; i++)
	{
		fscanf(f, "%d", &h.vect[i].urgenta);
		fscanf(f, "%s", buffer);
		h.vect[i].descriere = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(h.vect[i].descriere, buffer);
		fscanf(f, "%f", &h.vect[i].oreAsteptare);
	}
	fclose(f);

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	afisareHeap(h);

	printf("\n-----------------\n");

	spitalizare noua;
	printf("\nUrgenta = ");
	scanf("%d", &noua.urgenta);
	printf("\nDescriere = ");
	scanf("%s", buffer);
	noua.descriere = (char*)malloc((strlen(buffer) + 1) *
		sizeof(char));
	strcpy(noua.descriere, buffer);
	printf("\nOre = ");
	scanf("%f", &noua.oreAsteptare);

	h = inserare(h, noua);

	afisareHeap(h);

	printf("\n-----------------\n");

	spitalizare extras;
	h = extragere(h, &extras);
	printf("\nExtras -> Urgenta=%d, Descriere=%s, Durata=%5.2f",
		extras.urgenta, extras.descriere, extras.oreAsteptare);

	afisareHeap(h);

	printf("\n-----------------\n");
	spitalizare* vectSortat = (spitalizare*)malloc(h.nrElem *
		sizeof(spitalizare));
	int nr = h.nrElem;
	for (int i = 0; i < nr; i++)
	{
		h = extragere(h, &extras);
		vectSortat[i] = extras;
	}

	for (int i = 0; i < nr; i++)
		printf("\nUrgenta=%d, Descriere=%s, Durata=%5.2f",
			vectSortat[i].urgenta,
			vectSortat[i].descriere,
			vectSortat[i].oreAsteptare);

	for (int i = 0; i < nr; i++)
		free(vectSortat[i].descriere);
	free(vectSortat);

	//dezalocareHeap(h);
}