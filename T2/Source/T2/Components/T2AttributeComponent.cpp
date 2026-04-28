// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/T2AttributeComponent.h"
#include "T2AttributeComponent.h"

// Sets default values for this component's properties
UT2AttributeComponent::UT2AttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UT2AttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UT2AttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UT2AttributeComponent::CheckHasEnoughStamina(float StaminaCost) const
{
	return BaseStamina >= StaminaCost;
}

void UT2AttributeComponent::DecreaseStamina(float StaminaCost)
{
	BaseStamina = FMath::Clamp(BaseStamina - StaminaCost, 0.0f, MaxStamina);

	BroadcastAttributeChanged(ET2AttributeType::Stamina);
}

void UT2AttributeComponent::ToggleStaminaRegen(bool bEnabled, float StartDelay)
{
	if (bEnabled)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(StaminaRegenTimerHandle) == false)
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimerHandle, this, &UT2AttributeComponent::RegenStaminaHandler, StaminaRegenTime, true, StartDelay);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimerHandle);
	}
}

void UT2AttributeComponent::RegenStaminaHandler()
{
	BaseStamina = FMath::Clamp(BaseStamina + StaminaRegenRate, 0.0f, MaxStamina);

	BroadcastAttributeChanged(ET2AttributeType::Stamina);

	if (BaseStamina >= MaxStamina)
	{
		ToggleStaminaRegen(false);
	}
}

void UT2AttributeComponent::BroadcastAttributeChanged(ET2AttributeType InAttributeType) const
{
	if (OnAttributeChanged.IsBound())
	{
		float Ratio = 0.0f;
		switch (InAttributeType)
		{
		case ET2AttributeType::Stamina:
			Ratio = BaseStamina / MaxStamina;
			break;
		case ET2AttributeType::Health:
			break;
		default:
			break;
		}

		OnAttributeChanged.Broadcast(InAttributeType, Ratio);
	}
}

