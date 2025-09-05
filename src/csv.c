#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "csv.h"

int read_csv(char *path, CSV_FILE *file_data)
{
    FILE *file;
    unsigned long file_length;
    char read_char, *placeholder;
    int guess_cols = 15, guess_str = 100, str_index = 0, current_column = 0;

    memset(file_data, 0, sizeof(*file_data));

    file = fopen(path, "r");
    if (!file)
        return 1;

    placeholder = calloc(guess_str, sizeof(char));
    file_data->values = calloc(1, sizeof(CSV_VALUE*));
    file_data->values[0] = calloc(guess_cols, sizeof(CSV_VALUE));

    fseek(file, 0, SEEK_END);
    file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    /*
        overloaded num_rows as index into values
        num_cols = count of value*
    */
    while (fread(&read_char, sizeof(read_char), 1, file) == 1)
    {
        if (read_char == '\n' || read_char == ',')
        {
            if (is_alpha(placeholder[0]))
            {
                file_data->values[file_data->num_rows][current_column].decimal_valid = 0;
                file_data->values[file_data->num_rows][current_column].string_val = malloc(sizeof(char) * str_index + 1);
                memcpy(file_data->values[file_data->num_rows][current_column].string_val, placeholder, sizeof(char) * str_index);
                file_data->values[file_data->num_rows][current_column].string_val[str_index] = 0;
            }else
            {
                placeholder[str_index + 1] = 0;
                file_data->values[file_data->num_rows][current_column].decimal_valid = 1;
                file_data->values[file_data->num_rows][current_column].decimal_val = strtold(placeholder, NULL);
            }
            memset(placeholder, 0, sizeof(char) * guess_str);

            if (read_char == ',')
            {
                current_column++;
                if (current_column + 1 > guess_cols)
                {
                    guess_cols = current_column + 1;
                    file_data->values[file_data->num_rows] = realloc(file_data->values[file_data->num_rows], guess_cols * sizeof(CSV_VALUE));
                }
            }
            str_index = 0;
            if (read_char == '\n')
            {
                if (file_data->num_colums < (current_column + 1))
                {
                    file_data->num_colums = current_column + 1;
                    file_data->values[file_data->num_rows] = realloc(file_data->values[file_data->num_rows], sizeof(CSV_VALUE) * file_data->num_colums);
                }
                file_data->num_rows++;
                if (ftell(file) == file_length)
                    break;
                file_data->values = realloc(file_data->values, sizeof(CSV_VALUE*) * file_data->num_rows + 1);
                file_data->values[file_data->num_rows] = calloc(file_data->num_colums, sizeof(CSV_VALUE));
                current_column = 0;
            }
            continue;
        }
        if (read_char == '\r')
            continue;
        if (str_index == guess_str - 2) /* allocate one early for guess_cols to allow for 0 to be set above */
        {
            /* very unlikely */
            printf("ln %d WARN: very long string in %s @ row %d col %d.\n", __LINE__, path, file_data->num_rows + 1, current_column);
            guess_str += 100;
            placeholder = realloc(placeholder, sizeof(char) * guess_str);
        }
        placeholder[str_index] = read_char;
        str_index++;
    }
    if (file_data->num_colums == 0 || file_data->num_rows == 0)
    {
        for (int i = 0; i < file_data->num_rows; i++)
        {
            if (file_data->values[i])
                free(file_data->values[i]);
        }
        if (file_data->values)
            free(file_data->values);
    }
    free(placeholder);
    fclose(file);
    return 0;
}

void free_csv(CSV_FILE *file_data)
{
    if (file_data->num_rows == 0 || file_data->num_colums == 0 || file_data->values == NULL)
        return;

    for (int r = 0; r < file_data->num_rows; r++)
        free(file_data->values[r]);
    free(file_data->values);
    memset(file_data, 0, sizeof(*file_data));
}
