#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"

item::item(int id, const char *name)
{
	this->id = id;
	this->name = name;
}

void initItemDict(item itemList[])
{
	itemList[0] = item(0, "Big Muscles");
	itemList[1] = item(1, "Milk");
	itemList[2] = item(2, "AAAUUURRGGGHHHH");
	itemList[3] = item(3, "David");
	itemList[4] = item(4, "Uno reverse card");
	itemList[5] = item(5, "More Projectiles");
	itemList[6] = item(6, "Health");
}