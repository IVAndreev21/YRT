#include "databasemanager.hpp"

DatabaseManager::DatabaseManager() {

}

QSqlDatabase DatabaseManager::getDatabase() {
    return m_db;
}

void DatabaseManager::openConnection() {
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("project-yrt.mysql.database.azure.com");
    m_db.setPort(3306);  // Default MySQL port
    m_db.setDatabaseName("yrt");
    m_db.setUserName("sqladmin");
    m_db.setPassword("Project-YRT");

    if (m_db.open() && m_db.isOpen()) {
        qDebug() << "Database opened successfully";
    } else {
        // Handle connection error
        qDebug() << "Database failed to open";

    }
}

void DatabaseManager::closeConnection() {
    m_db.close();
}

