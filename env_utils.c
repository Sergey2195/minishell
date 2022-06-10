/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:11:22 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 17:15:20 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_val(t_env *head, char *key)
{
	t_env	*env;

	env = head;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return ("");
}

int		check_key_len(char *str, int is_tokenizer)
{
	int len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == ' ')
			break ;
		if (get_operator(str, len) && is_tokenizer)
			break ;
		len++;
	}
	return (len);
}

void	change_dollar_sign(int i)
{
	int		len;
	char	*key;
	char	*temp;
	char	*value;
	char	*input;

	input = g_info.input2;
	len = check_key_len(&input[i + 1], TRUE);
	key = ft_substr(&input[i + 1], 0, len);
	if (!ft_strcmp(key, "?"))
	{
		temp = ft_itoa(g_info.ret);
		value = ft_strdup(temp);
		free(temp);
	}
	else
		value = ft_strdup(find_env_val(g_info.env_head, key));
	free(key);
	temp = changed_str(input, i, i + len, value);
	free(g_info.input2);
	g_info.input2 = ft_strdup(temp);
	free(temp);
}