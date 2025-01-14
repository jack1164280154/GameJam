#include "TestBall.h"

#include "GameJamProject/GameCore/GameEventSystem.h"

void ATestBall::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	BIND_EVENT(this, "TestEvent", FFunctionSlot(this, &ATestBall::OnTestEvent));
	BIND_EVENT(this, "TestEventOneParam", FFunctionSlot(this, &ATestBall::OnTestEventOneParam));
}

void ATestBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Error, TEXT("Test Ball Tick!"));
	FIRE_EVENT(this, "TestEvent");
	FIRE_EVENT_OneParam(this, "TestEventOneParam", 10);
}

void ATestBall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UNBIND_EVENT(this, "TestEvent", FFunctionSlot(this, &ATestBall::OnTestEvent));
	UNBIND_EVENT(this, "TestEventOneParam", FFunctionSlot(this, &ATestBall::OnTestEventOneParam));
}

void ATestBall::OnTestEvent(QSVar& Var)
{
	UE_LOG(LogTemp, Error, TEXT("Test Event Fire!"));
}

void ATestBall::OnTestEventOneParam(QSVar& Var)
{
	UE_LOG(LogTemp, Error, TEXT("Test Event One Param Fire! %d"), Var[0].ToInt());
}
