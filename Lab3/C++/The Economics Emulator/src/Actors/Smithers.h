#pragma once

#include "../Actor.h"

class Burns;
class Apu;

class Smithers : public Actor
{
public:
    Smithers(Bank& bank, Money initialCash = 0);

    void SetEmployer(Burns* burns);
    void SetShopkeeper(Apu* apu);

    void Act() override;

private:
    void TryReopenAccount();
    void BuyGroceries();

    static constexpr Money GROCERY_COST = 50;
    static constexpr int REOPEN_ACCOUNT_PERIOD = 7;
    static constexpr int INFORM_EMPLOYER_PERIOD = 14;

    Burns* employer_ = nullptr;
    Apu* apu_ = nullptr;

    int actionCounter_ = 0;
};