#include "Snake.h"
#include "Homer.h"
#include "Apu.h"

Snake::Snake(Bank& bank, Money InitialCash)
    : Actor("Snake", bank, InitialCash)
{
    OpenBankAccount();
}

void Snake::SetVictim(Homer *homer)
{
    victim_ = homer;
}

void Snake::SetShopkeeper(Apu *apu)
{
    apu_ = apu;
}

void Snake::Act()
{
    ++actionCounter_;

    if (victim_ && victim_->HasAccount() && actionCounter_ % 5 == 0)
    {
        if (GetBank().TrySendMoney(victim_->GetAccountId(), accountId_, HACK_AMOUNT))
        {
            Log("hacked Homer's account and stole $" + std::to_string(HACK_AMOUNT));
        }
        else
        {
            Log("tried to hack Homer but he's broke");
        }
    }

    if (apu_ && apu_->HasAccount())
    {
        if (SendTo(*apu_, GROCERY_COST))
        {
            Log("bought groceries from Apu");
        }
    }
}
