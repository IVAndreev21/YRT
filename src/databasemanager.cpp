#include "databasemanager.hpp"

DatabaseManager::DatabaseManager() {

}

QSqlDatabase DatabaseManager::getDatabase() {
    return db;
}

bool DatabaseManager::openConnection() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("project-yrt.mysql.database.azure.com");
    db.setPort(3306);  // Default MySQL port
    db.setDatabaseName("yrt");
    db.setUserName("sqladmin");
    db.setPassword("Project-YRT");

    if (db.open()) {
        return true;
    } else {
        // Handle connection error
        return false;
    }
}

void DatabaseManager::closeConnection() {
    db.close();
}

