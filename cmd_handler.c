/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:49:29 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:14:57 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_empty_av(int ac)
{
	int		i;
	char	**av;

	i = 0;
	if (!ft_calloc(ac + 1, sizeof(char *), (void **)&av))
		exit(1);
	while (i < ac)
		av[i++] = 0;
	return (av);
}

void	add_cmd_back(t_cmd **head, char **av, int type)
{
	t_cmd	*cmd;
	int		ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (*head == NULL)
		*head = create_cmd(av, ac, type, 0);
	else
	{
		cmd = *head;
		while (cmd->next)
			cmd = cmd->next;
		cmd->next = create_cmd(av, ac, type, cmd);
	}
}

t_cmd	*create_cmd(char **av, int ac, int type, t_cmd *prev)
{
	t_cmd	*cmd;

	if (av == NULL)
		return (NULL);
	if (!ft_calloc(1, sizeof(t_cmd), (void *)&cmd))
		exit(1);
	cmd->av = av;
	cmd->ac = ac;
	cmd->type = type;
	cmd->next = 0;
	cmd->prev = prev;
	return (cmd);
}

void	jump_space(char *str, int *i)
{
	if (str)
		*i = *i + 1;
}

void	make_cmd(t_token *start, int ac, int type, int i)
{
	char	**av;
	char	*tmp;

	av = make_empty_av(ac);
	while (start && i < ac && start->type != 8 && start->type != 9)
	{
		if (start->type == 1)
			jump_space(av[i], &i);
		else
		{
			if ((start->type >= 4 && start->type <= 6 && av[i]))
				i++;
			else if (start->type == 3 || start->type == 0)
				check_backslash_and_env(&g_info, start);
			tmp = ft_strjoin2(av[i], start->str);
			free(av[i]);
			av[i] = tmp;
		}
		start = start->next;
	}
	add_cmd_back(&g_info.cmd_head, av, type);
}