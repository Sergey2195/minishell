/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iannmari <iannmari@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:56:08 by iannmari          #+#    #+#             */
/*   Updated: 2022/06/12 11:57:08 by iannmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <errno.h>
# include <string.h>

# define DEL 127
# define CNTRLD 4
# define UP 4283163
# define DOWN 4348699

typedef struct s_path
{
	char			*path;
	struct s_path	*next;
}	t_path;

typedef struct s_cmd
{
	char			**av;
	int				ac;
	int				type;
	int				pip[2];
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
}					t_env;

typedef struct s_trms
{
	struct termios	term;
	struct termios	save;
	char			*cm;
	char			*ce;
}	t_trms;

typedef struct s_save
{
	char			*input;
	int				flag;
	struct s_save	*prev;
	struct s_save	*next;
}	t_save;

typedef struct s_keypos
{
	int				col;
	int				row;
}	t_keypos;

typedef struct s_info
{
	t_token			*token_head;
	t_env			*env_head;
	t_cmd			*cmd_head;
	t_path			*path_head;
	t_trms			term;
	t_save			*save_head;
	int				s_flag;
	char			*input;
	char			*input2;
	int				is_fork;
	int				ret;
	t_keypos		cur;
	t_keypos		max;
	t_keypos		start;
}	t_info;

t_info	g_info;

void	init_info(t_info *info);
void	*ft_memset(void *ptr, int val, size_t n);
void	sig(int signal);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	init_env(char **envp, t_info *info);
void	add_env_back(t_env **head, char *key, char *value, int flag);
t_env	*create_env(char *key, char *value, int flag);
int		ft_calloc(size_t n, size_t size, void **ret);
void	update_env(t_env *head, char *key, char *value, int flag);
int		ft_strcmp(char *s1, char *s2);
t_env	*find_env(t_env *head, char *key);
char	*ft_strdup(const char *s1);
int		term_loop(t_info *s);
void	start(t_info *info);
void	init_terminal(t_info *s);
void	set_cursor_windows(t_info *s);
void	set_cursor(int *col, int *row);
int		ft_atoi(const char *str);
void	init_set_cursor(char buf[255], int *read_ret, int *i, int *flag);
int		get_nbr_len(int n);
void	key(t_info *s, int keycode);
void	end_of_file(t_info *s, char *input);
void	del_key(t_info *s);
int		ft_putchar(int c);
char	*del_char(char *str);
int		ft_isprint(int c);
void	print_element(t_info *s, char c);
char	*str_join_for_c(char *str, char c);
void	up(t_info *s);
void	down(t_info *s);
t_save	*push_front_save(char *input, t_save *old_head, int flag);
void	move_cursor(t_info *s);
void	clear_prompt(t_info *s);
void	reset_buffer(t_info *s);
void	tokenizer(int i, int count);
int		get_operator(char *c, int i);
int		get_len(char *input, int i);
int		make_token(t_info *s, int count, int i, int type);
int		find_end(t_info *s, int type, int i);
int		check_backslash_count(char *input, int i);
int		check_syntax_error(int cur_type, int next_type, int has_space);
int		check_deep_syntax_error(int cur_type, int next_type, int has_space);
t_token	*create_token(char *str, int type);
int		find_cur_type(t_token **head, int *has_space);
void	change_dollar_sign(int i);
int		check_key_len(char *str, int is_tokenizer);
char	*ft_itoa(int n);
char	*find_env_val(t_env *head, char *key);
char	*changed_str(char *origin, int start, int end, char *insert);
char	*ft_strjoin2(char *s1, char *s2);
void	check_token_error(t_info *s);
void	return_quote_error(t_info *s, t_token *token);
int		is_operator_error(int type);
char	**make_empty_av(int ac);
void	add_cmd_back(t_cmd **head, char **av, int type);
t_cmd	*create_cmd(char **av, int ac, int type, t_cmd *prev);
void	free_token(t_token *token);
void	make_cmd(t_token *start, int ac, int type, int i);
void	jump_space(char *str, int *i);
void	check_backslash_and_env(t_info *s, t_token *start);
void	check_backslash(t_token *token);
void	check_dollar_sign(t_info *s, t_token *token);
char	*check_env(t_info *s, t_token *token, char *value, int *i);
void	remove_space(t_token *token);
char	**ft_split(char const *s, char c);
void	parse_cmd(t_info *s, int ac);
void	executor(t_info *s, t_cmd *cmd, char **envp);
void	handle_syntax_error(t_info *s, t_cmd *cmd);
void	save_history(t_info *s);
int		check_redirection(t_cmd *cmd);
void	free_2d(char **array);
int		builtin(t_info *s, t_cmd *cmd);
void	set_pipe(t_cmd *cmd);
int		ft_pwd(t_info *s, t_cmd *cmd);
void	ft_echo(t_info *s, t_cmd *cmd);
void	print_env_all(t_env *env);
void	print_export(t_env *env_head);
void	ft_export(t_info *s, t_cmd *cmd, int i);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		check_key2(char *key);
void	error_export(t_info *s, t_cmd *cmd, int i);
int		parse_export(t_env *tmp, char *str);
void	ft_unset(t_info *s, t_cmd *cmd);
void	ft_exit(t_info *s, t_cmd *cmd);
void	make_path(t_cmd *cmd, char *str);
int		find_command(t_info *s, t_cmd *cmd);
void	free_path(t_path *path);
int		ft_cd(t_info *s, t_cmd *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_len(char *key, char *value, int has_equal);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strrchr(const char *s, int c);
void	execute_error(t_info *s, t_cmd *cmd, int type);
int		find_simple_cmd(t_cmd *cmd, int *err);
void	free_cmd(t_cmd *cmd);
#endif