#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

static bool KEEP_GOING = true;
static bool LOG = false;

class Human
{
	string name;
	unsigned short basicdmg;
	unsigned short dmg;
	unsigned short armor;
	float health;
	float healthMAX;
	float noweapspeed;
	float attcspeed;
public:
	Human() {}

	string getName()const { return name; }
	unsigned short getBasicDmg()const { return basicdmg; }
	unsigned short getDmg()const { return dmg; }
	unsigned short getArmor()const { return armor; }
	float getHP()const { return health; }
	float getHP_Max()const { return healthMAX; }
	float getNo_WeaponSpeed()const { return noweapspeed; }
	float getAttcSpeed()const { return attcspeed; }
	void setName(const string& n) { this->name = n; }
	void setBasicDmg(const unsigned short& n) { this->basicdmg = n; }
	void setDmg(const unsigned short& n) { this->dmg = n; }
	void setHP(const float& n) { this->health = n; }
	void setHPMAX(const float& n) { this->healthMAX = n; }
	void setArmor(const unsigned short& n) { this->armor = n; }
	void setNoWeap_Speed(const float& n) { this->noweapspeed = n; }
	void setAttcSpeed(const float& n) { this->attcspeed = n; }
	void Strike(Human &A, Human &B,string &str)
	{
		while (KEEP_GOING == true)
		{
			cout << A.getName() << " did " << A.getDmg() << " dmg\n";
			if (LOG == true)
			{
				str += A.getName();
				str += " did ";
				str += A.getDmg();
				str += " dmg\n";
			}
			B.setHP(B.getHP() - A.getDmg());
			cout << B.getName() << " HP left: ";
			if (LOG == true)
			{
				str += B.getName();
				str += " HP left: ";
			}
			if (B.getHP() > 0)
			{
				cout << B.getHP() << "\n\n";
				this_thread::sleep_for(chrono::milliseconds((int)A.getAttcSpeed() * 1000));
				if (LOG == true)
				{
					str += B.getHP();
					str += "\n\n";
				}
			}
			else
			{			
				cout << "0\n"<<A.getName()<<" won.\n\n";
				B.setHP(0);
				if (LOG == true)
				{
					str += "0\n";
					str += A.getName();
					str += " won.\n\n";
				}
				KEEP_GOING = false;
			}			
		}
	}

};
class Weapon
{
	string name;
	unsigned short dmg;
	float weapspeed;
public:
	Weapon() {}

	string getName_Weapon()const { return name; }
	unsigned short getDmg_Weapon()const { return dmg; }
	float getWeaponSpeed()const { return weapspeed; }
	void setName_Weapon(const string& n) { this->name = n; }
	void setDmg_Weapon(const unsigned short& n) { this->dmg = n; }
	void setSpeed_Weapon(const float& n) { this->weapspeed = n; }
};

class Hunter:virtual public Human 
{
public:
	void Te()
	{
		cout << "some msg\n";
	}
};

class Game
{
	string name;
	string LOG_game;
public:
	void LogtoFile(const string& str)
	{
		string path = "LogFight.txt";
		ofstream logtofile(path, ios::app);
		logtofile << str;
	}
	template<class T1, class T2>
	void Fight(T1 &W1, T2 &H1)
	{
		thread t1(&Human::Strike, H1, std::ref(W1), std::ref(H1), std::ref(LOG_game));
		this_thread::sleep_for(chrono::milliseconds(5));
		thread t2(&Human::Strike, W1, std::ref(H1), std::ref(W1), std::ref(LOG_game));
		t1.join();
		t2.join();
		if(LOG==true)
		LogtoFile(LOG_game);
	}
	
};


int main()
{
	Human H1;
	Hunter W1;
	Weapon B1;
	B1.setDmg_Weapon(50);
	B1.setSpeed_Weapon(1.8);
	Weapon B2;
	B2.setDmg_Weapon(100);
	B2.setSpeed_Weapon(3.5);

	H1.setName("Yur");
	H1.setArmor(20000);
	H1.setHP(550);
	H1.setDmg(B1.getDmg_Weapon());
	H1.setNoWeap_Speed(1.2);
	H1.setAttcSpeed(B1.getWeaponSpeed());

	W1.setName("DAn");
	W1.setArmor(10000);
	W1.setHP(350);
	W1.setDmg(B2.getDmg_Weapon());
	W1.setAttcSpeed(B2.getWeaponSpeed());

	cout << "Geared " << H1.getName() << " has:\n";
	cout << "Dmg: " << B1.getDmg_Weapon() << endl;
	cout << "Attack speed: " << B1.getWeaponSpeed() << endl;
	cout << "HP: " << H1.getHP() << endl << "Armor: " << H1.getArmor() << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	cout << "Geared " << W1.getName() << " has:\n";
	cout << "Dmg: " << W1.getDmg() << endl;
	cout << "Attack speed: " << B2.getWeaponSpeed() << endl;
	cout << "HP: " << W1.getHP() << endl << "Armor: " << W1.getArmor() << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
	Game Alo;
	Alo.Fight(W1, H1);
	
	cout << W1.getHP() << ' ' << W1.getName() << '\n';
	cout << H1.getHP() << ' ' << H1.getName() << '\n';
}