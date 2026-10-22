#ifndef OJ
#define OJ
#include <string>
#include <vector>
#include <stack>
#include <array>

//scary macros to define effect trigger conditions
#define TRIGGER_ROLL 0
#define TRIGGER_ADDCARD 1
#define TRIGGER_ADDSTARS 2
#define TRIGGER_ADDWINS 3
#define TRIGGER_PLAYCARD 4
#define TRIGGER_DISCARD 5
#define TRIGGER_HEAL 6
#define TRIGGER_HURT 7
#define TRIGGER_SETHP 8
#define TRIGGER_KO 9
#define TRIGGER_LAND 10
#define TRIGGER_LEVELUP 11
#define TRIGGER_DRAW 12
#define TRIGGER_BATTLESTART 13
#define TRIGGER_BATTLEWIN 14
#define TRIGGER_BATTLEDRAW 15
#define TRIGGER_BATTLELOSE 16
#define TRIGGER_TURNSTART 17
#define TRIGGER_TURNEND 18
#define TRIGGER_MOVEROLL 19
#define TRIGGER_REVIVE 20
#define TRIGGER_WARP 21
#define TRIGGER_BATTLEROUNDSTART 22 //needed for protagonist's privilege. I hate kai

//scary macros to define card types
#define CARD_BLANK 0
#define CARD_TRAP 1
#define CARD_BOOST 2
#define CARD_EVENT 3
#define CARD_BATTLE 4
//i'm not doing gift cards or the new banner cards; both are DLC additions that are out of the scope for this project

#define TILE_HOME 0
#define TILE_BONUS 1
#define TILE_DROP 2
#define TILE_ENEMY 3
#define TILE_WARP 4
#define TILE_WARP_DEADEND 5 //not sure if these exist in base orange juice but including to be sure
#define TILE_MOVE 6
#define TILE_DRAW 7
#define TILE_BLANK 8

#define DICE_NORMAL 0
#define DICE_SPECS 1 //always returns 6

#define UNIT_CONTROLLER_PLAYER 0
#define UNIT_CONTROLLER_RANDOMCHOICE 1
#define UNIT_CONTROLLER_NEURALNET 2 //one day...

#define GOAL_STARS 0
#define GOAL_WINS 1

//scary tile directional macros
#define DIR_N {true, false, false, false}
#define DIR_W {false, true, false, false}
#define DIR_S {false, false, true, false}
#define DIR_E {false, false, false, true}

#define DIR_NW {true, true, false, false}
#define DIR_WS {false, true, true, false}
#define DIR_SE {false, false, true, true}
#define DIR_EN {true, false, false, true}

#define DIR_NWS {true, true, true, false}
#define DIR_WSE {false, true, true, true}
#define DIR_SEN {true, false, true, true}
#define DIR_ENW {true, true, false, true}

#define DIR_NWSE {true, true, true, true}
//god i have so many macros
//too many, one might argure. but such is life

using namespace std;

//this is funny-looking but since i use pointers a lot this is a way to avoid Type <error> nonsense
class Player;
class Card;
class Tile;
class Board;
class Deck;
class Unit;
class EUnit;
class Effect;

struct PlayerChoice {
    vector<string> choiceNames;
    vector<bool> validChoices;
    string chooseMsg;
};

class EUnit //weird class with some stuff from Unit and some stuff from Player
{
private:
    string name;
    int stats[4];
    bool combatActions[3]={true,true,true};
    int stars;
    int curHP;
    int tempStatMods[4]={0,0,0,0};
    bool alive=true;
public:

