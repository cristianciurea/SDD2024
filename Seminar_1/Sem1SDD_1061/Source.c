#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int *cod;
	char* den;
	float pret;
	float cant;
} produs;

void citireVectProduse(produs* vp, int nr)
{
	char buffer[20];
	for (int i = 0; i < nr; i++)
	{
		printf("Cod=");
		vp[i].cod = (int*)malloc(1 * sizeof(int));
		scanf("%d", vp[i].cod);
		printf("Denumire=");
		scanf("%s", buffer);
		vp[i].den = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vp[i].den, buffer);
		printf("Pret=");
		scanf("%f", &vp[i].pret);
		printf("Cantitate=");
		scanf("%f", &vp[i].cant);
	}
}

void afisareVectProd(produs* vp, int nr)
{
	for (int i = 0; i < nr; i++)
		printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f",
			*(vp[i].cod), vp[i].den, vp[i].pret, vp[i].cant);
}

void dezalocareVectProd(produs* vp, int nr)
{
	for (int i = 0; i < nr; i++)
	{
		free(vp[i].den);
		free(vp[i].cod);
	}
	free(vp);
}

void citire4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int nr)
{
	char buffer[20];
	for (int i = 0; i < nr; i++)
	{
		printf("Cod=");
		scanf("%d", &coduri[i]);
		printf("Denumire=");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);
		printf("Pret=");
		scanf("%f", &preturi[i]);
		printf("Cantitate=");
		scanf("%f", &cantitati[i]);
	}
}

void afisare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int nr)
{
	for (int i = 0; i < nr; i++)
		printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f",
			coduri[i], denumiri[i], preturi[i], cantitati[i]);
}

void dezalocare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int nr)
{
	for (int i = 0; i < nr; i++)
		free(denumiri[i]);
	free(denumiri);
	free(coduri);
	free(preturi);
	free(cantitati);
}

void citireMatrice(float** mat, char** denumiri, int nr)
{
	char buffer[20];
	for (int i = 0; i < nr; i++)
	{
		printf("Cod=");
		scanf("%f", &mat[i][0]);
		printf("Denumire=");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);
		printf("Pret=");
		scanf("%f", &mat[i][1]);
		printf("Cantitate=");
		scanf("%f", &mat[i][2]);
	}
}

void afisareMatrice(float** mat, char** denumiri, int nr)
{
	for (int i = 0; i < nr; i++)
		printf("\nCod = %5.2f, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f",
			mat[i][0], denumiri[i], mat[i][1], mat[i][2]);
}

void dezalocareMatrice(float** mat, char** denumiri, int nr)
{
	for (int i = 0; i < nr; i++)
	{
		free(mat[i]);
		free(denumiri[i]);
	}
	free(mat);
	free(denumiri);
}

void main()
{
	int nr;
	printf("Nr. produse=");
	scanf("%d", &nr);

	/*produs* vp = (produs*)malloc(nr * sizeof(produs));
	citireVectProduse(vp, nr);
	afisareVectProd(vp, nr);
	dezalocareVectProd(vp, nr);*/

	/*int* coduri = (int*)malloc(nr * sizeof(int));
	char** denumiri = (char**)malloc(nr * sizeof(char*));
	float* preturi = (float*)malloc(nr * sizeof(float));
	float* cantitati = (float*)malloc(nr * sizeof(float));
	citire4Vectori(coduri, denumiri, preturi, cantitati, nr);
	afisare4Vectori(coduri, denumiri, preturi, cantitati, nr);
	dezalocare4Vectori(coduri, denumiri, preturi, cantitati, nr);*/

	float** mat = (float**)malloc(nr * sizeof(float*));
	for (int i = 0; i < nr; i++)
	{
		mat[i] = (float*)malloc(3 * sizeof(float));
	}
	char** denumiri = (char**)malloc(nr * sizeof(char*));
	citireMatrice(mat, denumiri, nr);
	afisareMatrice(mat, denumiri, nr);
	dezalocareMatrice(mat, denumiri, nr);
}