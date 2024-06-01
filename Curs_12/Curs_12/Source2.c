//Algoritmul Roy-Floyd - determinarea matricei drumurilor minime

#include <stdio.h>

int min(int a, int b)
{
	if (a <= b) 
		return a;
	else 
		return b;
}

void main()
{
	int i, j, k, n, mat[20][20];

	FILE* f = fopen("fisier2.txt", "r");
	if (f)
	{
		fscanf(f, "%d", &n);
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				fscanf(f, "%d", &mat[i][j]);
	}
	else 
		printf("\nNu exista fisier!");
	fclose(f);

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if ((i != k) && (j != k) && (i != j)) 
					mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

	printf("Matricea drumurilor minime este:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf(" %d ", mat[i][j]);
		printf("\n");
	}
}