    EUnit();
    string Name() const { return name; }
    int MaxHP() const { return stats[0] + tempStatMods[0]; }
    int Atk() const { return stats[1] + tempStatMods[1]; }
    int Def() const { return stats[2] + tempStatMods[2]; }
    int Evd() const { return stats[3] + tempStatMods[3]; }
    int CurHP() const { return curHP; }
    void resetHP(){ curHP = MaxHP(); }
    void setCombatRestrictions(array<bool, 3> restrictionsNew);
    bool Alive() { return Alive(); }
    int BattleRoll(bool offense=false, int attackRoll = 0);
    void Hurt(int Damage);
    void AddStatMods(array<int, 4> addStats, bool temp=1);
    void ResetStatMods();
    void WinBattle(Player* opponent);
    void KO() { alive = false; }
    int Stars() const { return Stars(); }

    virtual bool IsBoss() { return false; }
};

struct PlayerChoice; //It's a mystery mousekatool that'll help us later!

class Card
{
private:
    string cardName;
    string cardDesc;
    int cardType;
    int cardID;
    int level;
    int cost;
    string customCostString = "";
    int max=3;
    virtual bool typePlayable(Player* owner){ return false; }

public:
    bool canPlay(Player* owner);
    virtual void playCard(Player* owner) {};
    string Name() { return cardName; }
    string Desc() { return cardDesc; }
    string Level_Display() { return to_string(level); }
    string Cost_Display();
    int Max() const { return max; }
    int CardID() const { return cardID; }
    Card() {};
};

class BlankCard: public Card {
private:
    string cardName = "Hyper";
    string cardDesc = "This is a blank card. It does nothing, and should turn into a Hyper when drawn from the deck. If you see this, no you don't.";
    int cardType = CARD_BLANK;
    int cardID = 0;
    int level = 1;
    int cost = 0;
    bool typePlayable(Player* owner) { return false; }
};

class BattleCard: public Card {
private:
    string cardName = "Battle Card";
    string cardDesc = "This is a template Battle Card. This shouldn't be seen in-game: if you see it, no you don't.";
    int cardType = CARD_BATTLE;
    int cardID = -1;
    int level = 1;
    int cost = 0;
    bool typePlayable(Player* owner);
public:
    virtual void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr) {};
};

class BoostCard: public Card {
private:
    string cardName = "Boost Card";
    string cardDesc = "This is a template Boost Card. This shouldn't be seen in-game: if you see it, no you don't.";
    int cardType = CARD_BOOST;
    int cardID = -1;
    int level = 1;
    int cost = 0;
    bool typePlayable(Player* owner);
};

class TrapCard: public Card {
private:
    string cardName = "Trap Card";
    string cardDesc = "This is a template Trap Card. This shouldn't be seen in-game: if you see it, no you don't.";
    int cardType = CARD_TRAP;
    int cardID = -1;
    int level = 1;
    int cost = 0;
    bool typePlayable(Player* owner);
    Player* setter;
public:
    void playCard(Player* owner);
    virtual void landedOn(Player* poorSoul, Tile* myTile) {};
};

class EventCard: public Card {
private:
    string cardName = "Event Card";
    string cardDesc = "This is a template Event Card. This shouldn't be seen in-game: if you see it, no you don't.";
    int cardType = CARD_EVENT;
    int cardID = -1;
    int level = 1;
    int cost = 0;
    bool typePlayable(Player* owner);
};

class Deck
{
    private:
    vector<Card> fullDeck = {};
    vector<Card> currentDeck = {};

    public:
    Deck();
    Card drawCard();
    void initDeck(vector<Card> cardList);
    void resetDeck(){ currentDeck = fullDeck; };
};

class Tile
{
    private:
    EUnit tileEnemy;
    public: //vars
    int type;
    int xPos;
    int yPos;
    bool doubled;
    bool movesNWSE[4];
    bool trapped=false;
    int homeID;
    TrapCard trap=TrapCard();
    void summonEnemy();
    EUnit* fightTileEnemy(EUnit* boss = nullptr);
    //funcs
    Tile(int typeIn = TILE_BLANK, int xposIn, int yposIn, array<bool, 4> movesIn = {false, false, false, false}, bool doubler = false, int homeIDIn = 0);
    void landOn(Player* lander);
    void trapSet(TrapCard* trapToSet);
    void trapClear();
    void randoWarp(Player* lander);
    int BonusFormula(const int roll, Player* lander);
    int DropFormula(const int roll, Player* lander);
}; //to be consistent with everything else and to be safer, most of this should be read-only with just getters
//but the class would be twice as long just so...what, i don't change a tile's position in a random function by accident?
//i trust myself enough to not do that

