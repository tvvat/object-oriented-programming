#include <utility>
#include <string>
#include <string.h>
#include <iostream>
#include "Game.h"
#include "Enemy.h"

namespace cry {


	Enemy::Enemy(std::string title , int dam , int HP , int healka , int speadhealka ) : speedwolk(blockpersec) {
		name = title;
		damage = dam;
		maxHP = HP;
		nowHP = HP;
		speedwolk = 1;
		speedheal = speadhealka;
		heal = healka;

	}


	void Enemy::setSpeedh(int speed) {
		if (speed <= 0) {
			throw std::exception("speed must be > 0");
		}
		speedheal = speed;
	}
	void Enemy::setSpeedW(int speed) {
		if (speed <= 0) {
			throw std::exception("speed must be > 0");
		}
		speedwolk = speed;

	}
	void Enemy::setdamege(int dam) {

		if (dam <= 0) {
			throw std::exception("that isn t heal");
		}
		damage = dam;
	}
	int  Enemy::setHP(int hp) {
		if (hp <= 0) {
			return 1;
		}	
		if (hp > maxHP) {
			return 1;
		}
		nowHP = hp;
		return 0;
	}
	int  Enemy::fight(int damto) {
		nowHP -= damto;
		if (nowHP <= 0)
			return  1;
		return 0;
	}
	int  Enemy::plushp(time_t clock) {
		if (clock % secperHP == 0) {
			if (nowHP + heal <= maxHP)
				nowHP += heal;
			else
				nowHP = maxHP;
			return 1;
		}
		return 0;
	}
	void Enemy::setMax(int hp) {
		if (hp <= 0) {
			throw std::exception("enemy not die");
		}
		maxHP = hp;
	}


	std::pair<int,int> Enemylight::moving(const Playng_field& field, std::pair<int,int> step,int xy) {
		
		auto tmp = field.quad[step.first][step.second];
		int plus = 1;
		int minus = 1;
		std::pair<int, int> newstep01(0, 0);
		int flagplus = 0;
		int flagminus = 0;

		auto dist0 = std::hypot(field.palacecoordin.first  - step.first + 1, field.palacecoordin.second - (step.second ));
		auto dist = std::hypot(field.palacecoordin.first - step.first , field.palacecoordin.second - step.second);
		auto dist1 = std::hypot(field.palacecoordin.first - step.first - 1, field.palacecoordin.second - (step.second ));
		map<int, std::pair<int, int>> tmp1;/*
		tmp1[dist0] = std::make_pair(step.first-1,step.second );
		tmp1[dist] = std::make_pair(step.first,step.second);
		tmp1[dist1] = std::make_pair(step.first+1,step.second  );*/
		
		tmp1.insert(std::make_pair(dist0, std::make_pair(step.first - 1, step.second)));
		tmp1.insert(std::make_pair(dist, std::make_pair(step.first , step.second)));
		tmp1.insert(std::make_pair(dist1, std::make_pair(step.first + 1, step.second)));
		
		std::cout << dist0 << ' ' << dist << ' ' << dist1 << '\n';
		auto res = tmp1.begin();
		tmp = field.quad[(*res).second.first][(*res).second.second];
		if ((tmp.getType() == plain))
			return (*res).second;
		else {
			res++;
			tmp = field.quad[(*res).second.first][(*res).second.second];
			if ((tmp.getType() == plain) )
				return (*res).second;
			else {
				res++;
				tmp = field.quad[(*res).second.first][(*res).second.second];
				if ((tmp.getType() == plain) )
					return (*res).second;
				else {
					auto stepup = std::make_pair( step.first -1,step.second - 1);
					tmp = field.quad[ step.first - 1][step.second- 1];
					if ((tmp.getType() == plain) )
						return stepup;
					else
						return std::make_pair(0, 0);
				}
			}


		}

		return newstep01;
	}



