
#include "GameEventSystem.h"

void UGameEventSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGameEventSystem::Deinitialize()
{
	Super::Deinitialize();
}

void UGameEventSystem::Bind(const FString& EventName, const FFunctionSlot& EventFunction)
{
	if (!m_EventSet.Find(EventName))
	{
		m_EventSet.Add(EventName, EventFunction);
	}
	else
	{
		m_EventSet[EventName] = EventFunction;
	}
}

void UGameEventSystem::Unbind(const FString& EventName, const FFunctionSlot& EventFunction)
{
	if (m_EventSet.Find(EventName))
	{
		m_EventSet.Remove(EventName);
	}
}

void UGameEventSystem::Fire(const FString& EventName, QSVar& Args)
{
	if (m_EventSet.Find(EventName))
	{
		const auto FunctionSlot = m_EventSet[EventName];
		FunctionSlot(Args);
	}
}

void UGameEventSystem::Fire(const FString& EventName)
{
	QSVar Var;
	Fire(EventName, Var);
}