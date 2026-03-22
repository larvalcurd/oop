#include "Lisa.h"
#include "Apu.h"

Lisa::Lisa(Bank& bank, Money initialCash)
	: Child("Lisa", bank, initialCash)
{}

void Lisa::Act()
{
	Child::Act(); 
	if (apu_ && cash_ >= DOLL_THRESHOLD)
	{
		if (SpendCash(DOLL_COST))
		{
			apu_->ReceiveCashPayment(DOLL_COST);
			Log("bought a doll from Apu for $" + std::to_string(DOLL_COST));
		}
	}
}