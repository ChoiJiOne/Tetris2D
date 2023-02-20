#include "ServiceLocator.h"

std::unordered_map<ServiceLocator::EServiceType, std::unique_ptr<ISystem>> ServiceLocator::LocateSystems_;

void ServiceLocator::CleanupSystem()
{
	for (auto& System : LocateSystems_)
	{
		System.second.reset();
	}
}