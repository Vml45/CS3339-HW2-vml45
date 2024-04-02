//Victor Lopez (vml45)
//Ali Khawaja (xyr5)
#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <limits>

using namespace std;

// Function to convert a float value to IEEE 754 bit representation
bitset<32> cvtToIEEE(float f) {
    auto *bits_ptr = reinterpret_cast<unsigned int *>(&f);
    bitset<32> bs(*bits_ptr);
    return bs;
}

int main(int argc, char *argv[]) {
    // Check if the number of arguments is correct
    if (argc != 3) {
        cout << "usage: " << argv[0] << " loop_bound loop_counter" << endl;
        return 1; // indicate error
    }

    // Parse command-line arguments
    float loopBound, loopCounter;
    stringstream(argv[1]) >> loopBound;
    stringstream(argv[2]) >> loopCounter;

    // Display loop bound and loop counter IEEE representations
    cout << "Loop bound: 0 ";
    cout << cvtToIEEE(loopBound).to_string().substr(1, 8) << " ";
    cout << cvtToIEEE(loopBound).to_string().substr(9) << endl;

    cout << "Loop counter: 0 ";
    cout << cvtToIEEE(loopCounter).to_string().substr(1, 8) << " ";
    cout << cvtToIEEE(loopCounter).to_string().substr(9) << endl;

    // Extract exponents
    int boundExponent = (cvtToIEEE(loopBound) >> 23).to_ulong();
    int counterExponent = (cvtToIEEE(loopCounter) >> 23).to_ulong();

    // Check for potential overflow
    int expDiff = abs(boundExponent - counterExponent);
    if (expDiff >= 23) { // Exponent difference more than or equal to 23 indicates overflow
        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold:" << endl;
        float overflow_threshold = numeric_limits<float>::max() / 2;
        cout << scientific << setprecision(6) << overflow_threshold << endl;
        cout << "0 ";
        cout << cvtToIEEE(overflow_threshold).to_string().substr(1, 8) << " ";
        cout << cvtToIEEE(overflow_threshold).to_string().substr(9) << endl;
    } else {
        cout << "There is no overflow!" << endl;
    }

    return 0;
}
