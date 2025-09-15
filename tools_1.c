#include "cube.h"

int count_lines(int fd)
{
    int line_count = 0;
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        line_count++;
        free(line);
    }
    return line_count;
}

char **copy_map(char **file, int start, int end)
{
    int i;
    char **map;

    map = (char **)malloc((end - start + 2) * sizeof(char *));
    if (!map)
        return NULL;
    i = 0;
    while (start <= end)
    {
        map[i] = ft_strdup(file[start]);
        i++;
        start++;
    }
    map[i] = NULL;
    return map;
}

static int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == '2' ||
            c == 'N' || c == 'S' || c == 'E' || c == 'W' ||
            c == ' ');
}

int is_map(char *line)
{
    int i;
    int seen;

    if (!line)
        return (0);
    i = 0;
    seen = 0;
    while (line[i] && line[i] != '\n' && line[i] != '\r')
    {
        if (!is_map_char(line[i]))
            return (0);
        if (line[i] != ' ')
            seen = 1;
        i++;
    }
    return (seen);
}

int is_texture(char *line)
{
    if (!line)
        return 0;
    while (*line == ' ' || *line == '\t')
        line++;
    if (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "SO ", 3)
        || ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "EA ", 3))
        return 1;
    return 0;
}

int parse_texture(t_config *config, char *line)
{
    void *img;

    img = mlx_xpm_file_to_image(config->mlx, line, &(int){40}, &(int){40});
    if (!img)
        return (ft_putstr_fd("Error: Failed to load texture\n", 2), 0);
    return (mlx_destroy_image(config->mlx, img), 1);
}

int add_texture(char *line, t_config *config, int index)
{
    char *tmp;
    int i;

    i = 2;
    tmp = ft_strtrim(line, " \n\r\t");
    while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
        i++;
    if (ft_strnstr(tmp, "NO ", 3) && parse_texture(config, tmp + i))
        return (config->no_path = tmp + i, config->no_i = index, 1);  
    else if (ft_strnstr(tmp, "SO ", 3) && parse_texture(config, tmp + i))
        return (config->so_path = tmp + i, config->so_i = index, 1);
    else if (ft_strnstr(tmp, "WE ", 3) && parse_texture(config, tmp + i))
        return (config->we_path = tmp + i, config->we_i = index, 1);
    else if (ft_strnstr(tmp, "EA ", 3) && parse_texture(config, tmp + i))
        return (config->ea_path = tmp + i, config->ea_i = index, 1);
    else
        return (free(tmp), 0);
}