#include "libft.h"
#include <stdlib.h>
#include <unistd.h>


typedef struct	s_bits
{
	char	bit0 : 1;
	char	bit1 : 1;
	char	bit2 : 1;
	char	bit3 : 1;
	char	bit4 : 1;
	char	bit5 : 1;
	char	bit6 : 1;
	char	bit7 : 1;
}				t_bits;

typedef	union	s_test
{
	int		fd;
	t_bits	bits;
}				t_test;

typedef	enum	s_enum
{
	lst = 1,
	asdf,
	qwer,
}				t_enum;

int main(int argc, char **argv)
{
	t_test	fbi;
	t_enum	test = qwer;

	& | ~ ! ^

		   101
		101010
			   &
			   000000
			   |
			   101111
			   ~ 00000101
			     11111010
			   ! var != 0
			   false
			   ^
			   1111
			   0101
			   1010
			   
			   var = var | qwer
			   
	fbi.fd = 5;
	ft_putnbr(fbi.bits.bit7);
	ft_putnbr(test);
	return (0);
}
