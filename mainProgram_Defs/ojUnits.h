#ifndef OJ_UNITS
#define OJ_UNITS
#include "ojDefs.h"
#include "ojCards.h"

class Kai: public Unit{
	private:
	string name = "Kai";
	string desc= "";
	Card hyper = Protagonist();
	int stats[6] = {5, 1, 0, 0, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Marc: public Unit{
	private:
	string name = "Marc";
	string desc= "";
	Card hyper = X16();
	int stats[6] = {4, 1, 1, -1, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class QP: public Unit{
	private:
	string name = "QP";
	string desc= "";
	Card hyper = HyperMode();
	int stats[6] = {5, 0, 0, 0, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Suguri: public Unit{
	private:
	string name = "Suguri";
	string desc= "";
	Card hyper = Accelerator();
	int stats[6] = {4, 1, -1, 2, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Poppo: public Unit{
	private:
	string name = "Marie Poppo";
	string desc= "";
	Card hyper = Ubiquitous();
	int stats[6] = {7, -1, -1, -1, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Tomomo: public Unit{
	private:
	string name = "Tomomo (Softened)";
	string desc= "Softened: Tomomo is playing with her friends, and has lowered her attributes. Though, Singleplayer Tomomo doesn't even exist here, so this isn't a real passive.";
	Card hyper = MagicalMassacre();
	int stats[6] = {4, 2, 0, 0, 6, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Fernet: public Unit{
	private:
	string name = "Fernet";
	string desc= "";
	Card hyper = AirStrike();
	int stats[6] = {6, -1, 2, -2, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Peat: public Unit{
	private:
	string name = "Peat";
	string desc= "";
	Card hyper = BlueCrow();
	int stats[6] = {3, 1, 1, 1, 4, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Yuki: public Unit{
	private:
	string name = "Yuki";
	string desc= "";
	Card hyper = Gamble();
	int stats[6] = {5, 2, -1, -1, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Aru: public Unit{
	private:
	string name = "Aru";
	string desc= "";
	Card hyper = PresentForYou();
	int stats[6] = {5, -1, -1, 2, 5, 4}; //hp, atk, def, evd, rec, handsize
	public:
};

class Hime: public Unit{
	private:
	string name = "Hime";
	string desc= "";
	Card hyper = Chains();
	int stats[6] = {5, 1, -1, 1, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Sora: public Unit{
	private:
	string name = "Sora";
	string desc= "";
	Card hyper = Specs();
	int stats[6] = {4, 1, 0, 1, 5, 3}; //hp, atk, def, evd, rec, handsize
	public:
};

class Gull: public EUnit{
	private:
	string name = "Johnathan";
	string desc= "";
	int stats[4] = {3, 1, -1, -1};
	int curHP = 3;
	public:
};

class Ball: public EUnit{
	private:
	string name = "Robo Ball";
	string desc= "";
	int stats[4] = {3, -1, 1, -1};
	int curHP = 3;
	public:
};

class Chicken: public EUnit{
	private:
	string name = "Haruo";
	string desc= "";
	int stats[4] = {3, -1, -1, 1};
	int curHP = 3;
	public:
};

class Manager: public EUnit{
	private:
	string name = "Store Manager";
	string desc= "";
	int stats[4] = {8, 3, 2, -1};
	int curHP = 8;
	public:
	bool IsBoss() { return true; }
};

#endif