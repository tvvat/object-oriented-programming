#include <ctime>
#include <utility>
#include <string>
#include <string.h>
#include <iostream>
//#include <unistd.h>
#include <stdio.h>
#include <dos.h>

#include <windows.h>
#include <thread>
#include <chrono>
#include "Build.h"
#include "Game.h"
#include "Enemy.h"


using namespace std;

namespace cry {


	Game::Game() {

		towercoordin.resize(counttower);
		towercoordin[0] = std::make_pair(20, 30);
		towercoordin[1] = std::make_pair(20, 32);
		towercoordin[2] = std::make_pair(17, 26);
		towercoordin[3] = std::make_pair(15, 31);
		towercoordin[4] = std::make_pair(15, 35);
		towercoordin[5] = std::make_pair(17, 40);
		towercoordin[7] = std::make_pair(35, 40);
		towercoordin[8] = std::make_pair(30, 37);
		towercoordin[9] = std::make_pair(30, 39);
		towercoordin[6] = std::make_pair(30, 42);
		palacecordin = std::make_pair(25, 45);
		laircoordin = std::make_pair(30, 5);


		card.setCoordin(palacecordin, laircoordin, towercoordin);

		clocktolvl = min5;
		option.money = 0;
		option.time = 0;

		clock = time(NULL);
	}
	Playng_field  Game::start() {

		


		/*while ((clocktolvl >=  time(NULL)- clock) && (palace.gameover())) {*/


			auto tmp = lair.creatEnemytime(time(NULL) - clock );
			if (tmp.numberenemies > 0) {
				putenemy(tmp);
			}
			option.money += palace.earnmoney(time(NULL) - clock);
			card.calculateTrajectory();

			/*std::cout << "option:money: " << option.money << " time:" << time(NULL) - clock << "/" << clocktolvl << std::endl;*/
			
			for (auto i = 0; i < card.enemypalace.size(); i++) {
				auto tm = card.enemypalace[i];
				palace.setdem(tm->getDamage());
			}/*
			
			
			std::cout << "u want creat tower?y/n";
			char ans;
			std::cin >> ans;
			if (ans == 'y') {
				std::cout << "enter x y"; 
				int x, y;
				std::cin >> x >> y;
				option.money = creatbuild(std::make_pair(x, y), option.money);
			}*/
			return card;
		/*}*/
	}
	int Game::putenemy(allenemy& enemy) {
		for (int i = 0; i < enemy.numberenemies[light]; i++) {
			card.setpairenemy(laircoordin, light);
			Sleep(100);
			card.calculateTrajectory();
			
		}
		for (int i = 0; i < enemy.numberenemies[heavy]; i++) {
			card.setpairenemy(laircoordin, heavy);
			Sleep(100);
			card.calculateTrajectory();

		}
		for (int i = 0; i < enemy.numberenemies[fly]; i++) {
			card.setpairenemy(laircoordin, fly);
			Sleep(100);
			card.calculateTrajectory();

		}
		
		
		return 0;
	}
	time_t Game::gettime() {

		return clock;
	}
	time_t Game::countttime() {

		return clock;
	}

