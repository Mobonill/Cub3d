#include "../include/cub3d.h"


size_t   map_line_max_lenght(char **map)
{
    int     i;
    size_t  max;
    size_t  len;

    i = 0;
    max = 0;
    len = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        if (len > max)
            max = len;
        i++;
    }
    printf("max len = %zu", max);
    return (max);
}

// void    fullfil_map_with_x(t_data *data, char **map)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;
// while (map[i])
// {

// }
// }

