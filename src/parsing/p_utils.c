#include "../../include/cub3d.h"

char	*ft_charjoin(char *str, char c, t_cub *cub)
{
	int		len;
	int		i;
	char	*res;

	len = ft_strlen(str) + 1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		ft_error(cub, "Malloc Error");
	i = 0;
	while (str && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	return (res);
}
