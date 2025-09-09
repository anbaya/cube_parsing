# ifndef CUBE_H
# define CUBE_H

#include "libft.h"
#include "mlx.h"
#include "get_next_line.h"

typedef struct s_config
{
    void *mlx;
    void *win;
    char **file;
    char **map;
    char *no_path;
    char *so_path;
    char *we_path;
    char *ea_path;
    void *north_texture;
    void *south_texture;
    void *west_texture;
    void *east_texture;
    int floor_color[3]; // RGB values for floor color
    int ceiling_color[3]; // RGB values for ceiling color
} t_config;

int file_loader(char **file, t_config *config);
char **read_file(char *filename);
char **load_map(char **file);
int load_textures(char **file, t_config *config);
int is_map(char *line);
int is_texture(char *line);
int parse_texture(t_config *config, char *line);
int add_texture(char *line, t_config *config);
t_config *init_config(char *filename);
int file_loader(char **file, t_config *config);

# endif // CUBE_H