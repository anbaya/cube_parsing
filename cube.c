#include "cube.h"

static void print_config(t_config *cfg)
{
    int i;

    if (!cfg)
        return;
    printf("--- CONFIG SUMMARY ---\n");
    printf("NO: %s\n", cfg->no_path ? cfg->no_path : "(null)");
    printf("SO: %s\n", cfg->so_path ? cfg->so_path : "(null)");
    printf("WE: %s\n", cfg->we_path ? cfg->we_path : "(null)");
    printf("EA: %s\n", cfg->ea_path ? cfg->ea_path : "(null)");
    printf("Floor: %d,%d,%d\n", cfg->floor_color[0], cfg->floor_color[1], cfg->floor_color[2]);
    printf("Ceiling: %d,%d,%d\n", cfg->ceiling_color[0], cfg->ceiling_color[1], cfg->ceiling_color[2]);
    printf("File lines:\n");
    if (cfg->file)
    {
        i = 0;
        while (cfg->file[i])
        {
            printf("  file[%d]: %s", i, cfg->file[i]);
            i++;
        }
    }
    printf("Map lines:\n");
    if (cfg->map)
    {
        i = 0;
        while (cfg->map[i])
        {
            printf("  map[%d]: %s", i, cfg->map[i]);
            i++;
        }
    }
    printf("-----------------------\n");
}

t_config *init_config(char *filename)
{
    t_config *config;

    config = (t_config *)malloc(sizeof(t_config));
    if (!config)
        return NULL;
    *config = (t_config){0};
    config->mlx = mlx_init();
    config->file = read_file(filename);
    if (!config->file)
        return (free(config), NULL);
    config->map = load_map(config->file);
    if (!config->map)
        return (free(config->file), free(config), NULL);
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
    print_config(config);
    return (0);
}