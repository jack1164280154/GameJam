#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameJamProject/GameCore/QSVar.h"
#include "TestBall.generated.h"
UCLASS()
class ATestBall : public AActor
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	void OnTestEvent(QSVar& Var);
	void OnTestEventOneParam(QSVar& Var);
};