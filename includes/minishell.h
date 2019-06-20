/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 04:28:01 by afrancoi          #+#    #+#             */
/*   Updated: 2019/06/20 16:06:45 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


/*typedef struct	s_shell {
	char		**env;

}				t_shell;*/

char	**g_env;

/*
** Env
*/
char	**ft_copy_env(char **env);
char	*ft_get_env(char *name);
int		ft_setenv(char *name, char *value);
void	ft_display_env(void);
int		ft_unsetenv(char *name);

/*
** Builtins
*/
int		ft_check_builtins(char **cmds);

/*
** Input
*/
char	*read_input(void);

#endif
