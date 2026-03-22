#pragma once

#include "../Actor.h"

class Burns;

class Apu : public Actor
{
public:
	Apu(Bank& bank, Money initialCash = 0);

	void SetPowerCompany(Burns* burns);
	void ReceiveCashPayment(Money amount);

	void Act() override;

private:
	static constexpr Money ELECTRICITY_BILL = 100;
	static constexpr Money DEPOSIT_THRESHOLD = 50;
	static constexpr Money RESTOCK_COST = 85; 
	static constexpr Money RESTOCK_THRESHOLD = 260;

	Burns* powerCompany_ = nullptr;
};