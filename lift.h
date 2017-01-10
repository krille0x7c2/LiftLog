#ifndef LIFT_H
#define LIFT_H

#include <QString>
#include <QDateTime>

class Lift
{
public:
    Lift();
    Lift(const QString &date, const QString &exercise, const int reps, const int sets, const float weight);
    QString getDate() const;
    void setDate(const QString &value);

    QString getExercise() const;
    void setExercise(const QString &value);

    int getReps() const;
    void setReps(int value);

    int getSets() const;
    void setSets(int value);

    float getWeight() const;
    void setWeight(float value);

private:
    QString date;
    QString exercise;
    int reps;
    int sets;
    float weight;
};

#endif // LIFT_H
