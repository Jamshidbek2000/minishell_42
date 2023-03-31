/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:27:28 by zstenger          #+#    #+#             */
/*   Updated: 2023/03/31 11:45:08 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// cmd = "export"
// args is cmd_args from table
void	export(t_shell *shell, char *cmd, char **args)
{
	int	i;

	if (ft_strcmp(cmd, "export") == TRUE && args[1] == NULL
		&& shell->print == TRUE)
		print_export(shell);
	else if (ft_strcmp(cmd, "export") == TRUE && args[1] != NULL
		&& shell->exec_on_pipe == FALSE)
	{
		i = 0;
		while (args[i] != NULL)
		{
			if (is_valid_export(shell, args[i], i) == FALSE)
				do_not_export(shell, args, i);
			else if (ft_pf_strchr(args[i], '=') != NULL)
				export_new_variables(shell, args);
			i++;
		}
	}
}

bool	is_valid_export(t_shell *shell, char *args, int i)
{
	if (args[0] == '=' || ft_strlen(args) == 0)
		return (false);
	return (true);
}

void	do_not_export(t_shell *shell, char **args, int i)
{
	shell->exit_code = 1;
	if (shell->print == TRUE)
		p_err("%s%s: `%s': %s\n", SHELL, args[0], args[i], NVI);
}

// args is cmd_args from table
void	export_new_variables(t_shell *shell, char **args)
{
	int		i;
	char	**split_var;

	i = 1;
	while (args[i] != NULL)
	{
		split_var = ft_split(args[i], '=');
		if (find_env_var(shell->env_head, split_var[0]) == NULL)
			add_new_variable(shell, args[i]);
		else
			replace_var_content(shell, args[i], split_var[0]);
		free_char_array(split_var);
		i++;
	}
}

void	replace_var_content(t_shell *shell, char *str, char *var)
{
	t_env	*curr;

	curr = shell->env_head;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->var_name, var) == 1)
		{
			free(curr->content);
			curr->content = get_env_content(str, var);
		}
		curr = curr->next;
	}
}

// str is one arg from cmd_args
// ex. export a=b c= d
// it can be "a=b" || "c=" || d
void	add_new_variable(t_shell *shell, char *str)
{
	t_env	*new;

	new = init_env_node(str);
	add_back_env_node(shell->env_head, new);
}

void	print_export(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env_head;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->var_name, "TERM") == TRUE
			&& shell->color_codes == FALSE)
			;
		else if (curr->content == NULL)
			printf("declare -x %s\n", curr->var_name);
		else if (curr->content != NULL && curr->content[0] == ' '
				&& ft_strlen(curr->content) == 1)
			printf("declare -x %s=\"\"\n", curr->var_name);
		else
			printf("declare -x %s=\"%s\"\n", curr->var_name, curr->content);
		curr = curr->next;
	}
}