	std::pair<int, int> Enemyheavy::moving(const Playng_field& field, std::pair<int, int> step,int xy) {
		auto tmp = field.quad[step.first][step.second];
		int plus = 1;
		int minus = 1;
		std::pair<int, int> newstep01(0,0);
		int flagplus = 0;
		int flagminus = 0;

			auto dist0 = std::hypot(field.palacecoordin.first - step.first + 1, field.palacecoordin.second - (step.second ));
			auto dist = std::hypot(field.palacecoordin.first - step.first, field.palacecoordin.second - step.second);
			auto dist1 = std::hypot(field.palacecoordin.first - step.first - 1, field.palacecoordin.second - (step.second ));
			map<int, std::pair<int, int>> tmp1;/*
			tmp1[dist0] = std::make_pair(step.first -1, step.second );
			tmp1[dist] = std::make_pair(step.first, step.second );
			tmp1[dist1] = std::make_pair(step.first + 1, step.second );*/

			tmp1.insert(std::make_pair(dist0, std::make_pair(step.first - 1, step.second)));
			tmp1.insert(std::make_pair(dist, std::make_pair(step.first, step.second)));
			tmp1.insert(std::make_pair(dist1, std::make_pair(step.first + 1, step.second)));

			auto res = tmp1.begin();
			tmp = field.quad[(*res).second.first][(*res).second.second];
			if((tmp.getType() == plain) || (tmp.getType() == walltype))
				return (*res).second;
			else {
				res++;
				tmp = field.quad[(*res).second.first][(*res).second.second];
				if ((tmp.getType() == plain) || (tmp.getType() == walltype))
					return (*res).second;
				else {
					res++;
					tmp = field.quad[(*res).second.first][(*res).second.second];
					if ((tmp.getType() == plain) || (tmp.getType() == walltype))
						return (*res).second;
					else {
						auto stepup = std::make_pair(step.first -1 , step.second - 1);
						tmp = field.quad[step.first - 1][step.second - 1];
						if ((tmp.getType() == plain) || (tmp.getType() == walltype))
							return stepup;
						else 
							return std::make_pair(step.first-1, step.second+1);
					}
				}


			}
			
			return newstep01;
		/*}
		else {


		}
		return std::make_pair(0, 0);*/
	}

	std::pair<int, int> Enemyfly::moving(const Playng_field& field, std::pair<int, int> step, int xy) {
	
		auto tmp = field.quad[step.first][step.second];
		int plus = 1;
		int minus = 1;
		std::pair<int, int> newstep01(0, 0);
		int flagplus = 0;
		int flagminus = 0;

		auto dist0 = std::hypot(field.palacecoordin.first - step.first +1, field.palacecoordin.second - (step.second ));
		auto dist = std::hypot(field.palacecoordin.first - step.first, field.palacecoordin.second - step.second);
		auto dist1 = std::hypot(field.palacecoordin.first - step.first - 1, field.palacecoordin.second - step.second );
		map<int, std::pair<int, int>> tmp1;/*
		tmp1[dist0] = std::make_pair(step.first-1, step.second );
		tmp1[dist] = std::make_pair(step.first, step.second);
		tmp1[dist1] = std::make_pair(step.first+1, step.second );*/


		tmp1.insert(std::make_pair(dist0, std::make_pair(step.first - 1, step.second)));
		tmp1.insert(std::make_pair(dist, std::make_pair(step.first, step.second)));
		tmp1.insert(std::make_pair(dist1, std::make_pair(step.first + 1, step.second)));

		std::cout << dist0 << ' ' << dist << ' ' << dist1 << '\n';
		auto res = tmp1.begin();
		tmp = field.quad[(*res).second.first][(*res).second.second];
		if (!(tmp.getType() == mountain))
			return (*res).second;
		else {
			res++;
			tmp = field.quad[(*res).second.first][(*res).second.second];
			if (!(tmp.getType() == mountain))
				return (*res).second;
			else {
				res++;
				tmp = field.quad[(*res).second.first][(*res).second.second];
				if (!(tmp.getType() == mountain))
					return (*res).second;
				else {
					auto stepup = std::make_pair(step.first - 1, step.second - 1);
					tmp = field.quad[step.first - 1][step.second - 1];
					if (!(tmp.getType() == mountain))
						return stepup;
					else
						return std::make_pair(0, 0);
				}
			}


		}

		return newstep01;



	}


	std::pair<int, int> superEnemyheavy::findtower(std::pair<int, int> t, const Playng_field & field) {
		auto tmp = t;
		for (int i = tmp.first - R0; i < tmp.first + R0; i++) {
			for (int j = tmp.second - R0; j < tmp.second + R0; j++) {

				auto it = field.towerwhere.find(std::make_pair(i, j));
				if (it != field.towerwhere.end()) {
					if (it->second->setdamage(force)) {
						return it->first;

					}
				}
			}
		}


		return std::make_pair(0,0);

	}

	std::pair<int, int> superEnemylight::findtower(std::pair<int, int>t , const Playng_field& field) {

		auto tmp = t;
		for (int i = tmp.first - R0; i < tmp.first + R0; i++) {
			for (int j = tmp.second - R0; j < tmp.second + R0; j++) {

				auto it = field.towerwhere.find(std::make_pair(i, j));
				if (it != field.towerwhere.end()) {
					if (it->second->setdamage(force)) {
						return it->first;

					}
				}
			}
		}


		return std::make_pair(0, 0);
	}

	std::pair<int, int> superEnemyfly::findtower(std::pair<int, int>t,  const Playng_field& field ) {

		auto tmp = t;
		for (int i = tmp.first - R0; i < tmp.first + R0; i++) {
			for (int j = tmp.second - R0; j < tmp.second + R0; j++) {

				auto it = field.towerwhere.find(std::make_pair(i, j));
				if (it != field.towerwhere.end()) {
					if (it->second->setdamage(force)) {
						return it->first;

					}
				}
			}
		}


		return std::make_pair(0, 0);
	}


}