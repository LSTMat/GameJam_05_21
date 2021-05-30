// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"


UInteractionComponent::UInteractionComponent() 
{

    SetComponentTickEnabled(false);

    InteractionTime = 1.f;
    InteractionDistance = 200.f;
    InteractionObjectName = FText::FromString("Object Name");
    InteractionObjectDescription = FText::FromString("Object Description");

    Space = EWidgetSpace::Screen;
    DrawSize = FIntPoint(400,100);
    bDrawAtDesiredSize = true;

    SetActive(true);
    SetHiddenInGame(true);

}
