#include "libft.h"

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

char **map_read(char **file)
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
    map = copy_map(file, map_start, map_end);
    return map;
}

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
    close(fd);
    return file;
}