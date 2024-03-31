#include <stdio.h>
#include <malloc.h>

typedef struct 
{
	struct NodAO* adr; //adresa nod arbore
	struct NodAdr* next; //pointer de legatura
} NodAdr;

typedef struct
{
	int id; //cheie nod
	NodAdr* desc; //lista descendenti
} NodAO;

//functie de cautare a unui nod in arbore oarecare
void cautaNod(NodAO* rad, int idp, NodAO** t)
{
	if (rad)
	{
		if (rad->id == idp)
			*t = rad;
		NodAdr* q = rad->desc;
		while (q)
		{
			cautaNod(q->adr, idp, t);
			q = q->next;
		}
	}
}

NodAO* inserareNodAO(NodAO* rad, int idp, int idins)
{
	if (!rad)
	{
		//inserare nod radacina
		NodAO* nou = (NodAO*)malloc(sizeof(NodAO));
		nou->id = idins;
		nou->desc = NULL;
		return nou;
	}
	else
	{
		NodAO* t = NULL;
		cautaNod(rad, idp, &t);
		if (t)
		{
			//inserare nod in lista de descendenti ai nodului t
			NodAO* nou = (NodAO*)malloc(sizeof(NodAO));
			nou->id = idins;
			nou->desc = NULL;
			NodAdr* q = t->desc;
			//inserare nod in lista de descendenti
			NodAdr* nouAdr = (NodAdr*)malloc(sizeof(NodAdr));
			nouAdr->adr = nou;
			nouAdr->next = NULL;
			if (q)
			{
				while (q->next) q = q->next;
				q->next = nouAdr;
			}
			else
			{
				t->desc = nouAdr;
			}
		}
		return rad;
	}
}

void afis(NodAO* rad)
{
	NodAO* p = rad;
	while (p->desc != NULL)
	{
		printf("\n%d", p->id);
		NodAdr* t = p->desc;
		printf("\n");
		while (t != NULL)
		{
			NodAO* q = t->adr;
			printf("%d ", q->id);
			t = t->next;
		}
		if (p->desc) 
			p = p->desc->adr;
	}
}

void afisareAO(NodAO* rad)
{
	NodAO* p = rad;
	afis(p);

	NodAdr* q = rad->desc->next;
	while (q != NULL)
	{
		afis(q->adr);
		q = q->next;
	}
}

void main()
{
	NodAO* rad = NULL;
	int idP, idIns;

	FILE* f = fopen("arbore_oarecare.txt", "r");

	while (!feof(f))
	{
		//ID nod parinte
		fscanf(f,"%d", &idP);
		//ID nod de inserat
		fscanf(f, "%d", &idIns);

		//apel functie inserare nod
		rad = inserareNodAO(rad, idP, idIns);
	}
	fclose(f);

	//afisare structura arbore oarecare
	afisareAO(rad);
}
