#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct Masina {
	int id;
	int anFabricatie;
	char* sofer;
	float kilometriiParcursi;
	char initialaProducator;
};

struct Masina initializare(int id, int anFabricatie, const char* sofer, float kilometriiParcursi, char initialaProducator) {
	struct Masina m;
	m.id = id;
	m.anFabricatie = anFabricatie;
	if (sofer != NULL) {
		m.sofer = (char*)malloc(strlen(sofer) + 1);
		strcpy_s(m.sofer, strlen(sofer) + 1, sofer);
	}
	else {
		m.sofer = NULL;
	}
	m.kilometriiParcursi = kilometriiParcursi;
	m.initialaProducator = initialaProducator;
	return m;
}

void afisare(struct Masina m) {
	printf("ID: %d \n", m.id);
	printf("An fabricatie: %d \n", m.anFabricatie);
	printf("Sofer: %s \n", m.sofer);
	printf("Kilometrii Parcursi : %f \n", m.kilometriiParcursi);
	printf("Initiala producator: %c \n", m.initialaProducator);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	if (vector != NULL && nrElemente > 0) {
		for (int i = 0; i < nrElemente; i++) {
			afisare(vector[i]);
			printf("\n");
		}
	}
}

void modifica_Sofer(struct Masina* m, const char* nouSofer) {
	if (strlen(nouSofer) > 2) {
		if (m->sofer != NULL) {
			free(m->sofer);
		}
		m->sofer = (char*)malloc(strlen(nouSofer) + 1);
		strcpy_s(m->sofer, strlen(nouSofer) + 1, nouSofer);
	}
}

void dezalocare(struct Masina* m) {
	if (m->sofer != NULL) {
		free(m->sofer);
		m->sofer = NULL;
	}
}

//int main() {
//	struct Masina masina;
//	masina = initializare(1, 2004, "Robert", 2000, 'P');
//	afisare(masina);
//	modifica_Sofer(&masina, "Alex");
//	afisare(masina);
//	dezalocare(&masina);
//	afisare(masina);
//	return 0;
//}


struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Masina* vectorNou = NULL;
	if (vector != NULL && nrElementeCopiate <= nrElemente && nrElementeCopiate > 0) {
		vectorNou = malloc(sizeof(struct Masina) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = initializare(vector[i].id, vector[i].anFabricatie, vector[i].sofer, vector[i].kilometriiParcursi, vector[i].initialaProducator);
		}
	}

	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	if (vector != NULL && *nrElemente > 0) {
		for (int i = 0; i < *nrElemente; i++) {
			free((*vector)[i].sofer);
		}
		free(*vector);
		(*vector) = NULL;
		(*nrElemente) = 0;

	}

}


void copiazaAnumiteElemente(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	if (vector != NULL && nrElemente > 0) {
		(*dimensiune) = 0;
		for (int i = 0; i > nrElemente; i++) {
			if (vector[i].kilometriiParcursi > prag) {
				(*dimensiune)++;
			}
		}
		(*vectorNou) = malloc(sizeof(struct Masina) * (*dimensiune));
		int k = 0;
		for (int i = 0; i > nrElemente; i++) {
			if (vector[i].kilometriiParcursi > prag) {
				(*vectorNou)[k] = vector[i];
				(*vectorNou)[k].sofer = malloc(sizeof(char) * (strlen(vector[i].sofer) + 1));
				strcpy_s((*vectorNou)[k].sofer, strlen(vector[i].sofer), vector[i].sofer);
			}
		}
	}

}

struct Masina getPrimaMasinaDupaSofer(struct Masina* vector, int nrElemente, const char* soferCautat) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	for (int i = 0; i < nrElemente; i++)
	{
		if (strcmp(soferCautat, vector[i].sofer) == 0) {
			return vector[i];
		}
	}

	return initializare(-1, 0, NULL, 0, '-');
}


int main() {

	int nrElemente = 3;
	struct Masina* vector = malloc(sizeof(struct Masina) * nrElemente);

	vector[0] = initializare(1, 2010, "Marian", 2100, 'F');
	vector[1] = initializare(2, 2008, "Cristi", 3500.6, 'A');
	vector[2] = initializare(3, 2017, "Stefan", 750, 'R');
	afisareVector(vector, 3);
	int nrElementeCopiate = 2;
	struct Masina* vectorNou = copiazaPrimeleNElemente(vector, nrElemente, nrElementeCopiate);
	printf("Masini copiate: \n");
	afisareVector(vectorNou, nrElementeCopiate);
	dezalocare(&vectorNou, &nrElementeCopiate);
	float prag = 1000;
	copiazaAnumiteElemente(vector, nrElemente, prag, &vectorNou, &nrElementeCopiate);
	printf("Masina cu multi km: \n");
	afisareVector(vectorNou, nrElementeCopiate);
	dezalocare(&vectorNou, &nrElementeCopiate);

	struct Masina primaMasina = getPrimaMasinaDupaSofer(vector, nrElemente, "Ion");
	afisare(primaMasina);
	dezalocare(&vector, &nrElemente);
	return 0;
}