//Algoritmul lui Dijkstra

#include <stdio.h>
#include <malloc.h>

typedef struct 
{
    int nod, cost;
    struct nodls* next;
} nodls;

int n, m;
nodls* vect[1000];
int drum[1000], q[1000];

void adauga(int sursa, int dest, int cost)
{
    nodls* temp = (nodls*)malloc(sizeof(nodls));
    temp->nod = dest;
    temp->cost = cost;
    temp->next = vect[sursa];
    vect[sursa] = temp;
}

void citeste()
{
    FILE* f = fopen("fisier4.txt", "r");

    fscanf(f, "%d %d", &n, &m);

    int x, y, z;
    for (int i = 1; i <= m; i++)
    {
        fscanf(f, "%d %d %d", &x, &y, &z);
        adauga(x, y, z);
    }
}

void dijkstra()
{
    for (int i = 2; i <= n; ++i)
        drum[i] = 1000;

    int valMin, indexMin = 0;

    for (int i = 1; i <= n; ++i)
    {
        valMin = 1000;
        for (int j = 1; j <= n; ++j)
            if (drum[j] < valMin && !q[j])
            {
                valMin = drum[j];
                indexMin = j;
            }

        q[indexMin] = 1;

        nodls* temp = vect[indexMin];

        while (temp)
        {
            if (drum[temp->nod] > drum[indexMin] + temp->cost)
                drum[temp->nod] = drum[indexMin] + temp->cost;
            temp = temp->next;
        }
    }
}

void main()
{
    citeste();
    dijkstra();
    for (int i = 2; i <= n; i++)
        printf("\nLungimea drumului minim de la nodul 1 la nodul %d este %d", i, drum[i]);
}
