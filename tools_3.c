#include "cube.h"

int get_player(t_config *config, char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' ||
                map[i][j] == 'E' || map[i][j] == 'W')
            {
                config->p_x = i;
                config->p_y = j;
                return (1);
            };
            j++;
        }
        i++;
    }
    return (0);
}