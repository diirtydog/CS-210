#pragma once
#include <iostream>
using namespace std;
class Item
{
public:
	Item();
	Item(string itemName);
	void SetName(string itemName);
	string GetName();

private:
	string name;
};

