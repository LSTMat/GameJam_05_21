// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GameJam_052021/MainCharacter.h"
#include "GameJam_052021/InteractionWidget.h"


UInteractionComponent::UInteractionComponent() 
{

    SetComponentTickEnabled(false);

    InteractionTime = 1.f;
    InteractionDistance = 200.f;
    InteractionObjectName = FText::FromString("Object Name");
    InteractionObjectAction = FText::FromString("Object Action");

    Space = EWidgetSpace::Screen;
    DrawSize = FIntPoint(600,100);
    bDrawAtDesiredSize = true;

    SetActive(true);
    SetHiddenInGame(true);

}

void UInteractionComponent::SetInteractableNameText(const FText& NewNameText) 
{
    InteractionObjectName = NewNameText;
    RefreshWidget();
}

void UInteractionComponent::SetInteractableActionText(const FText& NewActionText) 
{
    InteractionObjectAction = NewActionText;
    RefreshWidget();
}

void UInteractionComponent::BeginFocus(class AMainCharacter* Character) 
{
    if (!IsActive() || !GetOwner() || !Character)
    {
        return;
    }

    OnBeginFocus.Broadcast(Character);

    SetHiddenInGame(false);

    for (auto& VisualComp : GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass()))
    {
        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
        {
            Prim->SetRenderCustomDepth(true);
        }
    }

    RefreshWidget();
}

void UInteractionComponent::EndFocus(class AMainCharacter* Character) 
{
    OnEndFocus.Broadcast(Character);

    SetHiddenInGame(true);

    for (auto& VisualComp : GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass()))
    {
        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
        {
            Prim->SetRenderCustomDepth(false);
        }
    }
}

void UInteractionComponent::BeginInteract(class AMainCharacter* Character) 
{
        Interactor = Character;
        OnBeginInteract.Broadcast(Character);
}

void UInteractionComponent::EndInteract(class AMainCharacter* Character) 
{
    Interactor = nullptr;
    OnEndInteract.Broadcast(Character);
}

void UInteractionComponent::Interact(class AMainCharacter* Character) 
{
        OnInteract.Broadcast(Character);
}

float UInteractionComponent::GetInteractPercentage() 
{
    if (Interactor && Interactor->IsInteracting())
    {
        return 1.f - FMath::Abs(Interactor->GetRemainingInteractTime() / InteractionTime);
    }

    return 0.f;
}

void UInteractionComponent::RefreshWidget()
{
    if(UInteractionWidget* InteractionWidget = Cast<UInteractionWidget>(GetUserWidgetObject()))
    {
        InteractionWidget->UpdateInteractionWidget(this);
    }
}


void UInteractionComponent::Deactivate() 
{
    if (Interactor)
    {
        EndFocus(Interactor);
        EndInteract(Interactor);
    }
    Interactor = nullptr;
}