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
    QSqlDatabase GetDatabase();
    void OpenConnection();
    void CloseConnection();
private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_HPP
