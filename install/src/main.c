#include "install.h"

const char	*detect_profile_file()
{
	const char	*shell = getenv("SHELL");

	if (shell && strstr(shell, "zsh"))
		return ".zsh";
	else if (shell && strstr(shell, "bash"))
		return ".bashrc";
	else
		return ".profile";
}

void	add_env_variable(const char *path, const char *home_path)
{
	const char	*profile_type = detect_profile_file();
	char		profile_file[MAX_PATH_LENGTH + 20];
	char		command[MAX_PATH_LENGTH + 100];

	snprintf(profile_file, sizeof(profile_file), "%s/%s", home_path, profile_type);
	snprintf(command, sizeof(command), "echo 'export %s=\"%s\"' >> %s", ENV_VAR, path, profile_file);
	system(command);

	snprintf(command, sizeof(command), "%s -c 'source %s'", getenv("SHELL"), profile_file);
	int	result = system(command);

	if (result == 0)
		printf("Environment variable set and loaded: %s=%s\n", ENV_VAR, path);
	else
		printf("Enviromnent variable added but could not auto-load. Please run: source %s\n", profile_file);

		

}

void	create_directory(const char *path)
{
	if (mkdir(path, 0755) == 0)
		printf("Installation directory created at: %s\n", path);
	else if (access(path, F_OK) == 0)
		printf("Directory already exists: %s\n", path);
	else
	{
		perror("Error creating directory");
		exit(EXIT_FAILURE);
	}
}

void	install()
{
	const char	*home_path = getenv("HOME");
	char		path[MAX_PATH_LENGTH];
	char		user_input[MAX_PATH_LENGTH];

	snprintf(path, MAX_PATH_LENGTH, "%s/%s", home_path, DEFAULT_PATH);
	printf("Enter installation path (or press Enter for default: %s): ", path);

	if (fgets(user_input, sizeof(user_input), stdin) != NULL)
	{
		user_input[strcspn(user_input, "\n")] = 0;

		if (strlen(user_input) > 0)
		{
			strncpy(path, user_input, MAX_PATH_LENGTH - 1);
			path[MAX_PATH_LENGTH] = '\0';
		}
	}

	create_directory(path);
	add_env_variable(path, home_path);
}

int	main(void)
{
	install();
	return (0);
}
