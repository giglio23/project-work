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
 *
 * Aggiunge un nuovo atomo alla molecola.
 * - Controlla che non si superi MAX_ATOMS
 * - Ricava la valenza massima dal simbolo chimico
 * - Assegna un ID univoco crescente (next_id)
 * Ritorna l'ID assegnato, oppure -1 in caso di errore.
 * ========================================================= */
int add_atom(Molecule *m, const char *symbol) {
    if (m->atom_count >= MAX_ATOMS) {
        fprintf(stderr, "Errore: numero massimo di atomi raggiunto.\n");
        return -1;
    }

    int valence = get_max_valence(symbol);
    if (valence == -1) {
        fprintf(stderr, "Errore: simbolo chimico '%s' non riconosciuto.\n", symbol);
        return -1;
    }

    Atom *a = &m->atoms[m->atom_count];
    a->id           = m->next_id;
    a->max_valence  = valence;
    a->used_valence = 0;
    strncpy(a->symbol, symbol, MAX_SYMBOL_LEN - 1);
    a->symbol[MAX_SYMBOL_LEN - 1] = '\0';

    m->atom_count++;
    m->next_id++;

    return a->id;
}

/* =========================================================
 * F2 — add_bond
 *
 * Aggiunge un legame tra due atomi esistenti.
 * - Verifica che entrambi gli ID esistano
 * - Verifica che il legame non esista già
 * - Verifica che la valenza di entrambi gli atomi
 *   non venga superata
 * Ritorna 0 in caso di successo, -1 in caso di errore.
 * ========================================================= */
int add_bond(Molecule *m, int id1, int id2, int bond_type) {
    Atom *a1 = find_atom(m, id1);
    Atom *a2 = find_atom(m, id2);

    if (a1 == NULL || a2 == NULL) {
        fprintf(stderr, "Errore: uno o entrambi gli ID (%d, %d) non esistono.\n", id1, id2);
        return -1;
    }

    /* Controlla se il legame esiste già */
    for (int i = 0; i < m->bond_count; i++) {
        Bond *b = &m->bonds[i];
        if ((b->id1 == id1 && b->id2 == id2) ||
            (b->id1 == id2 && b->id2 == id1)) {
            fprintf(stderr, "Errore: esiste già un legame tra %d e %d.\n", id1, id2);
            return -1;
        }
    }

    /* Controlla la valenza */
    if (a1->used_valence + bond_type > a1->max_valence) {
        fprintf(stderr, "Errore: valenza dell'atomo %s [%d] superata (%d/%d).\n",
                a1->symbol, a1->id, a1->used_valence, a1->max_valence);
        return -1;
    }
    if (a2->used_valence + bond_type > a2->max_valence) {
        fprintf(stderr, "Errore: valenza dell'atomo %s [%d] superata (%d/%d).\n",
                a2->symbol, a2->id, a2->used_valence, a2->max_valence);
        return -1;
    }

    /* Aggiunge il legame */
    Bond *bond  = &m->bonds[m->bond_count];
    bond->id1       = id1;
    bond->id2       = id2;
    bond->bond_type = bond_type;
    m->bond_count++;

    a1->used_valence += bond_type;
    a2->used_valence += bond_type;

    return 0;
}

/* =========================================================
 * F3 — remove_atom
 *
 * Rimuove un atomo e tutti i legami ad esso collegati.
 * - Per ogni legame rimosso, decrementa la used_valence
 *   dell'altro atomo coinvolto
 * - Compatta gli array atoms e bonds dopo la rimozione
 * Ritorna 0 in caso di successo, -1 se l'ID non esiste.
 * ========================================================= */
int remove_atom(Molecule *m, int id) {
    /* Trova l'indice dell'atomo */
    int atom_index = -1;
    for (int i = 0; i < m->atom_count; i++) {
        if (m->atoms[i].id == id) {
            atom_index = i;
            break;
        }
    }
    if (atom_index == -1) {
        fprintf(stderr, "Errore: atomo con ID %d non trovato.\n", id);
        return -1;
    }

    /* Rimuove i legami che coinvolgono questo atomo,
     * aggiornando la valenza dell'altro atomo */
    int i = 0;
    while (i < m->bond_count) {
        Bond *b = &m->bonds[i];
        if (b->id1 == id || b->id2 == id) {
            /* Decrementa la valenza dell'altro atomo */
            int other_id = (b->id1 == id) ? b->id2 : b->id1;
            Atom *other  = find_atom(m, other_id);
            if (other != NULL)
                other->used_valence -= b->bond_type;

            /* Compatta l'array bonds: sposta tutto indietro di 1 */
            for (int j = i; j < m->bond_count - 1; j++)
                m->bonds[j] = m->bonds[j + 1];
            m->bond_count--;
            /* Non incrementa i: il prossimo elemento è ora in posizione i */
        } else {
            i++;
        }
    }

    /* Compatta l'array atoms */
    for (int j = atom_index; j < m->atom_count - 1; j++)
        m->atoms[j] = m->atoms[j + 1];
    m->atom_count--;

    return 0;
}

