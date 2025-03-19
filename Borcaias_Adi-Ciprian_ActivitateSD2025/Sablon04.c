#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
struct Nod
{
	Masina info;
	struct Nod* next;
};
typedef struct Nod N;
//creare structura pentru un nod dintr-o lista simplu inlantuita

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(N* nod) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()
	while (nod) {
		afisareMasina(nod->info);
		nod = nod->next;
	}
}

void adaugaMasinaInLista(N** lista, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	N* nodNou;
	nodNou = (N*)malloc(sizeof(N));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;

	if ((*lista) == NULL) {
		(*lista) = nodNou;
	}
	else {
		N* aux = (*lista);
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nodNou;
	}
}

void adaugaLaInceputInLista(/*lista de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
}

 N* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f;
	f=fopen(numeFisier, "r");
	N* lista= NULL;
	while (!feof(f)) {
		Masina m;
		m = citireMasinaDinFisier(numeFisier);
		adaugaMasinaInLista(&lista, m);
	}
	fclose(f);
	return lista;
}

void dezalocareListaMasini(N** lista) {
	//sunt dezalocate toate masinile si lista de elemente
	while ((*lista)) {
		N* p = *lista;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
	}
}

float calculeazaPretMediu(N* lista) {
	//calculeaza pretul mediu al masinilor din lista.
	float suma = 0;
	int contor = 0;
	while (lista) {
		suma += lista->info.pret;
		contor++;
		lista = lista->next;
	}
	if (contor = 0) {
		return 0;
	}
	else return suma / contor;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int getNrUsiMasinaScumpa(N* lista) {
	if (lista) {
		int nrUsi = lista->info.nrUsi;
		float pretMaxim = lista->info.pret;
		lista = lista->next;
		while (lista) {
			if (lista->info.pret > pretMaxim) {
				nrUsi = lista->info.nrUsi;
				pretMaxim = lista->info.pret;
			}
		}
	}
}


int main() {
	N* nod;
	nod = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(nod);
	dezalocareListaMasini(&nod);
	float medie = calculeazaPretMediu(nod);
	printf("Media este : %.2f", nod);
	return 0;
}

