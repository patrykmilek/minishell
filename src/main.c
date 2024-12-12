#include "minishell.h"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	char *line;
	while(1)
	{
		write(STDOUT_FILENO, "minishell> ", 12);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if ((ft_strncmp(line, "exit", 4) == 0) && ft_strlen(line) == 5)
		{
			free(line);
			break;
		}
		printf("Wpisano: %s", line);
		free(line);
	}
}