/* =========================================================
 * F4 — get_formula
 *
 * Calcola la formula bruta della molecola.
 * - Conta quanti atomi ci sono per ogni elemento
 * - Scrive gli elementi in ordine alfabetico (C, H, N, O)
 * - Omette il numero se il contatore è 1 (es. "H2O" non "H2O1")
 * ========================================================= */
void get_formula(Molecule *m, char *output) {
    int cnt_C = 0, cnt_H = 0, cnt_N = 0, cnt_O = 0;

    for (int i = 0; i < m->atom_count; i++) {
        const char *s = m->atoms[i].symbol;
        if      (strcmp(s, "C") == 0) cnt_C++;
        else if (strcmp(s, "H") == 0) cnt_H++;
        else if (strcmp(s, "N") == 0) cnt_N++;
        else if (strcmp(s, "O") == 0) cnt_O++;
    }

    output[0] = '\0';
    char buf[16];

    if (cnt_C > 0) {
        if (cnt_C == 1) sprintf(buf, "C");
        else            sprintf(buf, "C%d", cnt_C);
        strcat(output, buf);
    }
    if (cnt_H > 0) {
        if (cnt_H == 1) sprintf(buf, "H");
        else            sprintf(buf, "H%d", cnt_H);
        strcat(output, buf);
    }
    if (cnt_N > 0) {
        if (cnt_N == 1) sprintf(buf, "N");
        else            sprintf(buf, "N%d", cnt_N);
        strcat(output, buf);
    }
    if (cnt_O > 0) {
        if (cnt_O == 1) sprintf(buf, "O");
        else            sprintf(buf, "O%d", cnt_O);
        strcat(output, buf);
    }
}

/* =========================================================
 * F5 — merge_molecules
 *
 * Unisce due molecole creando un legame tra id_a e id_b.
 * - Copia tutti gli atomi e legami di 'a' nella nuova molecola
 * - Copia tutti gli atomi e legami di 'b' con un offset sugli ID
 *   pari al numero di atomi di 'a', per evitare collisioni
 * - Aggiunge il legame tra i due atomi di giunzione
 * Ritorna la nuova molecola risultante.
 * ========================================================= */
Molecule merge_molecules(Molecule *a, int id_a, Molecule *b, int id_b, int bond_type) {
    Molecule result;
    init_molecule(&result);

    /* Copia gli atomi di 'a' mantenendo gli stessi ID */
    for (int i = 0; i < a->atom_count; i++) {
        result.atoms[result.atom_count] = a->atoms[i];
        result.atom_count++;
    }

    /* Copia i legami di 'a' (gli ID non cambiano) */
    for (int i = 0; i < a->bond_count; i++) {
        result.bonds[result.bond_count] = a->bonds[i];
        result.bond_count++;
    }

    /* Offset per rinumerare gli atomi di 'b':
     * usiamo il next_id di 'a' come base */
    int offset = a->next_id;

    /* Copia gli atomi di 'b' con ID rinumerati */
    for (int i = 0; i < b->atom_count; i++) {
        Atom new_atom    = b->atoms[i];
        new_atom.id     += offset;
        result.atoms[result.atom_count] = new_atom;
        result.atom_count++;
    }

    /* Copia i legami di 'b' aggiornando gli ID con l'offset */
    for (int i = 0; i < b->bond_count; i++) {
        Bond new_bond    = b->bonds[i];
        new_bond.id1    += offset;
        new_bond.id2    += offset;
        result.bonds[result.bond_count] = new_bond;
        result.bond_count++;
    }

    /* Aggiorna next_id della molecola risultante */
    result.next_id = offset + b->next_id;

    /* Aggiunge il legame di giunzione tra id_a e (id_b + offset) */
    int new_id_b = id_b + offset;
    if (add_bond(&result, id_a, new_id_b, bond_type) == -1) {
        fprintf(stderr, "Errore: impossibile creare il legame di giunzione.\n");
    }

    return result;
}
