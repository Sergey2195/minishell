/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:04:54 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:13:02 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **array)
{
	char	**temp;
	int		i;

	temp = array;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

char	*removed_space(char *str)
{
	char	**strs;
	char	*result;
	char	*temp;
	char	*temp2;
	int		i;

	strs = ft_split(str, ' ');
	i = 0;
	result = 0;
	temp = 0;
	if (!str)
		return (result);
	while (strs[i])
	{
		if (i != 0)
			temp = ft_strjoin2(result, " ");
		temp2 = ft_strjoin2(temp, strs[i]);
		free(result);
		result = ft_strdup(temp2);
		free(temp);
		free(temp2);
		i++;
	}
	free_2d(strs);
	return (result);
}

void	remove_space(t_token *token)
{
	char	*temp;

	while (token && token->type != 9 && token->type != 8)
	{
		if (token->type == 0)
		{
			temp = removed_space(token->str);
			free(token->str);
			if (temp)
			{
				token->str = ft_strdup(temp);
				free(temp);
			}
			else
				token->str = 0;
		}
		token = token->next;
	}
}

void	parse_cmd(t_info *s, int ac)
{
	t_token	*token;
	t_token *start;
	int		type;

	token = s->token_head;
	start = s->token_head;
	type = 0;
	while (token)
	{
		ac++;
		if (token->type >= 8 || !token->next)
		{
			if (token->type == 1 || token->type >= 8)
				ac--;
			make_cmd(start, ac, type, 0);
			if (token->type >= 8)
				type = token->type;
			ac = 0;
			start = token->next;
		}
		else if (token->type == 1)
			ac--;
		token = token->next;
	}
}
