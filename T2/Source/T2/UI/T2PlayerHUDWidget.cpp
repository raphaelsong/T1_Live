// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/T2PlayerHUDWidget.h"
#include "UI/T2StatBarWidget.h"
#include "Components/T2AttributeComponent.h"

UT2PlayerHUDWidget::UT2PlayerHUDWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UT2PlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* OwningPawn = GetOwningPlayerPawn();
	if (OwningPawn)
	{
		UT2AttributeComponent* AttributeComponent = OwningPawn->GetComponentByClass<UT2AttributeComponent>();

		if (AttributeComponent)
		{
			AttributeComponent->OnAttributeChanged.AddUObject(this, &UT2PlayerHUDWidget::OnAttributeChanged);
			AttributeComponent->BroadcastAttributeChanged(ET2AttributeType::Stamina);
		}
	}
}

void UT2PlayerHUDWidget::OnAttributeChanged(ET2AttributeType InAttributeType, float InValue)
{
	switch (InAttributeType)
	{
	case ET2AttributeType::Stamina:
		StaminaBarWidget->SetStatBarRatio(InValue);
		break;
	case ET2AttributeType::Health:
		break;
	default:
		break;
	}
}
