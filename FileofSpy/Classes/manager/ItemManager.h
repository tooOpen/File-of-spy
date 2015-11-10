/*
 * ItemManager.h
 *
 *  Created on: 2014. 5. 31.
 *      Author: pc
 */

#ifndef ITEMMANAGER_H_
#define ITEMMANAGER_H_

class ItemManager {
private:
	int ticket;
	int bag;
	int armor;
	int gun;

	int ticketArr[5];
	int bagArr[5];
	int armorArr[2];
	int gunArr[3];
	static ItemManager* itemmanager;
	ItemManager();
public:
	static ItemManager* getItemManager()
			{
					if(!itemmanager)
					{
						itemmanager = new ItemManager();
					}
					return itemmanager;
			}
	void setItem(int line,int index);

	int getTicketItem();
	int getBagItem();
	int getArmorItem();
	int getGunItem();

	int getTicketItemIndex();
	int getBagItemIndex();
	int getArmorItemIndex();
	int getGunItemIndex();
	virtual ~ItemManager();

};

#endif /* ITEMMANAGER_H_ */