class Board
{
    private:
    void SetWarpIndexes();
    void FillWithBlankTiles();
    public:
    bool tileAtExists(int xp, int yp);
    Tile* tileAt(int xp, int yp);
    vector<int> warpDestinationTiles;
    int boardSize[2];
    vector<Tile> tiles;
    bool bossActive=false;
    EUnit boss;
    int bossStars=0;
	int extraStars=0; //this exists only because I don't want to add board events right now and Holy Night would practically require I add board events
	void summonBoss();
    void killBoss();
    int chapter=0; //turncount
    Board();
};

class Effect
{
private:
    int effID=-1;
    string effName="Blank";
    int stocks=-1;
    bool active=0;
public:
    string Name() { return effName; }
    void Deplete() { stocks = stocks - 1; }
    int Stocks() { return stocks; }
    void OverwriteStocks(int newStocks) { stocks = newStocks; }
    virtual void OnApply(Player* effOwner) {};
    virtual void OnLose(Player* effOwner) {};
    virtual void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Card()) {};
};

class Unit
{
private:
    string name;
    string desc;
    int stats[6];
    Card hyper;

public:

    string Name() const { return name; }
    string Desc() const { return desc; }
    int MaxHP() const { return stats[0]; }
    int Atk() const { return stats[1]; }
    int Def() const { return stats[2]; }
    int Evd() const { return stats[3]; }
    int Rec() const { return stats[4]; }
    int HandSize() const { return stats[5]; }
    Card Hyper() const { return hyper; }
};


class Player
{
private:
    Unit character;
    vector<Card> hand;
    vector<Effect> myEffects;
    int controllerType = UNIT_CONTROLLER_RANDOMCHOICE;

    Player* allPlayers[4];
    Deck* mainDeck;
	Board* board;
    Tile* currTile;
    bool wonGame = false;
    int playerID; //ONE THROUGH FOUR ONLY, playerID - 1 is the index of the player with that ID in allPlayers[].
    int curHP;
    int statMods[7];
    int tempStatMods[7]; //while all stats are "temporary", temp stats are discarded after being used. More for conveneince than anything
    int extraDiceNum;
    int tempExtraDiceNum;
	int diceType=0;
	bool startedBattle=0;
    int stars=0;
    int wins=0;
    int norma=1;
    int revRolls;
	bool combatActions[3]={true, true, true}; //Attack, Defend, Evade
    int goalType;
    int goal;
    float starsLostOnKOMult = 0.5;
    float AddStarsMult = 1;
    int winsOnDeath = 2;
    bool alive=true;
    bool inBattle;
    int battleRounds = 2;
    char travelDir; //N, E, S, W, used for board movement
    bool interrupt; //this should be set to 0 at the start of every function that can trigger an effect
    //if the flag is set to 1 after an effect is triggered, these functions should return immediately
    //let's take Kai's "Protagonist Privilege" card, for example:
    //it wants to overwrite the battle function with a unique version of it where only the player who played the card can attack
    //so it sets this flag, and its effect trigger code can be the unique battle function
    //when it returns, the actual battle function sees the interrupt and returns instantly

    int Choose(PlayerChoice choice); //this is "later"

    //what do you mean "what do you mean this is 'later'" this is the payoff for the joke i set up on line 70.
    //this... i guess it's less funy than it was in my head, huh.

public:
    //getters
    int pID() const { return playerID; }

