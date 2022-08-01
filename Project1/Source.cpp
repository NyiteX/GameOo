#include <iostream>
using namespace std;

class Game
{
	string name;
protected:

	class Human
	{
		string name;
		unsigned short basicdmg;
		unsigned short armor;
		float noweapspeed;
	public:
		Human() {}

		string getName()const { return name; }
		unsigned short getDmg()const { return basicdmg; }
		unsigned short getArmor()const { return basicdmg; }
		float getNo_WeaponSpeed()const { return noweapspeed; }
		void setName(const string& n) { this->name = n; }
		void setDmg(const unsigned short& n) { this->basicdmg = n; }
		void setArmor(const unsigned short& n) { this->armor = n; }
		void setNoWeap_Speed(const float& n) { this->noweapspeed = n; }
	};

	class Weapon
	{
		string name;
		unsigned short dmg;
		float weapspeed;
	public:
		Weapon(){}

		string getName()const { return name; }
		unsigned short getDmg()const { return dmg; }
		float getWeaponSpeed()const { return weapspeed; }
		void setName(const string& n) { this->name = n; }
		void setDmg(const unsigned short& n) { this->dmg = n; }
		void setSpeed(const float& n) { this->weapspeed = n; }
	};

	class Warrior :public Human
	{
		string name;
		unsigned short basicdmg;
		float noweapspeed;
	public:

	};
	class Hunter :public Human
	{
		string name;
		unsigned short basicdmg;
		float noweapspeed;
	public:

	};

	class Weap_2H :public Weapon
	{
		string name;
		unsigned short dmg;
		float weapspeed;
	public:

	};
	class Weap_Bow :public Weapon
	{
		string name;
		unsigned short dmg;
		float weapspeed;
	public:

	};

public:
	Game() {}
	Game(const string& n) { name = n; };
};



int main()
{
	
}