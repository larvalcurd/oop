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
	if (apu_ && cash_ >= SPENDING_AMOUNT)
	{
		if (SpendCash(SPENDING_AMOUNT))
		{
			apu_->ReceiveCashPayment(SPENDING_AMOUNT);
			Log("bought candy from Apu for $" + std::to_string(SPENDING_AMOUNT));
		}
	}
	else if (cash_ < SPENDING_AMOUNT)
	{
		Log("no money for candy :(");
	}
}