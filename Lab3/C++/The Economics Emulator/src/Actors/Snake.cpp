#include "Snake.h"
#include "Homer.h"
#include "Apu.h"

Snake::Snake(Bank& bank, Money initialCash)
    : Actor("Snake", bank, initialCash)
{
    OpenBankAccount();
}

void Snake::SetVictim(Homer* homer)
{
    victim_ = homer;
}

void Snake::SetShopkeeper(Apu* apu)
{
    apu_ = apu;
}

void Snake::Act()
{
    ++actionCounter_;
    TryHackVictim();
    BuyGroceries();
}

void Snake::TryHackVictim()
{
    if (!victim_ || !victim_->HasAccount())
    {
        return;
    }

    if (actionCounter_ % HACK_PERIOD != 0)
    {
        return;
    }

    if (GetBank().TrySendMoney(victim_->GetAccountId(), GetAccountId(), HACK_AMOUNT))
    {
        Log("hacked Homer's account and stole $" + std::to_string(HACK_AMOUNT));
    }
    else
    {
        Log("tried to hack Homer but he's broke");
    }
}

void Snake::BuyGroceries()
{
    if (!apu_ || !apu_->HasAccount())
    {
        return;
    }

    if (SendTo(*apu_, GROCERY_COST))
    {
        Log("bought groceries from Apu");
    }
}