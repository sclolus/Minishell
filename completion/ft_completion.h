/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:06:31 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/08 03:18:57 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_COMPLETION_H__
# define __FT_COMPLETION_H__
# include "libft.h"

typedef struct  s_ltree	t_ltree;

struct	s_ltree
{
	char		c;
	t_ltree		*son;
	t_ltree		*alternative;
};


t_ltree	*ft_get_ltree_node(char c);
t_ltree	*ft_get_alternative_node(t_ltree *root, char c);
void	ft_ltree_add_word(t_ltree **root, char *word);
int32_t	ft_ltree_search(t_ltree *root, char *word);
t_ltree	*ft_get_ltree_dictionary_list(t_list *list);
t_ltree	*ft_get_ltree_dictionary(uint32_t size, char **strings);
void	ft_free_ltree(t_ltree *root);
#endif
