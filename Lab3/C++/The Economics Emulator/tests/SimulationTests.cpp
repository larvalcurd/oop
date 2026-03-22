#include "Simulation.h"
#include <gtest/gtest.h>

TEST(Simulation, PreservesInvariantsAfterRun)
{
    Simulation simulation(10000);
    simulation.Run(50);
    EXPECT_TRUE(simulation.VerifyInvariants());
}

TEST(Simulation, FinalStatePrintingDoesNotBreakInvariants)
{
    Simulation simulation(10000);
    simulation.Run(10);
    simulation.PrintFinalState();
    EXPECT_TRUE(simulation.VerifyInvariants());
}

