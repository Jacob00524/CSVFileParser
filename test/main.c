#include <stdio.h>
#include <math.h>

#include "csv.h"

#define min(x, y) (x > y ? y : x)

int main()
{
    CSV_FILE file;
    int status, last_index;

    status = read_csv("iris.csv", &file);
    if (status)
    {
        switch (status)
        {
        case 1:
                printf("ln: %d could not open path \"iris.csv\".\n", __LINE__);
                break;

        default:
                printf("ln: %d unexpected error %d\n", __LINE__, status);
                break;
        }
    }
    printf("Read CSV with %d rows and %d columns.\n", file.num_rows, file.num_colums);

    for (int r = 0; r < min(file.num_rows, 10); r++)
    {
        for (int c = 0; c < file.num_colums; c++)
        {
            if (file.values[r][c].decimal_valid)
                printf("%lf%s", file.values[r][c].decimal_val, (c < file.num_colums - 1 ? "," : "\n"));
            else
                printf("%s%s", file.values[r][c].string_val, (c < file.num_colums - 1 ? "," : "\n"));
        }
    }

    printf("Last line in CSV File.\n");
    last_index = file.num_rows - 1;
    for (int c = 0; c < file.num_colums; c++)
    {
        if (file.values[last_index][c].decimal_valid)
            printf("%lf%s", file.values[last_index][c].decimal_val, (c < file.num_colums - 1 ? "," : "\n"));
        else
            printf("%s%s", file.values[last_index][c].string_val, (c < file.num_colums - 1 ? "," : "\n"));
    }

    free_csv(&file);
    return 0;
}