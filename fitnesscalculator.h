#ifndef FITNESSCALCULATOR_H
#define FITNESSCALCULATOR_H


class FitnessCalculator
{
public:
    FitnessCalculator();
    float bmrCalc(float cm_len, float kg_wei, int age, int gender = 0);
    float bmiCalc(float cm_len, float kg_wei);

    enum CALCULATORS {
        BMR = 0,
        BMI = 1
    };

private:

};

#endif // FITNESSCALCULATOR_H
