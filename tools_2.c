#include "cube.h"

int parse_color(t_config *config)
{
    int i;

    i = 0;
    while (config->f_rgb[i])
    {
        if (config->f_rgb[i] < 0 || config->f_rgb[i] > 255)
            return 0;
        i++;
    }
    i = 0;
    while (config->c_rgb[i])
    {
        if (config->c_rgb[i] < 0 || config->c_rgb[i] > 255)
            return 0;
        i++;
    }
    return 1;
}

int is_color(char *line)
{
    if (!line)
        return 0;
    if (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "C ", 2))
        return 1;
    return 0;
}

void skip_space(char *line, int *i)
{
    while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
        (*i)++;
    while (line[*i] && (line[*i] == 'F' || line[*i] == 'C'))
        (*i)++;
    while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
        (*i)++;
}

char *c_reader(char *line, int i)
{
    int j;
    char num[] = "000,000,000";

    j = 0;
    while (line[i])
    {
        while (line[i] && (line[i] >= '0' && line[i] <= '9') && j < 9)
            num[j++] = line[i++];
        if (line[i] != ',' && line[i] != '\0' && j != 8 && line[i] != '\n')
            return (0);
        if (line[i] == '\n')
            break ;
        if (j < 8)
            num[j++] = ',';
        if (line[i] == ',' && line[i + 1] != ',')
            i++;
        else
            return (NULL);
        skip_space(line, &i);
    }
    return (ft_strdup(num));
}

char *read_color(char *line)
{
    int i;

    i = 0;
    skip_space(line, &i);
    if (!(line[i] >= '0' && line[i] <= '9'))
        return (NULL);
    return (c_reader(line, i));
}

void color_select(t_config *config, char *line, int *rgb, int index)
{
    int i;

    i = 0;
    while (line[i] && (line[i] != 'F' && line[i] != 'C'))
        i++;
    if (line[i] == 'F')
    {
        config->f_rgb[0] = rgb[0];
        config->f_rgb[1] = rgb[1];
        config->f_rgb[2] = rgb[2];
        config->f_i = index;
    }
    else if (line[i] == 'C')
    {
        config->c_rgb[0] = rgb[0];
        config->c_rgb[1] = rgb[1];
        config->c_rgb[2] = rgb[2];
        config->c_i = index;
    }
}

int add_color(char *line, char *color, t_config *config, int index)
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
    color_select(config, line, rgb, index);
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