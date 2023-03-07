/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 08:46:37 by zstenger          #+#    #+#             */
/*   Updated: 2023/03/07 18:03:30 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//OWN HEADERS
# include "lexer.h"
# include "error.h"
# include "parser.h"
# include "colors.h"
# include "defines.h"
# include "cleanup.h"
# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "general_utils.h"
# include "../libft/includes/libft.h"

//READLINE
# if defined (__APPLE__)
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include </home/linuxbrew/.linuxbrew/opt/readline/include/readline/readline.h>
#  include </home/linuxbrew/.linuxbrew/opt/readline/include/readline/history.h>
# endif

//STANDARD HEADERS
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_env
{
	struct s_env	*next;
	char			*content;
	char			*var_name;
}	t_env;

typedef struct s_shell
{
	char	*prompt;
	t_env	*env_head;
	char	*user_name;
	char	**cmd_paths;
	char	*prev_prompt;
	char	*trimmed_prompt;
	char	*terminal_prompt;
}	t_shell;

//MAIN UTILS
int		cmd(t_shell *shell, char *str, int s);
bool	add_history_if(char *prompt, char *prev_prompt);

//SHELL_LOOP
void	read_line(t_shell *shell);
void	shell_loop(t_shell *shell);

//PROMPT
char	*get_curr_dir(void);
void	terminal_prompt(t_shell *shell);

//BUILTINS
void	builtins(t_shell *shell);

//BUILTIN ENV
void	env(t_shell *shell);
char	*get_path(char **env);
t_env	*init_env(char **env);
t_env	*init_env_node(char *str);
void	print_env_vars(t_env *head);
void	add_back_env_node(t_env	*head, t_env *new);

//BUILTIN EXPORT
void	export(t_shell *shell);
char	*get_variable(char *prompt);
void	print_export(t_shell *shell);
int		count_equal_sign(t_shell *shell);
void	export_new_variables(t_shell *shell);
void	add_new_variable(t_shell *shell, char *str);
char	*get_env_content(char *full, char *var_name);
void	replace_var_content(t_shell *shell, char *str, char *var);

//BUILTIN UNSET
void	unset(t_shell *shell);
void	unset_all_vars(t_shell *shell);
void	delete_env_var(t_env *head, t_env *del);
t_env	*find_env_var(t_env *head, char *var_name);

//BUILTIN PWD
void	pwd(t_shell *shell);

//BUILTIN EXIT
void	exit_code(t_shell *shell);
void	exit_shell(t_shell *shell);
int		is_wrong_command(char *s, char c);

//INITIALIZE
char	*extract_user(t_shell *shell);
void	init_shell(t_shell *shell, char **env);
void	init_missing_environment(t_shell *shell, char **env);

//CLEANUP TOOLS
void	free_env(t_env *head);
void	free_at_exit(t_shell *shell);
void	free_char_array(char **array);

//what does the philosopher pigeon say?
//TO BE OR NOT TO BE
int	ft_print_2d_char_array(char **array_2d);

#endif