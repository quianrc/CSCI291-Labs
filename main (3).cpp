#include <iostream>
#include <iomanip>
using namespace std;

// 1) Template Function
template <typename S>
S calibrateValue(const S &x, char factor) {
    return x * factor;
}

// 2) adjustReading()
void adjustReading(double *value, double offset = 1.25) {
    *value += offset;
}

// 3) clampReading()
void clampReading(double &r) {
    if (r < 0) r = 0;
    else if (r > 100) r = 100;
}

// 4) computeDifference()
double computeDifference(int a, double b) {
    return a - b;
}

// 5) main()
int main() {
    int intSensor;
    double doubleSensor;

    // Formatting
    cout << fixed << setprecision(4);

    // (i) Input values
    cout << "Enter integer sensor reading: ";
    cin >> intSensor;

    cout << "Enter double sensor reading: ";
    cin >> doubleSensor;

    // (ii) Calibrate both values using factor = 2
    int calibratedInt = calibrateValue(intSensor, 2);
    double calibratedDouble = calibrateValue(doubleSensor, 2);

    cout << setw(10) << calibratedInt << endl;
    cout << setw(10) << calibratedDouble << endl;

    // (iii) Convert calibrated integer to double
    double intAsDouble = static_cast<double>(calibratedInt);

    // (iv) Adjust readings
    adjustReading(&intAsDouble);         // uses default offset 1.25
    adjustReading(&calibratedDouble, 3.4);

    cout << setw(10) << intAsDouble << endl;
    cout << setw(10) << calibratedDouble << endl;

    // (v) Clamp both adjusted values
    clampReading(intAsDouble);
    clampReading(calibratedDouble);

    cout << setw(10) << intAsDouble << endl;
    cout << setw(10) << calibratedDouble << endl;

    // (vi) Convert clamped double-from-int back to integer
    int finalIntValue = static_cast<int>(intAsDouble);
    cout << setw(10) << finalIntValue << endl;

    // (vii) Compute difference double - integer (but function is a - b)
    double diff = computeDifference(finalIntValue, calibratedDouble);
    cout << setw(10) << diff << endl;

    return 0;
}
