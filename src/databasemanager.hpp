#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDebug>
class DatabaseManager
{
public:
    DatabaseManager();
    QSqlDatabase getDatabase();
    void openConnection();
    void closeConnection();
private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_HPP
