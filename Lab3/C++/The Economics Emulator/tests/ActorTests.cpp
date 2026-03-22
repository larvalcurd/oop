#include "Bank.h"
#include "Actors/Apu.h"
#include "Actors/Bart.h"
#include "Actors/Burns.h"
#include "Actors/Homer.h"
#include "Actors/Lisa.h"
#include "Actors/Marge.h"
#include "Actors/Nelson.h"
#include "Actors/Smithers.h"
#include "Actors/Snake.h"
#include <gtest/gtest.h>

namespace
{
class TestSmithers final : public Smithers
{
public:
    using Smithers::Smithers;

    void ForceCloseAccount()
    {
        CloseBankAccount();
    }
};
}

TEST(ActorsHomer, SendsMoneyToFamilyEmployerAndApu)
{
    Bank bank(10000);
    Homer homer(bank);
    Marge marge(bank);
    Bart bart(bank);
    Lisa lisa(bank);
    Burns burns(bank);
    Apu apu(bank);

    homer.SetFamily(&marge, &bart, &lisa);
    homer.SetEmployer(&burns);
    homer.SetShopkeeper(&apu);

    bank.DepositMoney(homer.GetAccountId(), 1000);

    homer.Act();

    EXPECT_EQ(bank.GetAccountBalance(marge.GetAccountId()), 90);
    EXPECT_EQ(bank.GetAccountBalance(burns.GetAccountId()), 120);
    EXPECT_EQ(bank.GetAccountBalance(apu.GetAccountId()), 60);
    EXPECT_EQ(bank.GetAccountBalance(homer.GetAccountId()), 700);
    EXPECT_EQ(bart.GetCash(), 15);
    EXPECT_EQ(lisa.GetCash(), 15);
}

TEST(ActorsMarge, BuysGroceriesAndHouseSuppliesWhenRichEnough)
{
    Bank bank(10000);
    Marge marge(bank);
    Apu apu(bank);

    marge.SetShopkeeper(&apu);
    bank.DepositMoney(marge.GetAccountId(), 400);

    marge.Act();

    EXPECT_EQ(bank.GetAccountBalance(marge.GetAccountId()), 195);
    EXPECT_EQ(bank.GetAccountBalance(apu.GetAccountId()), 205);
}

TEST(ActorsBart, SpendsCashAtApu)
{
    Bank bank(10000);
    Bart bart(bank);
    Apu apu(bank);

    bart.SetShopkeeper(&apu);
    bart.ReceiveCashPayment(20);

    bart.Act();

    EXPECT_EQ(bart.GetCash(), 8);
    EXPECT_EQ(apu.GetCash(), 12);
}

TEST(ActorsLisa, BuysCandyAndDoll)
{
    Bank bank(10000);
    Lisa lisa(bank);
    Apu apu(bank);

    lisa.SetShopkeeper(&apu);
    lisa.ReceiveCashPayment(120);

    lisa.Act();

    EXPECT_EQ(lisa.GetCash(), 58);
    EXPECT_EQ(apu.GetCash(), 62);
}

TEST(ActorsBurns, PaysSalariesToHomerAndSmithers)
{
    Bank bank(10000);
    Burns burns(bank);
    Homer homer(bank);
    Smithers smithers(bank);

    burns.SetEmployee(&homer);
    burns.SetAssistant(&smithers);
    bank.DepositMoney(burns.GetAccountId(), 1000);

    burns.Act();

    EXPECT_EQ(bank.GetAccountBalance(homer.GetAccountId()), 258);
    EXPECT_EQ(bank.GetAccountBalance(smithers.GetAccountId()), 50);
    EXPECT_EQ(bank.GetAccountBalance(burns.GetAccountId()), 692);
}

TEST(ActorsBurns, SkipsPaymentIfSmithersAccountInvalid)
{
    Bank bank(10000);
    Burns burns(bank);
    Homer homer(bank);
    TestSmithers smithers(bank);

    burns.SetEmployee(&homer);
    burns.SetAssistant(&smithers);
    bank.DepositMoney(burns.GetAccountId(), 1000);
    smithers.ForceCloseAccount();

    burns.Act();

    EXPECT_EQ(bank.GetAccountBalance(homer.GetAccountId()), 258);
    EXPECT_FALSE(smithers.HasAccount());
    EXPECT_EQ(bank.GetAccountBalance(burns.GetAccountId()), 742);
}

TEST(ActorsApu, DepositsCashAndPaysBurns)
{
    Bank bank(10000);
    Apu apu(bank);
    Burns burns(bank);

    apu.SetPowerCompany(&burns);
    apu.ReceiveCashPayment(450);

    apu.Act();

    EXPECT_EQ(apu.GetCash(), 0);
    EXPECT_EQ(bank.GetAccountBalance(apu.GetAccountId()), 265);
    EXPECT_EQ(bank.GetAccountBalance(burns.GetAccountId()), 185);
}

TEST(ActorsNelson, StealsFromBartEveryThirdTurnAndBuysCigarettes)
{
    Bank bank(10000);
    Nelson nelson(bank);
    Bart bart(bank);
    Apu apu(bank);

    nelson.SetVictim(&bart);
    nelson.SetShopkeeper(&apu);
    bart.ReceiveCashPayment(10);

    nelson.Act();
    nelson.Act();
    nelson.Act();

    EXPECT_EQ(bart.GetCash(), 0);
    EXPECT_EQ(nelson.GetCash(), 7);
    EXPECT_EQ(apu.GetCash(), 3);
}

TEST(ActorsSnake, HacksHomerEveryFifthTurn)
{
    Bank bank(10000);
    Snake snake(bank);
    Homer homer(bank);
    Apu apu(bank);

    snake.SetVictim(&homer);
    snake.SetShopkeeper(&apu);
    bank.DepositMoney(homer.GetAccountId(), 100);
    bank.DepositMoney(snake.GetAccountId(), 20);

    for (int i = 0; i < 5; ++i)
    {
        snake.Act();
    }

    EXPECT_EQ(bank.GetAccountBalance(homer.GetAccountId()), 70);
    EXPECT_EQ(bank.GetAccountBalance(snake.GetAccountId()), 26);
    EXPECT_EQ(bank.GetAccountBalance(apu.GetAccountId()), 24);
}

TEST(ActorsSmithers, ReopensAccountOnParanoiaStep)
{
    Bank bank(10000);
    Smithers smithers(bank);
    Apu apu(bank);

    smithers.SetShopkeeper(&apu);
    bank.DepositMoney(smithers.GetAccountId(), 120);
    AccountId oldId = smithers.GetAccountId();

    for (int i = 0; i < 7; ++i)
    {
        smithers.Act();
    }

    EXPECT_TRUE(smithers.HasAccount());
    EXPECT_NE(smithers.GetAccountId(), oldId);
    EXPECT_EQ(bank.GetAccountBalance(smithers.GetAccountId()), 20);
    EXPECT_EQ(bank.GetAccountBalance(apu.GetAccountId()), 100);
}
