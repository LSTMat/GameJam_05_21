// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"
#include "GameJam_052021/InteractionComponent.h"


void UInteractionWidget::UpdateInteractionWidget(class UInteractionComponent* InteractionComponent) 
{
    OwningInteractionComponent = InteractionComponent;
    OnUpdateInteractionWidget();
}
