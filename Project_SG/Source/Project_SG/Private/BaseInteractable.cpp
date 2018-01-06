// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInteractable.h"



// Sets default values
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
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseInteractable::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult) 
{
	UE_LOG(LogTemp, Warning, TEXT("%s has overlapped with %s"), *(OverlappedComponent->GetName()), *(OtherActor->GetName()))
}

void ABaseInteractable::EndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) 
{
	UE_LOG(LogTemp, Warning, TEXT("%s has stopped overlapping with %s"), *(OverlappedComponent->GetName()), *(OtherActor->GetName()))
}
