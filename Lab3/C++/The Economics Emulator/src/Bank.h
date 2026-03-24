#pragma once

#include <stdexcept>
#include <unordered_map>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

class Bank
{
public:
	explicit Bank(Money cash);

	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;

	[[nodiscard]] AccountId OpenAccount();
	[[nodiscard]] Money CloseAccount(AccountId accountId);

	void DepositMoney(AccountId accountId, Money amount);
	void WithdrawMoney(AccountId accountId, Money amount);
	[[nodiscard]] bool TryWithdrawMoney(AccountId accountId, Money amount);

	void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	[[nodiscard]] Money GetCash() const;
	[[nodiscard]] Money GetAccountBalance(AccountId accountId) const;

private:
	void ValidatePositiveAmount(Money amount) const;
	void ValidateAccountExists(AccountId accountId) const;
	[[nodiscard]] Money& GetAccountRef(AccountId accountId);

	Money cash_;
	AccountId nextAccountId_ = 1;
	std::unordered_map<AccountId, Money> accounts_;
};