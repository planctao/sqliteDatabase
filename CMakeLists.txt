# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (sqlite_db)



# 指定生成目标
#add_executable(repl execute.c repl.c row.c table.c)

add_executable(./build/reql ./src/repl.c/execute.c/table.c)