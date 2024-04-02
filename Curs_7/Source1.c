#include <stdio.h>
#include <malloc.h>

//typedef struct student
//{
//	int cod;
//	char *nume;
//	float medie;
//};

typedef struct 
{
	int* vect;
	//student *vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexMax = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;

	if (indexS < h.nrElem && h.vect[indexS] > h.vect[indexMax])
		indexMax = indexS;
	if (indexD < h.nrElem && h.vect[indexD] > h.vect[indexMax])
		indexMax = indexD;

	if (index != indexMax)
	{
		int temp = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = temp;

		filtrare(h, indexMax);
	}
}

void inserare(heap* h, int elem)
{
	int* vect1 = (int*)malloc(((*h).nrElem + 1) * sizeof(int));
	for (int i = 0; i < (*h).nrElem; i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem++;
	free((*h).vect);
	(*h).vect = vect1;

	(*h).vect[(*h).nrElem - 1] = elem;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare((*h), i);
}

void extragere(heap* h, int* elem)
{
	int* vect1 = (int*)malloc(((*h).nrElem - 1) * sizeof(int));

	int temp = (*h).vect[0];
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1];
	(*h).vect[(*h).nrElem - 1] = temp;

	*elem = (*h).vect[(*h).nrElem - 1];

	for (int i = 0; i < (*h).nrElem - 1; i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem--;
	free((*h).vect);
	(*h).vect = vect1;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare((*h), i);
}

void afisare(heap h)
{
	printf("\nElemente heap: ");
	for (int i = 0; i < h.nrElem; i++)
		printf("%d ", h.vect[i]);
}

void dezalocare(heap h)
{
	free(h.vect);
}

void main()
{
	heap h;

	printf("Nr. elemente: ");
	scanf("%d", &h.nrElem);

	h.vect = (int*)malloc(h.nrElem * sizeof(int));

	for (int i = 0; i < h.nrElem; i++)
	{
		printf("\nElement: ");
		scanf("%d", &h.vect[i]);
	}

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	afisare(h);

	inserare(&h, 28);

	afisare(h);

	int elem;
	int* vectSortat = (int*)malloc(h.nrElem * sizeof(int));
	int n = h.nrElem;
	for (int i = 0; i < n; i++)
	{
		extragere(&h, &elem);
		vectSortat[i] = elem;
	}
	printf("\nVector sortat:\n");
	for (int i = 0; i < n; i++)
		printf("%d ", vectSortat[i]);
	free(vectSortat);

	afisare(h);

	//dezalocare(h);
}