
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "shell-utils.h"

#define INPUT_BUFFER_SIZE 2048
#define MAX_TOKENS 256
void wait_handler(int sig){
    waitpid(-1, NULL,WNOHANG);
}
/**
 *  fonction perméttant d'executer une commande avec ou sans redirection
 * @param tokens le programe à executer avec ses paramètres
 */
void lancementCommande(char** tokens){
    char* red=trouve_redirection(tokens,"<");
    if(red != NULL){
        int fd = open(red, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "%s: Impossible d'ouvrir le fichier '%s': %s\n",tokens[0], red, strerror(errno));
            exit(1);
        }
        dup2(fd,0);
        close(fd);
    } else{
        red=trouve_redirection(tokens,">");
        if(red != NULL){
            int fd = open(red, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                fprintf(stderr, "%s: Impossible d'ouvrir le fichier '%s': %s\n",tokens[0], red, strerror(errno));
                exit(1);
            }
            dup2(fd,1);
            close(fd);
        }
    }
    /* On exécute la commande donné par l'utilisateur.
     * Son nom est dans le premier token (le premier mot tapé)
     * ses arguments (éventuels) seront les tokens suivants */
    execvp(tokens[0], tokens);

    /* On ne devrait jamais arriver là */
    fprintf(stderr, "Commande introuvable: %s\n", tokens[0]);
    exit(1);
}
int main() {
    /* Une variable pour sotcker les caractères tapés au clavier */
    char line[INPUT_BUFFER_SIZE + 1];
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGCHLD,wait_handler);
    /* Une variable qui pointera vers les données lues par fgets
     * Sauf problème (erreur, plus de données, ...), elle pointera en
     * fait vers la variable précédente (line) */
    char *data;

    /* Un tableau où les mots de l'utilisateur seront stockés
     * indépendamment les uns des autres
     * Note: un mot est une suite de lettres séparées par une ou plusieurs
     * espaces des autres mots.  */
    char *tokens[MAX_TOKENS + 1];
    /* variables entières pour compter le nombre de token */
    int nb_tokens;
    while (1) {
        printf("commande:");
        fflush(stdout);
        /* Récupération des données entrées au clavier */
        data = fgets(line, INPUT_BUFFER_SIZE, stdin);
        if (data == NULL) {
            /* Erreur ou fin de fichier : on quitte tout de suite */
            if (errno) {
                /* Une erreur: on affiche le message correspondant
                 * et on quitte en indiquant une erreur */
                perror("fgets");
                exit(1);
            } else {
                /* Sinon ça doit être une fin de fichier.
                 * On l'indique et on quitte normalement */
                fprintf(stderr, "EOF: exiting\n");
                exit(0);
            }
        } else {



            /* On vérifie que l'utilisateur n'a pas donné une ligne qui soit trop longue */
            if (strlen(data) == INPUT_BUFFER_SIZE - 1) {
                fprintf(stderr, "Input line too long: exiting\n");
            } else {



                /* On découpe la ligne en tokens (mots)
                 * Voir documentation dans shell-utils.h (avec des exemples) */
                nb_tokens = split_tokens(tokens, data, MAX_TOKENS);

                /* S'il y a trop de tokens, on abandonne */
                if (nb_tokens == MAX_TOKENS) {
                    fprintf(stderr, "Too many tokens: exiting\n");
                } else {



                    /* S'il n'y a pas de token, c'est que l'utilisateur n'a pas donné de
                     * commande. Il n'y a rien à faire. On arrête tout. */
                    if (nb_tokens <= 0) {
                        fprintf(stderr, "No tokens found: exiting\n");
                    } else {
                        if(strcmp(tokens[0],"exit")==0){ exit(0);}
                        int ap =0;
                        ap = test_arriere_plan(tokens,"&");
                        pid_t pid = fork();
                        if (pid == 0) {
                            signal(SIGINT, SIG_DFL);
                            signal(SIGTSTP, SIG_DFL);
                            char **sec;
                            if ((sec = trouve_tube(tokens,"|"))!=NULL){
                                int fd[2];
                                if(pipe(fd)==-1){
                                    perror("pipe");

                                    exit(1);
                                }
                                if(fork()==0){
                                    close(fd[0]);
                                    dup2(fd[1],1);
                                    lancementCommande(tokens);
                                }else{
                                    wait(NULL);
                                    close(fd[1]);
                                    dup2(fd[0],0);
                                    lancementCommande(sec);
                                }
                            }else{
                                lancementCommande(tokens);
                            }
                        } else{

                            if(ap==1) {
                                printf("[PID: %d]\n", pid);
                            }else{
                                waitpid(-1, NULL,  0);
                            }
                        }
                    }
                }
            }
        }
    }
}

