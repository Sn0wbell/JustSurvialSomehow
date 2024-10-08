#include "Resource.h"

USING_NS_CC;

Resource* Resource::create(ItemType itemType, const std::string& name, const std::string& description, const std::string& spriteFile, ResourceType resourceType, int quantity, int maxQuantity, float effectValue, float durability)
{
    auto resource = new Resource();
    if (resource != nullptr && resource->initWithFile(spriteFile)) {
        resource->init(itemType, name, description, resourceType, quantity, maxQuantity, effectValue, durability);
        resource->autorelease();
        return resource;
    }

    CC_SAFE_DELETE(resource);
    return nullptr;
}

bool Resource::init(ItemType itemType, const std::string& name, const std::string& description, ResourceType resourceType, int quantity, int maxQuantity, float effectValue, float durability) {
    if (!Item::init(itemType, name, description, effectValue, durability)) {
        return false;
    }
    this->resourceType = resourceType;
    this->quantity = quantity;
    this->maxQuantity = maxQuantity;
    this->craftableItems.clear();

    this->scheduleUpdate();
    return true;
}

// Getter methods
Resource::ResourceType Resource::getType() const { return resourceType; }
int Resource::getQuantity() const { return quantity; }
int Resource::getMaxQuantity() const { return maxQuantity; }

// Method to exploit the resource
void Resource::exploit(int amount) {
    if (quantity > 0) {
        if (amount > quantity) {
            CCLOG("Not enough %s available. Exploiting all remaining.", getName().c_str());
            amount = quantity; // Collect all remaining resources
        }
        quantity -= amount;
        CCLOG("Exploited %d of %s. Remaining: %d", amount, getName().c_str(), quantity);
    }
    else {
        CCLOG("%s has already been fully exploited.", getName().c_str());
    }
}

// Method to add craftable items
void Resource::addCraftableItem(const std::string& itemName) {
    craftableItems.push_back(itemName);
    CCLOG("Added craftable item: %s for resource %s", itemName.c_str(), getName().c_str());
}

// Method to get craftable items
const std::vector<std::string>& Resource::getCraftableItems() const {
    return craftableItems;
}

// Override the onEnter method to set up the resource visual
void Resource::onEnter() {
    Item::onEnter();
    // Setup visual representation if necessary
}
