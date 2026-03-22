#include "Apu.h"
#include "Burns.h"

Apu::Apu(Bank& bank, Money initialCash)
	: Actor("Apu", bank, initialCash)
{
	OpenBankAccount();
}

void Apu::SetPowerCompany(Burns* burns)
{
	powerCompany_ = burns;
}

void Apu::ReceiveCashPayment(Money amount)
{
	ReceiveCash(amount);
}

void Apu::Act()
{
	if (cash_ >= DEPOSIT_THRESHOLD)
	{
		DepositToAccount(cash_);
	}

	if (powerCompany_ && powerCompany_->HasAccount())
	{
		if (SendTo(*powerCompany_, ELECTRICITY_BILL))
		{
			Log("paid electricity bill");
		}
		else
		{
			Log("couldn't pay electricity bill - not enough money");
		}
	}

	if (powerCompany_ && powerCompany_->HasAccount() && HasAccount())
	{
		Money balance = GetBank().GetAccountBalance(GetAccountId());
		if (balance >= RESTOCK_THRESHOLD)
		{
			if (SendTo(*powerCompany_, RESTOCK_COST))
			{
				Log("restocked goods from Burns' warehouse");
			}
		}
	}
}