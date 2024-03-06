#include <iostream>
#include "Item.h"
using namespace std;
Item::Item() {
	name = "NoName";
}
Item::Item(string itemName) {
	name = itemName;
}

void Item::SetName(string itemName)
{
	name = itemName;
}

string Item::GetName() {
	return name;
}

