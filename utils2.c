/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:14:56 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 17:07:19 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator(char *c, int i)
{
	if (c[i] == ' ')
		return (1);
	if (c[i] == '\'')
		return (2);
	if (c[i] == '\"')
		return (3);
	if (c[i] == '<')
		return (4);
	if (c[i] == '>')
	{
		if (c[i + 1] == '>')
			return (6);
		else
			return (5);
	}
	if (c[i] == ';')
		return (9);
	if (c[i] == '|')
		return (8);
	if (c[i] == '\\')
		return (7);
	if (c[i] == '$')
		return (10);
	return (0);
}

int		find_end(t_info *s, int type, int i)
{
	int		len;
	char	*input;

	len = 1;
	input = s->input2;
	while (input[i])
	{
		if (type == 2 && input[i] == '\'')
			return (len);
		if (type == 3 && input[i] == '\"')
		{
			if (input[i - 1] != '\\')
				return (len);
			else if (i >= 2)
			{
				if (!(check_backslash_count(input, i) % 2))
					return (len);
			}
		}
		len++;
		i++;
	}
	return (0);
}

int		check_backslash_count(char *input, int i)
{
	int	count;

	count = 0;
	i--;
	while (i >= 0)
	{
		if (input[i] != '\\')
			break ;
		i--;
		count++;
	}
	return (count);
}

t_token	*create_token(char *str, int type)
{
	t_token *token;

	if (!ft_calloc(1, sizeof(t_token), (void *)&token))
		exit(1);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = 0;
	return (token);
}

int		find_cur_type(t_token **head, int *has_space)
{
	t_token	*token;
	int		type;

	token = *head;
	type = token->type;
	while (token)
	{
		if (token->type != 1)
			type = token->type;
		else
			*has_space = TRUE;
		token = token->next;
	}
	return (type);
}