#include <stdio.h>
#include <string.h>

char *findLastPath(const char *path)
{
    char *lastPath = strrchr(path, '/');

    if (lastPath == NULL)
    {
        return NULL;
    }

    return lastPath + 1;
}

int main()
{
    const char *filePath = "59/myFile/1.txt";

    char *lastPath = findLastPath(filePath);

    if (lastPath == NULL)
    {
        printf("无法找到最后一个路径\n");
    }
    else
    {
        printf("最后一个路径是: %s\n", lastPath);
    }

    return 0;
}