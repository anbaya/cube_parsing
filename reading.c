#include "cube.h"

int map_parsing(t_config *config, int i, int j)
{
    static int space;

    if (i < 0 || j < 0 || i > config->num_rows || j > (int)ft_strlen(config->nap[i]))
        return 0;
    if (config->nap[i][j] == '1' || config->nap[i][j] == '@')
        return 0;
    if (config->nap[i][j] == ' ' || config->nap[i][j] == '\n')
    {
        space = 1;
        return 1;
    }
    config->nap[i][j] = '@';
    map_parsing(config, i + 1, j);
    map_parsing(config, i - 1, j);
    map_parsing(config, i, j + 1);
    map_parsing(config, i, j - 1);
    if (space == 1)
        return 1;
    else
        return 0;
}

char **load_map(t_config *config, char **file)
{
    int map_start;
    int map_end;
    int row;
    char **map;

    map_start = 0;
    map_end = 0;
    row = 0;
    while (file[row])
        row++;
    row--;
    while (file[row] && is_map(file[row]) == 0)
        row--;
    map_end = row;
    while (file[row] && is_map(file[row]))
        row--;
    map_start = row + 1;
    config->map_start = map_start;
    config->map_end = map_end;
    map = copy_map(file, map_start, map_end);
    return map;
}

char **read_file(char *filename)
{
    int fd;
    char **file;
    int line_count;
    int i;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;
    line_count = count_lines(fd);
    close(fd);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;
    file = (char **)malloc(line_count * sizeof(char *));
    if (!file)
        return (close(fd), NULL);
    i = 0;
    while (i < line_count)
    {
        file[i] = get_next_line(fd);
        i++;
    }
    file[i] = NULL;
    close(fd);
    return file;
}

int load_textures(char **file, t_config *config)
{
    int i;

    i = 0;
    while (file[i] && is_map(file[i]) == 0)
    {
        if (is_texture(file[i]))
        {

            if (!add_texture(file[i], config))
                return -1;
        }
        i++;
    }
    return 1;
}

int load_colors(char **file, t_config *config)
{
    int i;
    char *tmp;

    i = 0;
    while (file[i] && is_map(file[i]) == 0)
    {
        if (is_color(file[i]) == 1)
        {
            tmp = parse_color(file[i]);
            if (!tmp)
                return -1;
            if (!add_color(file[i], tmp, config))
                return -1;
        }
        i++;
    }
    return 1;
}

int file_loader(char **file, t_config *config)
{
    int i;

    i = 0;
    config->map = load_map(config, file);
    if (!config->map)
        return 0;
    while (config->map[i])
        i++;
    config->num_rows = i;
    config->nap = map_dup(config);
    if (!config->nap)
        return 0; 
    if (load_textures(file, config) == -1)
        return 0;
    if (load_colors(file, config) == -1)
        return 0;
    return 1;
}