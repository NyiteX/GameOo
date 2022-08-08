#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

static bool KEEP_GOING = true;
static bool LOG = false;
bool Proverka(string A)
{
	bool f = 0;
	for (int i = 0; i < A.size(); i++)
		if (isdigit(A[i]) != 0 || A[i] == '.')
			f = 1;
	if (f == 1)
		return 1;
	else
		return 0;
}

class Human
{
	string name;
	float basicdmg;
	float dmg;
	unsigned short armor;
	float health;
	float healthMAX;
	float noweapspeed;
	float attcspeed;
public:
	Human() {}
	friend ostream& operator << (ostream& os, const Human& w);

	string getName()const { return name; }
	float getBasicDmg()const { return basicdmg; }
	float getDmg()const { return dmg; }
	unsigned short getArmor()const { return armor; }
	float getHP()const { return health; }
	float getHP_Max()const { return healthMAX; }
	float getNo_WeaponSpeed()const { return noweapspeed; }
	float getAttcSpeed()const { return attcspeed; }
	void setName(const string& n) { this->name = n; }
	void setBasicDmg(const unsigned short& n) { this->basicdmg = n; }
	void setDmg(const unsigned short& n) { this->dmg = n; }
	void setHP(const float& n) { this->health = n; }
	void setHPMAX(const float& n) { this->healthMAX = this->health = n; }
	void setArmor(const unsigned short& n) { this->armor = n; }
	void setNoWeap_Speed(const float& n) { this->noweapspeed = n; }
	void setAttcSpeed(const float& n) { this->attcspeed = n; }
	void Strike(Human &A, Human &B,string &str)
	{
		while (KEEP_GOING == true)
		{
			unsigned short n = (A.getDmg() - (A.getDmg() / 100) * (B.getArmor() / 1000));
			cout << A.getName() << " did " << n << " dmg\n";
			if (LOG == true)
			{
				str += A.getName();
				str += " did ";
				str += n;
				str += " dmg\n";
			}
			B.setHP(B.getHP() - n);
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
				cout << "0\n\n"<<A.getName()<<" won.\n\n";
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
	void CreateCharacter()
	{
		cout << "Enter character name: ";
		cin >> name;
		string str = "a";
		while (Proverka(str)==0 || stof(str) < 1 || stof(str) > 20000)
		{
			cout << "Health(1-20000): ";
			cin >> str;
			if (Proverka(str) == 0 || stof(str) < 1 || stof(str) > 20000)
				cout << "Wrong numner.\n";
		}
		setHPMAX(stof(str));
		str = "a";
		while (Proverka(str) == 0 || stof(str) < 0 || stof(str) > 70000)
		{
			cout << "Armor(1-70000): ";
			cin >> str;
			if (stof(str) < 1 || stof(str) > 70000)
				cout << "Wrong numner.\n";
		}
		armor = stof(str);
	}

};
class Weapon
{
	string name;
	float dmg;
	float weapspeed;
public:
	Weapon() {}
	Weapon(const string& n) { this->name = n; }
	friend ostream& operator << (ostream& os, const Weapon& w);

	string getName_Weapon()const { return name; }
	float getDmg_Weapon()const { return dmg; }
	float getWeaponSpeed()const { return weapspeed; }
	void setName_Weapon(const string& n) { this->name = n; }
	void setDmg_Weapon(const unsigned short& n) { this->dmg = n; }
	void setSpeed_Weapon(const float& n) { this->weapspeed = n; }
};

class Hunter:virtual public Human 
{
public:
	Hunter()
	{
		setBasicDmg(10);
		setNoWeap_Speed(1.1);
		setArmor(20000);
	}
};
class Warrior :virtual public Human
{
public:
	Warrior()
	{
		setBasicDmg(20);
		setNoWeap_Speed(1.5);
		setArmor(40000);
	}
};

class Game
{
	string name;
	string LOG_game;
	vector<Weapon>HunterWeapon;
	vector<Weapon>WarriorWeapon;
public:
	Game() 
	{
		DataHunterWeapon();
		DataWarriorWeapon();
	};
	Game(const string& n) 
	{ 
		this->name = n;
		DataHunterWeapon();
		DataWarriorWeapon();
	}
	string getName()const { return name; }
	void setName(const string& n) { this->name = n; }
	void LogtoFile(const string& str)
	{
		string path = "LogFight.txt";
		ofstream logtofile(path, ios::app);
		if (logtofile.is_open())
			logtofile << str;
		else
			cout << "File isnt open.\n";
		logtofile.close();
	}
	template<class T1, class T2>
	void Fight(T1 &W1, T2 &H1)
	{
		for (int i = 3; i > 0; i--)
		{
			cout << "Starting fight in "<<i<<"...\n";
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		cout << endl;
		thread t1(&Human::Strike, H1, std::ref(W1), std::ref(H1), std::ref(LOG_game));
		this_thread::sleep_for(chrono::milliseconds(5));
		thread t2(&Human::Strike, W1, std::ref(H1), std::ref(W1), std::ref(LOG_game));
		t1.join();
		t2.join();
		if(LOG==true)
		LogtoFile(LOG_game);
	}
	void DataHunterWeapon()
	{		
		Weapon Bow_1("Wrathtide Longbow");
		Weapon Bow_2("Sunfury Bow of the Phoenix");
		Weapon Bow_3("Hurricane");
		Bow_1.setDmg_Weapon(226);
		Bow_1.setSpeed_Weapon(3.00);
		Bow_2.setDmg_Weapon(241.5);
		Bow_2.setSpeed_Weapon(2.90);
		Bow_3.setDmg_Weapon(157.5);
		Bow_3.setSpeed_Weapon(1.60);
		HunterWeapon.push_back(Bow_1);
		HunterWeapon.push_back(Bow_2);
		HunterWeapon.push_back(Bow_3);
	}
	void DataWarriorWeapon()
	{
		Weapon TwoHandedAxe_1("Soul Cleaver");
		Weapon TwoHandedSword_1("Lionheart Blade");
		Weapon TwoHandedSword_2("Apolyon, the Soul-Render");
		TwoHandedAxe_1.setDmg_Weapon(482);
		TwoHandedAxe_1.setSpeed_Weapon(3.7);
		TwoHandedSword_1.setDmg_Weapon(394);
		TwoHandedSword_1.setSpeed_Weapon(3.6);
		TwoHandedSword_2.setDmg_Weapon(505.5);
		TwoHandedSword_2.setSpeed_Weapon(3.4);
		WarriorWeapon.push_back(TwoHandedAxe_1);
		WarriorWeapon.push_back(TwoHandedSword_1);
		WarriorWeapon.push_back(TwoHandedSword_2);
	}
	void PrintDataHunterWeapon()const
	{
		for (int i = 0; i < HunterWeapon.size(); i++)
		{
			cout << i + 1 << ": " << HunterWeapon[i] << endl;

		}
	}
	void PrintDataWarriorWeapon()const
	{
		for (int i = 0; i < WarriorWeapon.size(); i++)
		{
			cout << i + 1 << ": " << WarriorWeapon[i] << endl;
		}
	}
	template<class T>
	void CreateCharacterWithEnemy(T&W1)
	{
		string str = "a";
		while (Proverka(str) == 0 || stof(str) < 1 || stof(str) > WarriorWeapon.size())
		{
			cout << "Enter id: ";
			cin >> str;
			if (Proverka(str) == 0 || stof(str) < 1 || stof(str) > WarriorWeapon.size())
				cout << "Wrong numner.\n";
		}
		float W1weapon = stof(str) - 1;
		W1.setDmg(WarriorWeapon[W1weapon].getDmg_Weapon());
		W1.setAttcSpeed(WarriorWeapon[W1weapon].getWeaponSpeed());
	}
	void Menu()
	{
		char vvod;

		do
		{
			system("cls");
			cout << "\t~~~~~~~~~~~~ " << getName() << " ~~~~~~~~~~~~\t\n";
			cout << "1. Start.\n2. Settings.\n~~~~~~~~~~~~~~~~\n\n";
			vvod = _getch();
			switch (vvod)
			{
			case'1':
			{
				char vvod2;
				do
				{
					system("cls");
					cout << "\t~~~~~~~~~~~~ " << getName() << " ~~~~~~~~~~~~\t\n";
					cout << "Choose ur class.\n";
					cout << "1. Warrior.\n2. Hunter.\n~~~~~~~~~~~~~~~~\n\n";
					vvod2 = _getch();
					switch (vvod2)
					{
					case'1':
					{
						Warrior W1;
						W1.CreateCharacter();
						system("cls");
						cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
						PrintDataWarriorWeapon();
						CreateCharacterWithEnemy(W1);					
						system("cls");						
						cout << "Who will fight against " << W1.getName() << endl;
						cout << "1. Warrior.\n2. Hunter.\n~~~~~~~~~~~~~~~~\n\n";
						char vvod3 = _getch();
						switch (vvod3)
						{
						case'1':
						{
							Warrior W2;
							W2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataWarriorWeapon();
							CreateCharacterWithEnemy(W2);
							system("cls");
							cout << W1 << endl;
							cout << "\tVS\n";
							cout << W2 << endl;
							Fight(W1, W2);
							break;
						}
						case'2':
						{
							Hunter H2;
							H2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataHunterWeapon();
							CreateCharacterWithEnemy(H2);
							system("cls");
							cout << W1 << endl;
							cout << "\tVS\n";
							cout << H2 << endl;
							Fight(W1, H2);
							break;
						}
						default:
							break;
						}
						system("pause");
						break;
					}
					case'2':
					{
						Hunter H1;
						H1.CreateCharacter();
						system("cls");
						cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
						PrintDataHunterWeapon();
						CreateCharacterWithEnemy(H1);
						system("cls");
						cout << "Who will fight against " << H1.getName() << endl;
						cout << "1. Warrior.\n2. Hunter.\n~~~~~~~~~~~~~~~~\n\n";
						char vvod3 = _getch();
						switch (vvod3)
						{
						case'1':
						{
							Warrior W2;
							W2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataWarriorWeapon();
							CreateCharacterWithEnemy(W2);
							system("cls");
							cout << H1 << endl;
							cout << "\tVS\n";
							cout << W2 << endl;
							Fight(H1, W2);
							break;
						}
						case'2':
						{
							Hunter H2;
							H2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataHunterWeapon();
							CreateCharacterWithEnemy(H2);
							system("cls");
							cout << H1 << endl;
							cout << "\tVS\n";
							cout << H2 << endl;
							Fight(H1, H2);
							break;
						}
						default:
							break;
						}
						system("pause");
						break;
					}
					default:
						break;
					}
				} while (vvod2 != 27);
				break;
			}
			case'2':
			{
				char vvod2;
				do
				{
					system("cls");
					cout << "\t~~~~~~~~~~~~ " << getName() << " ~~~~~~~~~~~~\t\n";
					cout << "Log to file.";
					if (LOG == true)
						cout << "(is active.)\n";
					else
						cout << "(isn't active.)\n";
					cout << "1. ON.\n2. OFF.\n~~~~~~~~~~~~~~~~\n\n";
					vvod2 = _getch();
					switch (vvod2)
					{
					case'1':
					{
						LOG = true;
						cout << "Log is enabled.\n";
						system("pause");
						vvod2 = 27;
						break;
					}
					case'2':
					{
						LOG = false;
						cout << "Log is disabled.\n";
						system("pause");
						vvod2 = 27;
						break;
					}
					default:
						break;
					}
				} while (vvod2 != 27);
				break;
			}
			default:
				break;
			}
		} while (vvod != 27);
	}
};

ostream& operator << (ostream& os, const Weapon& w)
{
	os << w.name << "\nDmg: " << w.dmg;
	os << "\nSpeed: " << w.weapspeed << endl;
	return os;
}
ostream& operator << (ostream& os, const Human& w)
{
	os << w.name << "\nDmg: " << w.dmg;
	os << "\nSpeed: " << w.attcspeed;
	os << "\nArmor: " << w.armor;
	os << "\nHealth: " << w.health << endl;
	return os;
}

int main()
{
	Game G("Heroes of ITStep");
	G.Menu();
}