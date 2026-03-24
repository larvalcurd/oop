#include "Smithers.h"
#include "Burns.h"
#include "Apu.h"

Smithers::Smithers(Bank& bank, Money initialCash)
	: Actor("Smithers", bank, initialCash)
{
	OpenBankAccount();
}

void Smithers::SetEmployer(Burns* burns)
{
	employer_ = burns;
}

void Smithers::SetShopkeeper(Apu* apu)
{
	apu_ = apu;
}

void Smithers::Act()
{
	++actionCounter_;
	TryReopenAccount();
	BuyGroceries();
}

void Smithers::TryReopenAccount()
{
	if (actionCounter_ % REOPEN_ACCOUNT_PERIOD != 0)
	{
		return;
	}

	const Money balance = CloseBankAccount();
	Log("paranoid! Closed account, got $" + std::to_string(balance) + " cash");

	OpenBankAccount();

	if (employer_ && actionCounter_ % INFORM_EMPLOYER_PERIOD == 0)
	{
		employer_->UpdateAssistantAccount(GetAccountId());
		Log("informed Burns about new account");
	}
	else
	{
		Log("did NOT inform Burns about new account");
	}

	if (cash_ > 0)
	{
		DepositToAccount(cash_);
	}
}

void Smithers::BuyGroceries()
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
		Log("can't afford groceries");
	}
}