//Sortarea topologica

#include <stdio.h>
#include <malloc.h>

typedef struct 
{
	int info;
	struct nod* next;
} nod;

void main()
{
	//vectorul de elemente de sortat
	int termen[20];
	//vector contor care retine numarul predecesorilor fiecarui element
	int nr_pred[20];
	//vector ce retine adresele listelor de succesori ai fiecarui element
	nod* lista_succ[20];

	int n, m, i, j, a, b;
	int gata;

	nod* cap = NULL;
	int k1, k2;

	FILE* f = fopen("fisier3.txt", "r");
	printf("\nSortare topologica\n");
	//cout << "\nDati numarul de termeni :";
	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++)
	{
		//cout << "Dati termenul " << i + 1 << " :";
		fscanf(f, "%d", &termen[i]);
		//elementele vectorilor se initializeaza cu 0, respectiv NULL, pentru ca nu s-a citit nici o pereche
		nr_pred[i] = 0;
		lista_succ[i] = NULL;
	}

	//cout << "\nDati numarul de relatii :";
	fscanf(f, "%d", &m);
	for (i = 0; i < m; i++)
	{
		//cout << "Relatia numarul " << i << " (a<b) : ";
		//cout << "\na = ";
		fscanf(f, "%d", &a);
		//cout << "b = ";
		fscanf(f, "%d", &b);
		for (j = 0; j < n; j++)
		{
			if (termen[j] == a) 
				k1 = j;
			if (termen[j] == b) 
				k2 = j;
		}
		//se adauga k2 in lista de succesori ai lui k1
		cap = (nod*)malloc(sizeof(nod));
		cap->info = k2;
		cap->next = lista_succ[k1];
		lista_succ[k1] = cap;
		//se incrementeaza nr. de predecesori ai lui k2
		nr_pred[k2] = nr_pred[k2] + 1;
	}
	fclose(f);

	for (i = 0; i < n; i++)
	{
		j = 0;
		gata = 0;
		while ((j < n) && (!gata))
		{
			if (nr_pred[j] == 0)
			{
				printf("%d ", termen[j]);
				gata = 1;
				//pe pozitia j se pune -1 pt. a nu mai fi luat in considerare
				nr_pred[j] = -1;
				cap = lista_succ[j];
				while (cap != NULL)
				{
					//pentru toti succesorii se scade 1 din elementul corespunzator din vectorul contor
					//deoarece ulterior consideram ca acestia au un predecesor mai putin
					nr_pred[cap->info]--;
					cap = cap->next;
				}
			}
			else j++;
		}
	}
}
