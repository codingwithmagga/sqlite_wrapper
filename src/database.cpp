#include "database.h"
#include <sqlite3.h>

std::expected<Database, std::string> Database::create(const std::filesystem::path& dbPath, ISqlite3* sqlite)
{
    sqlite3* db = nullptr;

    auto rc = sqlite->open(dbPath.string(), &db);

    if (rc != SQLITE_OK) {
        std::string errMsg = db ? sqlite->errmsg(db) : "Unknown error";
        if (db) {
            sqlite->close(db);
        }
        return std::unexpected("Failed to open database: " + errMsg);
    }

    return Database(db, sqlite);
}

inline Database::Database(sqlite3* db, ISqlite3* sqlite)
    : db(db), sqlite(sqlite)
{
}

Database::~Database()
{
    if (db) {
        sqlite->close(db);
    }
}
