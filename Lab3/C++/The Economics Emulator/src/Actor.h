#pragma once

#include "Bank.h"
#include <string>

class Actor
{
public:
	Actor(const std::string& name, Bank& bank, Money initialCash = 0);
	virtual ~Actor() = default;

	virtual void Act() = 0;

	[[nodiscard]] const std::string& GetName() const { return name_; }
	[[nodiscard]] Money GetCash() const { return cash_; }
	[[nodiscard]] bool HasAccount() const { return hasAccount_; }
	[[nodiscard]] AccountId GetAccountId() const { return accountId_; }
	[[nodiscard]] Money GetTotalMoney() const;

	bool GiveCashTo(Actor& recipient, Money amount);
	bool StealCash(Money amount);
	void ReceiveCashPayment(Money amount);

protected:
	void ReceiveCash(Money amount);
	bool SpendCash(Money amount);

	void OpenBankAccount();
	Money CloseBankAccount();

	bool DepositToAccount(Money amount);
	bool WithdrawFromAccount(Money amount);
	bool SendTo(Actor& recipient, Money amount);

	void Log(const std::string& message) const;
	[[nodiscard]] Bank& GetBank() { return bank_; }

	std::string name_;
	Bank& bank_;
	Money cash_;
	AccountId accountId_ = 0;
	bool hasAccount_ = false;
};