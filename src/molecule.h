#ifndef MOLECULE_H
#define MOLECULE_H

/* --- Costanti --- */
#define MAX_ATOMS      64
#define MAX_SYMBOL_LEN  4

/* Tipi di legame */
#define BOND_SINGLE    1
#define BOND_DOUBLE    2
#define BOND_TRIPLE    3

/* Valenze massime per elemento */
#define VALENCE_H      1
#define VALENCE_O      2
#define VALENCE_C      4
#define VALENCE_N      3

/* --- Struttura: nodo del grafo (atomo) --- */
typedef struct {
    int  id;                     /* Identificatore univoco */
    char symbol[MAX_SYMBOL_LEN]; /* Simbolo chimico: "H", "O", "C", "N" */
    int  max_valence;            /* Valenza massima dell'elemento */
    int  used_valence;           /* Valenza attualmente occupata */
} Atom;

/* --- Struttura: arco del grafo (legame) --- */
typedef struct {
    int id1;       /* ID del primo atomo */
    int id2;       /* ID del secondo atomo */
    int bond_type; /* 1=singolo, 2=doppio, 3=triplo */
} Bond;

/* --- Struttura principale: grafo molecola --- */
typedef struct {
    Atom atoms[MAX_ATOMS];              /* Array di atomi (nodi) */
    Bond bonds[MAX_ATOMS * MAX_ATOMS];  /* Array di legami (archi) */
    int  atom_count;                    /* Numero di atomi presenti */
    int  bond_count;                    /* Numero di legami presenti */
    int  next_id;                       /* Prossimo ID da assegnare */
} Molecule;

/* --- Prototipi delle funzioni --- */

/* F1 - Aggiunge un atomo. Ritorna l'ID assegnato, -1 in caso di errore. */
int add_atom(Molecule *m, const char *symbol);

/* F2 - Aggiunge un legame. Ritorna 0 ok, -1 se valenza violata o ID non esistono. */
int add_bond(Molecule *m, int id1, int id2, int bond_type);

/* F3 - Rimuove un atomo e tutti i suoi legami. Ritorna 0 ok, -1 se ID non esiste. */
int remove_atom(Molecule *m, int id);

/* F4 - Scrive la formula bruta in output (es. "H2O"). */
void get_formula(Molecule *m, char *output);

/* F5 - Fonde due molecole con un legame tra id_a e id_b. Ritorna la nuova molecola. */
Molecule merge_molecules(Molecule *a, int id_a, Molecule *b, int id_b, int bond_type);

/* --- Funzioni di utilità --- */
void  init_molecule(Molecule *m);
void  print_molecule(Molecule *m);
Atom *find_atom(Molecule *m, int id);

#endif /* MOLECULE_H */