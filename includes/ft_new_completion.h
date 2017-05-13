/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_completion.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 00:14:25 by aalves            #+#    #+#             */
/*   Updated: 2017/05/14 00:15:11 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_COMPLETION_H
# define NEW_COMPLETION_H

char		*ft_get_max_completion(char **tab, char *to_complete);
uint32_t	ft_get_max_common_len(char *s1, char *s2);
char		**ft_get_completions(char **tab, char *to_complete);
char		*ft_get_file_name(char *file);
char		*ft_get_path_name(char *file);
char		**ft_lsttotab_completion(t_list *lst);

#endif
