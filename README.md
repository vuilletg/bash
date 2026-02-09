# Compte rendu TP Mini-Shell 

## Auteur
**Gaspard Vuillet**

## Fonctionnalités implémentées
### Fonctionnalités de base
- **Exécution de programmes** : Lancement de commandes simples.
- **Redirections** : Gestion des entrées/sorties avec `<` et `>` .
- **Gestion des erreurs** : Affichage de messages explicites sur la sortie d'erreur.
- **Tubes (Pipes)** : Gestion d'une séquence de deux commandes reliées par `|`.

### Fonctionnalités avancées
- **Arrière-plan (`&`)** : Exécution de tâches de fond sans attendre leur terminaison via la fonction `test_arriere_plan()`.
- **Nettoyage des zombies** : Utilisation du signal `SIGCHLD` pour ramasser les processus fils terminés en arrière-plan.
- **Signaux** : Gestion du `Ctrl+C` pour ne pas interrompre le shell lui-même.
- **Commande** : implémentation de la commande `cd` avec gestion des erreurs et affichage du dossier courant.
cd
## Bugs connus
- **Entrée/Sortie** : Le message `fgets: No child processes` s'affiche lors d'une sortie normale du shell si une commande a été exécutée auparavant.
- **Signaux** : Le `Ctrl+Z` suspend l'intégralité du shell au lieu de suspendre uniquement le processus en cours d'exécution.

## Instructions de compilation
1. ### Méthode 1:
- dans un terminal executez :```./reload_shell``` (script de compilation du code et execution)
2. ### Méthode 2: 
- executez: `make`
- executez: `./shell`

## Bonus
- le programe `loop.c` est une boucle infini (peut être utiliser pour verifier le comportement du shell) 

**!!compilation à effectuer separément car hors makefile!!**
