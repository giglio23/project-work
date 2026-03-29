#include <stdio.h>
#include "molecule.h"

int main(void) {

    char formula[64];

    /* =====================================================
     * Scenario 1: Costruzione di O2
     * Due ossigeni con doppio legame → formula attesa: "O2"
     * ===================================================== */
    printf("=== Scenario 1: O2 ===\n");

    Molecule o2;
    init_molecule(&o2);

    int id_O1 = add_atom(&o2, "O");
    int id_O2 = add_atom(&o2, "O");
    add_bond(&o2, id_O1, id_O2, BOND_DOUBLE);

    print_molecule(&o2);
    get_formula(&o2, formula);
    printf("Formula: %s  (attesa: O2)\n\n", formula);

    /* =====================================================
     * Scenario 2: Costruzione di H2O
     * Un ossigeno + due idrogeni → formula attesa: "H2O"
     * ===================================================== */
    printf("=== Scenario 2: H2O ===\n");

    Molecule h2o;
    init_molecule(&h2o);

    int id_O  = add_atom(&h2o, "O");
    int id_H1 = add_atom(&h2o, "H");
    int id_H2 = add_atom(&h2o, "H");
    add_bond(&h2o, id_O, id_H1, BOND_SINGLE);
    add_bond(&h2o, id_O, id_H2, BOND_SINGLE);

    print_molecule(&h2o);
    get_formula(&h2o, formula);
    printf("Formula: %s  (attesa: H2O)\n\n", formula);

    /* =====================================================
     * Scenario 3: Violazione di valenza su H2O
     * L'ossigeno ha già valenza 2/2 → il terzo legame
     * deve essere rifiutato con un messaggio di errore
     * ===================================================== */
    printf("=== Scenario 3: violazione valenza ===\n");

    int id_H3 = add_atom(&h2o, "H");
    int result = add_bond(&h2o, id_O, id_H3, BOND_SINGLE);
    if (result == -1)
        printf("Legame rifiutato correttamente: valenza dell'ossigeno già satura.\n\n");

    /* =====================================================
     * Scenario 4: H2O2 tramite merge_molecules
     * Unione di due molecole OH → formula attesa: "H2O2"
     * ===================================================== */
    printf("=== Scenario 4: H2O2 via merge ===\n");

    /* Prima molecola OH */
    Molecule oh_a;
    init_molecule(&oh_a);
    int id_Oa = add_atom(&oh_a, "O");
    int id_Ha = add_atom(&oh_a, "H");
    add_bond(&oh_a, id_Oa, id_Ha, BOND_SINGLE);

    /* Seconda molecola OH */
    Molecule oh_b;
    init_molecule(&oh_b);
    int id_Ob = add_atom(&oh_b, "O");
    int id_Hb = add_atom(&oh_b, "H");
    add_bond(&oh_b, id_Ob, id_Hb, BOND_SINGLE);

    /* Fusione tramite legame O-O */
    Molecule h2o2 = merge_molecules(&oh_a, id_Oa, &oh_b, id_Ob, BOND_SINGLE);

    print_molecule(&h2o2);
    get_formula(&h2o2, formula);
    printf("Formula: %s  (attesa: H2O2)\n\n", formula);

    /* =====================================================
     * Scenario 5: Rimozione di un H da H2O2
     * Formula attesa dopo rimozione: "HO2"
     * ===================================================== */
    printf("=== Scenario 5: rimozione atomo da H2O2 ===\n");

    /* id_Ha appartiene alla molecola oh_a, il cui next_id era 2.
     * In h2o2 gli atomi di oh_b sono stati rinumerati con offset=2,
     * quindi l'H di oh_b ha id = id_Hb + 2 = 3.
     * Rimuoviamo l'H originale di oh_a, che ha ancora id_Ha = 1. */
    remove_atom(&h2o2, id_Ha);

    print_molecule(&h2o2);
    get_formula(&h2o2, formula);
    printf("Formula: %s  (attesa: HO2)\n\n", formula);

    return 0;
}