	int Game::creatbuild(std::pair<int, int> t,int money) {
		if (card.quad[t.first][t.second].getType() != towertypeempty)
			return money;
		Tower n;
		if (money - n.getcost() < 0) 
			return money;

		card.towerwhere[t] = std::make_shared<Tower>();
		card.quad[t.first][t.second].setType(towertype);
		return money - n.getcost();


	};
	Playng_field::Playng_field() :lenght(50), width(50) {

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < lenght; j++) {
				quad[i][j].setType(plain);

				/*quad[i][j].setCoordinat(std::make_pair(i,j));*/
			}
		}

		for (int i = 22; i < 35; i++) {
			for (int j = 30; j < 38; j++) {
				quad[i][j].setType(mountain);
			}

		}
		for (int i = 36; i < width; i++) {
			for (int j = 30; j < 38; j++) {
				quad[i][j].setType(reservoir);
			}

		}
		
		palacecoordin = std::make_pair(0, 0);
	}
	int Playng_field::show() {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < lenght; j++) {
				auto t = enemywhere.find(std::make_pair(i, j));
				if (t != enemywhere.end()) {
					std::cout << 'e' << ' ';
					continue;
				}
				if (quad[i][j].getType() == plain) {

					std::cout << ' ' << ' ';
					continue;
				}
				std::cout << quad[i][j].getType() << ' ';
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;

		return 0;
	}
	int Playng_field::calculateTrajectory() {
		map<std::pair<int, int>, std::shared_ptr<Enemy> > tmp;
		map<std::pair<int, int>, typeenemy > tmptype;
		auto type = typewhere.begin();


		for (auto it = enemywhere.begin(); it != enemywhere.end(); ++it, ++type) {
			if (it->first.second < palacecoordin.second) {
				auto newstep = it->second->moving(*this, std::make_pair(it->first.first , it->first.second+1), 0);
				if (newstep == palacecoordin) {/*
					enemypalace.pushBack(it->second);*/
				}
				else {
					tmp[newstep] = it->second;
					tmptype[newstep] = type->second;
				}
				
			}
			else
				if (it->first.second == palacecoordin.second) {
					auto newstep = it->second->moving(*this, std::make_pair(it->first.first, it->first.second +1), 1);
					if (newstep == palacecoordin) {/*
						enemypalace.pushBack(it->second);*/
					}
					else {
						tmp[newstep] = it->second;
						tmptype[newstep] = type->second;
					}
				}
				else {
					auto newstep = it->second->moving(*this, std::make_pair(it->first.first , it->first.second-1), 2);
					if (newstep == palacecoordin) {/*
						enemypalace.pushBack(it->second);*/
					}
					else {
						tmp[newstep] = it->second;
						tmptype[newstep] = type->second;
					}
				}
				
		}
		typewhere = tmptype;
		enemywhere = tmp;

		map<std::pair<int, int>, std::shared_ptr<Tower> >  tmptower;
		auto i = towerwhere.begin();
		for (; i != towerwhere.end(); i++) {
			auto tmp = i->second->calculatedistenemy(*this, i->first);
			if (std::make_pair(-1, -1) != tmp) {
				enemywhere.erase(tmp);
			}
		}
		return 0;
	}
	void Playng_field::setlenght(int a) {

		if (a < 0)
			throw std::exception("size can't be < 0\n");
		lenght = a;

	}
	void Playng_field::setwidth(int b) {
		if (b < 0)
			throw std::exception("size can't be < 0\n");
		width = b;


	};
	void Playng_field::setCoordin(std::pair<int, int> plc, std::pair<int, int>lr, Vector<std::pair<int, int>> twr) {

		for (int i = 0; i < counttower; i++)
			quad[twr[i].first][twr[i].second].setType(towertypeempty);

		quad[plc.first][plc.second].setType(palacetype);
		quad[lr.first][lr.second].setType(lairtype);
		palacecoordin = plc;
		laircoordin = lr;


	}
	int Playng_field::creatfiald(std::pair<int,int>coord,Typeland type) {
		if ((coord.second > width) || (coord.first > lenght) || (coord.first < 0) || (coord.second < 0))
			return 1;
		quad[coord.second][coord.first].setType(type);
		return 0;
	};
	int Playng_field::setpairpalace(std::pair<int, int> a) {
		if ((a.second > width) || (a.first > lenght) || (a.first < 0) || (a.second < 0))
			return 1;
		palacecoordin = a;
		return 0;
	};
	int Playng_field::setpairlair(std::pair<int, int> a) {
		if ((a.second > width) || (a.first > lenght) || (a.first < 0) || (a.second < 0))
			return 1;
		laircoordin = a;
		return 0;
	};

	int Playng_field::setpairenemy(std::pair<int, int> coord, typeenemy type) {
		if ((coord.first > width) || (coord.second > lenght) || (coord.first < 0) || (coord.second < 0))
			return 1;
		typewhere[(coord)] = type;
		

		if (type == fly){
			std::shared_ptr<Enemyfly> force ;
			 enemywhere[(coord)] = std::make_shared <Enemyfly>();
		}
		if (type == light) {
			std::shared_ptr<Enemylight> force;
			 enemywhere[(coord)] = std::make_shared <Enemylight>();;
		}
		if (type == heavy) {
			std::shared_ptr<Enemyheavy> force;
			enemywhere[(coord)] = std::make_shared <Enemyheavy>();;
		}
		return 0;

	};




	
	int landscape::setType(Typeland a) {
		if (a > enemytype)
			throw std::exception("unknow type\n");
		type = a;
		return 0;
	};






}