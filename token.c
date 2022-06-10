/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:05:07 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 17:22:38 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_str(char *str, int type)
{
	int	i;

	if (type == 2 || type == 3)
		str[ft_strlen(str) - 1] = '\0';
	else if (type == 7)
	{
		i = 0;
		str[i] = str[i + 1];
		str[i + 1] = '\0';
	}
	return (str);
}

void	add_token_back(t_token **head, char *str, int type)
{
	t_token *token;
	int		token_type;
	int		cur_type;
	int		has_space;

	str = trim_str(str, type);
	has_space = FALSE;
	if (*head == NULL)
	{
		token_type = check_syntax_error(-7, type, has_space);
		*head = create_token(str, token_type);
	}
	else
	{
		token = *head;
		while (token->next)
			token = token->next;
		cur_type = find_cur_type(head, &has_space);
		token_type = check_syntax_error(cur_type, type, has_space);
		token->next = create_token(str, token_type);
	}
}

int		make_token(t_info *s, int count, int i, int type)
{
	char	*token_str;
	int		j;

	if (!ft_calloc(count + 1, sizeof(char), (void *)&token_str))
		exit(1);
	j = 0;
	while (j < count)
		token_str[j++] = s->input2[i++];
	token_str[j] = '\0';
	add_token_back(&s->token_head, token_str, type);
	free(token_str);
	return (i);
}

int		get_len(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i])
	{
		if (get_operator(input, i))
			break ;
		i++;
		len++;
	}
	return (len);
}

void	tokenizer(int i, int count)
{
	int	type;

	if (!g_info.input2)
		return ;
	while (g_info.input2[i])
	{
		count = 1;
		type = get_operator(g_info.input2, i);
		if (!type)
			count = get_len(g_info.input2, i);
		else if (type == 6 || type == 7)
			count = 2;
		else if (type == 10)
		{
			change_dollar_sign(i);
			continue ;
		}
		else if (type == 2 || type == 3)
			if (!(count = find_end(&g_info, type, ++i)))
			{
				i = make_token(&g_info, 1, i - 1, -1);
				break ;
			}
		i = make_token(&g_info, count, i, type);
	}
	check_token_error(&g_info);
}