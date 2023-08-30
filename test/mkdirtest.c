#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./mkdir <directory>\n");
        return 1;
    }

    if (mkdir(argv[1], 0777) == -1)
    {
        perror("Error");
        return 1;
    }

    printf("Directory '%s' has been created.\n", argv[1]);

    return 0;
}