#include "ThrowRockAbility.h"

ThrowRockAbility::ThrowRockAbility(float extraDamage) : damage(extraDamage)
{
}

void ThrowRockAbility::ActivateAbility(std::shared_ptr<Character> user)
{
	//if target is dead we return
	auto target = user->GetTarget();
	if (target->IsDead)
		return;
	//cache original base damage
	float prevDamageAmount = user->BaseDamage;
	user->BaseDamage += damage; //Add damage
	user->Attack();
	user->BaseDamage = prevDamageAmount; //Set damage back to original after attack
}
