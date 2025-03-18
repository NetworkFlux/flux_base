#include "install.h"

int	main(void)
{
	// Get the user's home directory
	const char *home_dir = getenv("HOME");
	char database_path[MAX_PATH_SIZE];

	printf("User home directory: %s\n", home_dir);

	snprintf(database_path, MAX_PATH_SIZE, "%s%s", home_dir, DATABASE_PATH);
	
	printf("Database path: %s\n", database_path);

	if (mkdir(database_path, 0755) != 0)
		perror("mkdir");

	return (0);
}
