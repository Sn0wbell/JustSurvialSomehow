#ifndef __BUILD_OBJECT_H__
#define __BUILD_OBJECT_H__

#include "cocos2d.h"
#include "Object.h"
#include <string>
#include <vector>

class BuildObject : public Object {
public:
    enum class BuildObjectType {
        HOUSE,
        FARM,
        WORKSHOP,
        STORAGE
    };

    // Constructor
    static BuildObject* create(ObjectType objectType, const std::string& name, const std::string& spriteFile, BuildObjectType buildObjectType, float durability = 0);
    virtual bool init(ObjectType objectType, const std::string& name, BuildObjectType buildObjectType, float durability);

    // Getters
    BuildObjectType getBuildObjectType() const;

    // Method to build the building
    bool build();

private:
    BuildObjectType buildObjectType;
};

#endif // __BUILD_OBJECT_H__
