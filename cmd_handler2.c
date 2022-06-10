/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:59:22 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:04:51 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env_space(t_info *s)
{
	t_token	*token;

	token = s->token_head;
	while (token)
	{
		if (!ft_strcmp(token->str, "echo"))
		{
			token = token->next;
			remove_space(token);
		}
		if (token)
			token = token->next;
	}
}

void	check_backslash_and_env(t_info *s, t_token *start)
{
	check_backslash(start);
	check_dollar_sign(s, start);
	check_env_space(s);
}

void	check_backslash(t_token *token)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\\' &&
		(token->str[i + 1] == '\\' || token->str[i + 1] == '\"'))
		{
			tmp = ft_substr(token->str, 0, i);
			tmp2 = ft_strjoin2(tmp, &token->str[i + 1]);
			free(token->str);
			token->str = ft_strdup(tmp2);
			free(tmp);
			free(tmp2);
		}
		i++;
	}
}

void	check_dollar_sign(t_info *s, t_token *token)
{
	int		i;
	char	*value;
	char	*temp;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			value = NULL;
			temp = check_env(s, token, value, &i);
			free(value);
			free(token->str);
			if (temp)
			{
				token->str = ft_strdup(temp);
				free(temp);
			}
		}
		if (!token->str || !token->str[i])
			break ;
		i++;
	}
}

char	*check_env(t_info *s, t_token *token, char *value, int *i)
{
	int		len;
	char	*key;
	char	*temp;

	len = 0;
	if (*i > 0 && token->str[*i - 1] == '\\')
		*i = *i - 1;
	else if (token->str[*i + 1])
	{
		len = check_key_len(&token->str[*i + 1], FALSE);
		key = ft_substr(&token->str[*i + 1], 0, len);
		if (!ft_strcmp(key, "?"))
		{
			temp = ft_itoa(s->ret);
			value = ft_strdup(temp);
			free(temp);
		}
		else
			value = ft_strdup(find_env_val(s->env_head, key));
		free(key);
	}
	return (changed_str(token->str, *i, *i + len, value));
}