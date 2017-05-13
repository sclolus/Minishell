/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:06:31 by jaustry           #+#    #+#             */
/*   Updated: 2017/05/07 09:52:48 by jaustry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMPLETION_H
# define FT_COMPLETION_H
# include "libft.h"
# include <dirent.h>
# include "minishell.h"

typedef struct s_ltree	t_ltree;

struct		s_ltree
{
	t_ltree		*son;
	t_ltree		*alternative;
	char		c;
};

char		**ft_get_matching_filenames(char *prefix);

/*
**	Create ltree
*/

t_ltree		*ft_get_ltree_node(char c);
t_ltree		*ft_get_alternative_node(t_ltree *root, char c);
void		ft_ltree_add_word(t_ltree **root, char *word);

/*
**	Utility
*/

uint32_t	ft_ltree_count_suffixes(t_ltree *root);
uint32_t	ft_ltree_get_suffix_len(t_ltree *node, uint32_t index);
char		*ft_ltree_get_completion(t_ltree *root, char *prefix);
t_ltree		*ft_ltree_last_match(t_ltree *root, char *word);
void		ft_ltree_put(t_ltree *ltree);
uint32_t	ft_free_ltree(t_ltree *root);
int32_t		ft_ltree_search(t_ltree *root, char *word);
t_ltree		*ft_get_alternative_node(t_ltree *root, char c);
int32_t		ft_ltree_search(t_ltree *root, char *word);

/*
**	Get suffixes
*/

char		**ft_get_ltree_suffixes(t_ltree *root, char *prefix);
uint32_t	ft_ltree_get_suffix_len(t_ltree *node, uint32_t index);
char		*ft_ltree_get_match(t_ltree *root, char *prefix, uint32_t index);
char		*ft_ltree_get_match_no_prefix(t_ltree *root, uint32_t index);
char		**ft_get_ltree_all_suffixes(t_ltree *root);

/*
** Get ltree directory
*/

t_ltree		*ft_get_ltree_dictionary_list(t_list *list);
t_ltree		*ft_get_ltree_dictionary(uint32_t size, char **strings);

t_ltree		*ft_get_ltree_directory(char *path);
int32_t		ft_ltree_add_directory(t_ltree **ltree, char *path);
int32_t		ft_ltree_add_directory_bin(t_ltree **ltree, char *path);

/*
** Sanitization of completions
*/

void		ft_sanitize_completion(char **completion);
void		ft_sanitize_completions(char **completions);

void		ft_fuk_norminette(char *tmp, t_ltree **ltree
							, struct dirent *curr_entry);
uint32_t	*ft_fuk_norminette2(char **completions, uint32_t n,
							t_string *buf, int64_t *old_offset);
uint32_t	ft_fuk_norminette3(char **path, t_ltree **ltree);

#endif
