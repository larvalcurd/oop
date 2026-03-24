#pragma once

#include "Bank.h"
#include "Actors/Homer.h"
#include "Actors/Marge.h"
#include "Actors/Bart.h"
#include "Actors/Lisa.h"
#include "Actors/Apu.h"
#include "Actors/Burns.h"
#include "Actors/Nelson.h"
#include "Actors/Snake.h"
#include "Actors/Smithers.h"
#include <vector>

class Simulation
{
public:
	explicit Simulation(Money initialCash);

	void Run(int numIterations);
	void PrintFinalState() const;
	[[nodiscard]] bool VerifyInvariants() const;

private:
	void Step(int stepNumber);
	void SetupRelationships();
	void PrintActorState(const Actor& actor) const;
	[[nodiscard]] bool VerifyCashInvariant() const;
	[[nodiscard]] bool VerifyTotalMoneyInvariant() const;

	Bank bank_;
	Money initialTotalMoney_;

	Homer homer_;
	Marge marge_;
	Bart bart_;
	Lisa lisa_;
	Apu apu_;
	Burns burns_;
	Nelson nelson_;
	Snake snake_;
	Smithers smithers_;

	std::vector<Actor*> actors_;
};