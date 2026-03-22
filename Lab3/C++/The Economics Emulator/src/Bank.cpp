#include "Bank.h"
#include <stdexcept> 

Bank::Bank(Money cash)
	: cash_(cash)
{
	if (cash < 0)
	{
		throw BankOperationError("Cannot initialize bank with negative cash");
	}
}

void Bank::ValidatePositiveAmount(Money amount) const
{
	if (amount < 0)
	{
		throw std::out_of_range("Amount cannot be negative"); 
	}
}

void Bank::ValidateAccountExists(AccountId accountId) const
{
	if (accounts_.find(accountId) == accounts_.end())
	{
		throw BankOperationError("Account does not exist");
	}
}

Money& Bank::GetAccountRef(AccountId accountId)
{
	auto it = accounts_.find(accountId);
	if (it == accounts_.end())
	{
		throw BankOperationError("Account does not exist");
	}
	return it->second;
}

AccountId Bank::OpenAccount()
{
	AccountId newId = nextAccountId_++;
	accounts_[newId] = 0;
	return newId;
}

Money Bank::CloseAccount(AccountId accountId)
{
	auto it = accounts_.find(accountId);
	if (it == accounts_.end())
	{
		throw BankOperationError("Cannot close non-existent account");
	}

	Money balance = it->second;
	accounts_.erase(it);
	cash_ += balance; 
	return balance;
}

Money Bank::GetCash() const
{
	return cash_;
}

Money Bank::GetAccountBalance(AccountId accountId) const
{
	auto it = accounts_.find(accountId);
	if (it == accounts_.end())
	{
		throw BankOperationError("Account does not exist");
	}
	return it->second;
}

void Bank::DepositMoney(AccountId account, Money amount)
{
	ValidatePositiveAmount(amount);
	ValidateAccountExists(account);

	if (amount > cash_)
	{
		throw BankOperationError("Not enough cash in circulation");
	}

	cash_ -= amount;
	accounts_[account] += amount;
}

void Bank::WithdrawMoney(AccountId account, Money amount)
{
	ValidatePositiveAmount(amount);
	Money& balance = GetAccountRef(account);

	if (amount > balance)
	{
		throw BankOperationError("Insufficient funds on account");
	}

	balance -= amount;
	cash_ += amount;
}

bool Bank::TryWithdrawMoney(AccountId account, Money amount)
{
	ValidatePositiveAmount(amount);
	Money& balance = GetAccountRef(account);

	if (amount > balance)
	{
		return false;
	}

	balance -= amount;
	cash_ += amount;
	return true;
}

void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	ValidatePositiveAmount(amount);
	Money& srcBalance = GetAccountRef(srcAccountId);
	Money& dstBalance = GetAccountRef(dstAccountId);

	if (amount > srcBalance)
	{
		throw BankOperationError("Insufficient funds on source account");
	}

	srcBalance -= amount;
	dstBalance += amount;
}

bool Bank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	ValidatePositiveAmount(amount);
	Money& srcBalance = GetAccountRef(srcAccountId);
	Money& dstBalance = GetAccountRef(dstAccountId);

	if (amount > srcBalance)
	{
		return false;
	}

	srcBalance -= amount;
	dstBalance += amount;
	return true;
}