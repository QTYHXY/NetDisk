#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;

    // 循环删除每个文件
    for (i = 1; i < argc; i++)
    {
        if (unlink(argv[i]) == 0)
        {
            printf("Deleted file: %s\n", argv[i]);
        }
        else
        {
            printf("Failed to delete file: %s\n", argv[i]);
        }
    }

    return 0;
}