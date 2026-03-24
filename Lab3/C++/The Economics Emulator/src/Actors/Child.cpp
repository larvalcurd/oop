#include "Child.h"
#include "Apu.h"

Child::Child(const std::string& name, Bank& bank, Money initialCash)
	: Actor(name, bank, initialCash)
{
}

void Child::SetShopkeeper(Apu* apu)
{
	apu_ = apu;
}

void Child::Act()
{
	if (cash_ < SPENDING_AMOUNT)
	{
		Log("no money for candy :(");
		return;
	}

	if (!apu_ || !SpendCash(SPENDING_AMOUNT))
	{
		return;
	}

	apu_->ReceiveCashPayment(SPENDING_AMOUNT);
	Log("bought candy from Apu for $" + std::to_string(SPENDING_AMOUNT));
}