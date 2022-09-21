/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:38 by ekern             #+#    #+#             */
/*   Updated: 2022/09/21 12:00:49 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fc_start_up(void)
{
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-----------MINISHELL-----------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
}

static void	fc_envp_init(t_info *info, char **envp)
{
	t_list	*envtemp;
	int		a;

	a = 0;
	envtemp = ft_lstnew(envp[a]);
	while (envp[++a] != NULL)
		ft_lstadd_back(&envtemp, ft_lstnew(envp[a]));
	info->envp = envtemp;
}

void	fc_init_lexer(t_info *info)
{
	info->lex->pipes = false;
	info->lex->nbr_pipe = 0;
	info->lex->sgl_quotes = false;
	info->lex->nbr_pair_sgl_q = 0;
	info->lex->dbl_quotes = false;
	info->lex->nbr_pair_dbl_q = 0;
	info->lex->variable = false;
	info->lex->nbr_variable = 0;
	info->lex->re_append = false;
	info->lex->nbr_re_append = 0;
	info->lex->re_del = false;
	info->lex->nbr_re_del = 0;
	info->lex->re_input = false;
	info->lex->nbr_re_input = 0;
	info->lex->re_output = false;
	info->lex->nbr_re_output = 0;
	info->lex->error = false;
}

int	fc_init(t_info *info, t_lex_info *lex, char **envp)
{
	fc_start_up();
	fc_envp_init(info, envp);
	info->lex = lex;
	return (0);
}
