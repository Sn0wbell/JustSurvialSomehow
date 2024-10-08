#include "Building.h"

Building::Building() {
    // Initialize resources (example)
    resources["Wood"] = 100;
    resources["Stone"] = 50;

    // Create BuildObject templates
    // Add more BuildObjects as needed
}

BuildObject* Building::createBuildObject(BuildObject::BuildObjectType type) {
    if (buildObjectTemplates.find(type) != buildObjectTemplates.end()) {
        // Return a new instance of the BuildObject
    }
    return nullptr;
}

bool Building::canBuild(const BuildObject& BuildObject) const {
    for (const auto& cost : BuildObject.getItemsInclude()) {
        if (resources.at(cost.first) < cost.second) {
            return false; // Not enough resources
        }
    }
    return true; // Enough resources
}

void Building::placeBuildObject(BuildObject* BuildObject, const cocos2d::Vec2& position) {
    if (BuildObject && canBuild(*BuildObject)) {
        BuildObject->setPosition(position);
        BuildObject->build(); // Call build logic
        // Deduct resources
        for (const auto& cost : BuildObject->getItemsInclude()) {
            resources[cost.first] -= cost.second;
        }
        // Add BuildObject to the game scene (pseudo-code, adapt as needed)
        // cocos2d::Director::getInstance()->getRunningScene()->addChild(BuildObject);
    }
}
