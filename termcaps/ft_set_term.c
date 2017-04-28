/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 00:36:26 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 10:41:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int32_t		ft_unset_echo_mode(void)
{
	static struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

int32_t		ft_set_canonical_mode(void)
{
	static struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= ICANON;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

int32_t		ft_unset_echoctl_mode(void)
{
	static struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

int32_t		ft_set_term(void)
{
	static char				*name_term = "xterm-256color";
	static struct termios	term;

	if (tgetent(NULL, name_term) == -1)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	ft_set_insert();
	return (0);
}

int32_t		ft_unset_term(void)
{
	if (tcsetattr(0, TCSADRAIN, &shell->backup_term) == -1)
	{
		ft_error(1, (char*[])
	{"warning: Shell's parent term mode restoration failed"}, 1);
		exit(1);
	}
	return (1);
}
