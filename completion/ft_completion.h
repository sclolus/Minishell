/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:06:31 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/10 09:28:19 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMPLETION_H
# define FT_COMPLETION_H
# include "libft.h"
# include <dirent.h>

# define CHECK(x) do{ft_putendl("_____");ft_putendl(#x);ft_putendl("_____");}while(0);

// if prefix is empty -> insta segfault.
typedef struct s_ltree	t_ltree;

struct		s_ltree
{
	char		c;
	t_ltree		*son;
	t_ltree		*alternative;
};

void		ft_ltree_add_word(t_ltree **root, char *word);
t_ltree		*ft_get_ltree_node(char c);
t_ltree		*ft_get_alternative_node(t_ltree *root, char c);

int32_t		ft_ltree_search(t_ltree *root, char *word);
t_ltree		*ft_get_ltree_dictionary_list(t_list *list);
t_ltree		*ft_get_ltree_dictionary(uint32_t size, char **strings);

char		**ft_get_matching_filenames(char *prefix);
char		**ft_get_ltree_suffixes(t_ltree *root, char *prefix);
t_ltree		*ft_ltree_last_match(t_ltree *root, char *word);
t_ltree		*ft_get_ltree_directory(void);
void		ft_ltree_add_directory(t_ltree *ltree, char *path);
char		*ft_ltree_get_match(t_ltree *root, char *prefix, uint32_t index);
char		*ft_ltree_get_completion(t_ltree *root, char *prefix);
uint32_t	ft_ltree_count_suffixes(t_ltree *root);
uint32_t	ft_ltree_get_suffix_len(t_ltree *node, uint32_t index);

void		ft_free_ltree(t_ltree *root);
#endif
