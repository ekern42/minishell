/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:38 by ekern             #+#    #+#             */
/*   Updated: 2022/09/06 15:48:25 by ekern            ###   ########.fr       */
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
	fc_print_chainlist(envtemp, 's', 1);
}

static void	fc_init_lexer(t_lex_info *lex)
{
	lex->pipes = false;
	lex->sgl_quotes = false;
	lex->dlb_quotes = false;
	lex->variable = false;
	lex->re_append = false;
	lex->re_del = false;
	lex->re_input = false;
	lex->re_output = false;
}

int	fc_init(t_info *info, t_lex_info *lex, char **envp)
{
	fc_start_up();
	fc_envp_init(info, envp);
	fc_init_lexer(lex);	
	return (0);
}
