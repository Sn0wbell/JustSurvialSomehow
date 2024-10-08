#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "Item.h"
#include <vector>
#include <string>

class Resource : public Item {
public:
    // Enum for resource types
    enum class ResourceType {
        WOOD,
        STONE,
        METAL
    };

    static Resource* create(ItemType itemType, const std::string& name, const std::string& description, const std::string& spriteFile, ResourceType resourceType, int quantity, int maxQuantity = 64, float effectValue = 0, float durability = 0);
    virtual bool init(ItemType itemType, const std::string& name, const std::string& description, ResourceType resourceType, int quantity, int maxQuantity, float effectValue, float durability);

    // Getter methods
    ResourceType getType() const;
    int getQuantity() const;
    int getMaxQuantity() const;

    // Method to exploit the resource
    void exploit(int amount);

    // Method to add craftable items
    void addCraftableItem(const std::string& itemName);
    const std::vector<std::string>& getCraftableItems() const;

    // Override the onEnter method to set up the resource visual
    void onEnter() override;

private:
    ResourceType resourceType;
    int quantity;     // Amount of resource available
    int maxQuantity;  // Maximum amount of resource allowed
    std::vector<std::string> craftableItems; // List of items that can be crafted using this resource
};

#endif // __RESOURCE_H__
