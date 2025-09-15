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

int parse_file(char **file, t_config *config)
{
    int i;
    int j;

    i = 0;
    while (file[i] && i < config->map_start)
    {
        j = 0;
        if (i != config->no_i && i != config->so_i &&
            i != config->we_i && i != config->ea_i &&
            i != config->f_i && i != config->c_i)
            {
                while (file[i][j] == ' ' || file[i][j] == '\t')
                    j++;
                if (file[i][j] != '\0' && file[i][j] != '\n')
                    return (0);
            }
        i++;
    }
    i = config->map_end + 1;
    while (file[i])
    {
        j = 0;
        while (file[i] && (file[i][j] == ' ' || file[i][j] == '\t'))
            j++;
        if (file[i] && (file[i][j] != '\0' && file[i][j] != '\n'))
            return (0);
        i++;
    }
    return (1);
}