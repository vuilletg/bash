# Compte rendu TP Mini-Shell 

## Auteur
- **Gaspard Vuillet**

## Fonctionnalités implémentées
### Fonctionnalités de base
- [x] **Exécution de programmes** : Lancement de commandes simples.
- [x] **Redirections** : Gestion des entrées/sorties avec `<` et `>` .
- [x] **Gestion des erreurs** : Affichage de messages explicites sur la sortie d'erreur.
- [x] **Tubes (Pipes)** : Gestion d'une séquence de deux commandes reliées par `|`.

### Fonctionnalités avancées
- [x] **Arrière-plan (`&`)** : Exécution de tâches de fond sans attendre leur terminaison via la fonction `test_arriere_plan()`.
- [x] **Nettoyage des zombies** : Utilisation du signal `SIGCHLD` pour ramasser les processus fils terminés en arrière-plan.
- [x] **Signaux** : Gestion du `Ctrl+C` pour ne pas interrompre le shell lui-même.

## Bugs connus
- **commande**: certaines commandes indisponibles: ex cd;
- **Entrée/Sortie** : Le message `fgets: No child processes` s'affiche lors d'une sortie normale du shell si une commande a été exécutée auparavant.
- **Signaux** : Le `Ctrl+Z` suspend l'intégralité du shell au lieu de suspendre uniquement le processus en cours d'exécution.

## Instructions de compilation
Le code source est conçu pour être compilé sur les machines de l'UFR.
1. ### methode 1:
- dans un terminal executez :```./reload_shell``` (script de compilation du code et execution)
2. ### methode 2: 
- executez: `make`
- executez: `./shell`

### Bonus
le programe `loop.c` est une boucle infini (peu etre utiliser pour verifier le comportement du shell face à des )
