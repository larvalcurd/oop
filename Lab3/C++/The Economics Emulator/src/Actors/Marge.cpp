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
	BuyGroceries();
	TryBuyHouseSupplies();
}

void Marge::BuyGroceries()
{
	if (!apu_ || !apu_->HasAccount())
	{
		return;
	}

	if (SendTo(*apu_, GROCERY_COST))
	{
		Log("bought groceries from Apu");
	}
	else
	{
		Log("couldn't buy groceries - not enough money");
	}
}

void Marge::TryBuyHouseSupplies()
{
	if (!apu_ || !apu_->HasAccount())
	{
		return;
	}

	const Money balance = GetBank().GetAccountBalance(GetAccountId());
	if (balance < HOUSE_SUPPLIES_THRESHOLD)
	{
		return;
	}

	if (SendTo(*apu_, HOUSE_SUPPLIES_COST))
	{
		Log("bought house supplies from Apu");
	}
}