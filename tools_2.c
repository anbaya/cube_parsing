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
    char num[3];

    i = 0;
    j = 0;
    while (line[i] && (line[i] != 'F' || line[i] != 'C'))
        i++;
    while (line[i] && (line[i] == ' '))
        i++;
    while (line[i])
    {
        while (line[i] && (line[i] >= '0' && line[i] <= '9') && line[i] != ',')
            num[j++] = line[i++];
            num[j] = '\0';
            if (ft_atoi(num) < 0 || ft_atoi(num) > 255)
                return (0);
        i++;
        j = 0;
    }
    return (1);
}

int add_color(char *line, t_config *config)
{
    int i;
    int j;
    char num[3];
    int color;
    int index;

    i = 0;
    j = 0;
    index = 0;
    color = 0;
    while (line[i] && (line[i] != 'F' || line[i] != 'C'))
        i++;
    if (line[i] == 'F')
        color = 1;
    while (line[i] && (line[i] == ' '))
        i++;
    while (line[i])
    {
        while (line[i] && (line[i] >= '0' && line[i] <= '9') && line[i] != ',')
            num[j++] = line[i++];
            num[j] = '\0';
        if (color == 1)
            config->floor_color[index++] = ft_atoi(num);
        else
            config->ceiling_color[index++] = ft_atoi(num);
        i++;
        j = 0;
    }
    return (0);
}