#include <cmath>
#include <iostream>
float erf0(float x)
{
    // constants
    float a1 = (float)0.254829592;
    float a2 = (float)-0.284496736;
    float a3 = (float)1.421413741;
    float a4 = (float)-1.453152027;
    float a5 = (float)1.061405429;
    float p = (float)0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x);

    // A&S formula 7.1.26
    float t = 1.0f / (1.0f + p * x);
    float y = 1.0f - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    return sign * y;
}
void testErf()
{
    // Select a few input values
    float x[] =
    {
    -3.0f,
    -1.0f,
    0.0f,
    0.5f,
    2.1f
    };

    // Output computed by Mathematica
    // y = Erf[x]
    float y[] =
    {
    -0.999977909503f,
    -0.842700792950f,
    0.0f,
    0.520499877813f,
    0.997020533344f
    };

    int numTests = sizeof(x) / sizeof(float);

    float maxError = 0.0;
    for (int i = 0; i < numTests; ++i) {
        float error = fabs(y[i] - erf(x[i]));
        if (error > maxError)
            maxError = error;
    }

    std::cout << "Maximum error: " << maxError << "\n";
}
int main()
{
    testErf();
}