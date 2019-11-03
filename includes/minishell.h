/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 04:28:01 by afrancoi          #+#    #+#             */
/*   Updated: 2019/11/03 03:01:43 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_HOME_MISSING "Env \"HOME\" is not defined, no enough arguments."
# define ERR_OLDPWD_MISSING "Env \"OLDPWD\" is not defined, cannot use \'-\'."
# define ERR_EACCES "permission denied: "
# define ERR_ENOTDIR "not a directory: "
# define ERR_ENOENT "no such file or directory: "

char	**g_env;

/*
** Env
*/
char	**ft_copy_env(char **env);
char	*ft_get_env(char *name);
int		ft_get_i_env(char *name);
int		ft_get_size_env(void);
int		ft_setenv(char *name, char *value);
void	ft_display_env(void);
int		ft_unsetenv(char *name);

/*
** Builtins
*/
int		ft_check_builtins(char **cmds);
void	ft_builtin_cd(char **args);

/*
** Input
*/
char	*read_input(void);
char	*parse_tilt(char *input, int i);
char	*parse_env(char *input, int i);

/*
** Exec
*/
int		ft_searchbin(char **cmds);

#endif
