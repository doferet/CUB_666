// #include "../../include/cub3d.h"

// static void	check_around_floor(t_cub *cub, int x, int y)
// {
// 	if (cub->map.map[y][x] == '0' && cub->map.map[y][x - 1] == ' ')
// 		ft_error(cub, "Walls are not valid");
// 	if (cub->map.map[y][x] == '0' && cub->map.map[y][x + 1] == ' ')
// 		ft_error(cub, "Walls are not valid");
// 	if (cub->map.map[y][x] == '0' && (cub->map.map[y + 1][x] == ' '
// 			|| cub->map.map[y + 1][x] == '\0' || cub->map.map[y + 1][x] == 0))
// 		ft_error(cub, "Walls are not valid");
// 	if (cub->map.map[y][x] == '0' && (cub->map.map[y - 1][x] == ' '
// 			|| cub->map.map[y - 1][x] == '\0' || cub->map.map[y - 1][x] == 0))
// 		ft_error(cub, "Walls are not valid");
// }

// static bool	check_begin_end(t_cub *cub, int x, int y, bool start)
// {
// 	if (cub->map.map[y][x] == '1')
// 		start = true;
// 	if (cub->map.map[y][x] == '0' && start == false)
// 		ft_error(cub, "Walls are not valid");
// 	if (cub->map.map[0][x] == '0')
// 		ft_error(cub, "Walls are not valid");
// 	if (cub->map.map[y][(int)ft_strlen(cub->map.map[y]) - 1] == '0')
// 		ft_error(cub, "Walls are not valid");
// 	return (start);
// }

// static void	check_invalid_character(t_cub *cub, int x, int y)
// {
// 	if (cub->map.map[y][x] != 'N' && cub->map.map[y][x] != 'S'
// 		&& cub->map.map[y][x] != 'E' && cub->map.map[y][x] != 'W'
// 		&& cub->map.map[y][x] != '1' && cub->map.map[y][x] != '0'
// 		&& cub->map.map[y][x] != ' ' && cub->map.map[y][x] != '\n')
// 		ft_error(cub, "Invalid character in map");
// }


// static void	take_info_from_player(t_cub *cub, int x, int y)
// {
// 	if (cub->map.map[y][x] == 'N' || cub->map.map[y][x] == 'S'
// 		|| cub->map.map[y][x] == 'E' || cub->map.map[y][x] == 'W')
// 	{
// 		cub->player_pos.x = x;
// 		cub->player_pos.y = y;
// 		cub->player_pos.start_orientation = cub->map.map[y][x];
// 		cub->map.player++;
// 	}
// }

// void	check_player(t_cub *cub)
// {
//     bool start;
// 	int	x;
// 	int	y;

// 	y = -1;
//     x = -1;
//     start = false;
//     while (x++ < (int)ft_strlen(cub->map.map[cub->map.rows - 1]))
// 	{
// 		if (cub->map.map[y][x] == 'N' || cub->map.map[y][x] == 'S'
// 		|| cub->map.map[y][x] == 'E' || cub->map.map[y][x] == 'W')
// 			ft_error(cub, "Walls are not valid");
// 	}
// 	while (++y < cub->map.rows)
// 	{
// 		x = -1;
// 		while (++x < (int)ft_strlen(cub->map.map[y]))
// 		{
//             take_info_from_player(cub, x, y);
// 		}
// 	}
// 	if (cub->map.player != 1)
// 		ft_error(cub, "Incorrect number of players");
// }
