#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    double p1 = 0.1 * 0.1 * 0.1 * 0.1;
    double p2 = 0.9 * 0.1 * 0.1 * 0.1;
    double p3 = 1.0 * 0.9 * 0.1 * 0.1;
    printf("%.6lf %.6lf %.6lf", p1, p2, p3);
    return 0;
}