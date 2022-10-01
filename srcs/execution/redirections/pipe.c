/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:36:10 by angelo            #+#    #+#             */
/*   Updated: 2022/09/27 18:12:12 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Donc à gauche du pipe
int	fc_stdin_to_stdout(t_info *info)
{
	if (dup2(info->exe->fd[1], STDOUT_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - info->exe->fd[1], STDOUT_FILENO\n");
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close - fd[0]- fc_stdin_to_stdout\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close - fd[1]- fc_stdin_to_stdout\n");
	return (0);
}

// Donc à droite du pipe
int	fc_stdout_to_stdin(t_info *info)
{
	if (dup2(info->exe->fd[0], STDIN_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - info->exe->fd[0], STDIN_FILENO\n");
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close - fd[0] - fc_stdout_to_stdin\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close - fd[1]- fc_stdout_to_stdin\n");
	return (0);
}

/*
-	la fonction pipe me permet de créer un "tuyau", cad une entrée et une sortie.
	Elle me permet donc d'utiliser 2 files descriptor (fd[2]). Exemple : ls -l | wc -l
	- fd[0] : me permet de lire (read from), cad que la sortie de la commande, ici ls -l,
	est l'entrée du pipe.
	- fd[1] : me permet d'écrire (write the datas). Le pipe a mnt qqch à l'intérieur et il va pouvoir 
	sortir qqch. Ds notre exemple, ça veut dire qu'il va compter le nbr de ligne contenu ds "ls -l"

-	le fait d'utiliser la fonction pipe avant le fork permet au fork
	d'hériter (être copier dans info->pid_init) des files descriptor
	-	Ceci implique de gérer les fd dans chaque processus (enfant(s) et parent),
		cad de les ouvrir ou de les fermer en fonction de mes besoins

VIDéO: 
Exemple : ping -c 3 google.com | grep tty
je prends la sortie de ping en utilisant le pipe pour déplacer la sortie de la commande ping 
vers l'entrée de la commande grep.

Evidémment, je ne peux pas utiliser une commande pour le pipe, même si il ne fallait pas le coder soi-même.
Pour faire cela, on utilise les fd. Je dois bien comprendre que c'est une autre logique, un autre paradigme.

ping envoie un stdout au pipe '|', et pas au terminal comme dans une situation sans pipe. C'est donc pour cela
qu'on ne voit pas la commande ping dans le terminal ! OK, mais comment grep sait qu'il doit prendre
comme input la commande ping ? C'est parce que le standard input (stdin) de grep est "set" par le pipe. Illustration :
"ping" -c 3 google.com	|		"grep" tty
"stdout"			   pipe		"stdin"

A partir de là j'ai toutes les connaissances nécessaires :
1) Je sais comment créer un pipe
2) Je sais comment je sais comment exécuter un programme (cad une commande) grâce à la fonction execve
3) Je sais comment rediriger un input et un output (vidéo "redirecting standard output in C")

Les étapes :
1) je dois créer le processus principal
2) ensuite je dois créer un autre processus pour exécuter ma commande 
Note de moi : 	exceve le fait automatique. Je dois donc créer un autre fork, peut-être, pour les builtins...
				Question ? dois-je créer un nouveau processus dans le processus enfant de processus init ?
3) ensuite je dois créer un autre processus pour grep
Donc au total je vais avoir 3 processus : main, le point 2 et le point 3
4) ensuite gérer correctement les input et les output des deux commandes (cad stdin et stdout ; from ping to grep) 

là on est à la 8:20, et on commence à coder

avec seulement un pipe, je fais tout dans le processus enfant de processus init. 

regarder la min 11 pour utiliser dup2 pour gérer la redirection. L'intérêt de dup2 par rapport à dup est 
qu'avec dup2 je peux mettre la redirection et pas uniquement le fd (comme avec dup).
ensuite je dois fermer les deux fd. Sur ce dernier point, il faut penser que dup duplique les fd, alors même
que la fonction pipe en créees.

ensuite en refait un fork pour la deuxième commande. Rappelons-nous que que la première commande se trouve dans 
le processus enfant du processus init.
*/

