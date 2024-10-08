#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "cocos2d.h"

enum class ObjectType {
    TREE,
    ROCK,
    IRON,
    SILVER,
    GOLD
};

class Object : public cocos2d::Sprite {
public:

    static Object* create(ObjectType objectType, const std::string& name, const std::string& spriteFile, float durability = 0);
    virtual bool init(ObjectType objectType, const std::string& name, float durability);

    ObjectType getType() const;
    std::string getObjectName() const;
    float getDurability() const;
    std::vector<std::pair<std::string, int>> getItemsInclude() const;

private:
    ObjectType objectType;
    std::string name;
    std::string spriteFile;
    float durability;
    std::vector<std::pair<std::string, int>> itemsInclude;
};

#endif // __OBJECT_H__
