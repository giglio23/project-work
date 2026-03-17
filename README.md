# MoleculeGraph

Progetto per il modulo di **Linguaggio C** — ITS A.A. 2025/2026.

Implementazione di un sistema di rappresentazione e manipolazione di molecole chimiche tramite grafi in C.

## Struttura del progetto

```
project-work/
├── src/
│   ├── main.c       # Programma principale con i 5 scenari di test
│   ├── molecule.c   # Implementazione delle funzioni F1–F5
│   └── molecule.h   # Definizione delle strutture dati
├── docs/
│   └── relazione.pdf  # (da aggiungere a fine progetto)
├── Makefile
├── README.md
└── .gitignore
```

## Compilazione ed esecuzione

Dalla root del progetto:

```bash
make
./moleculegraph
```

Per pulire il binario:

```bash
make clean
```

## Funzioni implementate

| ID | Firma | Descrizione |
|----|-------|-------------|
| F1 | `add_atom(m, symbol)` | Aggiunge un atomo alla molecola |
| F2 | `add_bond(m, id1, id2, bond_type)` | Aggiunge un legame, verifica la valenza |
| F3 | `remove_atom(m, id)` | Rimuove un atomo e i suoi legami |
| F4 | `get_formula(m, output)` | Calcola la formula bruta (es. "H2O") |
| F5 | `merge_molecules(a, id_a, b, id_b, type)` | Fonde due molecole |

## Scenari di test

1. Costruzione di **O2** (doppio legame O=O)
2. Costruzione di **H2O**
3. Tentativo di **violazione della valenza** dell'ossigeno in H2O
4. Costruzione di **H2O2** tramite `merge_molecules`
5. **Rimozione** di un H da H2O2 → formula risultante: HO2