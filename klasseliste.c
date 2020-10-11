#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"

struct medlemsinfo { // definerer en type struct medlemsinfo
	char fornavn   [250]; // alle navn bortsett fra etternavn
	char etternavn [100]; // det siste navnet
	int  pub_key;         // 0 hvis medlem mangler offentlig noekkel
};

int i = 0; // den globale counteren for hvor mange entries i klasselista

// legger til en "type alias" i det globale name spacet
// kan nå feks si konto_t pub_key = 1, i motsetning til å måtte deklarere
// struct medlemsinfo pub_key = 1.
typedef struct medlemsinfo konto_t;

void les_data(konto_t *klasseliste);
void skriv_data(konto_t *klasseliste, char *args);

int main(int argc, char *argv[]) { // evt. int argc, char **argv. holder styr på argumenter fra kommandolinja
	/*
	konto_t er et alias for "struct medlemsinfo"
	klasseliste[200] = [ [person1: {fornavn:, etternavn:, pub_key: }], [person2], osv. ]
	det blir satt av 200 plasser til personer. personene er av typen medlemsinfo/konto_t
	*/
	
	konto_t klasseliste[200];
	char *args = NULL;
	les_data(klasseliste);

	if(argc > 1) {
		args = argv[1];
		skriv_data(klasseliste, args);
	}
//	skriv_data(klasseliste, args);

	return 0;
}


void les_data(konto_t *klasseliste) {
	char *txt = NULL; // sørger for at pekeren ikke peker til en ugyldig adresse
	char *string = NULL; // ^
	// hvis en peker ikke blir initialisert til NULL kan det være man får en segmenteringsfeil,
	// da den feks kan peke på en minneadresse man ikke har tilgang til
	size_t len = 0;
	
	while(-1 != (len=getline(&txt, &len, stdin))) {
		string = strtok(txt, " "); // extracter pub_key statusen
		klasseliste[i].pub_key = strtol(string, NULL, 10); // konverter til int og setter verdien

		string = strtok(NULL, " "); // extracter fornavn
		strcpy(klasseliste[i].fornavn, string); // kopierer fornavnet til variabelen

		string = strtok(NULL, "\n"); // extracter de siste navna
		strcpy(klasseliste[i].etternavn, string); // kopierer etternavn(og mellomnavn) til variabelen
		i++; // inkrementerer den globale counteren slik at skriv_data() vet hvor mange plasser som er i lista
	}
}

void skriv_data(konto_t *klasseliste, char *args) {
//	char *key = "key";
//	char *fornavn = "fornavn";
//	char *etternavn = "etternavn";
	char *m = getenv("KLASSE");

	if(strcmp("etternavn", args) == 0 || m == "etternavn") {
		for(int j=0; j<i; j++)
			printf("%s, %s\t%d\n", klasseliste[j].etternavn, klasseliste[j].fornavn, klasseliste[j].pub_key);
	}
	else if(strcmp("fornavn", args) == 0 || m == "fornavn") {
		for(int j=0; j<i; j++)
			printf("%s %s\t%d\n", klasseliste[j].fornavn, klasseliste[j].etternavn, klasseliste[j].pub_key);
	}
	else if(strcmp("key", args) == 0 || m == "key") {
		for(int j=0; j<i; j++)
			printf("%d\t%s %s\n", klasseliste[j].pub_key, klasseliste[j].fornavn, klasseliste[j].etternavn);
	}
	else
		printf("Argumentene er: fornavn, etternavn eller key (eller bruk og endre $KLASSE)\n");
	
//	for(int j=0; j<i; j++) { // bruker den globale counteren
//		printf("%d\t%s %s", klasseliste[j].pub_key, klasseliste[j].fornavn, klasseliste[j].etternavn);
//		printf("%d\t%s\n", klasseliste[j].pub_key, klasseliste[j].fornavn);
//		printf("%d\n", klasseliste[j].pub_key);
//	}
}
