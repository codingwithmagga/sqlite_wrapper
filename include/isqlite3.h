#pragma once
#include <string_view>

struct sqlite3;

class ISqlite3 {
public:
    virtual ~ISqlite3() = default;
    virtual int open(std::string_view filename, sqlite3** db) = 0;
    virtual int close(sqlite3* db) = 0;
    virtual const char* errmsg(sqlite3* db) = 0;
};