#include "../lib/listUtils.hpp"
#include "../lib/item.hpp"

Item::Item(char icon, const char *name) : Entity(&icon, {0, 0}, stdscr)
{
	this->name = name;
}

void initItemDict(Item itemList[])
{
	itemList[0] = Item('!', "Potion");
	itemList[1] = Item('?', "Scroll");
	itemList[2] = Item('(', "Sword");
	itemList[3] = Item(')', "Shield");
	itemList[4] = Item('[', "Bow");
	itemList[5] = Item(']', "Arrow");
	itemList[6] = Item('{', "Staff");
	itemList[7] = Item('}', "Wand");
	itemList[8] = Item('/', "Axe");
	itemList[9] = Item('\\', "Hammer");
	itemList[10] = Item('=', "Spear");
	itemList[11] = Item('`', "Dagger");
	itemList[12] = Item('~', "Mace");
	itemList[13] = Item(';', "Ring");
	itemList[14] = Item('"', "Necklace");

}