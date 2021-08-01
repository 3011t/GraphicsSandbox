#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Model.h"

class Scene {
public:
	// Init, Load, Hierarchy(?)

	static Scene loadFromFile(std::string& filename);
private:
	// TODO: Lights, Models, Camera(s?), 
	
};

