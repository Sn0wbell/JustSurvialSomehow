#ifndef __CRAFTING_H__
#define __CRAFTING_H__

#include <vector>
#include <string>
#include "Item.h"

class Crafting {
public:
    struct Recipe {
        std::string resultItem; // Name of the item produced
        std::vector<Item::ItemType> requiredItems; // Items required to craft
    };

    // Add crafting recipe
    void addRecipe(const std::string& resultItem, const std::vector<Item::ItemType>& requiredItems);

    // Attempt to craft an item
    bool craft(const std::string& itemName);

private:
    std::vector<Recipe> _recipes;
};

#endif // __CRAFTING_H__
