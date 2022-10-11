/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:26:02 by ekern             #+#    #+#             */
/*   Updated: 2022/10/11 20:26:49 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_re_input(t_info *info, int a, int i)
{

    int    fd;

    if (pipe(info->exe->fd) == -1)
        fc_error_tmp(1, "Problem with pipe\n");
    info->exe->pid_init = fork();
    if (info->exe->pid_init == -1)
        fc_error_tmp(1, "Problem with fork\n");
    
    fc_find_idx_file(info, "<", 2); // cette fonction permet de trouver le bon index pour le fichier
    fd = open(info->exe->cmds[info->idx_re][info->idx], O_RDONLY, 0777);
    if (fd == -1)    
        fc_error_tmp(1, "Problem with open\n");
    if (info->exe->pid_init == 0)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
            fc_error_tmp(1, "Problem with dup2\n");
        if (close(fd) == -1) // ce close n'est pas nécessaire
            fc_error_tmp(1, "Problem with close(fd)\n");
        info->idx = 0;
        info->exe->path = NULL;
        info->exe->path = fc_path_for_execve(info);
        //info->exe->cmds_execve = fc_create_left_str(info);
		info->exe->cmds_execve = info->exe->cmds[i];
		info->exe->cmds[0][1] = NULL;
        if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
            fc_error_tmp(1, "Problem with fc_execve_redir\n");
    }
    info->exe->buffer = malloc(sizeof(char) * 1000);
    if (read(fd, info->exe->buffer, 999) == -1)
        fc_error_tmp(1, "Problem with read\n");

    if (close(fd) == -1)
        fc_error_tmp(1, "Problem with close(fd)\n");

    if (waitpid(info->exe->pid_init, NULL, 0) == -1)
        fc_error_tmp(1, "Problem with waitpid\n");

    return (0);
}
