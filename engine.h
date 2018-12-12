/////////////////////////////////////////////////////////////////////////////////////////////
//
// This code represents the simulation engine. Some of this code is taken and/or adapated from
// a simulation written by Dr. Richard Fujimoto at the Georgia Institute of Technology.
//
/////////////////////////////////////////////////////////////////////////////////////////////

// Simulation Engine Interface

// Schedule an event with timestamp ts, event parameters *data, and callback function cb
void Schedule (double ts, void *data, void (*cb)(void *));

// Call this procedure to run the simulation
void RunSim (void);

// This function returns the current simulation time
double CurrentTime (void);

