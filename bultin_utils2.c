/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:02:24 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:11:02 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_all(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->flag == TRUE)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
			else
				printf("%s=\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

void	ft_export(t_info *s, t_cmd *cmd, int i)
{
	t_env	tmp;

	s->ret = 0;
	if (cmd->ac == 1)
		print_export(s->env_head);
	else
	{
		while (++i < cmd->ac)
		{
			if ((cmd->av[i][0] != '_' && !ft_isalpha(cmd->av[i][0]))
				|| !check_key2(cmd->av[i]))
				error_export(s, cmd, i);
			else if (ft_strrchr(cmd->av[i], '=') == 0)
				update_env(s->env_head, cmd->av[i], 0, 0);
			else
			{
				if (parse_export(&tmp, cmd->av[i]) == 0)
					tmp.value = 0;
				update_env(s->env_head, tmp.key, tmp.value, 1);
				free(tmp.key);
				free(tmp.value);
			}
		}
	}
}