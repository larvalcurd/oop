#include "Simulation.h"
#include <iostream>

Simulation::Simulation(Money initialCash)
	: bank_(initialCash)
	, initialTotalMoney_(initialCash)
	, homer_(bank_, 0)
	, marge_(bank_, 0)
	, bart_(bank_, 0)
	, lisa_(bank_, 0)
	, apu_(bank_, 0)
	, burns_(bank_, 0)
	, nelson_(bank_, 0)
	, snake_(bank_, 0)
	, smithers_(bank_, 0)
	, actors_{ &burns_, &homer_, &marge_, &bart_, &lisa_, &nelson_, &snake_, &smithers_, &apu_ }
{
	SetupRelationships();
	bank_.DepositMoney(burns_.GetAccountId(), initialCash);
}

void Simulation::SetupRelationships()
{
	homer_.SetFamily(&marge_, &bart_, &lisa_);
	homer_.SetEmployer(&burns_);
	homer_.SetShopkeeper(&apu_);

	marge_.SetShopkeeper(&apu_);
	bart_.SetShopkeeper(&apu_);
	lisa_.SetShopkeeper(&apu_);

	apu_.SetPowerCompany(&burns_);

	burns_.SetEmployee(&homer_);
	burns_.SetAssistant(&smithers_);

	if (smithers_.HasAccount())
	{
		burns_.UpdateAssistantAccount(smithers_.GetAccountId());
	}

	nelson_.SetVictim(&bart_);
	nelson_.SetShopkeeper(&apu_);

	snake_.SetVictim(&homer_);
	snake_.SetShopkeeper(&apu_);

	smithers_.SetEmployer(&burns_);
	smithers_.SetShopkeeper(&apu_);
}

void Simulation::Run(int numIterations)
{
	std::cout << "=== Starting simulation with " << numIterations << " iterations ===\n";
	std::cout << "Initial cash in system: $" << initialTotalMoney_ << "\n\n";

	for (int i = 1; i <= numIterations; ++i)
	{
		Step(i);
	}

	std::cout << "\n=== Simulation finished ===\n";
}

void Simulation::Step(int stepNumber)
{
	std::cout << "--- Step " << stepNumber << " ---\n";

	for (Actor* actor : actors_)
	{
		actor->Act();
	}

	std::cout << "\n";
}

void Simulation::PrintFinalState() const
{
	std::cout << "=== Final State ===\n\n";
	std::cout << "Cash in circulation (bank): $" << bank_.GetCash() << "\n\n";
	std::cout << "Actors:\n";

	for (const Actor* actor : actors_)
	{
		PrintActorState(*actor);
	}

	std::cout << "\n";
}

void Simulation::PrintActorState(const Actor& actor) const
{
	std::cout << "  " << actor.GetName() << ":\n";
	std::cout << "    Cash: $" << actor.GetCash() << "\n";

	if (actor.HasAccount())
	{
		std::cout << "    Account #" << actor.GetAccountId()
		          << ": $" << bank_.GetAccountBalance(actor.GetAccountId()) << "\n";
	}

	std::cout << "    Total: $" << actor.GetTotalMoney() << "\n";
}

bool Simulation::VerifyInvariants() const
{
	std::cout << "=== Verifying Invariants ===\n";

	const bool cashOk = VerifyCashInvariant();
	const bool totalOk = VerifyTotalMoneyInvariant();

	if (cashOk && totalOk)
	{
		std::cout << "\nAll invariants verified successfully!\n";
		return true;
	}

	return false;
}

bool Simulation::VerifyCashInvariant() const
{
	Money totalActorCash = 0;
	for (const Actor* actor : actors_)
	{
		totalActorCash += actor->GetCash();
	}

	const Money bankCash = bank_.GetCash();

	std::cout << "Total cash held by actors: $" << totalActorCash << "\n";
	std::cout << "Cash registered in bank: $" << bankCash << "\n";

	if (totalActorCash != bankCash)
	{
		std::cout << "ERROR: Cash mismatch!\n";
		return false;
	}

	std::cout << "OK: Cash matches.\n";
	return true;
}

bool Simulation::VerifyTotalMoneyInvariant() const
{
	const Money bankCash = bank_.GetCash();

	Money totalInAccounts = 0;
	for (const Actor* actor : actors_)
	{
		if (actor->HasAccount())
		{
			totalInAccounts += bank_.GetAccountBalance(actor->GetAccountId());
		}
	}

	const Money totalMoney = bankCash + totalInAccounts;

	std::cout << "Total in accounts: $" << totalInAccounts << "\n";
	std::cout << "Total money in system: $" << totalMoney << "\n";
	std::cout << "Initial money: $" << initialTotalMoney_ << "\n";

	if (totalMoney != initialTotalMoney_)
	{
		std::cout << "ERROR: Total money mismatch!\n";
		return false;
	}

	std::cout << "OK: Total money preserved.\n";
	return true;
}