#ifndef H_TEXT_H_100706175501__
#define H_TEXT_H_100706175501__

#define MAX_PRINT_VALUE_LENGTH (1024)
#define MAX_NEST_LEVEL         (50)

typedef enum
{
    T_NORMAL,
    T_ARRAY,
    T_STRUCT,
    T_STRING,
    T_RAW,
    T_NONE
} array_type_t;

struct nest_info_t
{
    array_type_t type;
    int num_of_element;
    int offset;
};


#endif //H_TEXT_H_100706175501__
