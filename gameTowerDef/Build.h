#pragma once
#include <time.h>
#include <string>
#include <string.h>
#include "Enemy.h"
//#include "Game.h"
#include <utility>
#include "vector.h"
#include <map>
#define numberoflvl 5
#define countenemy 3
#define timetab 40
#define wave 6
#define timewave 50
#define Num 3
#define counttower 10
#define min5 300
#define tensecond 10
#define towerlvl 10
#define R0 2
#define wallcost 30
#define rep 5
#define HPwall 10

using namespace std;
namespace cry {
	struct hcarater {
		int money;
		int speedmoney;
		int maxendurance;
		int endurance;
		int	heal;
		int	cost;
		int speedheal = tensecond;
	};
	class Palace {
	private:

		Vector<hcarater> table;
		int nowlvl;
	public:
		/**
		* @brief gconstract palace
		*
		**/
		Palace();
		/**
		* @brief lvl up our palace
		*
		**/
		bool lvlup(int);
		/**
		* @brief if hp < 0 game over
		*
		**/


		int gameover();

		/**
		* @brief how money we work for one time
		*
		**/
		int getmoney();
		/**
		* @brief demage to palace
		*
		**/
		void setdem(int t) { if (t < 0) return; table[nowlvl].endurance -= t; }

		/**
		* @brief earn money for time
		*
		**/
		int earnmoney(time_t);
		/**
		* @brief heal for time
		*
		**/
		int treatment(time_t);
	};

	enum Typetower {
		fire = 0,
		Strela,
		pushka,
	};
	struct Tablelvl {
		int radius;
		int damage;
		int speed;
		int cost;
	};
	class Tower {
	private:
		Typetower type;
		Vector<Tablelvl> lvl;
		int nowlvl;
	public:
		/**
		* @brief constract gefault = strela
		*@param t = type
		**/
		Tower(Typetower t = Strela);

		/**
		* @brief return type tower
		*
		**/
		Typetower getType() { return type; }
		/**
		* @brief lvl up
		*
		**/
		bool lvlup(int cost);
		/**
		* @brief quad around point R0
		*
		**/
		std::pair<int, int> calculatedistenemy(const Playng_field&, std::pair <int, int>);
		/**
		* @brief  return damage
		*
		**/
		int setdamage(int t) { if (t <= 0) return 0; return lvl[nowlvl].damage; }

		/**
		* @brief cost for lvl or creat
		*
		**/

		int getcost() { return lvl[nowlvl].cost; }


	};
	enum  typeenemy {
		light,
		heavy,
		fly,
		all,

	};
	struct allenemy {
		int numberenemies[all];

	};

	class Lair {
	private:
		map <time_t,allenemy > enemytime;
		/*time_t  time[countenemy];*/
	public:
		/**
		* @brief creats lair whith table time and number of emeny type
		*
		**/
		Lair();
		/**
		* @brief creat enemy for this time
		*
		**/
		allenemy& creatEnemytime(time_t);
		/**
		* @brief for didnt 
		*
		**/
		void creatEnemy();


	};


	class Wall {
	private:
		int maxHP;
		int nowHP;
		int repair;
		int cost;
	public:

		/**
		* @brief  creat wall
		*
		**/
		Wall();
		/**
		* @brief damage to wall
		*
		**/

	    int damage(int);

		/**
		* @brief heal wall by money
		*
		**/
		int heal(int);
		/**
		* @brief get max Hp
		*
		**/	
		int getMax() { return maxHP; };
		/**
		* @brief get now HP
		*
		**/
		int getNow() { return nowHP; };
		/**
		* @brief cost for wall
		*
		**/
		int getcost() { return cost; };

		/**
		* @brief set max HP
		*
		**/
		void setMax(int);
	};


}      // Исключите редко используемые компоненты из заголовков Windows
