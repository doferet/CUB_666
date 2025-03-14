#include "../../include/cub3d.h"

char	*ft_charjoin(char *str, char c, t_cub *cub)
{
	int		len;
	int		i;
	char	*res;

	if (ft_isalpha(c))
		ft_error(cub, "Caracter forbidden in color");
	if (c == '-')
		ft_error(cub, "Negative number are forbidden for color");
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

void check_wrong_char_color(char *str, t_cub *cub)
{
	int i;

	i = 1;
	while(str[i])
	{
		printf("%s", str[i]);
		if (str[i] == '-')
			ft_error(cub, "Negative number for color");
		if (str[i] == '-')
			ft_error(cub, "Negative number for color");
		// else if (ft_isalpha(str[i]) == true)
		// 	ft_error(cub, "Forbidden character in color");
		i++;
	}
}