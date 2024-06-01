#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int id;
	char* denumire;
} localitate;

typedef struct nodLP;

typedef struct
{
	struct nodLP* info;
	struct nodLS* next;
} nodLS;

typedef struct
{
	localitate info;
	struct nodLS* vecini;
	struct nodLP* next;
} nodLP;

nodLP* inserareLP(nodLP* capLP, localitate loc)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info.id = loc.id;
	nou->info.denumire = (char*)malloc((strlen(loc.denumire) + 1) *
		sizeof(char));
	strcpy(nou->info.denumire, loc.denumire);
	nou->vecini = NULL;
	nou->next = NULL;
	if (capLP == NULL)
		capLP = nou;
	else
	{
		nodLP* temp = capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return capLP;
}

nodLS* inserareLS(nodLS* capLS, nodLP* info)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = info;
	nou->next = NULL;
	if (capLS == NULL)
		capLS = nou;
	else
	{
		nodLS* temp = capLS;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return capLS;
}

nodLP* cautareDupaID(nodLP* capLP, int id)
{
	nodLP* temp = capLP;
	while (temp && temp->info.id != id)
		temp = temp->next;
	return temp;
}

void inserareArcInGraf(nodLP* capLP, int idNodStart, int idNodStop)
{
	if (capLP)
	{
		nodLP* nodStart = cautareDupaID(capLP, idNodStart);
		nodLP* nodStop = cautareDupaID(capLP, idNodStop);
		if (nodStart && nodStop)
		{
			nodStart->vecini = inserareLS(nodStart->vecini, nodStop);
			nodStop->vecini = inserareLS(nodStop->vecini, nodStart);
		}
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLP* aux = temp->info;
		printf("    %d.%s\n", aux->info.id + 1, aux->info.denumire);
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		printf("%d.%s are urmatorii vecini: \n",
			temp->info.id + 1, temp->info.denumire);
		traversareLS(temp->vecini);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		if (temp->vecini)
			dezalocareLS(temp->vecini);
		printf("\nAm sters: %s", temp->info.denumire);
		free(temp->info.denumire);
		free(temp);
		temp = temp2;
	}
}

typedef struct
{
	int id;
	struct nodStiva* next;
} nodStiva;

nodStiva* push(nodStiva* varf, int id)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->id = id;
	nou->next = NULL;
	if (varf == NULL)
		varf = nou;
	else
	{
		nou->next = varf;
		varf = nou;
	}
	return varf;
}

int pop(nodStiva** varf)
{
	if (*varf)
	{
		int id = (*varf)->id;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp);
		return id;
	}
	else
		return -1;
}

void parcurgereAdancime(nodLP* graf, int idNodStart, int nrNoduri)
{
	if (graf)
	{
		nodStiva* varf = NULL;
		int* vizitate = (int*)malloc(nrNoduri * sizeof(int));
		for (int i = 0; i < nrNoduri; i++)
			vizitate[i] = 0;
		varf = push(varf, idNodStart);
		vizitate[idNodStart] = 1;
		while (varf)
		{
			int idNodCurent = pop(&varf);
			nodLP* nodCurent = cautareDupaID(graf, idNodCurent);
			printf("%d.%s\n", nodCurent->info.id + 1,
				nodCurent->info.denumire);

			nodLS* temp = nodCurent->vecini;
			while (temp)
			{
				nodLP* aux = temp->info;
				if (vizitate[aux->info.id] == 0)
				{
					varf = push(varf, aux->info.id);
					vizitate[aux->info.id] = 1;
				}
				temp = temp->next;
			}
		}
	}
}

void main()
{
	FILE* f = fopen("fisier.txt", "r");

	nodLP* graf = NULL;
	int nrNoduri;
	char buffer[20];
	localitate loc;

	fscanf(f, "%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		loc.id = i;
		fscanf(f, "%s", buffer);
		loc.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(loc.denumire, buffer);
		graf = inserareLP(graf, loc);
	}

	int nrArce, idNodStart, idNodStop;
	fscanf(f, "%d", &nrArce);
	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &idNodStart);
		fscanf(f, "%d", &idNodStop);
		inserareArcInGraf(graf, idNodStart, idNodStop);
	}

	fclose(f);

	traversareLP(graf);

	printf("\nParcurgere in adancime de la nodul 1:\n");
	parcurgereAdancime(graf, 0, nrNoduri);

	dezalocareLP(graf);
}