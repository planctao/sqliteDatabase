
#include "../include/lib.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
/*
    select certain element, but now we can only choose the whole table
    put each sentence into a target row using deserialize_row
    then print the target row
*/
ExecuteResult execute_select(Statement* statement, Table* table) {
    Row row;
    for (u_int32_t i = 0;i < table->num_rows;i++) {
        deserialize_row(row_slot(table,i), &row);
        print_row(&row);
    }
    return EXECUTE_SUCCESS;
}

/*
    to insert a row at the end of the table
    we should first exam if the table is full, if full, return EXECUTE_TABLE_FULL
*/
ExecuteResult execute_insert(Statement* statement, Table* table) {
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    Row* row_to_insert = &(statement->row_to_insert);
    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    //("statement: %d %s %s\n",statement->row_to_insert.id,statement->row_to_insert.email,statement->row_to_insert.username);
    //debugf("row_to_insert: %d %s %s\n",row_to_insert->id,row_to_insert->email,row_to_insert->username);
    (table->num_rows)++;

    return EXECUTE_SUCCESS;
}

/*
    find 
*/
ExecuteResult execute_statement(Statement* statement, Table* table) {
    switch (statement->type) {
        case (STATE_INSERT) :
            return execute_insert(statement, table);
            break;
        case (STATE_SELECT) :
            return execute_select(statement, table);
            break;
    }
}


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


/*
    do_meta_command is a wrapper,it is to parse meta_command which starts as "."
*/
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
        sscanf(input_buffer->buffer,"insert %d %s %s",&statement->row_to_insert.id,statement->row_to_insert.username,statement->row_to_insert.email);
        parse_input_buffer(input_buffer, args,&argc);
        //debugf("inputbuffer: %s\n",input_buffer->buffer);
        if (argc < 3) {
            return PREPARE_SYNTAX_ERROR;
        }    
        //debugf("prepare_statement: %d %s %s",statement->row_to_insert.id,statement->row_to_insert.email,statement->row_to_insert.username);
        //int args_assigned = sscanf(input_buffer->buffer, "insert %s %s %s", &(statement->))
        return PREPARE_SUCCESS;
    }
    else if (strncmp(input_buffer->buffer,"select",6) == 0) {
        statement->type = STATE_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}


