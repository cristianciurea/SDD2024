#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int prioritate;
	char* denumire;
	float efortOre;
} task;

typedef struct
{
	task* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt<h.nrElem && h.vect[indexSt].prioritate>
		h.vect[indexRad].prioritate)
		indexRad = indexSt;

	if (indexDr<h.nrElem && h.vect[indexDr].prioritate>
		h.vect[indexRad].prioritate)
		indexRad = indexDr;

	if (index != indexRad)
	{
		task aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, task nou)
{
	task* vectNou = (task*)malloc((h.nrElem + 1) * sizeof(task));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	h.nrElem++;
	vectNou[h.nrElem - 1] = nou;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, task* extras)
{
	task* vectNou = (task*)malloc((h.nrElem - 1) * sizeof(task));
	
	task aux = h.vect[0];
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
		printf("\nPrioritate = %d, Denumire = %s, Efort = %5.2f",
			h.vect[i].prioritate,
			h.vect[i].denumire,
			h.vect[i].efortOre);
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
	h.vect = (task*)malloc(h.nrElem * sizeof(task));
	for (int i = 0; i < h.nrElem; i++)
	{
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].denumire = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(h.vect[i].denumire, buffer);
		fscanf(f, "%f", &h.vect[i].efortOre);
	}
	fclose(f);

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	afisareHeap(h);

	task nou;
	printf("\nPrioritate = ");
	scanf("%d", &nou.prioritate);
	printf("\nDenumire = ");
	scanf("%s", buffer);
	nou.denumire = (char*)malloc((strlen(buffer) + 1) *
		sizeof(char));
	strcpy(nou.denumire, buffer);
	printf("\nEfort = ");
	scanf("%f", &nou.efortOre);

	printf("\n---------------------------\n");

	h = inserare(h, nou);

	afisareHeap(h);

	printf("\n---------------------------\n");

	task extras;
	h = extragere(h, &extras);
	printf("\nTask extras Prioritate = %d, Denumire = %s, Efort = %5.2f",
		extras.prioritate, extras.denumire, extras.efortOre);
	afisareHeap(h);

	printf("\n---------------------------\n");


	task* vectSortat = (task*)malloc(h.nrElem * sizeof(task));
	int nr = h.nrElem;
	for (int i = 0; i < nr; i++)
	{
		h = extragere(h, &extras);
		vectSortat[i] = extras;
	}

	for (int i = 0; i < nr; i++)
		printf("\nPrioritate = %d, Denumire = %s, Efort = %5.2f",
			vectSortat[i].prioritate,
			vectSortat[i].denumire,
			vectSortat[i].efortOre);
	for (int i = 0; i < nr; i++)
		free(vectSortat[i].denumire);
	free(vectSortat);

	//dezalocareHeap(h);
}

