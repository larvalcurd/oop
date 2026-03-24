#pragma once
#include "../Actor.h"

class Marge;
class Bart;
class Lisa;
class Burns;
class Apu;

class Homer : public Actor
{
public:
	Homer(Bank& bank, Money initialCash = 0);

	void SetFamily(Marge* marge, Bart* bart, Lisa* lisa);
	void SetEmployer(Burns* burns);
	void SetShopkeeper(Apu* apu);

	void Act() override;

private:
	void SendAllowanceToMarge();
	void PayElectricityBill();
	void GiveAllowanceToKids();
	void TryBuyBeer();

	static constexpr Money ALLOWANCE_FOR_MARGE = 90;
	static constexpr Money ALLOWANCE_FOR_KIDS = 15;
	static constexpr Money ELECTRICITY_BILL = 120;
	static constexpr Money BEER_PARTY_THRESHOLD = 400;
	static constexpr Money BEER_PARTY_COST = 60; 

	Marge* marge_ = nullptr;
	Bart* bart_ = nullptr;
	Lisa* lisa_ = nullptr;
	Burns* employer_ = nullptr;
	Apu* apu_ = nullptr;
};