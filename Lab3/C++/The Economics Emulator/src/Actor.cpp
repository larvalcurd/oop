#include "Actor.h"
#include <iostream>

Actor::Actor(const std::string& name, Bank& bank, Money initialCash)
	: name_(name)
	, bank_(bank)
	, cash_(initialCash)
{}

Money Actor::GetTotalMoney() const
{
	if (!hasAccount_)
	{
		return cash_;
	}
	return cash_ + bank_.GetAccountBalance(accountId_);
}

void Actor::ReceiveCash(Money amount)
{
	if (amount > 0)
	{
		cash_ += amount;
	}
}

bool Actor::SpendCash(Money amount)
{
	if (amount <= 0 || amount > cash_)
	{
		return false;
	}

	cash_ -= amount;
	return true;
}

void Actor::OpenBankAccount()
{
	if (hasAccount_)
	{
		return;
	}

	accountId_ = bank_.OpenAccount();
	hasAccount_ = true;
	Log("opened bank account #" + std::to_string(accountId_));
}

Money Actor::CloseBankAccount()
{
	if (!hasAccount_)
	{
		return 0;
	}

	const Money balance = bank_.CloseAccount(accountId_);
	cash_ += balance;
	hasAccount_ = false;
	Log("closed bank account, received $" + std::to_string(balance) + " cash");
	return balance;
}

bool Actor::DepositToAccount(Money amount)
{
	if (!hasAccount_ || amount <= 0 || amount > cash_)
	{
		return false;
	}

	try
	{
		bank_.DepositMoney(accountId_, amount);
		cash_ -= amount;
		Log("deposited $" + std::to_string(amount) + " to account");
		return true;
	}
	catch (const BankOperationError&)
	{
		return false;
	}
}

bool Actor::WithdrawFromAccount(Money amount)
{
	if (!hasAccount_ || amount <= 0)
	{
		return false;
	}

	if (!bank_.TryWithdrawMoney(accountId_, amount))
	{
		return false;
	}

	cash_ += amount;
	Log("withdrew $" + std::to_string(amount) + " from account");
	return true;
}

bool Actor::SendTo(Actor& recipient, Money amount)
{
	if (!hasAccount_ || !recipient.HasAccount() || amount <= 0)
	{
		return false;
	}

	if (!bank_.TrySendMoney(accountId_, recipient.GetAccountId(), amount))
	{
		return false;
	}

	Log("sent $" + std::to_string(amount) + " to " + recipient.GetName());
	return true;
}

bool Actor::StealCash(Money amount)
{
	if (amount <= 0 || amount > cash_)
	{
		return false;
	}

	cash_ -= amount;
	return true;
}

bool Actor::GiveCashTo(Actor& recipient, Money amount)
{
	if (amount <= 0 || amount > cash_)
	{
		return false;
	}

	cash_ -= amount;
	recipient.ReceiveCash(amount);
	return true;
}

void Actor::ReceiveCashPayment(Money amount)
{
	ReceiveCash(amount);
}

void Actor::Log(const std::string& message) const
{
	std::cout << "[" << name_ << "] " << message << "\n";
}