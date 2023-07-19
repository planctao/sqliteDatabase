
//#include<string.h>
//#include<stdio.h>
#include "../include/lib.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
/*
    serialize_row and deserialize_row is to save the capacity between the struct Row
    and true space in the computer
    for the reason of alignment("dui qi" in Chinese), we can store our data as the type of 
    struct Row, we should save our space and store our data in a sequence line.
*/
/*void serialize_row(Row* source, void* destination) {
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username),USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email),EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination) {
    memcpy(&(destination->id), source + ID_OFFSET,ID_SIZE);
    memcpy(&(destination->username),source + USERNAME_OFFSET,USERNAME_SIZE);
    memcpy(&(destination->email),source + EMAIL_OFFSET,EMAIL_SIZE);
}
*/
/*
    output
*/
/*
void print_row(Row *row) {
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}
*/
/*
input a row_num to find the position of the corresponding row_num in the table
eg:
    input : row_num

    each page has ROWS_PER_PAGE rows
    (row_num / ROWS_PER_PAGE) means which page in the table
    (row_num % ROWS_PER_PAGE) means the offset in the target page
    ps: if the page is not find, then alloc one and find the position
    if the page exists, then find the target position

    output:bytes position in the table
*/
/*
void *row_slot(Table *table, u_int32_t row_num) {
    u_int32_t page_num = row_num / ROWS_PER_PAGE;

    void *page = get_page(table->pager,page_num);
    u_int32_t row_offset = row_num % ROWS_PER_PAGE;
    u_int32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}
*/
