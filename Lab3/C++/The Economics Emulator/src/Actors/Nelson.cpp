#include "Nelson.h"
#include "Bart.h"
#include "Apu.h"
#include <algorithm>

Nelson::Nelson(Bank &bank, Money initialCash) : Actor("Nelson", bank, initialCash)
{}

void Nelson::SetVictim(Bart* bart)
{
	victim_ = bart;
}

void Nelson::SetShopkeeper(Apu* apu)
{
	apu_ = apu;
}

void Nelson::Act()
{
    ++actionCounter_;

    if (victim_ && actionCounter_ % 3 == 0)
    {
        Money victimCash = victim_->GetCash();
        if (victimCash > 0)
        {
            Money stealAmount = std::min(victimCash, MAX_STEAL_AMOUNT);

            if (victim_->StealCash(stealAmount))
            {
                ReceiveCash(stealAmount);
                Log("stole $" + std::to_string(stealAmount) + " from Bart. Ha-ha!");
            }
        }
    }

    if (apu_ && cash_ >= CIGARETTE_COST)
    {
        if (SpendCash(CIGARETTE_COST))
        {
            apu_->ReceiveCashPayment(CIGARETTE_COST);
            Log("bought cigarettes from Apu");
        }
    }
}
