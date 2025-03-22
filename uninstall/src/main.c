#include "uninstall.h"

void	uninstall()
{
	char	user_input[MAX_USER_INPUT];
	const char	*flux_db_path;

	printf("Are you sure you want to uninstall Flux Base ? (type yes if you are sure)\n");

	if (fgets(user_input, sizeof(user_input), stdin) == NULL)
	{
		printf("Unisnstallation aborted.\n");
		return ;
	}

	user_input[strcspn(user_input, "\n")] = '\0';

	if (strcmp(user_input, "yes") != 0)
	{
		printf("Unisnstallation aborted.\n");
		return ;
	}

	if (!(flux_db_path = getenv("FLUX_DB_PATH")))
	{
		printf("Cannot find the Flux Base directory. Are you sure you installed it ?\n");
		return ;
	}

	remove_flux_base_directory(flux_db_path);

	return ;
}

int	main(void)
{
	uninstall();
}
