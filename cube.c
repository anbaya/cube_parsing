#include "cube.h"

t_config *init_config(char *filename)
{
    t_config *config;

    config = (t_config *)malloc(sizeof(t_config));
    if (!config)
        return NULL;
    *config = (t_config){0};
    config->mlx = mlx_init();
    config->file = read_file(filename);
    config->map = load_map(config->file);
    file_loader(config->file, config);
    return config;
}

int main(int argc, char **argv)
{
    t_config *config;

    if (argc != 2)
    {
        ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
        return (1);
    }
    config = init_config(argv[1]);
    if (!config)
        return (1);
    return (0);
}