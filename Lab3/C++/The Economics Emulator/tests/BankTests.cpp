#include "Bank.h"
#include <gtest/gtest.h>

TEST(BankConstructor, ValidCash)
{
	EXPECT_NO_THROW(Bank bank(1000));
}

TEST(BankConstructor, ZeroCash)
{
	EXPECT_NO_THROW(Bank bank(0));
}

TEST(BankConstructor, NegativeCash)
{
	EXPECT_THROW(Bank bank(-100), BankOperationError);
}

TEST(BankAccounts, OpenAccountReturnsUniqueIds)
{
	Bank bank(1000);

	AccountId id1 = bank.OpenAccount();
	AccountId id2 = bank.OpenAccount();
	AccountId id3 = bank.OpenAccount();

	EXPECT_NE(id1, id2);
	EXPECT_NE(id2, id3);
	EXPECT_NE(id1, id3);
}

TEST(BankAccounts, NewAccountHasZeroBalance)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();

	EXPECT_EQ(bank.GetAccountBalance(id), 0);
}

TEST(BankAccounts, CloseAccountReturnsBalance)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 500);

	Money returned = bank.CloseAccount(id);

	EXPECT_EQ(returned, 500);
}

TEST(BankAccounts, CloseAccountAddsToCash)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 500);

	bank.CloseAccount(id);

	EXPECT_EQ(bank.GetCash(), 1000);
}

TEST(BankAccounts, CloseNonExistentAccountThrows)
{
	Bank bank(1000);

	EXPECT_THROW(bank.CloseAccount(999), BankOperationError);
}

TEST(BankAccounts, GetBalanceOfNonExistentAccountThrows)
{
	Bank bank(1000);

	EXPECT_THROW(bank.GetAccountBalance(999), BankOperationError);
}

// ==================== Тесты Deposit ====================

TEST(BankDeposit, DepositIncreasesBalance)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();

	bank.DepositMoney(id, 300);

	EXPECT_EQ(bank.GetAccountBalance(id), 300);
}

TEST(BankDeposit, DepositDecreasesCash)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();

	bank.DepositMoney(id, 300);

	EXPECT_EQ(bank.GetCash(), 700);
}

TEST(BankDeposit, DepositMoreThanCashThrows)
{
	Bank bank(100);
	AccountId id = bank.OpenAccount();

	EXPECT_THROW(bank.DepositMoney(id, 200), BankOperationError);
}

TEST(BankDeposit, DepositNegativeThrows)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();

	EXPECT_THROW(bank.DepositMoney(id, -100), std::out_of_range);
}

TEST(BankDeposit, DepositToNonExistentAccountThrows)
{
	Bank bank(1000);

	EXPECT_THROW(bank.DepositMoney(999, 100), BankOperationError);
}

// ==================== Тесты Withdraw ====================

TEST(BankWithdraw, WithdrawDecreasesBalance)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 500);

	bank.WithdrawMoney(id, 200);

	EXPECT_EQ(bank.GetAccountBalance(id), 300);
}

TEST(BankWithdraw, WithdrawIncreasesCash)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 500);

	bank.WithdrawMoney(id, 200);

	EXPECT_EQ(bank.GetCash(), 700); 
}

TEST(BankWithdraw, WithdrawMoreThanBalanceThrows)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 100);

	EXPECT_THROW(bank.WithdrawMoney(id, 200), BankOperationError);
}

TEST(BankWithdraw, WithdrawNegativeThrows)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 500);

	EXPECT_THROW(bank.WithdrawMoney(id, -100), std::out_of_range);
}

TEST(BankWithdraw, TryWithdrawReturnsTrue)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 500);

	bool result = bank.TryWithdrawMoney(id, 200);

	EXPECT_TRUE(result);
	EXPECT_EQ(bank.GetAccountBalance(id), 300);
}

TEST(BankWithdraw, TryWithdrawReturnsFalseOnInsufficientFunds)
{
	Bank bank(1000);
	AccountId id = bank.OpenAccount();
	bank.DepositMoney(id, 100);

	bool result = bank.TryWithdrawMoney(id, 200);

	EXPECT_FALSE(result);
	EXPECT_EQ(bank.GetAccountBalance(id), 100); 
}

TEST(BankSendMoney, SendMoneyTransfersCorrectly)
{
	Bank bank(1000);
	AccountId src = bank.OpenAccount();
	AccountId dst = bank.OpenAccount();
	bank.DepositMoney(src, 500);

	bank.SendMoney(src, dst, 200);

	EXPECT_EQ(bank.GetAccountBalance(src), 300);
	EXPECT_EQ(bank.GetAccountBalance(dst), 200);
}

TEST(BankSendMoney, SendMoneyDoesNotChangeCash)
{
	Bank bank(1000);
	AccountId src = bank.OpenAccount();
	AccountId dst = bank.OpenAccount();
	bank.DepositMoney(src, 500);
	Money cashBefore = bank.GetCash();

	bank.SendMoney(src, dst, 200);

	EXPECT_EQ(bank.GetCash(), cashBefore);
}

TEST(BankSendMoney, SendMoreThanBalanceThrows)
{
	Bank bank(1000);
	AccountId src = bank.OpenAccount();
	AccountId dst = bank.OpenAccount();
	bank.DepositMoney(src, 100);

	EXPECT_THROW(bank.SendMoney(src, dst, 200), BankOperationError);
}

TEST(BankSendMoney, SendNegativeThrows)
{
	Bank bank(1000);
	AccountId src = bank.OpenAccount();
	AccountId dst = bank.OpenAccount();
	bank.DepositMoney(src, 500);

	EXPECT_THROW(bank.SendMoney(src, dst, -100), std::out_of_range);
}

TEST(BankSendMoney, TrySendMoneyReturnsFalseOnInsufficientFunds)
{
	Bank bank(1000);
	AccountId src = bank.OpenAccount();
	AccountId dst = bank.OpenAccount();
	bank.DepositMoney(src, 100);

	bool result = bank.TrySendMoney(src, dst, 200);

	EXPECT_FALSE(result);
	EXPECT_EQ(bank.GetAccountBalance(src), 100); 
	EXPECT_EQ(bank.GetAccountBalance(dst), 0);
}

TEST(BankInvariant, TotalMoneyRemainsSame)
{
	Money initialCash = 10000;
	Bank bank(initialCash);

	AccountId homer = bank.OpenAccount();
	AccountId marge = bank.OpenAccount();
	AccountId apu = bank.OpenAccount();

	bank.DepositMoney(homer, 3000);
	bank.DepositMoney(marge, 2000);
	bank.SendMoney(homer, marge, 500);
	bank.WithdrawMoney(marge, 1000);
	bank.DepositMoney(apu, 1500);
	bank.SendMoney(marge, apu, 300);

	Money totalInAccounts = bank.GetAccountBalance(homer)
		+ bank.GetAccountBalance(marge)
		+ bank.GetAccountBalance(apu);
	Money totalMoney = bank.GetCash() + totalInAccounts;

	EXPECT_EQ(totalMoney, initialCash);
}