#ifndef _LIB_H
#define _lIB_H
//#define DEBUG 1 //if open the mode of debug
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>

#define debugf printf

typedef struct{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

/*two of our new functions return enums indicating success or failure*/
typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR
}PrepareResult;

typedef enum{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
} ExecuteResult;

/*ROW*/
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef struct{
    u_int32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
#define offset_attribute(Struct, Attribute) (&(((Struct*)0)->Attribute))

extern const u_int32_t ID_SIZE;
extern const u_int32_t USERNAME_SIZE;
extern const u_int32_t EMAIL_SIZE;
extern const u_int32_t ID_OFFSET;
extern const u_int32_t USERNAME_OFFSET;
extern const u_int32_t EMAIL_OFFSET;
extern const u_int32_t ROW_SIZE;


/*Statement*/
typedef enum{
    STATE_INSERT,
    STATE_SELECT
} StatementType;
typedef struct{
    StatementType type;
    Row row_to_insert; //use in insert
} Statement;

#define TABLE_MAX_PAGES 100

/*Pager*/
typedef struct {
    int file_decriptor;
    u_int32_t file_length;
    void* pages[TABLE_MAX_PAGES];
} Pager;


/*Table*/
extern const u_int32_t PAGE_SIZE;/*it is the same as virtual page in most computer*/
extern const u_int32_t ROWS_PER_PAGE;
extern const u_int32_t TABLE_MAX_ROWS;
typedef struct {
    u_int32_t num_rows;
    Pager *pager;
} Table;


//function in repl.c
InputBuffer* new_input_buffer();
void print_prompt();
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);
MetaCommandResult do_meta_command(InputBuffer *input_buffer,Table* table);
PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);
ExecuteResult execute_statement(Statement* statement, Table* table);
void parse_input_buffer(InputBuffer* input_buffer, char** args, int *argc);
void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void *row_slot(Table *table, u_int32_t row_num);
Table* new_table();
void free_table(Table* table);
void print_row(Row *row);
Pager* pager_open(const char* filename);
void *get_page(Pager* pager, u_int32_t page_num);
Table* db_open(const char* filename);
void db_close(Table *table);
void pager_flush(Pager *pager, u_int32_t page_num, u_int32_t size);


#endif