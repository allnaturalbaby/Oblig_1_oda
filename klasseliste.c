#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


struct medlemsinfo {
  char fornavn   [250]; // alle navn bortsett fra etternavn
  char etternavn [100]; // det siste navnet
  int  pub_key;         // 0 hvis medlem mangler offentlig noekkel
};

typedef struct medlemsinfo konto_t;

void les_data   (konto_t *klasseliste);
void skriv_data (konto_t *klasseliste);
void lese_og_skrive_eksempel();

int main() {

  konto_t klasseliste[200];

  lese_og_skrive_eksempel();
  les_data  (klasseliste);
  skriv_data(klasseliste);

  return 0;
}


void les_data   (konto_t *klasseliste) {

  // skriv kode  her
}

void skriv_data (konto_t *klasseliste) {

  // skriv kode her
}


void lese_og_skrive_eksempel() {

  /*
    Leser fra standard inngang, og
    skriver til standard utgang -- som cat(1)
    Introduserer:
    - getline(3)
  */

  char  *txt = NULL; // peker til lagerplass for innlest linje
  size_t len = 0;    // lengde på innlest linje

  while ( -1 != ( len=getline( &txt, &len, stdin ) ) )
    printf("%s", txt);

}
