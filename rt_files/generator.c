#include <stdio.h>
#include <stdlib.h>

void    make_grid(int x, int y)
{
    printf("C %d,%d,%d 0,0,-1 90\n", 0,0,10 * (x+y));
    printf("L %d,%d,%d 1\n", 0,0,-10 * (x+y));
    for (int i = -y/2; i < y/2; ++i)
    {
        for(int j = -x/2; j < x/2; ++j)
        {
            printf("sp %d,%d,%d 10 %d,%d,%d\n", j * 10, i * 10, 0, 
                255,255,255);
                /*((i * j)*(i * j)*100) % 256
                ,((i * j)*(i * j)*100) % 256
                ,((i * j)*(i * j)*100) % 256);*/
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("");
        return 1;
    }
    if (argv[1][0] == 'g') // grid
        make_grid(atoi(argv[2]), atoi(argv[3]));
    return (0);
}