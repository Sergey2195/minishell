/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:00:56 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:13:59 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_syntax_error(int cur_type, int next_type, int has_space)
{
	int	type;

	type = next_type;
	if (cur_type == -7 && next_type >= 8)
	{
		if (next_type == 8)
			type = -2;
		else if (next_type == 9)
			type = -3;
	}
	else if ((cur_type >= 8 || cur_type <= -2) && next_type >= 8)
	{
		type = check_deep_syntax_error(cur_type, next_type, has_space);
	}
	return (type);
}

int		check_deep_syntax_error(int cur_type, int next_type, int has_space)
{
	int	type;

	type = next_type;
	if (cur_type == 8 || cur_type == -2)
	{
		if (next_type == 8)
			type = -4;
		else if (next_type == 9)
			type = -3;
		else if (has_space)
			type = -2;
	}
	else if (cur_type == 9 || cur_type == -3)
	{
		if (next_type == 9)
			type = -5;
		else if (next_type == 8)
			type = -2;
		else if (has_space)
			type = -3;
	}
	return (type);
}

void	check_token_error(t_info *s)
{
	t_token	*token;
	char	**av;

	token = s->token_head;
	while (token)
	{
		if (token->type <= -1)
			return (return_quote_error(s, token));
		else if (token->type >= 4 && token->type <= 6)
		{
			if (!token->next || is_operator_error(token->next->type))
			{
				av = make_empty_av(1);
				add_cmd_back(&g_info.cmd_head, av, -6);
				free_token(g_info.token_head);
				return ;
			}
		}
		token = token->next;
	}
	parse_cmd(s, 0);
	free_token(g_info.token_head);
}

void	return_quote_error(t_info *s, t_token *token)
{
	int		type;

	type = token->type;
	if (token->next)
	{
		if (token->next->type <= -4)
			type = token->next->type;
	}
	make_cmd(token, 1, type, 0);
	free_token(s->token_head);
}