#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Human
{
	string name;
	unsigned short basicdmg;
	unsigned short dmg;
	unsigned short armor;
	float MAXhealth;
	float health;
	float noweapspeed;
	float attcspeed;
public:
	Human() {}

	string getName()const { return name; }
	unsigned short getBasicDmg()const { return basicdmg; }
	unsigned short getDmg()const { return dmg; }
	unsigned short getArmor()const { return armor; }
	float getHP()const { return health; }
	float getMAXHP()const { return health; }
	float getNo_WeaponSpeed()const { return noweapspeed; }
	float getAttcSpeed()const { return attcspeed; }
	void setName(const string& n) { this->name = n; }
	void setBasicDmg(const unsigned short& n) { this->basicdmg = n; }
	void setDmg(const unsigned short& n) { this->dmg = n; }
	void setHP(const float& n) { this->health = n; }
	void setMAXHP(const float& n) { this->health = n; }
	void setArmor(const unsigned short& n) { this->armor = n; }
	void setNoWeap_Speed(const float& n) { this->noweapspeed = n; }
	void setAttcSpeed(const float& n) { this->attcspeed = n; }
	
	void Strike(Human A, Human B)
	{
		while (B.getHP() > 0&&A.getHP()>0)
		{
			cout << A.getName() << " did " << A.getDmg() << " dmg\n";
			B.setHP(B.getHP() - A.getDmg());
			cout << B.getName() << " HP left: ";
			if (B.getHP() > 0)
			{
				cout << B.getHP() << '\n';
				this_thread::sleep_for(chrono::milliseconds((int)A.getAttcSpeed() * 1000));
			}	
			else
				cout << '0' << endl << endl;
			
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

	string getName()const { return name; }
	unsigned short getDmg()const { return dmg; }
	float getWeaponSpeed()const { return weapspeed; }
	void setName(const string& n) { this->name = n; }
	void setDmg(const unsigned short& n) { this->dmg = n; }
	void setSpeed(const float& n) { this->weapspeed = n; }
};

class Hunter:public Human
{
public:

};

class Game
{
	string name;
public:
	template<class T1, class T2>
	void Fight(T1 &W1, T2 &H1)
	{
		thread t1(&Human::Strike, W1, W1, H1);
		thread t2(&Human::Strike, H1, H1, W1);
		t1.join();
		t2.detach();
	}
};


int main()
{
	Human H1;
	Hunter W1;
	Weapon B1;
	B1.setDmg(50);
	B1.setSpeed(1.8);
	Weapon B2;
	B2.setDmg(100);
	B2.setSpeed(3.5);

	H1.setName("Yur");
	H1.setArmor(20000);
	H1.setMAXHP(550);
	H1.setHP(H1.getMAXHP());
	H1.setDmg(B1.getDmg());
	H1.setNoWeap_Speed(1.2);
	H1.setAttcSpeed(B1.getWeaponSpeed());

	W1.setName("DAn");
	W1.setArmor(10000);
	W1.setHP(350);
	H1.setBasicDmg(20);
	W1.setDmg(100);
	W1.setNoWeap_Speed(1.5);
	W1.setAttcSpeed(B1.getWeaponSpeed());

	cout << "Geared " << H1.getName() << " has:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "Dmg: " << B1.getDmg() << endl;
	cout << "Attack speed: " << B1.getWeaponSpeed() << endl;
	cout << "HP: " << H1.getHP() << endl << "Armor: " << H1.getArmor() << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	cout << "Geared " << W1.getName() << " has:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "Dmg: " << B2.getDmg() << endl;
	cout << "Attack speed: " << B2.getWeaponSpeed() << endl;
	cout << "HP: " << W1.getHP() << endl << "Armor: " << W1.getArmor() << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
	Game Alo;
	Alo.Fight(W1, H1);
	
	cout << W1.getHP()<<' ' << W1.getName() << '\n';
	cout << H1.getHP() << ' ' << H1.getName() << '\n';
	/*while (W1.getHP() > 0 && H1.getHP() > 0)
	{
		if(W1.getHP() > 0 && H1.getHP() > 0)
		W1.Strike(W1, H1);
		if (W1.getHP() > 0 && H1.getHP() > 0)
		H1.Strike(H1, W1);
	}*/

}