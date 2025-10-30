#include "cube.h"

int rows_check(char **map)
{
    int index;
    int last_row;

    index = -1;
    // Check the first row
    while (map[0][++index])
    {
        if (map[0][index] != '1')
        return (0);
    }
    index = -1;
    last_row = 0;
    while (map[last_row])
        last_row++;
    last_row--;
    // Check the last row
    while (map[last_row][++index])
    {
        if (map[last_row][index] != '1')
        return (0);
    }
    return (1);
}

int columns_check(char **map)
{
    int row;
    int row_length;

    row = -1;
    // Check the first column in every row
    while (map[++row])
    {
        if (map[row][0] != '1')
        return (0);
    }
    row = -1;
    row_length = ft_strlen(map[0]);
    // Check the last column in every row
    while (map[++row])
    {
        if (map[row][row_length -1] != '1')
        return (0);
    }
    return (1);
}

int	empty_check(char **map, int x, int y)
{
	static int	space;

    if (y < 0 || map[y] == NULL || x < 0 || map[y][x] == '\0')
        return (0);
    if (map[y][x] == '1' || map[y][x] == 'X')
    {
        return (0);
    }
	if (map[y][x] == ' ')
		space = 1;
	map[y][x] = 'X';
	empty_check(map, x + 1, y);
	empty_check(map, x - 1, y);
	empty_check(map, x, y + 1);
	empty_check(map, x, y - 1);
	if (space == 1)
		return (1);
	else
		return (0);
}

int map_char_check(char **map)
{
    int row;
    int column;

    row = -1;
    // Check each character in the map
    while (map[++row])
    {
        column = -1;
        while (map[row][++column])
        {
            if (map[row][column] != '0' && map[row][column] != '1'
                && map[row][column] != 'N' && map[row][column] != 'E'
                && map[row][column] != 'S' && map[row][column] != 'W'
                && map[row][column] != ' ')
            {
                return (0);
            }
        }
    }
    // Return 1 if all characters are valid
    return (1);
}

int fname_check(char *fname)
{
    // Check if the filename is end with ".cube" or too short
    if (ft_strlen(fname) <= 5 || ft_strncmp(fname + ft_strlen(fname) - 5, ".cube", 5) != 0)
    {
        return (0);
    }
    return (1);
}