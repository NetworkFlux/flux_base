#include "flux_base.h"


char	*nf_strcat(char *str1, char *str2)
{
	char	*result;
	size_t	i = 0;
	size_t	j = 0;

	result = malloc(sizeof(char) * (nf_strlen(str1) + nf_strlen(str2) + 1));

	while (str1[i])
	{
		result[i] = str1[i];
		i++;
	}

	while (str2[i])
	{
		result[i] = str2[j];
		i++;
		j++;
	}

	return (result);
}

void	create_collection(int argc, char **argv)
{
	printf("Creating Collection\n");

	if (argc < 4)
	{
		printf("No database provided\n");
		return ;
	}
	else if (argc < 5)
	{
		printf("No name for collection provided\n");
		return ;
	}

	char	*file = nf_strcat("/", argv[4]);
	printf("File: %s\n", file);
	
	char	*pathname = nf_strcat(argv[3], file);

	printf("Pathname: %s\n", pathname);

	open(nf_strcat(argv[3], nf_strcat("/", argv[4])), O_CREAT);

}

void	create_database(int argc, char **argv)
{
	printf("Creating Database\n");

	if (argc < 4)
	{
		printf("No name provided for database\n");
		return ;
	}

	if (mkdir(argv[3], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
	{
		printf("Failed to create database\n");
		return ;
	}
}

void	creation(int argc, char **argv)
{
	printf("Creating Mode\n");
	
	if (argc < 3)
	{
		printf("No creation arguments provided!\n");
		return ;
	}

	if (nf_strcmp(argv[2], "database") == 0)
		create_database(argc, argv);
	else if (nf_strcmp(argv[2], "collection") == 0)
		create_collection(argc, argv);
	else
		printf("Unknown creation argument\n");
}

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("argv 1 = %s\n", argv[1]);
		if (nf_strcmp(argv[1], "create") == 0)
			creation(argc, argv);
		else
			printf("Unknown argument\n");
	}
	else
		printf("No arguments provided!\n");

	return (0);
}
