#pragma once

#include "../Actor.h"

class Homer;
class Smithers;

class Burns : public Actor
{
public:
	Burns(Bank& bank, Money initialCash = 0);

	void SetEmployee(Homer* homer);
	void SetAssistant(Smithers* smithers);
	void UpdateAssistantAccount(AccountId accountId);

	void Act() override;

private:
	void PayHomer();
	void PaySmithers();

	static constexpr Money HOMER_SALARY = 258;
	static constexpr Money SMITHERS_SALARY = 50;

	Homer* employee_ = nullptr;
	Smithers* assistant_ = nullptr;

	AccountId assistantAccountId_ = 0;
	bool hasAssistantAccount_ = false;
};