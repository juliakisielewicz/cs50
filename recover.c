#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

 
 const int BLOCK_SIZE = 512;
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    uint8_t block[BLOCK_SIZE];
    int counter = 0;
    char *filename = "";
    
    sprintf(filename, "%03i.jpg", counter);
    FILE *img = fopen(filename, "w");
    
    if (img == NULL)
    {
        fclose(file);
        fprintf(stderr, "Could not create %s.\n", filename);
        return 1;
    }
    
    while (fread(&block, sizeof(uint8_t), BLOCK_SIZE, file) == 512)
    {
        if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (counter != 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                
                if (img == NULL)
                {
                    fclose(file);
                    fprintf(stderr, "Could not create %s.\n", filename);
                    return 1;
                }
            }
            
            fwrite(&block, sizeof(uint8_t), BLOCK_SIZE, img);
            
            counter++;
        }
        else
        {
            if (counter != 0)
            {
                fwrite(&block, sizeof(uint8_t), BLOCK_SIZE, img);
            }
        }
    }
    
    fclose(file);
    fclose(img);
}