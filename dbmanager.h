#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSql>
#include <QSqlDatabase>

class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();

    bool addEntry(const QString &name);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
