# ifndef CUBE_H
# define CUBE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "get_next_line.h"

typedef struct s_config
{
    void *mlx;
    void *win;
    char **file;
    char **map;
    char **nap;
    int num_rows;
    int row_length;
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

// reading / loading
char **read_file(char *filename);
int file_loader(char **file, t_config *config);
char **load_map(char **file);
int load_textures(char **file, t_config *config);
int load_colors(char **file, t_config *config);
char **map_dup(t_config *config);

// texture helpers
int is_map(char *line);
int is_texture(char *line);
int parse_texture(t_config *config, char *line);
int add_texture(char *line, t_config *config);

// color helpers
int is_color(char *line);
int parse_color(char *line); // only validates
int add_color(char *line, t_config *config);

// generic utils
int count_lines(int fd);
char **copy_map(char **file, int start, int end);

// init
t_config *init_config(char *filename);

// map parsing
int map_parsing(t_config *config, int i, int j);
int rows_check(char **map);
int columns_check(char **map);
int	empty_check(char **map, int x, int y);
int map_char_check(char **map);
int fname_check(char *fname);

# endif // CUBE_H