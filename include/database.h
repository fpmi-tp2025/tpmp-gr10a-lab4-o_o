#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>

class Database {
public:
    Database(const std::string& db_name);
    ~Database();

    bool execute(const std::string& sql);
    sqlite3_stmt* prepareQuery(const std::string& sql);
    bool bindInt(sqlite3_stmt* stmt, int index, int value);
    bool bindDouble(sqlite3_stmt* stmt, int index, double value);
    bool bindText(sqlite3_stmt* stmt, int index, const std::string& value);
    bool step(sqlite3_stmt* stmt);
    void finalize(sqlite3_stmt* stmt);
    sqlite3* getHandle() const { return db; }

private:
    sqlite3* db;
};

#endif // DATABASE_H