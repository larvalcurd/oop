#pragma once

#include "Child.h"

class Bart : public Child
{
public:
	Bart(Bank& bank, Money initialCash = 0);
};