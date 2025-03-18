#include "flux_base.h"

int	nf_strcmp(char *str, char *target)
{
	size_t	i = 0;

	if ((str && !target) || (!str && target))
		return (1);

	if (!str && !target)
		return (0);

	while (target[i])
	{
		if (str[i] != target[i])
			return (1);
		i++;
	}

	if (str[i] != target[i])
		return (1);

	return (0);
}
