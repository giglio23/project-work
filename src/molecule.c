#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "molecule.h"

/* =========================================================
 * FUNZIONI DI UTILITÀ
 * ========================================================= */

void init_molecule(Molecule *m) {
    m->atom_count = 0;
    m->bond_count = 0;
    m->next_id    = 0;
}

Atom *find_atom(Molecule *m, int id) {
    for (int i = 0; i < m->atom_count; i++) {
        if (m->atoms[i].id == id)
            return &m->atoms[i];
    }
    return NULL;
}

static int get_max_valence(const char *symbol) {
    if (strcmp(symbol, "H") == 0) return VALENCE_H;
    if (strcmp(symbol, "O") == 0) return VALENCE_O;
    if (strcmp(symbol, "C") == 0) return VALENCE_C;
    if (strcmp(symbol, "N") == 0) return VALENCE_N;
    return -1;
}

void print_molecule(Molecule *m) {
    printf("--- Molecola (%d atomi, %d legami) ---\n",
           m->atom_count, m->bond_count);
    for (int i = 0; i < m->atom_count; i++) {
        Atom *a = &m->atoms[i];
        printf("  Atomo [%d] %s  (valenza: %d/%d)\n",
               a->id, a->symbol, a->used_valence, a->max_valence);
    }
    for (int i = 0; i < m->bond_count; i++) {
        Bond *b = &m->bonds[i];
        printf("  Legame %d--%d  tipo: %d\n", b->id1, b->id2, b->bond_type);
    }
}

/* =========================================================
 * F1 — add_atom
 * ========================================================= */
int add_atom(Molecule *m, const char *symbol) {
    /* TODO: implementa questa funzione
     *
     * Passi:
     * 1. Controlla che m->atom_count < MAX_ATOMS
     * 2. Ottieni la valenza con get_max_valence(); se -1, simbolo sconosciuto → errore
     * 3. Riempi m->atoms[m->atom_count]:
     *      .id           = m->next_id
     *      .symbol       = copia di symbol (usa strncpy)
     *      .max_valence  = risultato di get_max_valence
     *      .used_valence = 0
     * 4. Incrementa m->atom_count e m->next_id
     * 5. Ritorna l'id assegnato
     */
    return -1; /* placeholder */
}

/* =========================================================
 * F2 — add_bond
 * ========================================================= */
int add_bond(Molecule *m, int id1, int id2, int bond_type) {
    /* TODO: implementa questa funzione
     *
     * Passi:
     * 1. Trova i due atomi con find_atom(); se uno è NULL → errore
     * 2. Verifica che non esista già un legame tra id1 e id2
     * 3. Controlla che:
     *      atom1->used_valence + bond_type <= atom1->max_valence
     *      atom2->used_valence + bond_type <= atom2->max_valence
     *    Se no → stampa errore e ritorna -1
     * 4. Aggiungi il Bond in m->bonds[m->bond_count], incrementa m->bond_count
     * 5. Aggiorna used_valence di entrambi gli atomi
     * 6. Ritorna 0
     */
    return -1; /* placeholder */
}

/* =========================================================
 * F3 — remove_atom
 * ========================================================= */
int remove_atom(Molecule *m, int id) {
    /* TODO: implementa questa funzione
     *
     * Passi:
     * 1. Trova l'indice dell'atomo; se non esiste → ritorna -1
     * 2. Scorri m->bonds: per ogni legame che coinvolge id,
     *    decrementa used_valence dell'altro atomo e
     *    compatta l'array (shift degli elementi successivi)
     * 3. Rimuovi l'atomo dall'array atoms con lo stesso shift
     * 4. Aggiorna m->atom_count e m->bond_count
     * 5. Ritorna 0
     */
    return -1; /* placeholder */
}

/* =========================================================
 * F4 — get_formula
 * ========================================================= */
void get_formula(Molecule *m, char *output) {
    /* TODO: implementa questa funzione
     *
     * Passi:
     * 1. Dichiara contatori: int cnt_C=0, cnt_H=0, cnt_N=0, cnt_O=0
     * 2. Scorri m->atoms e incrementa il contatore corrispondente
     * 3. Costruisci output in ordine alfabetico (C, H, N, O):
     *    - se contatore > 0: aggiungi il simbolo
     *    - se contatore > 1: aggiungi il numero (es. "2")
     *    - se contatore == 1: aggiungi solo il simbolo
     * 4. Usa sprintf + strcat su output
     */
    output[0] = '\0'; /* placeholder */
}

/* =========================================================
 * F5 — merge_molecules
 * ========================================================= */
Molecule merge_molecules(Molecule *a, int id_a, Molecule *b, int id_b, int bond_type) {
    /* TODO: implementa questa funzione
     *
     * Passi:
     * 1. init_molecule(&result)
     * 2. Copia atomi di 'a' in result con nuovi id da 0
     *    (tieni una mappa old_id → new_id per aggiornare i legami)
     * 3. Copia legami di 'a' aggiornando id1/id2 con la mappa
     * 4. Copia atomi di 'b' con offset = a->atom_count
     * 5. Copia legami di 'b' aggiornando id1/id2 con l'offset
     * 6. Trova i nuovi id di id_a e id_b e chiama add_bond()
     * 7. Ritorna result
     */
    Molecule result;
    init_molecule(&result);
    return result; /* placeholder */
}