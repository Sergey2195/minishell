/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:58:10 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/10 19:01:23 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_info *s, t_cmd *cmd)
{
	char	buf[999];

	(void)cmd;
	(void)s;
	if (!getcwd(buf, 999))
		return (-1);
	else
	{
		printf("%s\n", buf);
		s->ret = 0;
	}
	return (0);
}

void	check_echo_flag(char **av, int *i, int *flag)
{
	int	j;

	*i = 1;
	if (av[1] && av[*i][0] == '-' && av[*i][1] == 'n')
	{
		while (av[*i][0] == '-' && av[*i][1] == 'n')
		{
			j = 1;
			while (av[1][j] != '\0')
			{
				if (av[1][j] != 'n')
					return ;
				j++;
			}
			(*i)++;
		}
		*flag = 1;
	}
}

void	ft_echo(t_info *s, t_cmd *cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	check_echo_flag(cmd->av, &i, &flag);
	while (i < cmd->ac)
	{
		write(1, cmd->av[i], ft_strlen(cmd->av[i]));
		if (i < cmd->ac - 1)
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	s->ret = 0;
}

int	change_dir(t_info *s, char *path)
{
	char	*buf;
	int		ret;

	if (!ft_strncmp(path, "~", 1))
		buf = ft_strdup(find_env_val(s->env_head, "HOME"));
	else if (!ft_strncmp(path, "-", 1))
		buf = ft_strdup(find_env_val(s->env_head, "OLDPWD"));
	else
		buf = ft_strdup(path);
	if (!buf)
		exit(1);
	ret = chdir(buf);
	free(buf);
	return (ret);
}

int	ft_cd(t_info *s, t_cmd *cmd)
{
	char	pwd[999];

	(void)cmd;
	if (cmd->ac == 1)
		change_dir(s, "~");
	else if (change_dir(s, cmd->av[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd->av[1]);
		s->ret = 1;
	}
	else
	{
		getcwd(pwd, 999);
		update_env(s->env_head, "OLDPWD", find_env_val(s->env_head, "PWD"), 1);
		update_env(s->env_head, "PWD", pwd, 1);
		s->ret = 0;
	}
	return (0);
}