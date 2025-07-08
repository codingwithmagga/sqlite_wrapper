#pragma once

#include <expected>
#include <filesystem>
#include <string>

#include "isqlite3.h"

class Database {
public:
    static std::expected<Database, std::string> create(const std::filesystem::path& dbPath, ISqlite3* sqlite);

    ~Database();

private:
    Database(sqlite3* db, ISqlite3* sqlite);

    sqlite3* db = nullptr;
    ISqlite3* sqlite = nullptr;
};
