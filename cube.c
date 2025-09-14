#include "cube.h"

// static void print_config(t_config *cfg)
// {
//     int i;
//     int n;

//     if (!cfg)
//         return;
//     printf("--- CONFIG SUMMARY ---\n");
//     printf("Rows: %d\n", cfg->num_rows);
//     printf("NO: %s\n", cfg->no_path ? cfg->no_path : "(null)");
//     printf("SO: %s\n", cfg->so_path ? cfg->so_path : "(null)");
//     printf("WE: %s\n", cfg->we_path ? cfg->we_path : "(null)");
//     printf("EA: %s\n", cfg->ea_path ? cfg->ea_path : "(null)");
//     printf("Floor: %d,%d,%d\n", cfg->f_rgb[0], cfg->f_rgb[1], cfg->f_rgb[2]);
//     printf("Ceiling: %d,%d,%d\n", cfg->c_rgb[0], cfg->c_rgb[1], cfg->c_rgb[2]);

//     n = 0; while (cfg->file && cfg->file[n]) n++;
//     printf("File lines (%d):\n", n);
//     if (cfg->file)
//     {
//         i = 0;
//         while (cfg->file[i])
//         {
//             printf("%s", cfg->file[i]);
//             i++;
//         }
//     }

//     n = 0; while (cfg->map && cfg->map[n]) n++;
//     printf("\nMap lines (%d):\n", n);
//     if (cfg->map)
//     {
//         i = 0;
//         while (cfg->map[i])
//         {
//             printf("%s", cfg->map[i]);
//             i++;
//         }
//     }

//     n = 0; while (cfg->nap && cfg->nap[n]) n++;
//     printf("\nNap lines (%d):\n", n);
//     if (cfg->nap)
//     {
//         i = 0;
//         while (cfg->nap[i])
//         {
//             printf("  nap[%d]: %s", i, cfg->nap[i]);
//             i++;
//         }
//     }
//     printf("-----------------------\n");
// }

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
    file_loader(config->file, config);
    if (!file_loader(config->file, config))
        return (free(config->file), free(config), NULL);
    return config;
}

int main(int argc, char **argv)
{
    t_config *config;

    if (argc != 2)    
        return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 1);
    if (!fname_check(argv[1]))
        return (ft_putstr_fd("Error\nInvalid file\n", 2), 1);
    config = init_config(argv[1]);
    if (!config)
        return (1);
    get_player(config, config->map);
    if (map_parsing(config, config->p_x, config->p_y))
    {
        ft_putstr_fd("Error\nInvalid map\n", 2);
    }
    if (map_char_check(config->map))
    {
        ft_putstr_fd("Error\nInvalid map characters\n", 2);
    }
    
    // print_config(config);
    return (0);
}