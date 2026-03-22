#include "Marge.h"
#include "Apu.h"

Marge::Marge(Bank& bank, Money initialCash)
	: Actor("Marge", bank, initialCash)
{
	OpenBankAccount();
}

void Marge::SetShopkeeper(Apu* apu)
{
	apu_ = apu;
}

void Marge::Act()
{
	if (apu_ && apu_->HasAccount())
	{
		if (SendTo(*apu_, GROCERY_COST))
		{
			Log("bought groceries from Apu");
		}
		else
		{
			Log("couldn't buy groceries - not enough money");
		}
	}

	Money balance = GetBank().GetAccountBalance(GetAccountId());
	if (balance >= HOUSE_SUPPLIES_THRESHOLD)
	{
		if (SendTo(*apu_, HOUSE_SUPPLIES_COST))
		{
			Log("bought house supplies from Apu");
		}
	}
}