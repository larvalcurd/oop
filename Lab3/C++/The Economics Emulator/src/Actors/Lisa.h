#pragma once

#include "Child.h"

class Lisa : public Child
{
public:
	Lisa(Bank& bank, Money initialCash = 0);

	void Act() override;

private:
	void TryBuyDoll();

	static constexpr Money DOLL_COST = 50;
	static constexpr Money DOLL_THRESHOLD = 60;
};