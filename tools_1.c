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

int is_map(char *line)
{
    if (!line)
        return (0);
    while (*line)
    {
        if (*line != '0' && *line != '1' && *line != '2'
            && *line != 'N' && *line != 'S' && *line != 'E'
            && *line != 'W' && *line != ' ')
            return (0);
        line++;
    }
    return (1);   
}

int is_texture(char *line)
{
    if (!line)
        return 0;
    if (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "SO ", 3)
        || ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "EA ", 3))
        return 1;
    return 0;
}

int parse_texture(t_config *config, char *line)
{
    void *img;

    img = mlx_xpm_file_to_image(config->mlx, line + 3, &(int){2}, &(int){2});
    if (!img)
    {
        ft_putstr_fd("Error: Failed to load texture\n", 2);
        return (0);
    }
    mlx_destroy_image(config->mlx, img);
    return (1);
}

int add_texture(char *line, t_config *config)
{
    if (ft_strnstr(line, "NO ", 3))
        config->no_path = ft_strdup(line + 3);
    else if (ft_strnstr(line, "SO ", 3))
        config->so_path = ft_strdup(line + 3);
    else if (ft_strnstr(line, "WE ", 3))
        config->we_path = ft_strdup(line + 3);
    else if (ft_strnstr(line, "EA ", 3))
        config->ea_path = ft_strdup(line + 3);
    else
        return 0; // Invalid texture line
    return 1;   
}