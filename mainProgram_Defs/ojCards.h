#ifndef OJ_CARDS
#define OJ_CARDS
#include "ojDefs.h"

class Dash: public BoostCard {
    private:
        
    public:
        Dash(){
            cardName = "Dash!";
            cardDesc = "For this turn, roll two dice for movement. \"Faster!\" - Suguri";
            cardID = 1;
            level = 1;
            cost = 3;
        }
        void playCard(Player* owner);
}; // this goes before the effects so effects have a "default card" to use, no effects currently use the card iirc but the default card constructors leave a bunch of stuff undefined

class DashEff: public Effect{
    public:
        DashEff(){
            effName="Dash!";
            effID = 0;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class JingleEff: public Effect {
    public:
        JingleEff(){
            effName="Nice Jingle";
            effID = 1;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class FlipEff: public Effect {
    private:
         
    public:
        FlipEff(){
            effName="Flip Out";
         effID = 2;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class ExtendEff: public Effect {
    private:
         
    public:
        ExtendEff(){
            effName="Extend";
         effID = 3;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class ProtagEff: public Effect {
    private:
        int roundsThisFight = 0;
    public:
        ProtagEff(){
            effName="Protagonist's Privilege";
         effID = 4;
         
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class AccelEff: public Effect {
    private:
         
    public:
        AccelEff(){
            effName="Accelerator";
         effID = 5;
        }
        void OnApply(Player* effOwner);
        void OnLose(Player* effOwner);
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class CrystEff: public Effect {
    private:
         
    public:
        CrystEff(){
            effName="Stiff Crystal";
         effID = 6;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class SpecsEff: public Effect {
    private:
         
    public:
        SpecsEff(){
            effName="Extraordinary Specs";
         effID = 7;
        }
        void OnApply(Player* effOwner);
        void OnLose(Player* effOwner);
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class BoundEff1: public Effect {
    private:
         
    public:
        BoundEff1(){
            effName="Binding Chains";
         effID = 8;
        }
        void OnLose(Player* effOwner);
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class BoundEff2: public Effect {
    private:
         
    public:
        BoundEff2(){
            effName="Bound";
         effID = 9;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class HyperEff: public Effect {
    private:
         
    public:
        HyperEff(){
            effName="Hyper Mode";
         effID = 10;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class OutOfAmmoEff: public Effect{
    private:
         
         int pidstarted = 0;
         int turnstarted = 0;
    public:
        OutOfAmmoEff(int pIDStarter, int turnCurr){
            effName="Out Of Ammo";
         effID = 11;
         pidstarted = pIDStarter;
         turnstarted = turnCurr;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class LittleWarEff: public Effect{
    private:
         
    public:
        LittleWarEff(){
            effName="Little War";
         stocks = 3;
         effID = 12;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class DangerousPuddingEff: public Effect{
    private:
         
    public:
        DangerousPuddingEff(){
            effName="Dangerous Pudding";
         effID = 13;
        }
        void Enact(Player* effOwner, int triggerID, int optionalNum = 0, Tile* optTile = nullptr, EUnit* optEnemy = nullptr, Player* optPlyr = nullptr, Card optCard = Dash());
};

class Cookie: public BoostCard {
    private:
         
    public:
        Cookie(){
            cardName = "Saki's Cookie";
         cardDesc = "Heal 1 HP. \"Have a cookie!\" - Saki";
         cardID = 2;
         level = 1;
         cost = 0;
        }
        void playCard(Player* owner);
};

class Pudding: public BoostCard {
    private:
    public:
        Pudding(){
            cardName = "Pudding";
         cardDesc = "Reset your HP to your max HP. \"Hooray!\" - QP";
         cardID = 3;
         level = 4;
         cost = 0;
        }
        void playCard(Player* owner);
};

class NicePresent: public BoostCard {
    private:
         
    public:
        NicePresent(){
            cardName = "Nice Present";
         cardDesc = "Draw 2 cards. \"You're going to help me deliver the presents.\" - Aru";
         cardID = 4;
         level = 2;
         cost = 10;
		 max = 1;
        }
        void playCard(Player* owner);
};

class Jingle: public BoostCard {
    private:
         
    public:
        Jingle(){
            cardName = "Nice Jingle";
         cardDesc = "The next bonus panel gives you twice as many stars. \"We've got a bunch.\" ―Aru";
         cardID = 5;
         level = 1;
         cost = 3;
		 max = 1;
        }
        void playCard(Player* owner);
};

class Flip: public BoostCard {
    private:
    public:
        Flip(){
         cardName = "Flip Out";
         cardDesc = "Next time you land on a drop panel, the player(s) with the highest number of stars will lose the same number of stars as you. \n \"......!\" - Mei";
         cardID = 6;
         level = 1;
         cost = 0;
        }
        void playCard(Player* owner);
};

class Shot: public BoostCard {
    private:

    public:
        Shot(){
         cardName = "Long-Distance Shot";
         cardDesc = "Deals 1 damage to the selected enemy unit. \"I can hit you from anywhere.\" - Iru";
         cardID = 7;
         level = 1;
         cost = 5;
        }
        void playCard(Player* owner);
};

class Extend: public BoostCard {
    private:

    public:
        Extend(){
         cardName = "Extend";
         cardDesc = "After suffering KO, you will revive on the following turn. \"All good for now!\" - Marc";
         cardID = 8;
         level = 3;
         cost = 10;
		 max = 1;
        }
        void playCard(Player* owner);
};

class StiffCrystal: public BoostCard {
    private:

    public:
        StiffCrystal(){
         cardName = "Stiff Crystal";
         cardDesc = "This card negates the effect of a trap card. Gain 5 stars per level of cancelled trap. \"Such a pain in the neck.\" - Kyoko";
         cardID = 9;
         level = 2;
         cost = 20;
		 max = 1;
        }
        void playCard(Player* owner);
};

class Princess: public BoostCard {
    private:

        bool typePlayable(Player* owner);
    public:
        Princess(){
         cardName = "Princess' Privilege";
         cardDesc = "Discard all cards in your hand and draw 3 cards. Can only be used when holding only Princess's Privilege or you have at least 3 cards in your hand. \n \"You may visit my house someday.\" - Fernet";
         cardID = 10;
         level = 4;
         cost = 20;
		 max = 1;
        }
        void playCard(Player* owner);
};

class Protagonist: public BoostCard {
    private:

    public:
        Protagonist(){
         cardName = "Protagonist's Privilege";
         cardDesc = "(Hyper) Effect duration: 3 chapters. When you are allowed to attack first, the opposing unit cannot attack (once per combat). \n \"This is the privilege of the main character!\" - Kai";
         cardID = 11;
         level = 3;
         cost = 20;
        }
        void playCard(Player* owner);
};

class Ubiquitous: public BoostCard {
    private:

    public:
        Ubiquitous(){
         cardName = "Ubiquitous";
         cardDesc = "(Hyper) Warp to target active enemy's panel. In addition, steal stars equal to 10x their level. \"Poppo! Poppopopopopo!\" - Marie Poppo";
         cardID = 12;
         level = 1;
         cost = 0;
        }
        void playCard(Player* owner);
};

class Accelerator: public BoostCard {
    private:
         
    public:
        Accelerator(){
            cardName = "Accelerator";
         cardDesc = "(Hyper) Effect duration: 1 chapter. Roll 2 dice for all dice rolls this turn. \"I'm accelerating.\" - Suguri";
         cardID = 13;
         level = 3;
         cost = 30;
        }
        void playCard(Player* owner);
};

class X16: public BoostCard {
    private:
         
        bool typePlayable(Player* owner);
    public:
        X16(){
            cardName = "x16 Big Rocket";
         cardDesc = "(Hyper) Deal damage equal to your level to target unit. A KO from this effect gives you 2 Wins. \"Charged! Go!\" - Marc";
         cardID = 14;
         level = 1;
         cost = 0;
         customCostString = "10 * Level";
        }
        void playCard(Player* owner);
};

class AirStrike: public EventCard {
    private:
         
    public:
        AirStrike(){
            cardName = "Air Strike";
         cardDesc = "(Hyper) All enemies take 1 to 3 damage. Gain 15 stars on every KO. \"Hmph, go down, all of you.\" - Fernet";
         cardID = 15;
         level = 2;
         cost = 30;
        }
        void playCard(Player* owner);
};

class Gamble: public EventCard {
    private:
         
    public:
        Gamble(){
            cardName = "Gamble";
         cardDesc = "(Hyper) A randomly chosen unit is KO'd. \"Why not use this to decide whose turn it is?\" - Yuki";
         cardID = 16;
         level = 3;
         cost = 15;
        }
        void playCard(Player* owner);
};

class PresentForYou: public EventCard {
    private:
         
    public:
        PresentForYou(){
            cardName = "Present For You";
         cardDesc = "(Hyper) All players draw cards until they have a full hand. Those with full hand draw 1 card instead. \n Gain stars equal to 10x the number of all cards drawn. \"Presents for good boys and girls.\" - Aru";
         cardID = 17;
         level = 2;
         cost = 30;
        }
        void playCard(Player* owner);
};

class Chains: public EventCard {
    private:
         
    public:
        Chains(){
            cardName = "Binding Chains";
         cardDesc = "(Hyper) All Units except yours will skip their next turn. Apply \"Bound\" to all active enemies. \n Effect Duration: 2 Chapters. Gain -2 EVD and -1 MOV. \"I don't like doing this sort of thing.\" - Hime";
         cardID = 18;
         level = 1;
         cost = 0;
        }
        void playCard(Player* owner);
};

class Specs: public BoostCard {
    private:
         
    public:
        Specs(){
            cardName = "Extraordinary Specs";
         cardDesc = "(Hyper) Effect Duration: 1 chapter. Roll 6 for all dice rolls this turn. \"I'd appreciate it if you dropped your weapons.\" - Sora";
         cardID = 19;
         level = 3;
         cost = 30;
        }
        void playCard(Player* owner);
};

class MagicalMassacre: public EventCard {
    private:
         
    public:
        MagicalMassacre(){
            cardName = "Magical Massacre";
         cardDesc = "(Hyper) All units whose HP is full or higher will suffer KO. Gain -1 REC on next Revive roll per unit KO'd (other than yourself). \n \"Disappear.\" - Tomomo";
         cardID = 20;
         level = 4;
         cost = 20;
        }
        void playCard(Player* owner);
};

class BlueCrow: public BattleCard {
    private:
         
    public:
        BlueCrow(){
            cardName = "Blue Crow the Second";
         cardDesc = "(Hyper) During this battle, gain ATK and DEF but lose EVD equal to the number of cards in your hand. \"I'm gonna settle this!\" - Peat";
         cardID = 21;
         level = 2;
         cost = 10;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class HyperMode: public BattleCard {
    private:
         
    public:
        HyperMode(){
            cardName = "Hyper Mode";
         cardDesc = "(Hyper) Gain +3 ATK during this battle. If your unit suffers KO during this battle, you give no stars or Wins and the unit will revive next turn. \n \"HYPER MODE!\" - QP";
         cardID = 22;
         level = 1;
         cost = 10;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class HereAndThere: public EventCard {
    private:
         
    public:
        HereAndThere(){
            cardName = "Here and There";
         cardDesc = "All units are moved to randomly chosen panels. \"To the next world!\" - Marie Poppo";
         cardID = 23;
         level = 2;
         cost = 10;
        }
        void playCard(Player* owner);
};

class OutOfAmmo: public EventCard {
    private:
         
    public:
        OutOfAmmo(){
            cardName = "Out of Ammo";
         cardDesc = "Effect duration: 1 chapter. No player may use any cards. \"Ran out of ammo!\" - Peat";
         cardID = 24;
         level = 2;
         cost = 5;
        }
        void playCard(Player* owner);
};

class GiftExchange: public EventCard {
    private:
    public:
        GiftExchange(){
            cardName = "Gift Exchange";
         cardDesc = "All cards are gathered from the players and dealt back randomly. The total number of each player's cards remains unchanged. \n \"This card is extremely strong for reasons that are difficult to explain.\" - Me";
         cardID = 25;
         level = 3;
         cost = 10;
        }
        void playCard(Player* owner);
};

class LittleWar: public EventCard {
    private:
    public:
        LittleWar(){
            cardName = "Little War";
         cardDesc = "Effect Duration: 3 chapters. \n Offense and defense will happen twice in all battles.\"I believe... I have the power to stop this...\" - Suguri";
         cardID = 26;
         level = 4;
         cost = 50;
		 max = 1;
        }
        void playCard(Player* owner);
};

class HolyNight: public EventCard {
    private:
    public:
        HolyNight(){
            cardName = "Holy Night";
         cardDesc = "Start-of-chapter bonus stars are increased by one. \"Aha, that's why it's a party night.\" - Hime";
         cardID = 27;
         level = 1;
         cost = 0;
        }
        void playCard(Player* owner);
};

class AllOutMode: public EventCard {
    private:
    public:
        AllOutMode(){
            cardName = "Super All-Out Mode";
         cardDesc = "Stock Effect: All units gain +2 ATK during their next battle. \"This is gonna hurt even if you know it's coming!!\" - Tomomo";
         cardID = 28;
         level = 3;
         cost = 30;
        }
        void playCard(Player* owner);
};

class Dinner: public EventCard {
    private:
    public:
        Dinner(){
            cardName = "Dinner";
         cardDesc = "Heal all units for 3 HP. \"Let's have supper together.\" - Natsumi";
         cardID = 29;
         level = 3;
         cost = 10;
        }
        void playCard(Player* owner);
};

class Seagulls: public EventCard {
    private:
    public:
        Seagulls(){
            cardName = "Cloud of Seagulls";
         cardDesc = "A randomly chosen unit will receive 2 damage. \"Squaawk!\" - Seagull";
         cardID = 30;
         level = 1;
         cost = 0;
        }
        void playCard(Player* owner);
};

class SealedGuardian: public EventCard {
    private:
    public:
        SealedGuardian(){
            cardName = "Sealed Guardian";
         cardDesc = "Every unit's HP becomes 1. \"Meet the guardian angel of this vessel.\" - Shifu";
         cardID = 31;
         level = 5;
         cost = 50;
		 max = 1;
        }
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
    public:
        OhMyFriend(){
            cardName = "Oh My Friend";
         cardDesc = "A boss will show up. \"Machines have friends too.\" - NoName";
         cardID = 33;
         level = 1;
         cost = 30;
		 max = 1;
        }
        void playCard(Player* owner);
};

class ForcedRevival: public EventCard {
    private:
    public:
        ForcedRevival(){
            cardName = "Forced Revival";
         cardDesc = "All units suffering KO will be revived with 1 HP. \"You'll be up in a jiffy.\" - Kiriko";
         cardID = 34;
         level = 3;
         cost = 30;
        }
        void playCard(Player* owner);
};

class RainbowColoredCircle: public BattleCard {
    private:
    public:
        RainbowColoredCircle(){
        cardName = "Rainbow-Colored Circle";
         cardDesc = "During this battle, gain +2 EVD and -1 DEF. \"Like drawing a rainbow-colored circle.\"";
         cardID = 35;
         level = 2;
         cost = 5;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class Rbits: public BattleCard {
    private:
    public:
        Rbits(){
            cardName = "Rbits";
         cardDesc = "During this battle, gain +2 DEF. You may not use the Evade command. \"Formation Orbit!\" - QP";
         cardID = 36;
         level = 2;
         cost = 3;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class ImOnFire: public BattleCard {
    private:
    public:
        ImOnFire(){
            cardName = "I'm On Fire!";
         cardDesc = "During this battle, gain +1 ATK and -1 DEF. \"Let's play our lives away!\" - Kae";
         cardID = 37;
         level = 1;
         cost = 5;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class FinalBattle: public BattleCard {
    private:
    public:
        FinalBattle(){
            cardName = "Final Battle";
         cardDesc = "This battle will last until either unit suffers KO (Maximum of 10 rounds). \"To protect everyone!\" - Suguri & Hime";
         cardID = 38;
         level = 4;
         cost = 30;
		 max = 1;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class ReverseAttributeField: public BattleCard {
    private:
    public:
        ReverseAttributeField(){
            cardName = "Reverse Attribute Field";
         cardDesc = "During this battle, the positive and negative values of each ability of both units are inverted after adjustment. \n \"Aren't you too serious about this game? You're so da... I mean, far too immature!\" - Mei";
         cardID = 39;
         level = 3;
         cost = 10;
		 max = 1;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class BigMagnum: public BattleCard {
    private:
    public:
        BigMagnum(){
            cardName = "Big Magnum";
         cardDesc = "Pay 1 HP when you use this card. During this battle, gain +2 ATK. If you would suffer KO from using this card, the card cannot be used. \n \"Go! Big Magnum!\" ―Captain Tequila";
         cardID = 40;
         level = 3;
         cost = 20;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class Shield: public BattleCard {
    private:
        bool typePlayable(Player* owner);
    public:
        Shield(){
            cardName = "Shield";
             cardDesc = "Gain +3 DEF for this battle, but you may not attack. Can only be used by the defender. \n \"The most important thing is: make it back here alive.\" - Sham";
             cardID = 41;
             level = 3;
             cost = 5;
        }
        void playCard(Player* owner, Player* opp = nullptr, EUnit* npcOpp = nullptr);
};

class Assault: public TrapCard {
    private:
        Player* setter;
    public:
        Assault(){
        cardName = "Assault";
         cardDesc = "Battle the player who set this card, starting with their attack. \"I'll make you leave the guild today, for sure!\" - Peat";
         cardID = 42;
         level = 2;
         cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class MimyuusHammer: public TrapCard {
    private:
    public:
        MimyuusHammer(){
        cardName = "Mimyuu's Hammer";
         cardDesc = "Deals 1 damage. \"Thank you for dying!\" - Mimyuu";
         cardID = 43;
         level = 1;
         cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class BadPudding: public TrapCard {
    private:
    public:
        BadPudding(){
        cardName = "Bad Pudding";
         cardDesc = "Discard 1 random card. \"Pudding with soy sauce, tastes like sea urchin!\" - Yuki";
         cardID = 44;
         level = 1;
         cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class DangerousPudding: public TrapCard {
    private:
    public:
        DangerousPudding(){
            cardName = "Dangerous Pudding";
             cardDesc = "Stock Effect: Your next turn will be skipped. \"All it took was one glance for that pudding to steal my heart.\"";
             cardID = 45;
             level = 1;
             cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class SkyRestaurantPures: public TrapCard {
    private:
    public:
        SkyRestaurantPures(){
            cardName = "Sky Restaurant Pures";
             cardDesc = "Lose half your stars and fully restore HP. \"We have a guest to treat!\" - Chris";
             cardID = 46;
             level = 4;
             cost = 0;
             max = 1;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class PiggyBank: public TrapCard {
    private:
        int chapSet = 0;
        Player* setter;
    public:
        PiggyBank(){
             cardName = "Piggy Bank";
             cardDesc = "Gain stars equal to five times the number of chapters passed since this card was set. \"Dad, can't I break the piggy yet?\" - Mescal";
             cardID = 47;
             level = 1;
             cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
        void playCard(Player* owner);
};

class Invasion: public TrapCard {
    private:
    public:
        Invasion(){
             cardName = "Invasion";
            cardDesc = "You will have an encounter. The enemy will attack first. \"What, I was attacked...?\" - Suguri";
            cardID = 48;
            level = 1;
            cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class GoAway: public TrapCard {
    private:
    public:
        GoAway(){
            cardName = "Go Away";
            cardDesc = "You are moved to a randomly chosen panel. \"Ahaha, I like this.\" - Nanako";
            cardID = 49;
            level = 1;
            cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class Heat300: public TrapCard {
    private:
    public:
        Heat300(){
            cardName = "Heat 300%";
             cardDesc = "Stock Effect: In the next battle, gain -2 DEF. \"All I need to do is dodge every attack!\" - Suguri";
             cardID = 50;
             level = 1;
             cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class TragedyInTheDeadOfNight: public TrapCard {
    private:
        Player* setter;
    public:
        TragedyInTheDeadOfNight(){
            cardName = "Tragedy in the Dead of Night";
            string cardDesc = "Discard a random card. That card will go to the player who set this card. \"Such happiness will be snatched away just like that.\"";
             cardID = 51;
             level = 3;
             cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class Exchange: public TrapCard {
    private:
        Player* setter;
    public:
        Exchange(){
            cardName = "Exchange";
             cardDesc = "Exchange the cards in your hand, your stars and your current panel position with the player who set this card. \n \"Heavy...\" - Suguri. \"So drafty without my cap...\" - Marc.";
             cardID = 52;
             level = 2;
             cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class Flamethrower: public TrapCard {
    private:
    public:
        Flamethrower(){
        cardName = "Flamethrower";
         cardDesc = "KO's a player. If the player has any cards in their hand, they will lose all of them instead of suffering KO. \"Heeehaaaaah!\" - Punk";
         cardID = 53;
         level = 3;
         cost = 0;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};

class ForTheFutureOfTheToyStore: public TrapCard {
    private:
        bool typePlayable(Player* owner);
    public:
        ForTheFutureOfTheToyStore(){
            cardName = "For The Future Of The Toy Store";
            cardDesc = "Lose half your stars. The player who set this card will gain the lost stars. This card can only be used with less than 50 stars. \"If only! If only there was no Santa!\" - Arthur";
             cardID = 54;
             level = 2;
             cost = 0;
		     max = 1;
        }
        void landedOn(Player* poorSoul, Tile* myTile);
};
#endif