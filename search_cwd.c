#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char *search_cwd(char *filename)
{
	DIR *dir;
	struct dirent *sd;
	char *ret;
	int len = 0;
	int i = 0;

	while (filename[len])
		len++;
	ret = malloc(sizeof(char) * (len + 3));
	dir = opendir(".");
	if (!dir)
	{
		printf("Error! Unable to open directory.\n");
		exit(1);
	}
	while ((sd = readdir(dir)))
	{
		for (i = 0; sd->d_name[i] && filename[i]; i++)
		{
			if (sd->d_name[i] != filename[i])
				break;
			if (i == (len - 1) && !(sd->d_name[i + 1]))
			{
				strcpy(ret, "./");
				strcat(ret, filename);
				closedir(dir);
				return (ret);
			}
		}
	}
	closedir(dir);
	return("error");
}
