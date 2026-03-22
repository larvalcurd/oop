#pragma once

#include "../Actor.h"

class Bart;
class Apu;

class Nelson : public Actor
{
public:
	Nelson(Bank& bank, Money initialCash = 0);

	void SetVictim(Bart* bart);
	void SetShopkeeper(Apu* apu);

	void Act() override;

private:
	static constexpr Money MAX_STEAL_AMOUNT = 10;
	static constexpr Money CIGARETTE_COST = 3;

	Bart* victim_ = nullptr;
	Apu* apu_ = nullptr;

	int actionCounter_ = 0;
};