    int MaxHP() const { return character.MaxHP() + statMods[0] + tempStatMods[0]; }
    int Atk() const { return character.Atk() + statMods[1] + tempStatMods[1]; }
    int Def() const { return character.Def() + statMods[2] + tempStatMods[2]; }
    int Evd() const { return character.Evd() + statMods[3] + tempStatMods[3]; }
    int Rec() const { return character.Rec() + statMods[4] + tempStatMods[4]; }
    int HandSize() const { return character.HandSize() + statMods[5] + tempStatMods[5]; }
    int Mov() const { return statMods[6] + tempStatMods[6]; }
    int CurHP() const { return curHP; }
    int DiceNum() const { return 1 + extraDiceNum + tempExtraDiceNum; }
    int Stars() const { return stars; }
    int Wins() const { return wins; }
    int XPos() const { return currTile->xPos; }
    int YPos() const { return currTile->yPos; }
    int Norma() const { return norma; }
    bool Battling() const { return inBattle; }
    bool StartedBattle() const { return startedBattle; }
    bool Alive() const { return alive; }
    Tile* CurrTile() const { return currTile; }
    vector<Card>* Hand() { return &hand; }
    vector<bool> checkPlayableCards();
	Player* GetPlayers(int id) { return allPlayers[id-1]; }
    Board* GetBoard() { return board; }
    int PickCardFromHand();

    //should contain most of the turn logic
    void TakeTurn();
    void ResetKOStars(); //should be called after every battle loss, since cards that adjust this number would do so on TRIGGER_BATTLELOSE
    void ResetAddStarsMult(); //should be called on AddStars
    float KOStarsMult() { return starsLostOnKOMult; }
    int WinsOnDeath() { return winsOnDeath; }
    void resetWinsDeath() { winsOnDeath = 2; }
    void setWinsOnDeath(int inp) { winsOnDeath = inp; }

    //effect checker

    //card helpers
    void SetAddStarsMult(float newMult);
    void AddEffect(Effect effectToAdd);
    void AddStatMods(array<int, 7> addStats, bool temp=1); //i Dont Like that array<> thing it feels gross but i can't call AddStatMods({0, 0, ... 0}) otherwise
    void AddDice(int exDiceNum, bool temp=1);
    void LoseDice(int exDiceNum, bool temp=1);
    Player* choosePlayer(bool alivePlayersOnly=1, bool excludeSelf=1);
	void SetDiceType(int newType);
    void TrapSet(Tile* trapTile, TrapCard myTrap);
    void AdjustKOStars(float newMult);
    void SetRounds(int rounds); //exclusively for battle cards, should only be used at start of battle
    void CombatRestrict(array<bool, 3> restrict, array<bool, 3> unrestrict);
    void skipAction();
    void CheckEffects(int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Card());

    //stuff that should be able to trigger Effects
    int Roll(); //0
    void AddCard(Card newCard); //1
    void AddStars(int starNum); //2
    void LoseStars(int starNum){ AddStars(starNum * -1); }; //not unique, we check for if starNum is negative
    void AddWins(int winNum); //3
    void PlayCard(int toPlay, Player* opp = nullptr, EUnit* npcOpp = nullptr); //4
    void DisCard(int pos); //5
    void Heal(int healAmnt, bool overheal = false); //6
    void Hurt(int dmgAmnt); //7
    void SetHP(int setTo); //8; for "gain/lose HP" effects
    void KO(); //9
    void Land(Tile* landedOn); //10
    void NormaUp(); //11
    void Draw(); //12
    void StartBattle(Player* opponent, bool goFirst = true); //13
    void StartBattle(EUnit* opponent, bool goFirst = true); //13
    void WinBattle(Player* opponent); //14
    void WinBattle(EUnit* opponent); //14
    
    //EXTRA Trigger IDs:
    //Battle End (Draw) //15
    //Battle End (Lose) //16
    //Turn Start //17
    //Turn End //18
    void RollToMove(); //19
    bool NormaCheck();

    void Revive(); //20
    void warpTo(Tile* warpTo); //21
    //Battle Round Start //22
};

#endif