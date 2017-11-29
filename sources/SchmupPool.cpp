#include "SchmupPool.hpp"

my::schmup::ShipModule::ShipModulePtr	my::schmup::SchmupPool::CreateShipModule(XMLNode::XMLNodePtr shipModuleNode) throw (std::out_of_range, std::invalid_argument)
{
	ShipModule::ShipModulePtr newShipModule;
	XMLNode::XMLNodePtr childStk;

	try
	{
		if (!shipModuleNode)
			throw (std::invalid_argument("null node"));
		newShipModule = ShipModule::ShipModulePtr(new ShipModule);
		newShipModule->SetShipPosition(sf::Vector2i(std::stol(shipModuleNode->GetContent("x").second), std::stol(shipModuleNode->GetContent("y").second)));
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
	catch (const std::invalid_argument & e)
	{
		throw (e);
	}
}