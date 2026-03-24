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
	DepositCashIfNeeded();
	PayElectricityBill();
	TryRestockGoods();
}

void Apu::DepositCashIfNeeded()
{
	if (cash_ >= DEPOSIT_THRESHOLD)
	{
		DepositToAccount(cash_);
	}
}

void Apu::PayElectricityBill()
{
	if (!powerCompany_ || !powerCompany_->HasAccount())
	{
		return;
	}

	if (SendTo(*powerCompany_, ELECTRICITY_BILL))
	{
		Log("paid electricity bill");
	}
	else
	{
		Log("couldn't pay electricity bill - not enough money");
	}
}

void Apu::TryRestockGoods()
{
	if (!powerCompany_ || !powerCompany_->HasAccount() || !HasAccount())
	{
		return;
	}

	const Money balance = GetBank().GetAccountBalance(GetAccountId());
	if (balance < RESTOCK_THRESHOLD)
	{
		return;
	}

	if (SendTo(*powerCompany_, RESTOCK_COST))
	{
		Log("restocked goods from Burns' warehouse");
	}
}