#include <utility>
#include <string>
#include <string.h>
#include <iostream>
#include "Build.h"
#include "Game.h"
using namespace std;
namespace cry {


	Palace::Palace() {
		hcarater tmp;
		for (int i = 1; i <= numberoflvl; i++) {
			tmp.money = i * 10;
			tmp.cost = i * 50;
			tmp.maxendurance = i * 70;
			tmp.endurance = i * 70;
			tmp.heal = 1;
			tmp.speedheal = tensecond;
			tmp.speedmoney = tensecond;
			table.pushBack(tmp);
			

		}
		nowlvl = 0;
	}
	bool Palace::lvlup(int money) {
		if ((nowlvl + 1 == numberoflvl) || (money < table[nowlvl].money))
			return false;
		nowlvl++;
		return true;
	}
	int Palace::treatment(time_t clock) {
		if (clock % table[nowlvl].speedheal == 0) {
			if((table[nowlvl].endurance + table[nowlvl].heal<= table[nowlvl].maxendurance))
				table[nowlvl].endurance += table[nowlvl].heal;
			else
				table[nowlvl].endurance =table[nowlvl].maxendurance;
			return 1;
		}

		return 0;

	}
	int Palace::gameover() {
		return table[nowlvl].endurance;
	}
	int Palace::getmoney() {
		return table[nowlvl].money;
	}
	int Palace::earnmoney(time_t clock) {
		if (!clock % table[nowlvl].speedmoney) 
			return getmoney();
		return 0;

	}
	Tower::Tower(Typetower t) {
		type = t;
		nowlvl = 0;
		for (int i = 0; i < towerlvl; i++) {
			Tablelvl tmp;
			tmp.radius = R0;
			tmp.damage = (i + 1)*10;
			tmp.cost = i * sqrt(10);
			tmp.speed = sqrt(1 + i);
			lvl.pushBack(tmp);
		}

	}

	std::pair<int,int> Tower::calculatedistenemy(const Playng_field& field, std::pair<int, int> twrcrd) {
		auto tmp = twrcrd;
		for (int i = tmp.first - R0; i < tmp.first + R0; i++) {
			for (int j = tmp.second - R0; j < tmp.second + R0; j++){

				auto it = field.enemywhere.find(std::make_pair(i,j));
				if (it != field.enemywhere.end()) {
					if (it->second->fight(lvl[nowlvl].damage)) {
						return it->first;
				
					}
				}
			}
		}

		return std::make_pair(-1,-1);
	}
	bool Tower::lvlup(int cost) {
		if ((nowlvl + 1 == towerlvl) || (cost < lvl[nowlvl].cost))
			return false; 
		nowlvl++;
		return  true;
	};

	Lair::Lair() {

		for (int i = 0; i < timetab; i++) {

			allenemy tmpenemy ;
			for(int j = 0; j < all; j++)
				tmpenemy.numberenemies[j] = 1 ;
			
			enemytime[i] = tmpenemy;
		}
		for (int i = 1; i < wave; i++) {


			allenemy tmpenemy ; 
			for (int j = 0; j < all; j++)
				tmpenemy.numberenemies[j] = sqrt(i * ((int)timewave));	
			
			enemytime[i * timewave] = tmpenemy ;

		}

	}
	allenemy& Lair::creatEnemytime(time_t clock) {

		auto check = enemytime.find(clock);
		if (check == enemytime.end()) {
			auto i = enemytime.find(0);

			for (int j = 0; j < all; j++)
				i->second.numberenemies[j] = 0;

			return i->second;
		}

		return check->second;
	}
	void Lair::creatEnemy() {





	}





	Wall::Wall() {
		 cost = wallcost;
		 maxHP = HPwall;
		 nowHP = maxHP;
		 repair = rep;
	}
	int  Wall::damage(int a) {
		if (a < 0)
			return 0;
		nowHP -= a;
		if (nowHP <= 0)
			return 1;
		return 0;
	}
	int Wall::heal(int money) {
		if (money == cost){
			if (nowHP + repair > maxHP)
				nowHP = maxHP;
			else
				nowHP += repair;
			return 1;
		}
		return 0;
	}
	void Wall::setMax(int a) {
		if (a <= 0)
			throw std::exception("HP>0");
		maxHP = a;

	}



}