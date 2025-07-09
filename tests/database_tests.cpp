#include "database.h"
#include "isqlite3.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

constexpr int SQLITE_OK = 0;
constexpr int SQLITE_ERROR = 1;

class MockSqlite3 : public ISqlite3 {
public:
    MOCK_METHOD(int, open, (std::string_view filename, sqlite3** db), (override));
    MOCK_METHOD(int, close, (sqlite3 * db), (override));
    MOCK_METHOD(const char*, errmsg, (sqlite3 * db), (override));
};

// Need to define the struct here
struct sqlite3 {
};

class DatabaseTest : public ::testing::Test {
};

TEST_F(DatabaseTest, CreateDatabaseSuccess)
{
    MockSqlite3 mockSqlite;
    sqlite3 fakeDb {};

    EXPECT_CALL(mockSqlite, open("test.db", _))
        .WillOnce(
            [&](std::string_view, sqlite3** db) {
                *db = &fakeDb;
                return SQLITE_OK;
            });

    auto result = Database::create("test.db", &mockSqlite);
    EXPECT_TRUE(result.has_value());
}

TEST_F(DatabaseTest, CreateDatabaseFailure)
{
    MockSqlite3 mockSqlite;
    sqlite3 fakeDb {};

    EXPECT_CALL(mockSqlite, open("/invalid/path/to/db.sqlite", _))
        .WillOnce(
            [&](std::string_view, sqlite3** db) {
                *db = &fakeDb;
                return SQLITE_ERROR;
            });
    EXPECT_CALL(mockSqlite, errmsg(&fakeDb))
        .WillOnce(Return("mocked error"));
    EXPECT_CALL(mockSqlite, close(&fakeDb))
        .WillOnce(Return(SQLITE_OK));

    auto result = Database::create("/invalid/path/to/db.sqlite", &mockSqlite);
    EXPECT_FALSE(result.has_value());
    if (!result.has_value()) {
        EXPECT_NE(result.error().find("Failed to open database"), std::string::npos);
    }
}
