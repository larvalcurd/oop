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

	if (!assistant_ || !assistant_->HasAccount())
	{
		return;
	}

	assistantAccountId_ = assistant_->GetAccountId();
	hasAssistantAccount_ = true;
}

void Burns::UpdateAssistantAccount(AccountId accountId)
{
	assistantAccountId_ = accountId;
	hasAssistantAccount_ = true;
}

void Burns::Act()
{
	PayHomer();
	PaySmithers();
}

void Burns::PayHomer()
{
	if (!employee_ || !employee_->HasAccount())
	{
		return;
	}

	if (SendTo(*employee_, HOMER_SALARY))
	{
		Log("paid salary to Homer");
	}
	else
	{
		Log("couldn't pay salary - not enough money");
	}
}

void Burns::PaySmithers()
{
	if (!hasAssistantAccount_)
	{
		return;
	}

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