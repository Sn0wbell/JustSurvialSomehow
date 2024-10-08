#ifndef __BuildObject_MANAGER_H__
#define __BuildObject_MANAGER_H__

#include "BuildObject.h"
#include <map>
#include <string>
#include <vector>

class Building {
public:
    Building();

    // Method to create a BuildObject
    BuildObject* createBuildObject(BuildObject::BuildObjectType type);

    // Method to check if there are enough resources to build
    bool canBuild(const BuildObject& BuildObject) const;

    // Method to place the BuildObject in the world
    void placeBuildObject(BuildObject* BuildObject, const cocos2d::Vec2& position);

private:
    std::map<BuildObject::BuildObjectType, BuildObject*> buildObjectTemplates; // To store BuildObject templates
    std::map<std::string, int> resources; // Player resources
};

#endif // __BuildObject_MANAGER_H__
