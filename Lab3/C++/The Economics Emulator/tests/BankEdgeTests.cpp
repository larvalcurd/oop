#include "Bank.h"
#include <gtest/gtest.h>

TEST(BankTryWithdraw, InvalidAccountThrows)
{
    Bank bank(1000);
    EXPECT_THROW(bank.TryWithdrawMoney(999, 10), BankOperationError);
}

TEST(BankTrySend, InvalidSourceAccountThrows)
{
    Bank bank(1000);
    AccountId dst = bank.OpenAccount();
    EXPECT_THROW(bank.TrySendMoney(999, dst, 10), BankOperationError);
}

TEST(BankTrySend, InvalidDestinationAccountThrows)
{
    Bank bank(1000);
    AccountId src = bank.OpenAccount();
    bank.DepositMoney(src, 100);
    EXPECT_THROW(bank.TrySendMoney(src, 999, 10), BankOperationError);
}

TEST(BankTrySend, NegativeAmountThrows)
{
    Bank bank(1000);
    AccountId src = bank.OpenAccount();
    AccountId dst = bank.OpenAccount();
    bank.DepositMoney(src, 100);
    EXPECT_THROW(bank.TrySendMoney(src, dst, -1), std::out_of_range);
}

