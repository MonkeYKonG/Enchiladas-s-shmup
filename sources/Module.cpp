#include "Module.hpp"

my::schmup::Module::Module()
{}

my::schmup::Module::ModulePtr my::schmup::Module::Create(XMLNode::XMLNodePtr moduleNode) throw(std::out_of_range, std::invalid_argument)
{
	ModulePtr newModule;

	try
	{
		if (!moduleNode)
			throw (std::invalid_argument("moduleNode: null node"));
		newModule = ModulePtr(new Module());
	}
	catch (const std::out_of_range & e)
	{
		throw (std::out_of_range("Module: Create: " + std::string(e.what())));
	}
	catch (const std::invalid_argument & e)
	{
		throw (std::invalid_argument("Module: Create: " + std::string(e.what())));
	}
	return (newModule);
}