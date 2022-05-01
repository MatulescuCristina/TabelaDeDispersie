#include<stdio.h>
#include<malloc.h>

struct Oras
{
	int cod;
	char* denumire;
	int nrLocuitori;
	float suprafata;
};

struct TabelaDispersie
{
	struct Oras** vector;
	int dimensiune;
};

// fuctie tabela de dispersie
int functieTabelaDispersie(struct TabelaDispersie tabela, int cheie)
{
	return cheie % tabela.dimensiune;
}

// inserare in tabela de dispersie
int inserareTabela(struct TabelaDispersie tabela, struct Oras* o)
{
	int pozitie;
	if (tabela.vector != NULL)
	{
		pozitie = functieTabelaDispersie(tabela, (*o).cod);

		if (tabela.vector[pozitie] == NULL)
		{
			tabela.vector[pozitie] = o;
		}
		else
		{
			int index = 1;
			while (pozitie + index < tabela.dimensiune)
			{
				if (tabela.vector[pozitie + index] == NULL)
				{
					pozitie += index;
					tabela.vector[pozitie] = 0;
				}
				index++;
			}
		}
		return pozitie;
	}
}

// afisare tabela de dispersie
void afisare(struct TabelaDispersie tabela)
{
	if (tabela.vector)
	{
		for (int i = 0; i < tabela.dimensiune; i++)
		{
			if (tabela.vector[i])
			{
				printf("\n	Pozitia %d", i);
				printf("\nCod oras: %d, denumire oras: %s, nr locuitori: %d, suprafata: %5.2f\n",
					tabela.vector[i]->cod, tabela.vector[i]->denumire, tabela.vector[i]->nrLocuitori, tabela.vector[i]->suprafata);
			}
		}
	}
}

void main()
{
	int nr;
	char buffer[20];
	struct Oras* o;
	struct TabelaDispersie tabela;
	tabela.dimensiune = 10;
	tabela.vector = (struct Oras**)malloc(sizeof(struct Oras*) * tabela.dimensiune);

	for (int i = 0; i < tabela.dimensiune; i++)
	{
		tabela.vector[i] = NULL;
	}

	FILE* f = fopen("oras1.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		o = (struct Oras*)malloc(sizeof(struct Oras));

		fscanf(f, "%d", &o->cod);

		fscanf(f, "%s", buffer);
		o->denumire = (char*)malloc((strlen(buffer)+1) * sizeof(char));
		strcpy(o->denumire, buffer);

		fscanf(f, "%d", &o->nrLocuitori);
		fscanf(f, "%f", &o->suprafata);

		inserareTabela(tabela, o);
	}
	fclose(f);

	afisare(tabela);
}