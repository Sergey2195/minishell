/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:38:09 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 18:40:27 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_new_cmd(t_cmd *cmd, int cnt, char **new)
{
	int	i;
	int	j;

	if (!ft_calloc(cnt + 1, sizeof(char *), (void **)&new))
		exit(1);
	i = 0;
	j = 0;
	while (cmd->ac > i)
	{
		if (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
			i++;
		else
		{
			new[j] = ft_strdup(cmd->av[i]);
			if (!new[j])
				exit(1);
			j++;
		}
		i++;
	}
	new[cnt] = 0;
	return (new);
}

void	renewal_cmd(t_cmd *cmd)
{
	char	**new;
	int		cnt;
	int		i;

	i = 0;
	cnt = 0;
	while (cmd->ac > i)
	{
		if (cmd->av[i][0] == '<' || cmd->av[i][0] == '>')
			cnt++;
		i++;
	}
	if (cnt == 0)
		return ;
	cnt = cmd->ac - (cnt * 2);
	new = 0;
	new = make_new_cmd(cmd, cnt, new);
	free_2d(cmd->av);
	cmd->av = new;
	cmd->ac = cnt;
}

int		check_redirection(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	while (cmd->av[i])
	{
		if (cmd->av[i][0] == '>')
		{
			if (cmd->av[i][1] == '>')
				cmd->fd_out = open(cmd->av[i + 1], O_WRONLY
						| O_APPEND | O_CREAT, 0644);
			else
				cmd->fd_out = open(cmd->av[i + 1], O_WRONLY
						| O_TRUNC | O_CREAT, 0644);
		}
		if (cmd->av[i][0] == '<')
			cmd->fd_in = open(cmd->av[i + 1], O_RDONLY);
		i++;
	}
	if (cmd->fd_out == -1 || cmd->fd_in == -1)
		return (0);
	renewal_cmd(cmd);
	return (1);
}