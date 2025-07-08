#include "isqlite3.h"
#include <sqlite3.h>

class Sqlite3Wrapper : public ISqlite3 {
public:
    int open(const std::string& filename, sqlite3** db) override
    {
        return sqlite3_open(filename.c_str(), db);
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