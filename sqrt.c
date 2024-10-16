#include <emacs-module.h>
#include <stdio.h>

int plugin_is_GPL_compatible; // Declare GPL compatibility

// Your existing code, including the module functions

int emacs_module_init(struct emacs_runtime* ert)
{
    return 0; // Your initialization code here (if needed)
}

float newton_sqrt(float number)
{
    if (number <= 0)
        return 0;                // Handle invalid inputs like negative numbers
    float approx = number / 2.0; // Initial guess
    float better_approx;

    // Iterate the Newton-Raphson method
    for (int i = 0; i < 10; i++) {
        better_approx = 0.5 * (approx + number / approx);
        approx = better_approx;
    }

    return approx;
}
