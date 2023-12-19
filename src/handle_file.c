#include "../inc/maze.h"

/**
 * open_file - opens a file
 * @filename: string pointer to file name
 * Return: File pointer
 */
FILE *open_file(char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	return (fp);
}

/**
 * read_file - reads the content of a file
 * @fp: File pointer
 * Return: map_t data structure containing map data
 */
map_t read_file(FILE *fp)
{
	size_t line_count = 0;
	char *line = NULL;
	map_t *map;
	unsigned int line_number = 0, i = 0, j;
	char *dup_line = NULL;

	map = malloc(sizeof(map_t));
	map->rows = count_rows(fp) - 1;
	map->layout = malloc(sizeof(int *) * (map->rows + 1));

	for (i = 0; i < map->rows; i++)
	{
		 if (getline(&line, &line_count, fp) == -1)
		 	break;
        map->cols = strlen(line) - 1;
		map->layout[i] = malloc(sizeof(int) * (strlen(line)));
		for (j = 0; j < strlen(line) - 1; j++)
		{
			map->layout[i][j] = line[j] - '0';
		}
	}
	free(line);

	return (*map);
}
void close_file(FILE *fp)
{
	if (fp)
		fclose(fp);
}

int count_rows(FILE *fp)
{
	char ch;
	int lines = 0;

	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n')
		{
			lines++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	return (lines + 1);
}
