#pragma once

#include "../Actor.h"

class Apu;

class Child : public Actor
{
public:
	Child(const std::string& name, Bank& bank, Money initialCash = 0);

	void SetShopkeeper(Apu* apu);

	void Act() override;

protected:
	static constexpr Money SPENDING_AMOUNT = 12;

	Apu* apu_ = nullptr;
};