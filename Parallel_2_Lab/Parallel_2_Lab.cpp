#include <omp.h>
#include <cmath>
#include <iostream>

using namespace std;


typedef double (*func)(double);
double integral_function(double x)
{
    return (4 * x) / ( 1 + x * x);
}

double trapezoid(double a, double b, func f)
{
    return (f(a) + f(b)) * (b - a) / 2;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    int n = rand();
    double a = 0 , b = 1 , integral_sum = 0.0;

#pragma omp parallel reduction(+ : integral_sum)
    {
# pragma omp for
        for (size_t i = 0; i < n; i++)
            integral_sum += trapezoid(a + (b - a) * (i) / n, a + (b - a) * (i + 1) / n, integral_function);;
    }
    cout << "Результат: " << integral_sum << endl;
    return 0;
}