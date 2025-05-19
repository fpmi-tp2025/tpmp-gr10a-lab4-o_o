#include "database.h"
#include <iostream>

Database::Database(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

bool Database::execute(const std::string& sql) {
    char* err_msg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK) {
        std::cerr << "Ошибка SQL: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

sqlite3_stmt* Database::prepareQuery(const std::string& sql) {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    return stmt;
}

bool Database::bindInt(sqlite3_stmt* stmt, int index, int value) {
    if (sqlite3_bind_int(stmt, index, value) != SQLITE_OK) {
        std::cerr << "Ошибка привязки int: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

bool Database::bindDouble(sqlite3_stmt* stmt, int index, double value) {
    if (sqlite3_bind_double(stmt, index, value) != SQLITE_OK) {
        std::cerr << "Ошибка привязки double: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

bool Database::bindText(sqlite3_stmt* stmt, int index, const std::string& value) {
    if (sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Ошибка привязки текста: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

bool Database::step(sqlite3_stmt* stmt) {
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        std::cerr << "Ошибка выполнения шага: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return rc == SQLITE_ROW;
}

void Database::finalize(sqlite3_stmt* stmt) {
    sqlite3_finalize(stmt);
}