#ifndef OJ_UNITS
#define OJ_UNITS
#include "ojDefs.h"
#include "ojCards.h"

class Kai: public Unit{
	private:
	
	public:
	Kai(){
		name = "Kai";
		desc= "";
		hyper = Protagonist();
		int realStats[6] = {5, 1, 0, 0, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Marc: public Unit{
	private:
	
	public:
	Marc(){
		name = "Marc";
		desc= "";
		hyper = X16();
		int realStats[6] = {4, 1, 1, -1, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class QP: public Unit{
	private:
	
	public:
	QP(){
		name = "QP";
		desc= "";
		hyper = HyperMode();
		int realStats[6] = {5, 0, 0, 0, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Suguri: public Unit{
	private:
	
	public:
	Suguri(){
		name = "Suguri";
		desc= "";
		hyper = Accelerator();
		int realStats[6] = {4, 1, -1, 2, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Poppo: public Unit{
	private:
	 
	public:
	Poppo(){
		name = "Marie Poppo";
		desc= "";
		hyper = Ubiquitous();
		int realStats[6] = {7, -1, -1, -1, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Tomomo: public Unit{
	private:
	
	public:
	Tomomo(){
		name = "Tomomo (Softened)";
		desc= "Softened: Tomomo is playing with her friends, and has lowered her attributes. Though, Singleplayer Tomomo doesn't even exist here, so this isn't a real passive.";
		hyper = MagicalMassacre();
		int realStats[6] = {4, 2, 0, 0, 6, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Fernet: public Unit{
	private:
	
	public:
	Fernet(){
		name = "Fernet";
		desc= "";
		hyper = AirStrike();
		int realStats[6] = {6, -1, 2, -2, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Peat: public Unit{
	private:
	
	public:
	Peat(){
		name = "Peat";
		desc= "";
		hyper = BlueCrow();
		int realStats[6] = {3, 1, 1, 1, 4, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Yuki: public Unit{
	private:

	public:
	Yuki(){
		name = "Yuki";
		desc= "";
		hyper = Gamble();
		int realStats[6] = {5, 2, -1, -1, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Aru: public Unit{
	private:
	
	public:
	Aru(){
		name = "Aru";
		desc= "";
		hyper = PresentForYou();
		int realStats[6] = {5, -1, -1, 2, 5, 4}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Hime: public Unit{
	private:

	public:
	Hime(){
		name = "Hime";
		desc= "";
		hyper = Chains();
		int realStats[6] = {5, 1, -1, 1, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Sora: public Unit{
	private:

	public:
	Sora(){
		name = "Sora";
		desc = "";
		hyper = Specs();
		int realStats[6] = {4, 1, 0, 1, 5, 3}; //hp, atk, def, evd, rec, handsize
		copy(begin(realStats), end(realStats), begin(stats));
	}
};

class Gull: public EUnit{
	private:
	
	public:
	Gull(){
		name = "Johnathan";
		int realStats[4] = {3, 1, -1, -1};
		copy(begin(realStats), end(realStats), begin(stats));
	 	curHP = 3;
	}
};

class Ball: public EUnit{
	private:
	
	public:
	Ball(){
		name = "Robo Ball";
		int realStats[4] = {3, -1, 1, -1};
		copy(begin(realStats), end(realStats), begin(stats));
		curHP = 3;
	}
};

class Chicken: public EUnit{
	private:
	
	public:
	Chicken(){
		name = "Haruo";
		int realStats[4] = {3, -1, -1, 1};
		copy(begin(realStats), end(realStats), begin(stats));
		curHP = 3;
	}
};

class Manager: public EUnit{
	private:

	public:
	Manager(){
		name = "Store Manager";
	 	int realStats[4] = {8, 3, 2, -1};
		copy(begin(realStats), end(realStats), begin(stats));
	 	curHP = 8;
	}
	bool IsBoss() { return true; }
};

#endif