#include <iostream>
#include <iomanip>
#include "StatsCalculator.h"
#include "Vector.h"

using namespace std;

int main()
{
    cout << fixed << setprecision(4);
    cout << "=== StatsCalculator Test ===\n\n";

    StatsCalculator stats;

    // Test data
    Vector<double> data1;
    data1.Append(10.0);
    data1.Append(20.0);
    data1.Append(30.0);
    data1.Append(40.0);
    data1.Append(50.0);

    Vector<double> data2;
    data2.Append(5.0);
    data2.Append(10.0);
    data2.Append(15.0);
    data2.Append(20.0);
    data2.Append(25.0);

    Vector<double> emptyData;

    // Test 1: getMean
    cout << "Test 1: getMean\n";
    double mean;
    if (stats.getMean(data1, mean))
        cout << "  Mean of [10,20,30,40,50] = " << mean << " (expected: 30)\n";
    else
        cout << "  FAILED\n";

    if (stats.getMean(emptyData, mean))
        cout << "  Empty data: FAILED (should return false)\n";
    else
        cout << "  Empty data: Correctly returned false\n";
    cout << endl;

    // Test 2: getSampleStandardDeviation
    cout << "Test 2: getSampleStandardDeviation\n";
    double stdDev;
    if (stats.getSampleStandardDeviation(data1, 30.0, stdDev))
        cout << "  StdDev of [10,20,30,40,50] = " << stdDev << " (expected: 15.8114)\n";
    else
        cout << "  FAILED\n";
    cout << endl;

    // Test 3: getSum
    cout << "Test 3: getSum\n";
    double sum;
    if (stats.getSum(data1, sum))
        cout << "  Sum of [10,20,30,40,50] = " << sum << " (expected: 150)\n";
    else
        cout << "  FAILED\n";
    cout << endl;

    // Test 4: getsPCC
    cout << "Test 4: getsPCC (Pearson Correlation)\n";
    double corr;
    if (stats.getsPCC(data1, data2, corr))
        cout << "  Correlation [10,20,30,40,50] vs [5,10,15,20,25] = " << corr << " (expected: 1.00)\n";
    else
        cout << "  FAILED\n";

    Vector<double> data3;
    data3.Append(10.0);
    data3.Append(20.0);
    data3.Append(30.0);
    data3.Append(40.0);
    data3.Append(100.0);

    if (stats.getsPCC(data1, data3, corr))
        cout << "  Correlation [10,20,30,40,50] vs [10,20,30,40,100] = " << corr << " (expected: ~0.96)\n";
    else
        cout << "  FAILED\n";
    cout << endl;

    // Test 5: getMad (Mean Absolute Deviation)
    cout << "Test 5: getMad\n";
    double mad;
    if (stats.getMad(data1, mad))
        cout << "  MAD of [10,20,30,40,50] = " << mad << " (expected: 12.0)\n";
    else
        cout << "  FAILED\n";
    cout << endl;

    // Test 6: Edge Cases
    cout << "Test 6: Edge Cases\n";

    Vector<double> singleValue;
    singleValue.Append(42.0);

    if (stats.getSampleStandardDeviation(singleValue, 42.0, stdDev))
        cout << "  Single value stdDev: FAILED (should return false)\n";
    else
        cout << "  Single value stdDev: Correctly returned false\n";

    Vector<double> twoValues;
    twoValues.Append(10.0);
    twoValues.Append(20.0);

    if (stats.getSampleStandardDeviation(twoValues, 15.0, stdDev))
        cout << "  Two values stdDev = " << stdDev << " (expected: 7.0711)\n";
    else
        cout << "  Two values stdDev: FAILED\n";

    cout << "\n=== Test Complete ===\n";
    return 0;
}
