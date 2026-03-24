#pragma once

#include "../Actor.h"

class Homer;
class Apu;

class Snake : public Actor
{
public:
    Snake(Bank& bank, Money initialCash = 0);

    void SetVictim(Homer* homer);
    void SetShopkeeper(Apu* apu);

    void Act() override;

private:
    void TryHackVictim();
    void BuyGroceries();

    static constexpr Money HACK_AMOUNT = 30;
    static constexpr Money GROCERY_COST = 6;
    static constexpr int HACK_PERIOD = 5;

    Homer* victim_ = nullptr;
    Apu* apu_ = nullptr;

    int actionCounter_ = 0;
};