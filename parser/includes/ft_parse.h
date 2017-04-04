/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 04:17:40 by aalves            #+#    #+#             */
/*   Updated: 2017/03/08 07:14:35 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE
# define FT_PARSE

#include <libft.h>
/**/
/*		Parser definition		*/
/**/

typedef struct	s_parser
{
	char			retained;
	char			*name;
	t_parser_type	type;
	t_parse_data	data;
};				t_parser;

typedef union {
	undef = 0,
	fail = 1

}				t_parser_type;

typedef struct	s_pdata_fail
{
	char			*message;
};				t_pdata_fail;

typedef union {
  t_pdata_fail		fail;
  mpc_pdata_lift_t lift;
  mpc_pdata_expect_t expect;
  mpc_pdata_anchor_t anchor;
  mpc_pdata_single_t single;
  mpc_pdata_range_t range;
  mpc_pdata_satisfy_t satisfy;
  mpc_pdata_string_t string;
  mpc_pdata_apply_t apply;
  mpc_pdata_apply_to_t apply_to;
  mpc_pdata_predict_t predict;
  mpc_pdata_not_t not;
  mpc_pdata_repeat_t repeat;
  mpc_pdata_and_t and;
  mpc_pdata_or_t or;
}				t_parse_data;


#endif
