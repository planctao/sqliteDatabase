
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "../include/lib.h"
void page_alloc(void **page) {
    *page = malloc(PAGE_SIZE); 
}

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

/*void *row_slot(Table *table, u_int32_t row_num) {
    u_int32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = table->page[page_num];

    if (page == NULL) {
        //alloc a page 
        table->page[page_num] = malloc(PAGE_SIZE);
        page = table->page[page_num];
    }

    u_int32_t row_offset = row_num % ROWS_PER_PAGE;
    u_int32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}*/

Table* db_open(const char* filename) {
    Pager *pager = pager_open(filename);
    u_int32_t num_rows = pager->file_length / ROW_SIZE;
    #ifdef DEBUG
        debugf("num_rows == %d && file_length == %d",num_rows,pager->file_length);
    #endif
    Table* table = (Table*)malloc(sizeof(Table));
    table->pager = pager;
    table->num_rows = num_rows; 
    return table;
}

void db_close(Table *table) {
    Pager *pager = table->pager;
    u_int32_t num_full_pages = table->num_rows / ROWS_PER_PAGE;
    debugf("now we try to exit\n");
    for (u_int32_t i = 0;i < num_full_pages;i++) {
        if (pager->pages[i] == NULL) {
            continue;
        }
        pager_flush(pager,i,PAGE_SIZE);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    u_int32_t num_additional_rows = table->num_rows % ROWS_PER_PAGE;
    debugf("num_additional_rows == %d\n",num_additional_rows);
    if (num_additional_rows > 0) {
        u_int32_t page_num = num_full_pages;
        if (pager->pages[page_num] != NULL) {
            pager_flush(pager, page_num, num_additional_rows * ROW_SIZE);
            free(pager->pages[page_num]);
            pager->pages[page_num] = NULL;
        }
    }

    int result = close(pager->file_decriptor);
    if (result == -1) {
        printf("Error closing %d\n",errno);
        exit(EXIT_FAILURE);
    }

    for (u_int32_t i = 0;i < TABLE_MAX_PAGES;i++) {
        void *page = pager->pages[i];
        if (page) {
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
}

/*
    pager_open: 
    first open a file and return its fileid.
    next create a new pager and malloc it.
    finally connect the fileid and new pager.
*/
Pager* pager_open(const char* filename) {
    int fd = open(filename, O_RDWR | O_CREAT , S_IWUSR | S_IRUSR);
    /*
        O_RDWR : read and write
        O_CREAT: creat if not exist
        S_IWUSR: user write permission
        S_IRUSR: user read perission

        fd means file_id
    */
    
    if (fd == -1) {
        printf("Unable to open the file!\n");
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(fd,0,SEEK_END);
    /*lseek: https://blog.csdn.net/qq_37414405/article/details/83688800*/

    Pager *pager = malloc(sizeof(Pager));
    pager->file_decriptor = fd;
    pager->file_length = file_length;

    for (u_int32_t i = 0;i < TABLE_MAX_PAGES;i++) {
        pager->pages[i] = NULL;
    }

    return pager;

}

void free_table(Table* table) {
    for (u_int32_t i = 0;i < table->num_rows;i++) {
        free(table->pager->pages[i]);
    }
    free(table);
}


/*
    get_page:
    if page_num in pager is NULL(chche miss), we should malloc one and return
    else we return the target page
*/
void *get_page(Pager* pager, u_int32_t page_num) {
    //debugf("page_num == %d\n",page_num);
    if (page_num > TABLE_MAX_PAGES) {
        printf("Tried to fetch page number out of bounds. %d > %d\n", page_num,
           TABLE_MAX_PAGES);
        exit(EXIT_FAILURE);
    }

    if(pager->pages[page_num] == NULL) {
        /*if cache miss*/
        void *page = malloc(PAGE_SIZE);
        u_int32_t num_pages = pager->file_length / PAGE_SIZE;

        if (pager->file_length % PAGE_SIZE != 0) {
            num_pages++;
        }

        if (page_num <= num_pages) {
            lseek(pager->file_decriptor,page_num * PAGE_SIZE,SEEK_SET);
            ssize_t bytes_read = read(pager->file_decriptor,page,PAGE_SIZE);
            if (bytes_read == -1) {
                printf("Error reading file: %d\n", errno);
                exit(EXIT_FAILURE);
            }
        }

        pager->pages[page_num] = page;
    }
    return pager->pages[page_num];
}


void pager_flush(Pager *pager, u_int32_t page_num, u_int32_t size) {
    if (pager->pages[page_num] == NULL) {
        printf("Tried to flush null page\n");
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(pager->file_decriptor,page_num * PAGE_SIZE,SEEK_SET);
    if (offset == -1) {
        printf("Error seeking: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    #ifdef DEBUG
    debugf("fd == %d && pages == %s \n",pager->file_decriptor,(char*)pager->pages[page_num]);
    #endif
    ssize_t byte_written = write(pager->file_decriptor,pager->pages[page_num],size);

    if (byte_written == -1) {
        printf("Error writing %d\n",errno);
        exit(EXIT_FAILURE);
    }
}

void serialize_row(Row* source, void* destination) {
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username),USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email),EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination) {
    memcpy(&(destination->id), source + ID_OFFSET,ID_SIZE);
    memcpy(&(destination->username),source + USERNAME_OFFSET,USERNAME_SIZE);
    memcpy(&(destination->email),source + EMAIL_OFFSET,EMAIL_SIZE);
}


/*some function about row*/
/*
    output
*/
void print_row(Row *row) {
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

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
void *row_slot(Table *table, u_int32_t row_num) {
    u_int32_t page_num = row_num / ROWS_PER_PAGE;

    void *page = get_page(table->pager,page_num);
    u_int32_t row_offset = row_num % ROWS_PER_PAGE;
    u_int32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}

