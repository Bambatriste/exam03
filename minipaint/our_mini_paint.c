#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR_ARGS "Error: argument\n"
#define	ERROR_FD "Error: Operation file corrupted\n"

typedef struct draw_zone
{
	int height;
	int width;
	char draw_char;
	char *zone;
}	t_zone;

typedef struct circle
{
	char type;
	float x;
	float y;
	float radius;
	char draw_char;
}	t_circle;

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write (fd, str, ft_strlen(str));
}

void	ft_putchar (char c)
{
	write(1 , &c, 1);
}

int zone_validity(int value)
{
	if (value > 300 || value <= 0)
		return (0);
	return (1);
}

int print_zone(t_zone *zone)
{
	int i = 0;
	int j = 0;

	while (i < zone->height)
	{
		while (j < zone->width)
		{
			ft_putchar(zone->zone[i * zone->width + j]);
			j++;
		}
		j = 0;
		i++;
		ft_putchar('\n');
	}
	return (0);
}

int init_zone(FILE *fd, t_zone *zone)
{
	int ret;
	int i = 0;
	int j = 0;

	ret = fscanf(fd, "%d %d %c\n" , &zone->width, &zone->height, &zone->draw_char);
	if (ret != 3 || !zone_validity(zone->width) || !zone_validity(zone->height))
		return (1);
	zone->zone = malloc(sizeof(char) * (zone->height * zone->width));
	while (i < zone->height)
	{
		while (j < zone->width)
		{
			zone->zone[i * zone->width + j] = zone->draw_char;
			j++;
		}
		j = 0;
		i++;
	}
	return (0); 
}

 int	is_in_circle(float x, float y, t_circle *circle)
{
	float dist;
	float x_diff;
	float y_diff;
	float delta_diff;

	x_diff = (x - circle->x) * (x - circle->x);
	y_diff = (y - circle->y) * (y - circle->y);
	dist = sqrtf(x_diff + y_diff);
	delta_diff = dist - circle->radius;
	if (delta_diff <= 0.00000)
	{
		if (circle->type == 'C')
			return (1);
		else if (circle->type == 'c')
		{
			if (delta_diff <= -1.00000000)
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

int draw_circle(t_zone *zone, t_circle *circle)
{
	int i = 0;
	int j = 0;

	while (i < zone->height)
	{
		while (j < zone->width)
		{
			if (is_in_circle((float)j, (float)i , circle))
				zone->zone[i * zone->width + j] = circle->draw_char;
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	add_circles(t_zone *zone, FILE *fd)
{
	int ret;

	t_circle circle;

	ret = fscanf(fd, "%c %f %f %f %c\n", &circle.type, &circle.x,
		 &circle.y, &circle.radius, &circle.draw_char);
	while (ret == 5)
	{
		if ((circle.type != 'c' && circle.type != 'C') || (circle.radius <= 0.0000000000))
			return (-1);
		draw_circle(zone, &circle);
		ret = fscanf(fd, "%c %f %f %f %c\n", &circle.type,
			 &circle.x, &circle.y, &circle.radius, &circle.draw_char);
	}
	if (ret != -1)
		return (-1);
	return (0);
}

int main(int ac, char **av)
{
	char *pathname;
	FILE *fd;
	t_zone drawzone;

	if (ac != 2)
	{
		ft_putstr_fd(ERROR_ARGS, 1);
		return (1);
	}
	pathname = av[1];
	fd = fopen(pathname, "r");
	if (fd == NULL)
	{
		ft_putstr_fd(ERROR_FD, 1);
		return (1);
	}
	if (init_zone(fd, &drawzone))
	{
		ft_putstr_fd(ERROR_FD, 1);
		return (1);
	}
	if (add_circles(&drawzone, fd))
	{
		ft_putstr_fd(ERROR_FD, 1);
		free(drawzone.zone);
		return (1);
	}
	print_zone(&drawzone);
	fclose(fd);
	free(drawzone.zone);
	return (0);
}
