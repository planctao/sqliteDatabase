#!/bin/bash

#rm -rf mydb

gcc ./src/repl.c ./src/execute.c ./src/table.c -o ./build/db && ./build/db mydb



