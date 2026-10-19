#ifndef OJ_CARDS
#define OJ_CARDS
#include "ojDefs.h"

class Dash: public BoostCard {
    private:
        string cardName = "Dash!";
        string cardDesc = "For this turn, roll two dice for movement. \"Faster!\" - Suguri";
        int cardID = 1;
        int level = 1;
        int cost = 3;
    public:
        void playCard(Player* owner);
}; // this goes before the effects so effects have a "default card" to use, no effects currently use the card iirc but the default card constructors leave a bunch of stuff undefined

class DashEff: public Effect {
    private:
        string effName="Dash!";
        int effID = 0;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class JingleEff: public Effect {
    private:
        string effName="Nice Jingle";
        int effID = 1;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class FlipEff: public Effect {
    private:
        string effName="Flip Out";
        int effID = 2;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class ExtendEff: public Effect {
    private:
        string effName="Extend";
        int effID = 3;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class ProtagEff: public Effect {
    private:
        string effName="Protagonist's Privilege";
        int effID = 4;
        int roundsThisFight = 0;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class AccelEff: public Effect {
    private:
        string effName="Accelerator";
        int effID = 5;
    public:
        void OnApply(Player* effOwner);
        void OnLose(Player* effOwner);
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class CrystEff: public Effect {
    private:
        string effName="Stiff Crystal";
        int effID = 6;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class SpecsEff: public Effect {
    private:
        string effName="Extraordinary Specs";
        int effID = 7;
    public:
        void OnApply(Player* effOwner);
        void OnLose(Player* effOwner);
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class BoundEff1: public Effect {
    private:
        string effName="Binding Chains";
        int effID = 8;
    public:
        void OnLose(Player* effOwner);
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class BoundEff2: public Effect {
    private:
        string effName="Bound";
        int effID = 9;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class HyperEff: public Effect {
    private:
        string effName="Hyper Mode";
        int effID = 10;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class OutOfAmmoEff: public Effect{
    private:
        string effName="Out Of Ammo";
        int effID = 11;
        int pidstarted = 0;
        int turnstarted = 0;
    public:
        OutOfAmmoEff(int pIDStarted, int turnStarted);
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class LittleWarEff: public Effect{
    private:
        string effName="Little War";
        int stocks = 3;
        int effID = 12;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class DangerousPuddingEff: public Effect{
    private:
        string effName="Dangerous Pudding";
        int effID = 13;
    public:
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class Cookie: public BoostCard {
    private:
        string cardName = "Saki's Cookie";
        string cardDesc = "Heal 1 HP. \"Have a cookie!\" - Saki";
        int cardID = 2;
        int level = 1;
        int cost = 0;
    public:
        void playCard(Player* owner);
};

class Pudding: public BoostCard {
    private:
        string cardName = "Pudding";
        string cardDesc = "Reset your HP to your max HP. \"Hooray!\" - QP";
        int cardID = 3;
        int level = 4;
        int cost = 0;
    public:
        void playCard(Player* owner);
};

class NicePresent: public BoostCard {
    private:
        string cardName = "Nice Present";
        string cardDesc = "Draw 2 cards. \"You're going to help me deliver the presents.\" - Aru";
        int cardID = 4;
        int level = 2;
        int cost = 10;
		int max = 1;
    public:
        void playCard(Player* owner);
};

class Jingle: public BoostCard {
    private:
        string cardName = "Nice Jingle";
        string cardDesc = "The next bonus panel gives you twice as many stars. \"We've got a bunch.\" ―Aru";
        int cardID = 5;
        int level = 1;
        int cost = 3;
		int max = 1;
    public:
        void playCard(Player* owner);
};

class Flip: public BoostCard {
    private:
        string cardName = "Flip Out";
        string cardDesc = "Next time you land on a drop panel, the player(s) with the highest number of stars will lose the same number of stars as you. \n \"......!\" - Mei";
        int cardID = 6;
        int level = 1;
        int cost = 0;
    public:
        void playCard(Player* owner);
};

class Shot: public BoostCard {
    private:
        string cardName = "Long-Distance Shot";
        string cardDesc = "Deals 1 damage to the selected enemy unit. \"I can hit you from anywhere.\" - Iru";
        int cardID = 7;
        int level = 1;
        int cost = 5;
    public:
        void playCard(Player* owner);
};

class Extend: public BoostCard {
    private:
        string cardName = "Extend";
        string cardDesc = "After suffering KO, you will revive on the following turn. \"All good for now!\" - Marc";
        int cardID = 8;
        int level = 3;
        int cost = 10;
		int max = 1;
    public:
        void playCard(Player* owner);
};

class StiffCrystal: public BoostCard {
    private:
        string cardName = "Flip Out";
        string cardDesc = "This card negates the effect of a trap card. Gain 5 stars per level of cancelled trap. \"Such a pain in the neck.\" - Kyoko";
        int cardID = 9;
        int level = 2;
        int cost = 20;
		int max = 1;
    public:
        void playCard(Player* owner);
};

class Princess: public BoostCard {
    private:
        string cardName = "Princess' Privilege";
        string cardDesc = "Discard all cards in your hand and draw 3 cards. Can only be used when holding only Princess's Privilege or you have at least 3 cards in your hand. \n \"You may visit my house someday.\" - Fernet";
        int cardID = 10;
        int level = 4;
        int cost = 20;
		int max = 1;
        bool typePlayable(Player* owner);
    public:
        void playCard(Player* owner);
};

class Protagonist: public BoostCard {
    private:
        string cardName = "Protagonist's Privilege";
        string cardDesc = "(Hyper) Effect duration: 3 chapters. When you are allowed to attack first, the opposing unit cannot attack (once per combat). \n \"This is the privilege of the main character!\" - Kai";
        int cardID = 11;
        int level = 3;
        int cost = 20;
    public:
        void playCard(Player* owner);
};

class Ubiquitous: public BoostCard {
    private:
        string cardName = "Ubiquitous";
        string cardDesc = "(Hyper) Warp to target active enemy's panel. In addition, steal stars equal to 10x their level. \"Poppo! Poppopopopopo!\" - Marie Poppo";
        int cardID = 12;
        int level = 1;
        int cost = 0;
    public:
        void playCard(Player* owner);
};

class Accelerator: public BoostCard {
    private:
        string cardName = "Accelerator";
        string cardDesc = "(Hyper) Effect duration: 1 chapter. Roll 2 dice for all dice rolls this turn. \"I'm accelerating.\" - Suguri";
        int cardID = 13;
        int level = 3;
        int cost = 30;
    public:
        void playCard(Player* owner);
};

class X16: public BoostCard {
    private:
        string cardName = "x16 Big Rocket";
        string cardDesc = "(Hyper) Deal damage equal to your level to target unit. A KO from this effect gives you 2 Wins. \"Charged! Go!\" - Marc";
        int cardID = 14;
        int level = 1;
        int cost = 0;
        string customCostString = "10 * Level";
        bool typePlayable(Player* owner);
    public:
        void playCard(Player* owner);
};

class AirStrike: public EventCard {
    private:
        string cardName = "Air Strike";
        string cardDesc = "(Hyper) All enemies take 1 to 3 damage. Gain 15 stars on every KO. \"Hmph, go down, all of you.\" - Fernet";
        int cardID = 15;
        int level = 2;
        int cost = 30;
    public:
        void playCard(Player* owner);
};

class Gamble: public EventCard {
    private:
        string cardName = "Gamble";
        string cardDesc = "(Hyper) A randomly chosen unit is KO'd. \"Why not use this to decide whose turn it is?\" - Yuki";
        int cardID = 16;
        int level = 3;
        int cost = 15;
    public:
        void playCard(Player* owner);
};

class PresentForYou: public EventCard {
    private:
        string cardName = "Present For You";
        string cardDesc = "(Hyper) All players draw cards until they have a full hand. Those with full hand draw 1 card instead. \n Gain stars equal to 10x the number of all cards drawn. \"Presents for good boys and girls.\" - Aru";
        int cardID = 17;
        int level = 2;
        int cost = 30;
    public:
        void playCard(Player* owner);
};

class Chains: public EventCard {
    private:
        string cardName = "Binding Chains";
        string cardDesc = "(Hyper) All Units except yours will skip their next turn. Apply \"Bound\" to all active enemies. \n Effect Duration: 2 Chapters. Gain -2 EVD and -1 MOV. \"I don't like doing this sort of thing.\" - Hime";
        int cardID = 18;
        int level = 1;
        int cost = 0;
    public:
        void playCard(Player* owner);
};

class Specs: public BoostCard {
    private:
        string cardName = "Extraordinary Specs";
        string cardDesc = "(Hyper) Effect Duration: 1 chapter. Roll 6 for all dice rolls this turn. \"I'd appreciate it if you dropped your weapons.\" - Sora";
        int cardID = 19;
        int level = 3;
        int cost = 30;
    public:
        void playCard(Player* owner);
};

class MagicalMassacre: public EventCard {
    private:
        string cardName = "Magical Massacre";
        string cardDesc = "(Hyper) All units whose HP is full or higher will suffer KO. Gain -1 REC on next Revive roll per unit KO'd (other than yourself). \n \"Disappear.\" - Tomomo";
        int cardID = 20;
        int level = 4;
        int cost = 20;
    public:
        void playCard(Player* owner);
};

class BlueCrow: public BattleCard {
    private:
        string cardName = "Blue Crow the Second";
        string cardDesc = "(Hyper) During this battle, gain ATK and DEF but lose EVD equal to the number of cards in your hand. \"I'm gonna settle this!\" - Peat";
        int cardID = 21;
        int level = 2;
        int cost = 10;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class HyperMode: public BattleCard {
    private:
        string cardName = "Hyper Mode";
        string cardDesc = "(Hyper) Gain +3 ATK during this battle. If your unit suffers KO during this battle, you give no stars or Wins and the unit will revive next turn. \n \"HYPER MODE!\" - QP";
        int cardID = 22;
        int level = 1;
        int cost = 10;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class HereAndThere: public EventCard {
    private:
        string cardName = "Here and There";
        string cardDesc = "All units are moved to randomly chosen panels. \"To the next world!\" - Marie Poppo";
        int cardID = 23;
        int level = 2;
        int cost = 10;
    public:
        void playCard(Player* owner);
};

class OutOfAmmo: public EventCard {
    private:
        string cardName = "Out of Ammo";
        string cardDesc = "Effect duration: 1 chapter. No player may use any cards. \"Ran out of ammo!\" - Peat";
        int cardID = 24;
        int level = 2;
        int cost = 5;
    public:
        void playCard(Player* owner);
};

class GiftExchange: public EventCard {
    private:
        string cardName = "Gift Exchange";
        string cardDesc = "All cards are gathered from the players and dealt back randomly. The total number of each player's cards remains unchanged. \n \"This card is extremely strong for reasons that are difficult to explain.\" - Me";
        int cardID = 25;
        int level = 3;
        int cost = 10;
    public:
        void playCard(Player* owner);
};

class LittleWar: public EventCard {
    private:
        string cardName = "Little War";
        string cardDesc = "Effect Duration: 3 chapters. \n Offense and defense will happen twice in all battles.\"I believe... I have the power to stop this...\" - Suguri";
        int cardID = 26;
        int level = 4;
        int cost = 50;
		int max = 1;
    public:
        void playCard(Player* owner);
};

class HolyNight: public EventCard {
    private:
        string cardName = "Holy Night";
        string cardDesc = "Start-of-chapter bonus stars are increased by one. \"Aha, that's why it's a party night.\" - Hime";
        int cardID = 27;
        int level = 1;
        int cost = 0;
    public:
        void playCard(Player* owner);
};

class AllOutMode: public EventCard {
    private:
        string cardName = "Super All-Out Mode";
        string cardDesc = "Stock Effect: All units gain +2 ATK during their next battle. \"This is gonna hurt even if you know it's coming!!\" - Tomomo";
        int cardID = 28;
        int level = 3;
        int cost = 30;
    public:
        void playCard(Player* owner);
};

class Dinner: public EventCard {
    private:
        string cardName = "Dinner";
        string cardDesc = "Heal all units for 3 HP. \"Let's have supper together.\" - Natsumi";
        int cardID = 29;
        int level = 3;
        int cost = 10;
    public:
        void playCard(Player* owner);
};

class Seagulls: public EventCard {
    private:
        string cardName = "Cloud of Seagulls";
        string cardDesc = "A randomly chosen unit will receive 2 damage. \"Squaawk!\" - Seagull";
        int cardID = 30;
        int level = 1;
        int cost = 0;
    public:
        void playCard(Player* owner);
};

class SealedGuardian: public EventCard {
    private:
        string cardName = "Sealed Guardian";
        string cardDesc = "Every unit's HP becomes 1. \"Meet the guardian angel of this vessel.\" - Shifu";
        int cardID = 31;
        int level = 5;
        int cost = 50;
		int max = 1;
    public:
        void playCard(Player* owner);
};

//class WeAreWaruda: public EventCard { 
//    private:
//        string cardName = "We Are Waruda";
//        string cardDesc = "Move all trap cards onto randomly chosen panels. \"Useless. No one can beat Tomato.\" - Tomato";
//        int cardID = 32;
//        int level = 2;
//        int cost = 5;
//    public:
//        void playCard(Player* owner);
//};
// extremely niche card that would REALLY REALLY SUCK to implement. Not worth it.

class OhMyFriend: public EventCard {
    private:
        string cardName = "Oh My Friend";
        string cardDesc = "A boss will show up. \"Machines have friends too.\" - NoName";
        int cardID = 33;
        int level = 1;
        int cost = 30;
		int max = 1;
    public:
        void playCard(Player* owner);
};

class ForcedRevival: public EventCard {
    private:
        string cardName = "Forced Revival";
        string cardDesc = "All units suffering KO will be revived with 1 HP. \"You'll be up in a jiffy.\" - Kiriko";
        int cardID = 34;
        int level = 3;
        int cost = 30;
    public:
        void playCard(Player* owner);
};

class RainbowColoredCircle: public BattleCard {
    private:
        string cardName = "Rainbow-Colored Circle";
        string cardDesc = "During this battle, gain +2 EVD and -1 DEF. \"Like drawing a rainbow-colored circle.\"";
        int cardID = 35;
        int level = 2;
        int cost = 5;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class Rbits: public BattleCard {
    private:
        string cardName = "Rbits";
        string cardDesc = "During this battle, gain +2 DEF. You may not use the Evade command. \"Formation Orbit!\" - QP";
        int cardID = 36;
        int level = 2;
        int cost = 3;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class ImOnFire: public BattleCard {
    private:
        string cardName = "I'm On Fire!";
        string cardDesc = "During this battle, gain +1 ATK and -1 DEF. \"Let's play our lives away!\" - Kae";
        int cardID = 37;
        int level = 1;
        int cost = 5;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class FinalBattle: public BattleCard {
    private:
        string cardName = "Final Battle";
        string cardDesc = "This battle will last until either unit suffers KO (Maximum of 10 rounds). \"To protect everyone!\" - Suguri & Hime";
        int cardID = 38;
        int level = 4;
        int cost = 30;
		int max = 1;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class ReverseAttributeField: public BattleCard {
    private:
        string cardName = "Reverse Attribute Field";
        string cardDesc = "During this battle, the positive and negative values of each ability of both units are inverted after adjustment. \n \"Aren't you too serious about this game? You're so da... I mean, far too immature!\" - Mei";
        int cardID = 39;
        int level = 3;
        int cost = 10;
		int max = 1;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class BigMagnum: public BattleCard {
    private:
        string cardName = "Big Magnum";
        string cardDesc = "Pay 1 HP when you use this card. During this battle, gain +2 ATK. If you would suffer KO from using this card, the card cannot be used. \n \"Go! Big Magnum!\" ―Captain Tequila";
        int cardID = 40;
        int level = 3;
        int cost = 20;
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class Shield: public BattleCard {
    private:
        string cardName = "Shield";
        string cardDesc = "Gain +3 DEF for this battle, but you may not attack. Can only be used by the defender. \n \"The most important thing is: make it back here alive.\" - Sham";
        int cardID = 41;
        int level = 3;
        int cost = 5;
        bool typePlayable(Player* owner);
    public:
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class Assault: public TrapCard {
    private:
        string cardName = "Assault";
        string cardDesc = "Battle the player who set this card, starting with their attack. \"I'll make you leave the guild today, for sure!\" - Peat";
        int cardID = 42;
        int level = 2;
        int cost = 0;
        Player* setter;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class MimyuusHammer: public TrapCard {
    private:
        string cardName = "Mimyuu's Hammer";
        string cardDesc = "Deals 1 damage. \"Thank you for dying!\" - Mimyuu";
        int cardID = 43;
        int level = 1;
        int cost = 0;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class BadPudding: public TrapCard {
    private:
        string cardName = "Bad Pudding";
        string cardDesc = "Discard 1 random card. \"Pudding with soy sauce, tastes like sea urchin!\" - Yuki";
        int cardID = 44;
        int level = 1;
        int cost = 0;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class DangerousPudding: public TrapCard {
    private:
        string cardName = "Dangerous Pudding";
        string cardDesc = "Stock Effect: Your next turn will be skipped. \"All it took was one glance for that pudding to steal my heart.\"";
        int cardID = 45;
        int level = 1;
        int cost = 0;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class SkyRestaurantPures: public TrapCard {
    private:
        string cardName = "Sky Restaurant Pures";
        string cardDesc = "Lose half your stars and fully restore HP. \"We have a guest to treat!\" - Chris";
        int cardID = 46;
        int level = 4;
        int cost = 0;
		int max = 1;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class PiggyBank: public TrapCard {
    private:
        string cardName = "Piggy Bank";
        string cardDesc = "Gain stars equal to five times the number of chapters passed since this card was set. \"Dad, can't I break the piggy yet?\" - Mescal";
        int cardID = 47;
        int level = 1;
        int cost = 0;
        int chapSet = 0;
        Player* setter;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
        void playCard(Player* owner);
};

class Invasion: public TrapCard {
    private:
        string cardName = "Invasion";
        string cardDesc = "You will have an encounter. The enemy will attack first. \"What, I was attacked...?\" - Suguri";
        int cardID = 48;
        int level = 1;
        int cost = 0;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class GoAway: public TrapCard {
    private:
        string cardName = "Go Away";
        string cardDesc = "You are moved to a randomly chosen panel. \"Ahaha, I like this.\" - Nanako";
        int cardID = 49;
        int level = 1;
        int cost = 0;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class Heat300: public TrapCard {
    private:
        string cardName = "Heat 300%";
        string cardDesc = "Stock Effect: In the next battle, gain -2 DEF. \"All I need to do is dodge every attack!\" - Suguri";
        int cardID = 50;
        int level = 1;
        int cost = 0;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class TragedyInTheDeadOfNight: public TrapCard {
    private:
        string cardName = "Tragedy in the Dead of Night";
        string cardDesc = "Discard a random card. That card will go to the player who set this card. \"Such happiness will be snatched away just like that.\"";
        int cardID = 51;
        int level = 3;
        int cost = 0;
        Player* setter;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class Exchange: public TrapCard {
    private:
        string cardName = "Exchange";
        string cardDesc = "Exchange the cards in your hand, your stars and your current panel position with the player who set this card. \n \"Heavy...\" - Suguri. \"So drafty without my cap...\" - Marc.";
        int cardID = 52;
        int level = 2;
        int cost = 0;
        Player* setter;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class Flamethrower: public TrapCard {
    private:
        string cardName = "Flamethrower";
        string cardDesc = "KO's a player. If the player has any cards in their hand, they will lose all of them instead of suffering KO. \"Heeehaaaaah!\" - Punk";
        int cardID = 53;
        int level = 3;
        int cost = 0;
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};

class ForTheFutureOfTheToyStore: public TrapCard {
    private:
        string cardName = "For The Future Of The Toy Store";
        string cardDesc = "Lose half your stars. The player who set this card will gain the lost stars. This card can only be used with less than 50 stars. \"If only! If only there was no Santa!\" - Arthur";
        int cardID = 54;
        int level = 2;
        int cost = 0;
		int max = 1;
        bool typePlayable(Player* owner);
    public:
        void landedOn(Player* poorSoul, Tile* myTile);
};
#endif