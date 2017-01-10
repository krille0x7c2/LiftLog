#include "lift.h"

Lift::Lift()
{

}

Lift::Lift(const QString &date, const QString &exercise, const int reps, const int sets, const float weight)
{
    this->setDate(date);
    this->setExercise(exercise);
    this->setReps(reps);
    this->setSets(sets);
    this->setWeight(weight);
}

QString Lift::getDate() const
{
    return date;
}

void Lift::setDate(const QString &value)
{
    date = value;
}

QString Lift::getExercise() const
{
    return exercise;
}

void Lift::setExercise(const QString &value)
{
    exercise = value;
}

int Lift::getReps() const
{
    return reps;
}

void Lift::setReps(int value)
{
    reps = value;
}

int Lift::getSets() const
{
    return sets;
}

void Lift::setSets(int value)
{
    sets = value;
}

float Lift::getWeight() const
{
    return weight;
}

void Lift::setWeight(float value)
{
    weight = value;
}
