#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <mutex>

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
	void Strike(const Human& A, Human& B, string& str)
	{
		mutex s;
		while (KEEP_GOING == true)
		{
			float n = (A.getDmg() - (A.getDmg() / 100) * (B.getArmor() / 1000));
			s.lock();
			cout << A.getName() << " did " << n << " dmg\n";
			s.unlock();
			if (LOG == true)
			{
				str += A.getName();
				str += " did ";
				str += to_string(n);
				str += " dmg\n";
			}
			B.setHP(B.getHP() - n);
			s.lock();
			cout << B.getName() << " HP left: ";
			s.unlock();
			if (LOG == true)
			{
				str += B.getName();
				str += " HP left: ";
			}
			if (B.getHP() > 0)
			{
				s.lock();
				cout << B.getHP() << "\n\n";
				s.unlock();
				if (LOG == true)
				{
					str += to_string(B.getHP());
					str += "\n\n";
				}
				this_thread::sleep_for(chrono::milliseconds((int)A.getAttcSpeed() * 1000));
			}
			else
			{
				KEEP_GOING = false;
				s.lock();
				cout << "0\n\n" << A.getName() << " won.\n\n";
				s.unlock();
				B.setHP(0);
				if (LOG == true)
				{
					str += "0\n";
					str += A.getName();
					str += " won.\n\n";
				}				
				break;
			}
		}
	}
	void CreateCharacter()
	{
		cout << "Enter character name: ";
		cin >> name;
		string str = "a";
		while (Proverka(str) == 0 || stof(str) < 1 || stof(str) > 20000)
		{
			cout << "Health(1-20000): ";
			cin >> str;
			if (Proverka(str) == 0 || stof(str) < 1 || stof(str) > 20000)
				cout << "Wrong numner.\n";
		}
		setHPMAX(stof(str));
		cout << "Wanna change default(" << armor << ") armor value ?\n";
		char vv;
		cout << "1. Yes.\n2. No.\n";
		vv=_getch();
		if (vv == '1')
		{
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

class Hunter :virtual public Human
{
public:
	Hunter()
	{
		setBasicDmg(50);
		setNoWeap_Speed(1.1);
		setArmor(20000);
	}
	void AimedShot(Human& A, Human& B, string& str) //1.Hunter used aimshot 2.victim
	{
		mutex s;
		while (KEEP_GOING == true)
		{
			float tmpdmg = A.getDmg();
			A.setDmg(tmpdmg + ((tmpdmg / 100) * 50));
			float n = (A.getDmg() - (A.getDmg() / 100) * (B.getArmor() / 1000));
			s.lock();
			cout << A.getName();
			cout << " used AimedShot(" << n << "dmg).\n";
			s.unlock();
			B.setHP(B.getHP() - n);
			if (LOG == true)
			{
				str += A.getName();
				str += " used AimedShot(";
				str += to_string(n);
				str += "dmg).\n";
				str += B.getName();
				str += " HP left: ";
			}
			s.lock();
			cout << B.getName() << " HP left: ";
			s.unlock();
			if (B.getHP() > 0)
			{
				A.setDmg(tmpdmg);
				cout << B.getHP();
				if (LOG == true)
					str += to_string(B.getHP());
				this_thread::sleep_for(chrono::milliseconds(int(rand() % 3000 + 5000)));
			}
			else
			{
				if (KEEP_GOING == true)
				{
					KEEP_GOING = false;
					s.lock();
					cout << "0\n\n" << A.getName() << " won.\n\n";
					s.unlock();
					if (LOG == true)
					{
						str += "0\n";
						str += A.getName();
						str += " won.\n\n";
					}
				}
				else
				break;
			}
		}
	}
};
class Warrior :virtual public Human
{
public:
	Warrior()
	{
		setBasicDmg(70);
		setNoWeap_Speed(1.5);
		setArmor(40000);
	}
	void Disarm(Human& A, const Human& B, string& str) //1.victim 2.Warrior(who used Disarm)
	{
		mutex l;
		while (KEEP_GOING == true)
		{
			float tmpdmg = A.getDmg();
			float tmpspeed = A.getAttcSpeed();
			A.setDmg(A.getBasicDmg());
			A.setAttcSpeed(A.getNo_WeaponSpeed());
			l.lock();
			cout << B.getName();
			cout << " used Disarm for 4 seconds.\n";
			l.unlock();
			if (LOG == true)
			{
				str += B.getName();
				str += " used Disarm for 4 seconds.\n";
			}
			if (B.getHP() > 0 && A.getHP() > 0)
			{
				this_thread::sleep_for(chrono::milliseconds(4000));
				A.setDmg(tmpdmg);
				A.setAttcSpeed(tmpspeed);
				l.lock();
				cout << "Disarm ended.\n";
				l.unlock();
				if (LOG == true)
					str += "Disarm ended.\n";
			}
			if(B.getHP() > 0 && A.getHP() > 0)
			{
				this_thread::sleep_for(chrono::milliseconds(int(rand()%4000+7000)));
			}
		}
	}
};
class Mage :virtual public Human
{
public:
	Mage()
	{
		setBasicDmg(10);
		setNoWeap_Speed(1.5);
		setArmor(10000);
	}
	void Fireball(Human& A, Human& B, string& str)
	{
		while (KEEP_GOING == true)
		{
			mutex m;
			m.lock();
			cout << A.getName() << " is casting Fireball...\n\n";
			m.unlock();
			this_thread::sleep_for(chrono::milliseconds(int(A.getAttcSpeed() * 1000)));			
			if (B.getHP() > 0 && A.getHP() > 0)
			{
				m.lock();
				cout << A.getName();
				cout << " used Fireball(" << A.getDmg() << "dmg).\n";
				m.unlock();
				B.setHP(B.getHP() - A.getDmg());
				if (LOG == true)
				{
					str += A.getName();
					str += " is casting Fireball...\n\n";
					str += A.getName();
					str += " used Firebal(";
					str += to_string(A.getDmg());
					str += "dmg).\n";
				}
				if (LOG == true)
				{
					str += B.getName();
					str += " HP left: ";
				}
				m.lock();
				cout << B.getName() << " HP left: ";
				m.unlock();
			}
			
			if (B.getHP() > 0 && A.getHP() > 0)
			{
				m.lock();
				cout << B.getHP() << endl;
				m.unlock();
				if (LOG == true)
				{
					str += to_string(B.getHP());
					str += '\n';
				}
				this_thread::sleep_for(chrono::milliseconds(int(rand() % 1000 + 3000)));
			}
			if (B.getHP() <= 0)
			{
				if (KEEP_GOING == true)
				{
					KEEP_GOING = false;
					m.lock();
					cout << "0\n\n" << A.getName() << " won.\n\n";
					m.unlock();
					if (LOG == true)
					{
						str += "0\n";
						str += A.getName();
						str += " won.\n\n";
					}
				}
				else
					break;
			}
		}
	}
	void Fireblast(Human& A, Human& B, string& str)
	{
		while (KEEP_GOING == true)
		{
			float flk = A.getDmg() - (A.getDmg() * 0.2);
			mutex m;			
			if (B.getHP() > 0 && A.getHP() > 0)
			{
				m.lock();
				cout << A.getName();
				cout << " used Fireblast(" << flk << "dmg).\n";
				m.unlock();
				B.setHP(B.getHP() - flk);
				if (LOG == true)
				{
					str += A.getName();
					str += " is casting Fireblast...\n\n";
					str += A.getName();
					str += " used Firebal(";
					str += to_string(flk);
					str += "dmg).\n";
				}
				if (LOG == true)
				{
					str += B.getName();
					str += " HP left: ";
				}
				m.lock();
				cout << B.getName() << " HP left: ";
				m.unlock();
			}

			if (B.getHP() > 0 && A.getHP() > 0)
			{
				m.lock();
				cout << B.getHP() << endl;
				m.unlock();
				if (LOG == true)
				{
					str += to_string(B.getHP());
					str += '\n';
				}
				this_thread::sleep_for(chrono::milliseconds(int(rand()%3000+6000)));
			}
			if (B.getHP() <= 0)
			{
				if (KEEP_GOING == true)
				{
					KEEP_GOING = false;
					m.lock();
					cout << "0\n\n" << A.getName() << " won.\n\n";
					m.unlock();
					if (LOG == true)
					{
						str += "0\n";
						str += A.getName();
						str += " won.\n\n";
					}
				}
				else
				break;
			}
		}
	}
};

class Game
{
	string name;
	string LOG_game;
	vector<Weapon>HunterWeapon;
	vector<Weapon>WarriorWeapon;
	vector<Weapon>MageWeapon;
public:
	Game()
	{
		DataHunterWeapon();
		DataWarriorWeapon();
		DataMageWeapon();
	};
	Game(const string& n)
	{
		this->name = n;
		DataHunterWeapon();
		DataWarriorWeapon();
		DataMageWeapon();
	}
	string getName()const { return name; }
	void setName(const string& n) { this->name = n; }
	void LogtoFile(const string& str)
	{
		string path = "LogFight.txt";
		ofstream logtofile(path, ios::app);
		if (logtofile.is_open())
		{
			logtofile << str;
			logtofile.close();
		}
		else
			cout << "File isnt open.\n";
	}
	template<class T1, class T2>
	void Fight(T1& W1, T2& H1)
	{
		KEEP_GOING = true;
		for (int i = 3; i > 0; i--)
		{
			cout << "Starting fight in " << i << "...\n";
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		cout << "\tFIGHT!\n~~~~~~~~~~~~~~~~\n\n";
		Warrior Ktmp;
		Hunter Htmp;
		Mage Mtmp;
		if (typeid(T1).name() == typeid(Warrior).name())
		{
			thread t1(&Human::Strike, W1, ref(W1), ref(H1), ref(LOG_game));					
			if (typeid(T2).name() == typeid(Warrior).name())
			{
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t3(&Warrior::Disarm, Ktmp, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t2(&Human::Strike, H1, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t5(&Warrior::Disarm, Ktmp, ref(W1), ref(H1), ref(LOG_game));
				t1.join();
				t2.join();
				t3.join();
				t5.join();
			}
			if (typeid(T2).name() == typeid(Hunter).name())
			{
				thread t3(&Warrior::Disarm, Ktmp, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t4(&Human::Strike, H1, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t6(&Hunter::AimedShot, Htmp, ref(H1), ref(W1), ref(LOG_game));
				t1.join();
				t3.join();
				t4.join();
				t6.join();
			}
			if (typeid(T2).name() == typeid(Mage).name())
			{
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t6(&Mage::Fireball, Mtmp, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t9(&Mage::Fireblast, Mtmp, ref(H1), ref(W1), ref(LOG_game));
				t1.join();
				t6.join();
				t9.join();
			}
		}
		if (typeid(T1).name() == typeid(Hunter).name())
		{
			thread t1(&Human::Strike, W1, ref(W1), ref(H1), ref(LOG_game));
			this_thread::sleep_for(chrono::milliseconds(10));
			thread t4(&Hunter::AimedShot, Htmp, ref(W1), ref(H1), ref(LOG_game));
			if (typeid(T2).name() == typeid(Warrior).name())
			{
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t2(&Human::Strike, H1, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t7(&Warrior::Disarm, Ktmp, ref(W1), ref(H1), ref(LOG_game));
				t1.join();
				t2.join();
				t4.join();
				t7.join();
			}
			if (typeid(T2).name() == typeid(Hunter).name())
			{
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t2(&Human::Strike, H1, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t8(&Hunter::AimedShot, Htmp, ref(H1), ref(W1), ref(LOG_game));
				t1.join();
				t2.join();
				t4.join();
				t8.join();
			}
			if (typeid(T2).name() == typeid(Mage).name())
			{
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t6(&Mage::Fireball, Mtmp, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(10));
				thread t9(&Mage::Fireblast, Mtmp, ref(H1), ref(W1), ref(LOG_game));
				t9.join();
				t1.join();
				t4.join();
				t6.join();
			}
		}
		if (typeid(T1).name() == typeid(Mage).name())
		{
			thread t1(&Mage::Fireball, Mtmp, ref(W1), ref(H1), ref(LOG_game));
			this_thread::sleep_for(chrono::milliseconds(15));
			thread t9(&Mage::Fireblast, Mtmp, ref(W1), ref(H1), ref(LOG_game));
			if (typeid(T2).name() == typeid(Warrior).name())
			{
				this_thread::sleep_for(chrono::milliseconds(15));
				thread t2(&Human::Strike, H1, ref(H1), ref(W1), ref(LOG_game));
				t9.join();
				t1.join();
				t2.join();
			}
			if (typeid(T2).name() == typeid(Hunter).name())
			{
				this_thread::sleep_for(chrono::milliseconds(15));
				thread t2(&Human::Strike, H1, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(15));
				thread t8(&Hunter::AimedShot, Htmp, ref(H1), ref(W1), ref(LOG_game));
				t9.join();
				t1.join();
				t2.join();
				t8.join();
			}
			if (typeid(T2).name() == typeid(Mage).name())
			{
				this_thread::sleep_for(chrono::milliseconds(15));
				thread t6(&Mage::Fireball, Mtmp, ref(H1), ref(W1), ref(LOG_game));
				this_thread::sleep_for(chrono::milliseconds(15));
				thread t0(&Mage::Fireblast, Mtmp, ref(H1), ref(W1), ref(LOG_game));
				t0.join();
				t9.join();
				t1.join();
				t6.join();
			}
		}
		if (LOG == true)
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
	void DataMageWeapon()
	{
		Weapon Staff_1("Crystalheart Pulse-Staff");
		Weapon Staff_2("Apostle of Argus");
		Weapon Staff_3("Golden Staff of the Sin'dorei");
		Staff_1.setDmg_Weapon(466);
		Staff_1.setSpeed_Weapon(3);
		Staff_2.setDmg_Weapon(399);
		Staff_2.setSpeed_Weapon(2.5);
		Staff_3.setDmg_Weapon(525.5);
		Staff_3.setSpeed_Weapon(3.5);
		MageWeapon.push_back(Staff_1);
		MageWeapon.push_back(Staff_2);
		MageWeapon.push_back(Staff_3);
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
	void PrintDataMageWeapon()const
	{
		for (int i = 0; i < MageWeapon.size(); i++)
		{
			cout << i + 1 << ": " << MageWeapon[i] << endl;
		}
	}
	template<class T>
	void CreateCharacterWithEnemy(T& W1, const vector<Weapon>& tmpWeapon)
	{
		string str = "a";
		while (Proverka(str) == 0 || stof(str) < 1 || stof(str) > tmpWeapon.size())
		{
			cout << "Enter id: ";
			cin >> str;
			if (Proverka(str) == 0 || stof(str) < 1 || stof(str) > tmpWeapon.size())
				cout << "Wrong numner.\n";
		}
		float W1weapon = stof(str) - 1;
		W1.setDmg(tmpWeapon[W1weapon].getDmg_Weapon());
		W1.setAttcSpeed(tmpWeapon[W1weapon].getWeaponSpeed());
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
					cout << "1. Warrior.\n2. Hunter.\n3. Mage.\n~~~~~~~~~~~~~~~~\n\n";
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
						CreateCharacterWithEnemy(W1, WarriorWeapon);
						system("cls");
						cout << "Who will fight against " << W1.getName() << endl;
						cout << "1. Warrior.\n2. Hunter.\n3. Mage\n~~~~~~~~~~~~~~~~\n\n";
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
							CreateCharacterWithEnemy(W2, WarriorWeapon);
							system("cls");
							cout << W1 << endl;
							cout << "\tVS\n";
							cout << W2 << "\n~~~~~~~~~~~~~~~~\n\n";
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
							CreateCharacterWithEnemy(H2, HunterWeapon);
							system("cls");
							cout << W1 << endl;
							cout << "\tVS\n";
							cout << H2 << "\n~~~~~~~~~~~~~~~~\n\n";
							Fight(W1, H2);
							break;
						}
						case'3':
						{
							Mage M2;
							M2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataMageWeapon();
							CreateCharacterWithEnemy(M2, MageWeapon);
							system("cls");
							cout << W1 << endl;
							cout << "\tVS\n";
							cout << M2 << "\n~~~~~~~~~~~~~~~~\n\n";
							Fight(W1, M2);
							break;
						}
						default:
							break;
						}
						system("pause");
						vvod2 = 27;
						break;
					}
					case'2':
					{
						Hunter H1;
						H1.CreateCharacter();
						system("cls");
						cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
						PrintDataHunterWeapon();
						CreateCharacterWithEnemy(H1, HunterWeapon);
						system("cls");
						cout << "Who will fight against " << H1.getName() << endl;
						cout << "1. Warrior.\n2. Hunter.\n3. Mage\n~~~~~~~~~~~~~~~~\n\n";
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
							CreateCharacterWithEnemy(W2, WarriorWeapon);
							system("cls");
							cout << H1 << endl;
							cout << "\tVS\n";
							cout << W2 << "\n~~~~~~~~~~~~~~~~\n\n";
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
							CreateCharacterWithEnemy(H2, HunterWeapon);
							system("cls");
							cout << H1 << endl;
							cout << "\tVS\n";
							cout << H2 << "\n~~~~~~~~~~~~~~~~\n\n";
							Fight(H1, H2);
							break;
						}
						case'3':
						{
							Mage M2;
							M2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataMageWeapon();
							CreateCharacterWithEnemy(M2, MageWeapon);
							system("cls");
							cout << H1 << endl;
							cout << "\tVS\n";
							cout << M2 << "\n~~~~~~~~~~~~~~~~\n\n";
							Fight(H1, M2);
							break;
						}
						default:
							break;
						}
						system("pause");
						vvod2 = 27;
						break;
					}
					case'3':
					{
						Mage M1;
						M1.CreateCharacter();
						system("cls");
						cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
						PrintDataMageWeapon();
						CreateCharacterWithEnemy(M1, MageWeapon);
						system("cls");
						cout << "Who will fight against " << M1.getName() << endl;
						cout << "1. Warrior.\n2. Hunter.\n3. Mage\n~~~~~~~~~~~~~~~~\n\n";
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
							CreateCharacterWithEnemy(W2, WarriorWeapon);
							system("cls");
							cout << M1 << endl;
							cout << "\tVS\n";
							cout << W2 << "\n~~~~~~~~~~~~~~~~\n\n";
							Fight(M1, W2);
							break;
						}
						case'2':
						{
							Hunter H2;
							H2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataHunterWeapon();
							CreateCharacterWithEnemy(H2, HunterWeapon);
							system("cls");
							cout << M1 << endl;
							cout << "\tVS\n";
							cout << H2 << "\n~~~~~~~~~~~~~~~~\n\n";
							Fight(M1, H2);
							break;
						}
						case'3':
						{
							Mage M2;
							M2.CreateCharacter();
							system("cls");
							cout << "Choose ur weapon.\n~~~~~~~~~~~~~~~~\n\n";
							PrintDataMageWeapon();
							CreateCharacterWithEnemy(M2, MageWeapon);
							system("cls");
							cout << M1 << endl;
							cout << "\tVS\n";
							cout << M2 << "\n~~~~~~~~~~~~~~~~\n\n";
							Fight(M1, M2);
							break;
						}
						default:
							break;
						}
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

	~Game()
	{
		HunterWeapon.clear();
		WarriorWeapon.clear();
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
	srand(time(0));
	Game G("Heroes of ITStep");
	G.Menu();
}