#pragma once

#include <map>
#include <memory>
#include <filesystem>

template<class Ressource, class Identifier>
class RessourceHolder
{
private:
	std::map<Identifier, std::unique_ptr<Ressource>> mRessourceMap;
public:
	void insert(Identifier id, std::unique_ptr<Ressource> ressource);
	Ressource& get(Identifier id);
	Ressource const& get(Identifier id) const;
};

#include "RessourceHolder.inl"
