#include "cube.h"

int is_color(char *line)
{
    if (!line)
        return 0;
    if (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "C ", 2))
        return 1;
    return 0;
}

char *parse_color(char *line)
{
    int i;
    int j;
    char num[] = "000,000,000";

    i = 0;
    j = 0;
    while (line[i] && (line[i] != 'F' && line[i] != 'C'))
    i++;
    while (line[i] && (line[i] == 'F' || line[i] == 'C'))
    i++;
    while (line[i] && line[i] == ' ')
    i++;
    while (line[i])
    {
        while (line[i] && (line[i] >= '0' && line[i] <= '9') && j < 9)
        {
            num[j++] = line[i];
            i++;
        }
        if (line[i] != ',' && line[i] != '\0' && j != 8 && line[i] != '\n')
            return (0);
        if (line[i] == '\n')
            break ;
        if (ft_atoi(num) < 0 || ft_atoi(num) > 255)
            return (0);
        if (j < 8)
            num[j++] = ',';
        if (line[i] == ',')
            i++;
        while (line[i] == ' ')
            i++;
    }
    return (ft_strdup(num));
}

int add_color(char *line, char *color, t_config *config)
{
    int i;
    int rgb[3];
    char **tmp;

    i = 0;
    tmp = ft_split(color, ',');
    if (!tmp)
        return (0);
    rgb[0] = ft_atoi(tmp[0]);
    rgb[1] = ft_atoi(tmp[1]);
    rgb[2] = ft_atoi(tmp[2]);
    free(color);
    while (line[i] && (line[i] != 'F' && line[i] != 'C'))
        i++;
    if (line[i] == 'F')
    {
        config->f_rgb[0] = rgb[0];
        config->f_rgb[1] = rgb[1];
        config->f_rgb[2] = rgb[2];
    }
    else if (line[i] == 'C')
    {
        config->c_rgb[0] = rgb[0];
        config->c_rgb[1] = rgb[1];
        config->c_rgb[2] = rgb[2];
    }
    i = 0;
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
    return (1);
}

char **map_dup(t_config *config)
{
    int i;
    char **nap;

    nap = malloc(sizeof(char *) * (config->num_rows + 1));
    if (!nap)
        return NULL;
    i = 0;
    while (config->map[i])
    {
        nap[i] = ft_strdup(config->map[i]);
        i++;
    }
    nap[i] = NULL;
    return nap;
}