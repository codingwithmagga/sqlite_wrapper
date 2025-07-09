#include "isqlite3.h"
#include <sqlite3.h>

class Sqlite3Wrapper : public ISqlite3 {
public:
    int open(std::string_view filename, sqlite3** db) override
    {
        return sqlite3_open(filename.data(), db);
    }
    int close(sqlite3* db) override
    {
        return sqlite3_close(db);
    }
    const char* errmsg(sqlite3* db) override
    {
        return sqlite3_errmsg(db);
    }
};