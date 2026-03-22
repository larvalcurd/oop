#include "Smithers.h"
#include "Burns.h"
#include "Apu.h"

Smithers::Smithers(Bank &bank, Money initialCash)
    : Actor("Smithers", bank, initialCash)
{
    OpenBankAccount();
}

void Smithers::SetEmployer(Burns *burns)
{
    employer_ = burns;
}

void Smithers::SetShopkeeper(Apu *apu)
{
    apu_ = apu;
}

void Smithers::Act()
{
	++actionCounter_;

	if (actionCounter_ % 7 == 0)
	{
		Money balance = CloseBankAccount();
		Log("paranoid! Closed account, got $" + std::to_string(balance) + " cash");

		OpenBankAccount();

		if (employer_ && actionCounter_ % 14 == 0)
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

	if (apu_ && apu_->HasAccount())
	{
		if (SendTo(*apu_, GROCERY_COST))
		{
			Log("bought groceries from Apu");
		}
		else
		{
			Log("can't afford groceries");
		}
	}
}
