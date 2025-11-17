#include <vector>
#include "ceres/ceres.h"

// A CostFunction implementing analytically derivatives for the
// function f(x) = 10 - x.
class QuadriticCostFunction : public ceres::SizedCostFunction<1,1>
{
private:
    /* data */
public:
    bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override{
        double x  = parameters[0][0];
        // f(x) = 10 - x.
        residuals[0] = 10 - x;
    // f'(x) = -1. Since there's only 1 parameter and that parameter
    // has 1 dimension, there is only 1 element to fill in the
    // jacobians.
    //
    // Since the Evaluate function can be called with the jacobians
    // pointer equal to nullptr, the Evaluate function must check to see
    // if jacobians need to be computed.
    //
    // For this simple problem it is overkill to check if jacobians[0]
    // is nullptr, but in general when writing more complex
    // CostFunctions, it is possible that Ceres may only demand the
    // derivatives w.r.t. a subset of the parameter blocks.
        if (jacobians != nullptr && jacobians[0] != nullptr)
        {
            jacobians[0][0] = -1;
        }
        return true;
    }
};

int main(int argc, char** argv){
    // The variable to solve for with its initial value. It will be
    // mutated in place by the solver.
    double x = 5.0;
    const double initial_x = x;
    // Build the problem.
    ceres::Problem problem;
    // Set up the only cost function (also known as residual). This uses
    // auto-differentiation to obtain the derivative (jacobian).
    // ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction<CostFunctor,1,1>(new CostFunctor);
    // numeric differentiation to obtain the derivative (jacobian)
    ceres::CostFunction* cost_function = new QuadriticCostFunction;
    problem.AddResidualBlock(cost_function, nullptr, &x);
    // Run the solver
    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout << summary.BriefReport() << "\n";
    std::cout << "x : " << initial_x << " -> " << x << "\n";  
    return 0;
}

