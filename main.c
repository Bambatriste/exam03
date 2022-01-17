#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minipaint.h"


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

int print_zone(t_zone *zone)
{
	int i = 0;
	int j = 0;

	while (i < zone->height)
	{
		while (j < zone->width)
		{
			ft_putchar(zone->zone[i * zone->height + j]);
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
	return (0);
}

int init_zone(FILE *fd, t_zone *zone)
{
	int ret;
	int i = 0;
	int j = 0;

	ret = fscanf(fd, "%d %d %c\n" , &zone->width, &zone->height, &zone->draw_char);
	if (ret != 3)
		return (-1);
	zone->zone = malloc(sizeof(char) * (zone->height * zone->width));
	while (i < zone->height)
	{
		while (j < zone->width)
		{
			zone->zone[i * zone->height + j] = zone->draw_char;
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

	x_diff = (x - circle->x) * (x - circle->x);
	y_diff = (y - circle->y) * (y - circle->y);


	dist = sqrtf(x_diff + y_diff);
	//printf("dist : %f", dist);
	if (dist < circle->radius)
		return (1);
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
				zone->zone[i * zone->height + j] = circle->draw_char;
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
		draw_circle(zone, &circle);
		ret = fscanf(fd, "%c %f %f %f %c\n", &circle.type,
			 &circle.x, &circle.y, &circle.radius, &circle.draw_char);
	}
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
		return (0);
	}
	pathname = av[1];
	fd = fopen(pathname, "r");
	if (fd == NULL)
	{
		ft_putstr_fd(ERROR_FD, 1);
		return (0);
	}
	init_zone(fd, &drawzone);
	add_circles(&drawzone, fd);
	print_zone(&drawzone);
		
		
}
