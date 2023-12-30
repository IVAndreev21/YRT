#include "databasemanager.hpp"

DatabaseManager::DatabaseManager() {

}

QSqlDatabase DatabaseManager::getDatabase() {
    return db;
}

void DatabaseManager::openConnection() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("project-yrt.mysql.database.azure.com");
    db.setPort(3306);  // Default MySQL port
    db.setDatabaseName("yrt");
    db.setUserName("sqladmin");
    db.setPassword("Project-YRT");

    if (db.open() && db.isOpen()) {
        qDebug() << "Database opened successfully";
    } else {
        // Handle connection error
        qDebug() << "Database failed to open";

    }
}

void DatabaseManager::closeConnection() {
    db.close();
}

