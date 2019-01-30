#include "nmpc_model.hpp"
#include "multiple_shooting_cgmres.hpp"
#include "multiple_shooting_cgmres_simulator.hpp"


int main()
{
    // Define the model in NMPC.
    NMPCModel nmpc_model;

    // Define the solver of C/GMRES.
    MultipleShootingCGMRES nmpc_solver(1.0, 1.0, 50, 1.0e-06, 1000, 3);


    // Set the initial state.
    Eigen::VectorXd initial_state(nmpc_model.dimState());
    initial_state = Eigen::VectorXd::Zero(nmpc_model.dimState());

    // Set the initial guess of the control input vector.
    Eigen::VectorXd initial_guess_control_input(nmpc_model.dimControlInput()+nmpc_model.dimConstraints());
    initial_guess_control_input = Eigen::VectorXd::Zero(nmpc_model.dimControlInput()+nmpc_model.dimConstraints());


    // Initialize the solution of the C/GMRES method.
    nmpc_solver.initSolution(0, initial_state, initial_guess_control_input, 1.0e-06, 50);

    // Perform a numerical simulation.
    nmpcsim::simulation(nmpc_solver, initial_state, 0, 10, 0.001, "example1");


    return 0;
}