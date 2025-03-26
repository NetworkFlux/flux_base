#include "uninstall.h"

void	remove_flux_env_variable()
{
	FILE	*bashrc, *temp;
	char	*home;
	char	bashrc_file[MAX_PATH_LENGTH];
	char	temp_file[MAX_PATH_LENGTH];
	char	line[1024];

	if (unsetenv(ENV_VAR) != 0)
	{
		perror("Failed to unset environment variable");
		return ;
	}

	if (!(home = getenv("HOME")))
	{
		perror("Couldn't find the home directory");
		return ;
	}

	snprintf(bashrc_file, sizeof(bashrc_file), "%s/%s", home, ".bashrc");
	snprintf(temp_file, sizeof(temp_file), "%s/%s", home, ".bashrc_tmp");
	bashrc = fopen(bashrc_file, "r");
	temp = fopen(temp_file, "w");

	if (!bashrc || !temp)
	{
		perror("Failed to open files");
		return ;
	}

	while (fgets(line, sizeof(line), bashrc))
	{
		if (strstr(line, TARGET_LINE) == NULL)
			fputs(line, temp);
	}

	fclose(bashrc);
	fclose(temp);

	if (rename(temp_file, bashrc_file) != 0) {
        perror("Failed to update .bashrc");
    } else {
        printf("Environment variable removed from .bashrc.\n");
    }
}

void	remove_flux_base_directory(const char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			full_path[MAX_PATH_LENGTH];
	struct stat		statbuf;

	if (!(dir = opendir(path)))
	{
		perror("Failed to open directory");
		return ;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

		if (lstat(full_path, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				remove_flux_base_directory(full_path);
			else
			{
				if (unlink(full_path) != 0)
					perror("Failed to remove path");
			}
		}
	}

	closedir(dir);

	if (rmdir(path) != 0)
		perror("Failed to remove directory");
	else
		printf("Deleted directory: %s\n", path);
}

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
	remove_flux_env_variable();

	return ;
}

int	main(void)
{
	uninstall();
}
