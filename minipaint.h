#ifndef MINIPAINT_H
 #define MINIPAINT_H

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

#endif
