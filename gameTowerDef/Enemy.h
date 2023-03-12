#pragma once
#include <string>
#include <string.h>
//#include "Build.h"
//#include "Game.h"
#include <utility>
#include <iostream>
#include <ctime>
#define R0 3
#define blockpersec 1
#define heatlight 5
#define HPlight 1
#define heallight 30 
#define secperHP 3

#define heatheavy 7
#define HPheavy 40
#define healheavy 1 



#define heatfly 5
#define HPfly 20
#define healfly 1 
#define secperHPfly 4



namespace cry {

	class Playng_field;
	class Enemy {
	private:
		std::string name;
		int damage;
		int speedwolk;
		int speedheal;
		int heal;
		int maxHP;
		int nowHP;
	public:
		/**
		*@param "title"= name
		*@param "dam"=dam
		*@param "HP"= MAX HP
		*@param "healka"= HEAL HP PER SPEED
		*@param "speadhealka"= SEC PER HP
		**/

		Enemy(std::string title = "light", int dam = heatlight, int HP = HPlight, int healka = heallight, int speadhealka = secperHP);

		int getMaxHP() { return maxHP; }
		/**
		* @brief get now hphero
		*
		**/
		int getHP() { return nowHP; }
		/**
		* @brief get damege hero
		*
		**/
		int getDamage() { return damage; }
		/**
		* @brief get speed walk
		*
		**/
		int getSpeedW() { return speedwolk; }
		/**
		* @brief get speed heal
		*
		**/
		int getSpeedH() { return speedheal; }
		/**
		* @brief get heal [ser per hp]
		*
		**/
		int getHeal() { return heal; }
		/**
		* @brief change speed heal
		*
		**/
		void setSpeedh(int);
		/**
		* @brief change speed heal
		*
		**/
		void setSpeedW(int);
		/**
		* @brief change damage
		*
		**/
		void setdamege(int);
		/**
		* @brief new noww hp
		*
		**/
		int setHP(int);
		/**
		* @brief demag to emeny
		*
		**/
		int fight(int);	
		/**
		* @brief  heal
		*
		**/
		int plushp(time_t);

		/**
		* @brief  set max
		*
		**/
		void setMax(int);	
		/** 
		* @brief  for find min step
		* 
		* @param name="field"</wheresters>
		* @param name = "step"</ourstep>
		* @param name = "xy"</horizont or vertical>
		*<returns></returns>
		**/
		virtual std::pair<int, int> moving(const Playng_field&, std::pair<int, int>, int) = 0;
		~Enemy() = default;
	};

	struct aura {
		int radius = 0;
		int weakness;

	};
	class Playng_field;
	class Enemylight :public Enemy {
	private:/*
		Enemy light;*/
	public:
		Enemylight() {};

		std::pair<int,int> moving(const Playng_field &, std::pair<int, int>,int  );


	};


	class Enemyheavy:public Enemy {
	private:/*
		Enemy heavy("heavy", heatheavy, HPheavy,  healheavy, secperHP);*/
	public:

		Enemyheavy() : Enemy("heavy", heatheavy, HPheavy, healheavy, secperHP) {};
		std::pair<int,int>moving(const Playng_field &, std::pair<int, int>,int  );


	};
	class Enemyfly :public Enemy {
	private:/*
		Enemy fly;*/
	public:
		Enemyfly() : Enemy("fly", heatfly, HPfly, healfly, secperHPfly) {};
		std::pair<int,int> moving(const Playng_field &, std::pair<int, int>,int );



	}; 
	
	class superEnemylight :public Enemylight {
	private:/*
		Enemy light;*/int force = 3;
	public:
		std::pair<int,int> findtower(std::pair<int,int>, const Playng_field& );

	};


	class superEnemyheavy :public Enemyheavy {
	private:/*
		Enemy heavy("heavy", heatheavy, HPheavy,  healheavy, secperHP);*/int force = 3;
	public:

		superEnemyheavy() {};

		std::pair<int, int> findtower(std::pair<int, int>, const Playng_field&);


	};
	class superEnemyfly :public Enemyfly {
	private:/*
		Enemy fly;*/int force = 3;
	public:
		superEnemyfly() {};
		std::pair<int, int> findtower(std::pair<int, int>, const Playng_field&);


	};


}