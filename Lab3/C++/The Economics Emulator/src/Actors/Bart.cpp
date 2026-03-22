#include "Bart.h"

Bart::Bart(Bank& bank, Money initialCash)
	: Child("Bart", bank, initialCash)
{
}