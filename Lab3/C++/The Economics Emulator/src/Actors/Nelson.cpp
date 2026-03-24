#include "Nelson.h"
#include "Bart.h"
#include "Apu.h"
#include <algorithm>

Nelson::Nelson(Bank& bank, Money initialCash)
	: Actor("Nelson", bank, initialCash)
{}

void Nelson::SetVictim(Bart* bart)
{
	victim_ = bart;
}

void Nelson::SetShopkeeper(Apu* apu)
{
	apu_ = apu;
}

void Nelson::Act()
{
	++actionCounter_;

	const Money stolenAmount = TryStealFromVictim();
	if (stolenAmount > 0)
	{
		BuyCigarettes(stolenAmount);
	}
}

Money Nelson::TryStealFromVictim()
{
	if (!victim_ || actionCounter_ % STEAL_PERIOD != 0)
	{
		return 0;
	}

	const Money victimCash = victim_->GetCash();
	if (victimCash <= 0)
	{
		return 0;
	}

	const Money stealAmount = std::min(victimCash, MAX_STEAL_AMOUNT);
	if (!victim_->StealCash(stealAmount))
	{
		return 0;
	}

	ReceiveCash(stealAmount);
	Log("stole $" + std::to_string(stealAmount) + " from Bart. Ha-ha!");
	return stealAmount;
}

void Nelson::BuyCigarettes(Money budget)
{
	if (!apu_)
	{
		return;
	}

	while (budget >= CIGARETTE_COST && cash_ >= CIGARETTE_COST)
	{
		if (!SpendCash(CIGARETTE_COST))
		{
			break;
		}

		apu_->ReceiveCashPayment(CIGARETTE_COST);
		budget -= CIGARETTE_COST;
	}

	Log("bought cigarettes from Apu");
}