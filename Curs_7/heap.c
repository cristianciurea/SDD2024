#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int prioritate;
	char* denumire;
	float cost;
} cheltuiala;

typedef struct
{
	cheltuiala* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt<h.nrElem && h.vect[indexSt].prioritate<
		h.vect[indexRad].prioritate)
		indexRad = indexSt;
	if (indexDr<h.nrElem && h.vect[indexDr].prioritate<
		h.vect[indexRad].prioritate)
		indexRad = indexDr;

	if (index != indexRad)
	{
		cheltuiala temp = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = temp;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, cheltuiala noua)
{
	cheltuiala* vectNou = (cheltuiala*)malloc((h.nrElem + 1) *
		sizeof(cheltuiala));
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

heap extragere(heap h, cheltuiala* extrasa)
{
	cheltuiala* vectNou = (cheltuiala*)malloc((h.nrElem - 1) *
		sizeof(cheltuiala));
	cheltuiala temp = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = temp;

	*extrasa = h.vect[h.nrElem - 1];

	h.nrElem--;

	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		printf("\nPrioritate: %d, Denumire: %s, Cost: %5.2f",
			h.vect[i].prioritate,
			h.vect[i].denumire, h.vect[i].cost);
}

void dezalocareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		free(h.vect[i].denumire);
	free(h.vect);
}

void main()
{
	heap h;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	h.vect = (cheltuiala*)malloc(h.nrElem * sizeof(cheltuiala));
	for (int i = 0; i < h.nrElem; i++)
	{
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].denumire, buffer);
		fscanf(f, "%f", &h.vect[i].cost);
	}
	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisare(h);

	cheltuiala noua;
	printf("\nPrioritate: ");
	scanf("%d", &noua.prioritate);
	printf("\nDenumire: ");
	scanf("%s", buffer);
	noua.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(noua.denumire, buffer);
	printf("\nCost: ");
	scanf("%f", &noua.cost);

	h = inserare(h, noua);
	afisare(h);

	printf("\n--------------------------\n");

	cheltuiala extrasa;
	h = extragere(h, &extrasa);
	afisare(h);
	printf("\nExtras -> Prioritate: %d, Denumire: %s, Cost: %5.2f",
		extrasa.prioritate,
		extrasa.denumire, extrasa.cost);

	printf("\n--------------------------\n");

	cheltuiala* vectSortat = (cheltuiala*)malloc(h.nrElem *
		sizeof(cheltuiala));
	int nr = h.nrElem;
	for (int i = 0; i < nr; i++)
	{
		h = extragere(h, &extrasa);
		vectSortat[i] = extrasa;
	}

	for (int i = 0; i < nr; i++)
		printf("\nPrioritate: %d, Denumire: %s, Cost: %5.2f",
			vectSortat[i].prioritate,
			vectSortat[i].denumire, vectSortat[i].cost);

	for (int i = 0; i < nr; i++)
		free(vectSortat[i].denumire);
	free(vectSortat);

	//dezalocareHeap(h);

}