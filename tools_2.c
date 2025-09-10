#include "cube.h"

int is_color(char *line)
{
    if (!line)
        return 0;
    if (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "C ", 2))
        return 1;
    return 0;
}

int parse_color(char *line)
{
    int i;
    int j;
    char num[4];

    i = 0;
    j = 0;
    while (line[i] && (line[i] != 'F' && line[i] != 'C'))
        i++;
    while (line[i] && line[i] == ' ')
        i++;
    while (line[i])
    {
        while (line[i] && (line[i] >= '0' && line[i] <= '9'))
        {
            if (j < 3)
                num[j++] = line[i];
            i++;
        }
        num[j] = '\0';
        if (j == 0 || ft_atoi(num) < 0 || ft_atoi(num) > 255)
            return (0);
        j = 0;
        if (line[i] == ',')
            i++;
        while (line[i] == ' ')
            i++;
    }
    return (1);
}

int add_color(char *line, t_config *config)
{
    int i;
    int j;
    char num[4];
    int color; // 1 floor, 0 ceiling
    int index;

    i = 0;
    j = 0;
    index = 0;
    color = 0;
    while (line[i] && (line[i] != 'F' && line[i] != 'C'))
        i++;
    if (line[i] == 'F')
        color = 1;
    while (line[i] && line[i] == ' ')
        i++;
    while (line[i] && index < 3)
    {
        while (line[i] && (line[i] >= '0' && line[i] <= '9'))
        {
            if (j < 3)
                num[j++] = line[i];
            i++;
        }
        num[j] = '\0';
        if (color == 1)
            config->floor_color[index++] = ft_atoi(num);
        else
            config->ceiling_color[index++] = ft_atoi(num);
        j = 0;
        if (line[i] == ',')
            i++;
        while (line[i] == ' ')
            i++;
    }
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