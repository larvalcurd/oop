#include "Burns.h"
#include "Homer.h"
#include "Smithers.h"

Burns::Burns(Bank& bank, Money initialCash)
	: Actor("Mr. Burns", bank, initialCash)
{
	OpenBankAccount();
}

void Burns::SetEmployee(Homer* homer)
{
	employee_ = homer;
}

void Burns::SetAssistant(Smithers* smithers)
{
	assistant_ = smithers;

	if (assistant_ && assistant_->HasAccount())
	{
		assistantAccountId_ = assistant_->GetAccountId();
		hasAssistantAccount_ = true;
	}
}

void Burns::UpdateAssistantAccount(AccountId accountId)
{
	assistantAccountId_ = accountId;
	hasAssistantAccount_ = true;
}

void Burns::Act()
{
	if (employee_ && employee_->HasAccount())
	{
		if (SendTo(*employee_, HOMER_SALARY))
		{
			Log("paid salary to Homer");
		}
		else
		{
			Log("couldn't pay salary - not enough money");
		}
	}

	if (hasAssistantAccount_)
	{
		try
		{
			if (GetBank().TrySendMoney(GetAccountId(), assistantAccountId_, SMITHERS_SALARY))
			{
				Log("paid salary to Smithers");
			}
			else
			{
				Log("couldn't pay Smithers - not enough money");
			}
		}
		catch (const BankOperationError&)
		{
			Log("tried to pay Smithers but his account is invalid!");
		}
	}
}