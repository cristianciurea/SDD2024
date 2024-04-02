#include <stdio.h>
#include <malloc.h>

typedef struct 
{
	int prioritate;
	char* numeApelant;
} apelUrgenta;

typedef struct 
{
	apelUrgenta* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexMax = index;//nod radacina
	int indexS = 2 * index + 1;//fiul stg
	int indexD = 2 * index + 2;//fiul dreapta

	if (indexS < h.nrElem && h.vect[indexS].prioritate > h.vect[indexMax].prioritate)
		indexMax = indexS;//interschimbare indici
	if (indexD < h.nrElem && h.vect[indexD].prioritate > h.vect[indexMax].prioritate)
		indexMax = indexD;

	if (index != indexMax)//interschimbare elemente din vector
	{
		apelUrgenta temp = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = temp;

		filtrare(h, indexMax);//se reia filtrarea de la pozitia ramasa
	}
}

void inserare(heap* h, apelUrgenta elem)
{
	apelUrgenta* vect1 =  (apelUrgenta*)malloc(((*h).nrElem + 1)*sizeof(apelUrgenta));
	for (int i = 0; i < (*h).nrElem; i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem++;
	free((*h).vect);
	(*h).vect = vect1;

	(*h).vect[(*h).nrElem - 1] = elem;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) //filtrare de la ultimul element
		filtrare((*h), i);
}

void extragere(heap* h, apelUrgenta* elem)
{
	apelUrgenta* vect1 = (apelUrgenta*)malloc(((*h).nrElem - 1) * sizeof(apelUrgenta));

	apelUrgenta temp = (*h).vect[0];//interschimbam primul elem cu ultimul din vector
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1];
	(*h).vect[(*h).nrElem - 1] = temp;

	*elem = (*h).vect[(*h).nrElem - 1];//elementul maxim care se afla acum pe ultima pozitie in vector

	for (int i = 0; i < (*h).nrElem - 1; i++)
		vect1[i] = (*h).vect[i];

	(*h).nrElem--;
	free((*h).vect);
	(*h).vect = vect1;//noul vector

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--)
		filtrare((*h), i);//filtrare de jos in sus
}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
	{
		printf("\nPrioritatea este: %d", h.vect[i].prioritate);
		printf("\nNumele apelantului este: %s", h.vect[i].numeApelant);
	}
}

void dezalocare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		free(h.vect[i].numeApelant);
	free(h.vect);
}

void main()
{
	heap h;

	printf("Nr. elemente: ");
	scanf("%d", &h.nrElem);

	char buffer[20];

	h.vect = (apelUrgenta*)malloc(h.nrElem *sizeof(apelUrgenta));

	for (int i = 0; i < h.nrElem; i++)
	{
		printf("Prioritate: ");
		scanf("%d", &h.vect[i].prioritate);

		printf("Numele apelantului: ");
		scanf("%s", buffer);
		h.vect[i].numeApelant = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
		strcpy(h.vect[i].numeApelant, buffer);
	}

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	afisare(h);
	apelUrgenta s;
	s.numeApelant = (char*)malloc((strlen("Marcel") + 1) * sizeof(char));
	strcpy(s.numeApelant, "Marcel");
	s.prioritate = 25;
	inserare(&h, s);
	//inserare(&h, 6);

	afisare(h);

	apelUrgenta elem;
	extragere(&h, &elem);
	printf("\nElement extras are prioritatea %d", elem.prioritate);

	afisare(h);

	dezalocare(h);
}
