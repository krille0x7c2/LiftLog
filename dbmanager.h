#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "lift.h"
#include <QSql>
#include <QSqlDatabase>
#include <QList>

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

    bool entryDuplicate(const QString &date, const QString &exercise) const;

    bool updateEntry(const QString &date, const QString &exercise,
                     const int reps, const int sets, const float weight);

    void printDatabase() const;

    QList<Lift *> *getExerciseData(QString &exercise);

    bool removeAllEntries();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
