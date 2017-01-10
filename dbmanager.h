#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSql>
#include <QSqlDatabase>

class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();

    bool isOpen() const;

    bool createTable();

    bool addEntry(const QString &date, const QString &exercise,
                  const int reps, const int sets, const float weight);

    bool removeEntry(const QString &date);

    bool entryExists(const QString &date) const;

    void printDatabase() const;

    bool removeAllEntrys();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
