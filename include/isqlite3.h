#pragma once
#include <string>

struct sqlite3;

class ISqlite3 {
public:
    virtual ~ISqlite3() = default;
    virtual int open(const std::string& filename, sqlite3** db) = 0;
    virtual int close(sqlite3* db) = 0;
    virtual const char* errmsg(sqlite3* db) = 0;
};