#include "fitnesscalculator.h"

FitnessCalculator::FitnessCalculator()
{

}

float FitnessCalculator::bmrCalc(float cm_len, float kg_wei, int age, int gender)
{
    return (gender == 0 ? (66 + (13.7 * kg_wei) + (5 * cm_len) - (6.8 * age) ) :
                          (655 + (9.6 * kg_wei) + (1.8 * cm_len) - (4.7 * age) ));
}

float FitnessCalculator::bmiCalc(float cm_len, float kg_wei)
{
     return (kg_wei / (cm_len * cm_len));
}
