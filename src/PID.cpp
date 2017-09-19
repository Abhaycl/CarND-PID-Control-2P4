#include "PID.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    
    p_error = 0;
    i_error = 0;
    d_error = 0;
    
    // Twiddling parameters
    step = 1;
    index = 2; // This will wrao back to 0 after the first twiddle loop
	dp = {0.1 * Kp, 0.1 * Ki, 0.1 * Kd};
    n_settle_steps = 100;
    n_eval_steps = 2000;
    total_error = 0;
    best_error = std::numeric_limits<double>::max();
    twiddle = false;
	adding = false;
    subtracting = false;
}

void PID::UpdateError(double cte) {
    // To get correct initial d_error
    if (step == 1) {
        p_error = cte;
    }
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
    
    // Update total error only if we're past number of settle steps
    if (step % (n_settle_steps + n_eval_steps) > n_settle_steps) {
        total_error += pow(cte, 2);
    }
    
    // Last step in twiddle loop
    if (twiddle && step % (n_settle_steps + n_eval_steps) == 0) {
        cout << "step: " << step << endl;
        cout << "total error: " << total_error << endl;
        cout << "best error: " << best_error << endl;
        if (total_error < best_error) {
            cout << "improvement!" << endl;
            best_error = total_error;
            if (step != n_settle_steps + n_eval_steps) {
                // Don't do it if it's the first time
                dp[index] *= 1.1;
            }
            // Next parameter
            index = (index + 1) % 3;
            adding = subtracting = false;
        }
        if (!adding && !subtracting) {
            // Try adding dp[index] to params[index]
            if (index == 0) {
                Kp += dp[index];
            } else if (index == 1) {
                Ki += dp[index];
            } else if (index == 2) {
                Kd += dp[index];
            } else {
                std::cout << "Index out of bounds";
            }
            
            adding = true;
        }
        else if (adding && !subtracting) {
            // Try subtracting dp[index] from params[index]
            if (index == 0) {
                Kp += (-2 * dp[index]);
            } else if (index == 1) {
                Ki += (-2 * dp[index]);
            } else if (index == 2) {
                Kd += (-2 * dp[index]);
            } else {
                std::cout << "Index out of bounds";
            }
            
            subtracting = true;         
        }
        else {
            // Set it back, reduce dp[index], move on to next parameter
            if (index == 0) {
                Kp += dp[index];
            } else if (index == 1) {
                Ki += dp[index];
            } else if (index == 2) {
                Kd += dp[index];
            } else {
                std::cout << "Index out of bounds";
            }
            
            dp[index] *= 0.9;
            // Next parameter
            index = (index + 1) % 3;
            adding = subtracting = false;
        }
        total_error = 0;
        cout << "new parameters" << endl;
        cout << "P: " << Kp << ", I: " << Ki << ", D: " << Kd << endl;
    }
    step++;
}

double PID::TotalError() {
    return 0;
}