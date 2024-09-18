#include <iostream>

float fast_inverse_sqrt(float number, int iters)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*)&y;            // Evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1); // What the heck? The magic number!
    y = *(float*)&i;

    for (int n = i; n < iters; ++n) {
        y = y * (threehalfs - (x2 * y * y)); // 1st iteration of Newton's method
    }
    // y = y * (threehalfs - (x2 * y * y));   // 2nd iteration can be added for more precision

    return y;
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < 10; ++i) {
        std::cout << i << std::endl;
        std::cout << 1 / fast_inverse_sqrt(2.0, i) << std::endl;
    }
};
