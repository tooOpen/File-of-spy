/*
 * ItemManager.cpp
 *
 *  Created on: 2014. 5. 31.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/manager/ItemManager.h"

ItemManager::ItemManager() {
	// TODO Auto-generated constructor stub
	ticket = -1;
	bag = -1;
	armor = -1;
	gun = -1;

	ticketArr[0] = 10;
	ticketArr[1] = 15;
	ticketArr[2] = 20;
	ticketArr[3] = 25;
	ticketArr[4] = 30;

	bagArr[0] = 15;
	bagArr[1] = 20;
	bagArr[2] = 25;
	bagArr[3] = 30;
	bagArr[4] = 35;

	armorArr[0] = 2;
	armorArr[1] = 3;

	gunArr[0] = 2;
	gunArr[1] = 3;
	gunArr[2] = 5;

}
ItemManager* ItemManager::itemmanager;
ItemManager::~ItemManager() {
	// TODO Auto-generated destructor stub
}

int ItemManager::getTicketItem()
{
	if(ticket >=0)
	return ticketArr[ticket];
	else
		return -1;
}
int ItemManager::getBagItem()
{
	if(bag >=0)
	return ticketArr[bag];
	else
		return -1;
}
int ItemManager::getArmorItem()
{
	if(armor >=0)
	return ticketArr[armor];
	else
		return -1;
}
int ItemManager::getGunItem()
{
	if(gun >=0)
	return ticketArr[gun];
	else
		return -1;
}

int ItemManager::getTicketItemIndex()
{
	return ticket;
}
int ItemManager::getBagItemIndex()
{
	return bag;
}
int ItemManager::getArmorItemIndex()
{
	return armor;
}
int ItemManager::getGunItemIndex()
{
	return gun;
}

void ItemManager::setItem(int line,int index)
{
	switch(line)
	{
	case 1:
		this->ticket = index;
		break;
	case 2:
		this->bag = index-5;
		break;
	case 3:
		this->armor = index-10;
		break;
	case 4:
		this->gun = index-12;
		break;
	}
}

