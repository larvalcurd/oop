#pragma once

#include "../Actor.h"

class Apu;

class Marge : public Actor
{
public:
	Marge(Bank& bank, Money initialCash = 0);

	void SetShopkeeper(Apu* apu);

	void Act() override;

private:
	void BuyGroceries();
	void TryBuyHouseSupplies();

	static constexpr Money GROCERY_COST = 85;
	static constexpr Money HOUSE_SUPPLIES_THRESHOLD = 300;
	static constexpr Money HOUSE_SUPPLIES_COST = 120;

	Apu* apu_ = nullptr;
};