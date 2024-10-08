#include "Crafting.h"

void Crafting::addRecipe(const std::string& resultItem, const std::vector<Item::ItemType>& requiredItems) {
    Recipe newRecipe;
    newRecipe.resultItem = resultItem;
    newRecipe.requiredItems = requiredItems;
    _recipes.push_back(newRecipe);
}

bool Crafting::craft(const std::string& itemName) {
    for (const auto& recipe : _recipes) {
        if (recipe.resultItem == itemName) {
            // Here you would typically check the player's inventory for the required items
            // For simplicity, we'll just log the crafting action
            CCLOG("Crafting %s using:", itemName.c_str());
            for (const auto& item : recipe.requiredItems) {
                CCLOG(" - %s", static_cast<int>(item));
            }
            return true; // Crafting successful
        }
    }
    CCLOG("Crafting failed: No valid recipe found for %s.", itemName.c_str());
    return false; // No recipe found
}
