/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrancoi <afrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:47:31 by afrancoi          #+#    #+#             */
/*   Updated: 2019/11/03 02:42:39 by afrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>

static void	ft_cd_err(char *msg, char *path)
{
	ft_putstr("cd: ");
	ft_putstr(msg);
	if (path)
		ft_putendl(path);
	else
		ft_putchar('\n');
}

static void	ft_err_dir(char *path)
{
	if (access(path, F_OK))
		ft_cd_err(ERR_ENOENT, path);
	else if (access(path, R_OK))
		ft_cd_err(ERR_EACCES, path);
	else
		ft_cd_err(ERR_ENOTDIR, path);
}

static int	ft_change_dir(char *path)
{
	char pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	if (!chdir(path))
	{
		ft_setenv("OLDPWD", pwd);
		getcwd(pwd, PATH_MAX);
		ft_setenv("PWD", pwd);
		return (1);
	}
	else
	{
		ft_err_dir(path);
		return (0);
	}
}

void		ft_builtin_cd(char **args)
{
	char	*path;

	path = NULL;
	if (!args[0])
	{
		if (!(path = ft_get_env("HOME")))
		{
			ft_cd_err(ERR_HOME_MISSING, NULL);
			return ;
		}
	}
	else if (*args[0] == '-')
	{
		if (!(path = ft_get_env("OLDPWD")))
		{
			ft_cd_err(ERR_OLDPWD_MISSING, NULL);
			return ;
		}
	}
	else
		path = args[0];
	if (!(ft_change_dir(path)))
		return ;
}
