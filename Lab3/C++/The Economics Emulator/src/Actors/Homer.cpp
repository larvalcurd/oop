#include "Homer.h"
#include "Marge.h"
#include "Bart.h"
#include "Lisa.h"
#include "Burns.h"
#include "Apu.h"

Homer::Homer (Bank& bank, Money initialCash)
	: Actor("Homer", bank, initialCash)
{
	OpenBankAccount();
}

void Homer::SetFamily(Marge* marge, Bart* bart, Lisa* lisa)
{
	marge_ = marge;
	bart_ = bart;
	lisa_ = lisa;
}

void Homer::SetEmployer(Burns* burns)
{
	employer_ = burns;
}

void Homer::SetShopkeeper(Apu* apu)
{
	apu_ = apu;
}

void Homer::Act()
{
	if (marge_ && marge_->HasAccount())
	{
		if (!SendTo(*marge_, ALLOWANCE_FOR_MARGE))
		{
			Log("couldn't send allowance to Marge - not enough money");
		}
	}

	if (employer_ && employer_->HasAccount())
	{
		if (!SendTo(*employer_, ELECTRICITY_BILL))
		{
			Log("couldn't pay electricity bill - not enough money");
		}
	}

	Money cashForKids = ALLOWANCE_FOR_KIDS * 2;
	if (WithdrawFromAccount(cashForKids))
	{
		if (bart_)
		{
			GiveCashTo(*bart_, ALLOWANCE_FOR_KIDS);
			Log("gave $" + std::to_string(ALLOWANCE_FOR_KIDS) + " cash to Bart");
		}
		if (lisa_)
		{
			GiveCashTo(*lisa_, ALLOWANCE_FOR_KIDS);
			Log("gave $" + std::to_string(ALLOWANCE_FOR_KIDS) + " cash to Lisa");
		}
	}
	else
	{
		Log("couldn't withdraw cash for kids");
	}

	if (apu_ && apu_->HasAccount() && HasAccount())
	{
		Money balance = GetBank().GetAccountBalance(GetAccountId());
		if (balance >= BEER_PARTY_THRESHOLD)
		{
			if (SendTo(*apu_, BEER_PARTY_COST))
			{
				Log("bought beer and relaxed with friends");
			}
		}
	}
}