#pragma once

#include "FFunctionSlot.h"
#include "QSVar.h"
#include "GameEventSystem.generated.h"

UCLASS()
class UGameEventSystem: public UGameInstanceSubsystem
{
	GENERATED_BODY()

	typedef TMap<FString, FFunctionSlot> EventSet;
	EventSet m_EventSet;
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	void Bind(const FString& EventName, const FFunctionSlot& EventFunction);
	void Unbind(const FString& EventName, const FFunctionSlot& EventFunction);
	void Fire(const FString& EventName, QSVar& Args);
	void Fire(const FString& EventName);
	template <typename... TArgs>
	void FireEvent(const FString& EventName, TArgs... Args)
	{
		QSVar Var;

		int Arr[] = {(__PzEventCreateArgs(Var, Args), 0)...};

		Fire(EventName, Var);
	}

	static UGameEventSystem* Get(const UObject* WorldContext)
	{
		if (IsEngineExitRequested())
		{
			UE_LOG(LogTemp, Warning, TEXT("UGameEventSystem Get But Engine Is Exiting"));
			return nullptr;
		}
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
		if (!IsValid(World))
		{
			return nullptr;
		}
		const auto GameInstance = World->GetGameInstance();
		if (!IsValid(GameInstance))
		{
			return nullptr;
		}
		
		UGameEventSystem* GameEventSystem = GameInstance->GetSubsystem<UGameEventSystem>();

		if (!IsValid(GameEventSystem))
		{
			return nullptr;
		}
		
		return GameEventSystem;
	}
private:
	template <typename T>
	static void __PzEventCreateArgs(QSVar& Var, T Arg)
	{
		Var.push_back(Arg);
	}
};

#define BIND_EVENT(WorldContext, EventName, Slot) if (UGameEventSystem* EventSystem = UGameEventSystem::Get(WorldContext)) EventSystem->Bind(EventName, Slot)
#define UNBIND_EVENT(WorldContext, EventName, Slot) if (UGameEventSystem* EventSystem = UGameEventSystem::Get(WorldContext)) EventSystem->Unbind(EventName, Slot)
#define FIRE_EVENT(WorldContext, EventName) if (UGameEventSystem* EventSystem = UGameEventSystem::Get(WorldContext)) EventSystem->Fire(EventName)
#define FIRE_EVENT_OneParam(WorldContext, EventName, Param1) if (UGameEventSystem* EventSystem = UGameEventSystem::Get(WorldContext)) EventSystem->FireEvent(EventName, Param1)