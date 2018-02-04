// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Project_SGCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "Classes/Kismet/KismetMathLibrary.h"
#include "ConstructorHelpers.h"

//////////////////////////////////////////////////////////////////////////
// ABaseInteractable

ABaseInteractable::ABaseInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a static mesh component as the root
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMesh"));
	RootComponent = InteractableMesh;
	
	// Sphere Collision component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->InitSphereRadius(SphereCollisionRadius);

	// Setup Sphere Overlap Functions
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractable::BeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractable::EndOverlap);

	// Widget Component
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Item_Name"));
	WidgetComponent->SetupAttachment(RootComponent);

	// Wiget settings
	WidgetComponent->SetRelativeLocation(FVector(0.f, -10.f, 40.f), false);
	WidgetComponent->SetRelativeRotation(FRotator(0.f));
	WidgetComponent->SetPivot(FVector2D(0.25f, 0.5f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	SetupWigetClass();
	
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();

	WidgetComponent->SetVisibility(false);
}

//////////////////////////////////////////////////////////////////////////
// Overlap functions

void ABaseInteractable::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) 
{
	if (!OtherActor->IsA(AProject_SGCharacter::StaticClass())) { return; }

	WidgetComponent->SetVisibility(true); // object displays text
	InteractableMesh->SetRenderCustomDepth(true); // object glows
}

void ABaseInteractable::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (!OtherActor->IsA(AProject_SGCharacter::StaticClass())) { return; }
		
	WidgetComponent->SetVisibility(false); // object stops displaying text
	InteractableMesh->SetRenderCustomDepth(false); // object stops glowing
}

//////////////////////////////////////////////////////////////////////////
// ABaseInteractable functions

void ABaseInteractable::SetupWigetClass()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BaseInteractable_UI(TEXT("/Game/UI/BaseInteractable_UI"));
	if (!BaseInteractable_UI.Succeeded()) { return; }

	WidgetComponent->SetWidgetClass(BaseInteractable_UI.Class);
}