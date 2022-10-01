/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:19:16 by ekern             #+#    #+#             */
/*   Updated: 2022/10/01 10:26:58 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
static void test(t_info *info)
{
	if (info->lex->pipes == true)
		printf("%d piped\n", info->lex->nbr_pipe);
	if (info->lex->sgl_quotes == true)
		printf("sgl quoted\n");
	if (info->lex->dbl_quotes == true)
		printf("dbl quoted\n");
	if (info->lex->re_append == true)
		printf("%d re appended\n", info->lex->nbr_re_append);
	if (info->lex->re_del == true)
		printf("%d re deled\n", info->lex->nbr_re_del);
	if (info->lex->re_input == true)
		printf("%d re inputed\n", info->lex->nbr_re_input);
	if (info->lex->re_output == true)
		printf("%d re outputed\n", info->lex->nbr_re_output);
	if (info->lex->variable == true)
		printf("%d variabled\n", info->lex->nbr_variable);
}
*/

void fc_print_list(t_info *info)
{
	t_quotes *temp;
	
	temp = info->quotes_list;
	while (temp)
	{
		printf("Type : %c, begin : %d, end : %d\n", temp->type, temp->begin, temp->end);
		temp = temp->next;
	}
	printf(" sgl quote : %d, dlb quote : %d\n", info->lex->nbr_pair_sgl_q, info->lex->nbr_pair_dbl_q);
}

int	fc_check_lex(t_info *info, int a)
{
	if (info->command_line[a + 1] == '\0')
	{
		info->lex->error = true;
		return (0);
	}
	if (info->command_line[a + 1] == ' ')
		a++;
	if (info->command_line[a + 1] == '|'
		|| info->command_line[a + 1] == '<'
		|| info->command_line[a + 1] == '>')
	{
		info->lex->error = true;
		return (0);
	}
	return (1);
}

void	fc_lexer(t_info *info)
{
	int	a;
	int	b;

	a = -1;
	while (info->command_line[++a] != '\0')
	{
		
		a = fc_lex_quotes(info, a);
		if (info->command_line[a] == '$')
			fc_lex_variables(info);
		if (info->command_line[a] == '|')
			if (fc_lex_pipes(info, a) == 0)
				return ;
		if (info->command_line[a] == '<' || info->command_line[a] == '>')
		{
			b = fc_lex_redirections(info, a);
			if (b == 0)
				return ;
			else if (b == 2)
				a++;
		}
//		if (info->command_line[a] == '\0')	// si stack overflow dans fc_lexer decommente ce "if"
//			break ;
	}
//	fc_print_list(info); // printer pour la liste des quotes
//	test(info); // permet de voir le nombre de meta chara
}
