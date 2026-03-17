#include <stdio.h>
#include "molecule.h"

int main(void) {

    /* =====================================================
     * Scenario 1: Costruzione di O2
     * Due ossigeni con doppio legame → formula attesa: "O2"
     * ===================================================== */
    printf("=== Scenario 1: O2 ===\n");
    Molecule o2;
    init_molecule(&o2);

    /* TODO: aggiungi due atomi O e un legame doppio tra loro
     *
     *   int id1 = add_atom(&o2, "O");
     *   int id2 = add_atom(&o2, "O");
     *   add_bond(&o2, id1, id2, BOND_DOUBLE);
     */

    char formula[64];
    get_formula(&o2, formula);
    printf("Formula: %s (attesa: O2)\n\n", formula);

    /* =====================================================
     * Scenario 2: Costruzione di H2O
     * Un ossigeno + due idrogeni → formula attesa: "H2O"
     * ===================================================== */
    printf("=== Scenario 2: H2O ===\n");
    Molecule h2o;
    init_molecule(&h2o);

    /* TODO: aggiungi O, H, H e i due legami O-H
     *
     *   int id_O  = add_atom(&h2o, "O");
     *   int id_H1 = add_atom(&h2o, "H");
     *   int id_H2 = add_atom(&h2o, "H");
     *   add_bond(&h2o, id_O, id_H1, BOND_SINGLE);
     *   add_bond(&h2o, id_O, id_H2, BOND_SINGLE);
     */

    get_formula(&h2o, formula);
    printf("Formula: %s (attesa: H2O)\n\n", formula);

    /* =====================================================
     * Scenario 3: Violazione di valenza su H2O
     * Tentativo di aggiungere un terzo legame all'ossigeno
     * → il sistema deve rifiutarlo con un messaggio di errore
     * ===================================================== */
    printf("=== Scenario 3: violazione valenza ===\n");

    /* TODO: aggiungi un terzo atomo H e tenta di legarlo all'ossigeno
     *
     *   int id_H3 = add_atom(&h2o, "H");
     *   int result = add_bond(&h2o, id_O, id_H3, BOND_SINGLE);
     *   if (result == -1)
     *       printf("Errore correttamente segnalato.\n");
     */

    printf("\n");

    /* =====================================================
     * Scenario 4: H2O2 tramite merge_molecules
     * Unione di due molecole OH → formula attesa: "H2O2"
     * ===================================================== */
    printf("=== Scenario 4: H2O2 via merge ===\n");
    Molecule oh_a, oh_b;
    init_molecule(&oh_a);
    init_molecule(&oh_b);

    /* TODO: costruisci due molecole OH (O + H con legame singolo)
     *       poi uniscile tramite legame O-O
     *
     *   int id_Oa = add_atom(&oh_a, "O");
     *   int id_Ha = add_atom(&oh_a, "H");
     *   add_bond(&oh_a, id_Oa, id_Ha, BOND_SINGLE);
     *
     *   int id_Ob = add_atom(&oh_b, "O");
     *   int id_Hb = add_atom(&oh_b, "H");
     *   add_bond(&oh_b, id_Ob, id_Hb, BOND_SINGLE);
     *
     *   Molecule h2o2 = merge_molecules(&oh_a, id_Oa, &oh_b, id_Ob, BOND_SINGLE);
     *   get_formula(&h2o2, formula);
     *   printf("Formula: %s (attesa: H2O2)\n", formula);
     */

    printf("\n");

    /* =====================================================
     * Scenario 5: Rimozione di un H da H2O2
     * Formula attesa dopo rimozione: "HO2"
     * ===================================================== */
    printf("=== Scenario 5: rimozione atomo da H2O2 ===\n");

    /* TODO: rimuovi uno degli H da h2o2 e stampa la formula
     *
     *   remove_atom(&h2o2, id_Ha);   // oppure id_Hb rinumerato
     *   get_formula(&h2o2, formula);
     *   printf("Formula: %s (attesa: HO2)\n", formula);
     */

    printf("\n");
    return 0;
}