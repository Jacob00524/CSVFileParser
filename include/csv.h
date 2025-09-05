#define is_alpha(x) ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || x == '_')

typedef struct CSV_VALUE
{
    int decimal_valid;
    char *string_val;
    double decimal_val;
}CSV_VALUE;

typedef struct CSV_FILE
{
    int num_colums;
    int num_rows;
    CSV_VALUE **values;
}CSV_FILE;

int read_csv(char *path, CSV_FILE *file_data);
void free_csv(CSV_FILE *file_data);
