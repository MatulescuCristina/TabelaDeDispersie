#include<stdio.h>
#include<malloc.h>

struct Oras
{
	int cod;
	char* denumire;
	int nrLocuitori;
	float suprafata;
};

struct Nod
{
	struct Oras info;
	struct Nod* next;
};

struct TabelaDispersie
{
	struct Nod** vector;
	int dimensiune;
};

// functie tabela de dispersie
int functieTabelaDispersie(struct TabelaDispersie tabela, int cheie)
{
	return cheie % tabela.dimensiune;
}

// inserare in tabela de dispersie
int inserareTabela(struct TabelaDispersie tabela, struct Oras o)
{
	int pozitie = -1;
	if (tabela.vector != NULL)
	{
		pozitie = functieTabelaDispersie(tabela, o.cod);

		struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

		nou->info.cod = o.cod;

		nou->info.denumire = (char*)malloc((strlen(o.denumire) + 1) * sizeof(char));
		strcpy(nou->info.denumire, o.denumire);

		nou->info.nrLocuitori = o.nrLocuitori;
		nou->info.suprafata = o.suprafata;

		nou->next = NULL;

		if (tabela.vector[pozitie] == NULL)
		{
			tabela.vector[pozitie] = nou;
		}
		else
		{
			struct Nod* aux = tabela.vector[pozitie];
			while (aux->next != NULL)
				aux = aux->next;
			aux->next = nou;
		}
	}
	return pozitie;
}

// afisare tabela de dispersie
void afisare(struct TabelaDispersie tabela)
{
	if (tabela.vector != NULL)
	{
		for (int i = 0; i < tabela.dimensiune; i++)
		{
			if (tabela.vector[i] != NULL)
			{
				struct Nod* aux = tabela.vector[i];

				printf("\n	Pozitia %d", i);
				while (aux)
				{
					printf("\nCod oras: %d, denumire oras: %s, nr locuitori: %d, suprafata: %5.2f\n",
						aux->info.cod, aux->info.denumire, aux->info.nrLocuitori, aux->info.suprafata);
					aux = aux->next;
				}
			}
		}
	}
}

void main()
{
	int nr;
	char buffer[20];
	struct Oras o;
	struct TabelaDispersie tabela;
	tabela.dimensiune = 10;
	tabela.vector = (struct Nod**)malloc(sizeof(struct Nod*) * tabela.dimensiune);
	
	for (int i = 0; i < tabela.dimensiune; i++)
	{
		tabela.vector[i] = NULL;
	}

	FILE* f = fopen("oras2.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &o.cod);

		fscanf(f, "%s", buffer);
		o.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(o.denumire, buffer);

		fscanf(f, "%d", &o.nrLocuitori);

		fscanf(f, "%f", &o.suprafata);

		inserareTabela(tabela, o);
	}
	fclose(f);

	afisare(tabela);
}