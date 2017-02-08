/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 23:21:31 by sclolus           #+#    #+#             */
/*   Updated: 2017/02/07 22:38:04 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_exec_ast(t_btree *tree, char **env, char **path)
{
	if (((t_token*)tree->content)->type == TYPE_TOKEN_STATEMENT)
		return (ft_exec_statement(tree, env, path));
	else if (((t_token*)tree->content)->type == TYPE_TOKEN_OR)
		return (ft_exec_token_or(tree, env, path));
	else if (((t_token*)tree->content)->type == TYPE_TOKEN_AND)
		return (ft_exec_token_and(tree, env, path));
	else if (((t_token*)tree->content)->type == TYPE_TOKEN_SINGLE_AND)
		return (ft_exec_token_single_and(tree, env, path));
# if 0
	else if (((t_token*)tree->content)->type == TYPE_TOKEN_PIPE)
		return (ft_exec_token_pipe(tree, env, path));
	#endif
	return (0);
}
