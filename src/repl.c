

/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>*/
#include "../include/lib.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>

const u_int32_t ID_SIZE = size_of_attribute(Row, id);
const u_int32_t USERNAME_SIZE = size_of_attribute(Row,username);
const u_int32_t EMAIL_SIZE = size_of_attribute(Row, email);
const u_int32_t ID_OFFSET = 0;
const u_int32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const u_int32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE; 
const u_int32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE+ EMAIL_SIZE;

const u_int32_t PAGE_SIZE = 4096;/*it is the same as virtual page in most computer*/
#define TABLE_MAX_PAGES 100
const u_int32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const u_int32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("argc is too low in main\n");
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1];
    Table *table = db_open(filename);
    InputBuffer *input_buffer = new_input_buffer();
    while(1) {
        print_prompt();
        read_input(input_buffer);

        /*meta-command*/
        if (strncmp(input_buffer->buffer,".",1) == 0) {
            switch (do_meta_command(input_buffer,table)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS) :
                break;
            case (PREPARE_SYNTAX_ERROR) :
                printf("PREPARE_SYNTAX_ERROR: we could not parse statement!\n");
                continue; 
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n",input_buffer->buffer);
                continue;//if unrecognized keyword we continue for next line to parse
        }

        //execute_statement(&statement);
        switch (execute_statement(&statement, table)) {
            case (EXECUTE_SUCCESS) :
                printf("execute success!\n");
                break;
            case (EXECUTE_TABLE_FULL) :
                printf("execute error: table is full!\n");
                break;    
        }
    }
}


/*
InputBuffer* new_input_buffer() {
    InputBuffer *input_buffer = (InputBuffer*)(malloc(sizeof(InputBuffer)));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() {
    printf("db > ");
}

void read_input(InputBuffer *input_buffer) {
  ssize_t byte_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (byte_read <= 0) {
        printf("read_input error!\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = byte_read - 1;
    input_buffer->buffer[byte_read - 1] = '\0';
}

void close_input_buffer(InputBuffer *input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

*/
/*
    do_meta_command is a wrapper,it is to parse meta_command which starts as "."
*/
/*
MetaCommandResult do_meta_command(InputBuffer *input_buffer,Table* table) {
    if (strcmp(input_buffer->buffer,".exit") == 0) {
        printf("we eixt!\n");
        db_close(table);
        exit(EXIT_SUCCESS);
    }
    else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

void parse_input_buffer(InputBuffer* input_buffer, char** args, int *argc) {
    *argc = 0;
    while(*(input_buffer->buffer)) {
        if (*(input_buffer->buffer) == ' ') {
            (input_buffer->buffer)++;
            continue;
        }
        else {
            int start = 0;
            while(*(input_buffer->buffer) != '\0' && *(input_buffer->buffer) != ' ') {
                args[*argc][start++] = *(input_buffer->buffer);
                (input_buffer->buffer)++;
            }
            args[*argc][start] = '\0';
            (*argc)++;
        }
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement) {
    char **args = (char**)malloc(sizeof(char*) * 10);
    for (int i = 0;i < 10;i++) {args[i] = (char*)malloc(sizeof(char) * 50);}
    int argc = 0;

    if (strncmp(input_buffer->buffer,"insert",6) == 0) {
        statement->type = STATE_INSERT;
        parse_input_buffer(input_buffer, args,&argc);
        if (argc < 3) {
            return PREPARE_SYNTAX_ERROR;
        }        
        //int args_assigned = sscanf(input_buffer->buffer, "insert %s %s %s", &(statement->))
        return PREPARE_SUCCESS;
    }
    else if (strncmp(input_buffer->buffer,"select",6) == 0) {
        statement->type = STATE_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}
*/

