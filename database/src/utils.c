#include "flux_base.h"

size_t	nf_strlen(char *str)
{
	size_t	i = 0;

	while (str[i])
		i++;

	return (i);
}
