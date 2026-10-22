#include <string>
#include <vector>
#include <stack>
#include <array>
#include <random>
#include <iostream>
#include "ojDefs.h"
#include "ojUnits.h"

namespace { //so other files don't break
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> pIDRand(1, 4);
    uniform_int_distribution<int> diceRand(1, 6);
    uniform_real_distribution<float> fracRand(0, 1); //used for UNIT_CONTROLLER_RANDOMCHOICE in Player::Choose
    uniform_int_distribution<int> cardRand(0, 39); //deck stuff
}

//Can you believe this is the last definition file i'm writing?
//ojUnits.h and ojBoards.h are done,
//ojCards.h and ojCards.cpp are done, fullly coded,
//and of course, ojDefs.h is done, it was the first thing I wrote
//I probably will change these a little, things won't work as intended in testing,
//but the way all these systems interact, while not ideal (I'm not sure Nice Jingle and Flip Out should "replace" their panel's effects)
//should, in theory, mimic the behavior of the game pretty well.
//Count the lines in ojCards.cpp; right now they're 625

bool Card::canPlay(Player* owner){
     return (owner->Norma() >= level && owner->Stars() >= cost && typePlayable(owner)); 
}

string Card::Cost_Display(){
    if(customCostString == "") return to_string(cost);
    return customCostString;
}

bool BattleCard::typePlayable(Player* owner){ //only card type with this condition btw
    return owner->Battling();
}

bool BoostCard::typePlayable(Player* owner){
    return !owner->Battling();
}

bool EventCard::typePlayable(Player* owner){
    return !owner->Battling();
}

bool TrapCard::typePlayable(Player* owner){
    return !owner->Battling();
}

void TrapCard::playCard(Player* owner){
    setter = owner;
    owner->LoseStars(cost);
    owner->CurrTile()->trapSet(this); //kinda weird but lets me bypass having to give every single trap a setter function
}

//i think the default card definitions are done


Card Deck::drawCard(){
    Card toDraw = currentDeck.back();
    currentDeck.pop_back();
    if(currentDeck.size() <= 0){
        resetDeck();
    }
    return toDraw;
}

void Deck::initDeck(vector<Card> cardList){ //This function is designed so you can throw any valid 40-card deck in it
    int randInt = 0;
    fullDeck = {};
    for(int i = 0; i < 48; i++){
        if(i < 8){
            fullDeck.push_back(BlankCard());
        } else{
            randInt = cardRand(mt);
            fullDeck.push_back(cardList[randInt]);
            cardList[randInt] = cardList.back();
            cardList.pop_back();
        }
    }
    currentDeck = fullDeck;
}

Tile::Tile(int typeIn, int xposIn, int yposIn, array<bool, 4> movesIn, bool doubler, int homeIDIn){
    type = typeIn;
    xPos = xposIn;
    yPos = yposIn;
    doubled = doubler;
    homeID = homeIDIn;
    movesNWSE[0] = movesIn[0];
    movesNWSE[1] = movesIn[1];
    movesNWSE[2] = movesIn[2];
    movesNWSE[3] = movesIn[3];
}

void Tile::trapClear(){
    trap = TrapCard();
    trapped = false;
}

void Tile::trapSet(TrapCard* trapToSet){
    trapped = true;
    trap = *trapToSet;
}

void Tile::landOn(Player* lander){
    if(trapped){
        trap.landedOn(lander, this);
        trapClear();
    }
    switch(type){
        case TILE_BONUS:
            lander->AddStars(BonusFormula(lander->Roll(), lander));
            break;
        case TILE_DROP:
            lander->LoseStars(DropFormula(lander->Roll(), lander));
            break;
        case TILE_ENEMY:
            if(!lander->GetBoard()->bossActive) lander->StartBattle(fightTileEnemy());
            else lander->StartBattle(&lander->GetBoard()->boss);
            break;
        case TILE_DRAW:
            lander->Draw();
            break;
        case TILE_MOVE:
            lander->RollToMove();
            break;
        case TILE_HOME:
            if(lander->NormaCheck()){
                lander->NormaUp();
            }
            lander->Heal(1);
            break;
        case TILE_WARP:
        case TILE_WARP_DEADEND:
            Board* tempboard = lander->GetBoard();
            lander->warpTo(&tempboard->tiles[tempboard->warpDestinationTiles[static_cast<int>(fracRand(mt)) * tempboard->warpDestinationTiles.size()]]);
            break;
    }
}

void Tile::summonEnemy(){
    int genericEnemy = static_cast<int>(fracRand(mt) * 3);
    switch(genericEnemy){
        case 0:
            tileEnemy = Chicken();
            break;
        case 1:
            tileEnemy = Gull();
            break;
        default:
            tileEnemy = Ball();
            break;
    }
}

EUnit* Tile::fightTileEnemy(EUnit* boss){
    if(boss != nullptr) return boss;
    if(!tileEnemy.Alive()) summonEnemy();
    return &tileEnemy;
}

int Tile::BonusFormula(const int roll, Player* lander){
    return (roll * min(3, lander->Norma()));
}

int Tile::DropFormula(const int roll, Player* lander){
    return (roll * lander->Norma());
}
//tile is fully defined

Board::Board(){
    SetWarpIndexes();
    FillWithBlankTiles();
}

void Board::FillWithBlankTiles(){
    int vectorPos = 0;
    for(int y = 0; y < boardSize[1]; y++){
        for(int x = 0; x < boardSize[0]; x++){
            if(tiles[vectorPos].xPos < x){
                //dummy
            }

        }
    }
}

void Board::summonBoss(){
    if(!bossActive){
        bossActive = true;
        bossStars = 0;
        boss.resetHP();
    }
}

void Board::killBoss(){
    if(bossActive){
        bossActive = false;
        bossStars = 0;
        boss.resetHP();
    }
}

bool Board::tileAtExists(int xp, int yp){
    //dummy
}

Tile* Board::tileAt(int xp, int yp){
    //dummy
}

void Board::SetWarpIndexes(){
    for(int i = 0; i < tiles.size(); i++){
        if(tiles[i].type == TILE_WARP){
            warpDestinationTiles.push_back(i);
        }
    }
}

//board is fully defined

EUnit::EUnit(){
    stars = 0;
    curHP = stats[0];
    alive = true;
}

int EUnit::BattleRoll(bool offense, int attackRoll){
    int Roll = diceRand(mt);
    if(offense){
        if(combatActions[0]) return Atk() + Roll;
        return 0;
    } else{
        if(combatActions[2] && curHP <= 1 || combatActions[2] && 3 + Evd() > attackRoll || combatActions[2] && (min(1, attackRoll - (3 + Def()))) >= MaxHP() && (6 + Evd()) > attackRoll){
            if((Evd() + Roll) <= attackRoll) Hurt(attackRoll);
            return Evd() + Roll;
        } else if(combatActions[1]) {
            Hurt(min(1, attackRoll - (Def() + Roll)));
            return Def() + Roll;
        }
        Hurt(attackRoll);
        return 0;
    } //I don't know if this is how OJ enemy AI works, but this is usually what you want to do
} //and the AI usually does stuff along these lines anyways

void EUnit::Hurt(int Damage){
    curHP = curHP - Damage;
    if(curHP <= 0){
        alive = false;
        curHP = 0;
    }
}

void EUnit::AddStatMods(array<int, 4> addStats, bool temp){
    tempStatMods[0] = addStats[0];
    tempStatMods[1] = addStats[2];
    tempStatMods[2] = addStats[3];
    tempStatMods[3] = addStats[4];
    //i dont need anything besides this for this implementation, lol
    //this only matters for RAF
}

void EUnit::setCombatRestrictions(array<bool, 3> restrictionsNew){
    for(int i = 0; i < 3; i++){
        if(restrictionsNew[i]) combatActions[i] == false;
        else combatActions[i] == true;
    }
}

//eunit is fully defined now!!! yay!!!!

PlayerChoice P1Thru4 = {{"Player 1", "Player 2", "Player 3", "Player 4"}, {1, 1, 1, 1}, "Pick a Player!"};
PlayerChoice NormaPick = {{"Stars", "Wins"}, {1, 1}, "Pick a Norma goal:"};

int Player::Choose(PlayerChoice choice){
    vector<string> validChoiceNames = {};
    vector<int> invalidChoiceIndices = {};
    for(int i = 0; i < choice.choiceNames.size(); i++){
        if(choice.validChoices[i]){
            validChoiceNames.push_back(choice.choiceNames[i]);
        } else { invalidChoiceIndices.push_back(i); }
    }
    if(controllerType == UNIT_CONTROLLER_RANDOMCHOICE){
        float frac = fracRand(mt);
        frac = frac * validChoiceNames.size();
        return static_cast<int>(frac);
    } else if (controllerType == UNIT_CONTROLLER_PLAYER){
        int validChoicesNum = 1;
        int playerPick = 0;
        cout<<choice.chooseMsg<<endl;
        for(int i = 0; i < choice.choiceNames.size(); i++){
            if(choice.validChoices[i]){
                cout<<validChoicesNum<<": "<<choice.choiceNames[i]<<endl;
                validChoicesNum++;
            } else {
                cout<<"(Unavailable) "<<choice.choiceNames[i]<<endl;
            }
        }
        cout<<"Please enter your choice."<<endl;
        cin>>playerPick;
        for(int i = 0; i < invalidChoiceIndices.size(); i++){
            if(playerPick >= invalidChoiceIndices[i]){
                playerPick++;
            }
        }
        return min(static_cast<int>(choice.choiceNames.size()) - 1, (max(0, playerPick - 1))); //Why the HELL do I have to cast size() to an int why is it not already an int
    }
    return -1;
}

int Player::PickCardFromHand(){
    PlayerChoice handChoice = {{},{}, "Pick a card from your hand."};
    for(int i = 0; i < hand.size(); i++){
        handChoice.choiceNames.push_back(hand[i].Name() + " (" + hand[i].Desc() + ")");
        if(hand[i].canPlay(this)) handChoice.validChoices.push_back(true);
        else handChoice.validChoices.push_back(false);
    }
    return Choose(handChoice);
}

void Player::TakeTurn(){
    if(!alive){
        CheckEffects(TRIGGER_TURNSTART);
        if(!alive){
            int revAttempt = Roll();
            if(revAttempt >= (Rec() - revRolls)){
                Revive();
            } else {
                revRolls++;
            }
        }
        CheckEffects(TRIGGER_TURNEND);
    }
    //dummy
}
void Player::ResetKOStars(){starsLostOnKOMult = 0.5;} //should be called after every battle loss, since cards that adjust this number would do so on TRIGGER_BATTLELOSE
void Player::ResetAddStarsMult(){AddStarsMult=1;} //should be called on AddStars

    //effect checker

    //card helpers
void Player::SetAddStarsMult(float newMult) { AddStarsMult = newMult; }
void Player::AddEffect(Effect effectToAdd) {    myEffects.push_back(effectToAdd); }
void Player::AddStatMods(array<int, 7> addStats, bool temp){
    if(temp){
        for(int i = 0; i < 7; i++){
            tempStatMods[i] += addStats[i];
        }
    }
    else {
        for(int i = 0; i < 7; i++){
            statMods[i] += addStats[i];
        }
    }
} //i Dont Like that array<> thing it feels gross but i can't call AddStatMods({0, 0, ... 0}) otherwise
void Player::AddDice(int exDiceNum, bool temp) { 
    if(temp){
        tempExtraDiceNum += exDiceNum;
    } else extraDiceNum += exDiceNum;
}
void Player::LoseDice(int exDiceNum, bool temp) { 
    if(temp){
        tempExtraDiceNum -= exDiceNum;
    } else extraDiceNum -= exDiceNum;
}
Player* Player::choosePlayer(bool alivePlayersOnly, bool excludeSelf){
    PlayerChoice picker = P1Thru4;
    if(excludeSelf){
        picker.validChoices[playerID-1] = false;
    }
    int mypick = Choose(picker);
    if(mypick >= 0 && mypick < 4){
        return allPlayers[mypick];
    }
    return nullptr;
}
void Player::SetDiceType(int newType) { diceType = newType; }
void Player::TrapSet(Tile* trapTile, TrapCard myTrap){ trapTile->trapSet(&myTrap); }
void Player::AdjustKOStars(float newMult){ starsLostOnKOMult = newMult;}
void Player::SetRounds(int rounds){ battleRounds = rounds; } //exclusively for battle cards, should only be used at start of battle
void Player::CombatRestrict(array<bool, 3> restrict = {false, false, false}, array<bool, 3> unrestrict = {false, false, false}){
    for(int i = 0; i < 3; i++){
        if(restrict[i] == true){
            combatActions[i] = false;
        }
        if(unrestrict[i] == true){
            combatActions[i] = true;
        }
    }
}
void Player::skipAction(){ interrupt = true; }

void Player::CheckEffects(int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
    for(int i = 0; i < myEffects.size(); i++){
        myEffects[i].Enact(this, triggerID, optionalNum, optTile, optEnemy, optPlyr, optCard);
        if(myEffects[i].Stocks() <= 0){
            myEffects[i].OnLose(this);
            myEffects[i] = myEffects.back();
            myEffects.pop_back();
        }
    }
}

    //stuff that should be able to trigger Effects
int Player::Roll(){
    CheckEffects(TRIGGER_ROLL);
    int rollSum = 0;
    switch(diceType){
        case DICE_NORMAL:
            for(int i = 0; i < DiceNum(); i++){
                rollSum += diceRand(mt);
            }
            break;
        case DICE_SPECS:
            for(int i = 0; i < DiceNum(); i++){
                rollSum += 6;
            }
            break;
    }
    tempExtraDiceNum = 0;
    interrupt = false;
    return rollSum;
}
void Player::AddCard(Card newCard){
    CheckEffects(TRIGGER_ADDCARD, 0, nullptr, nullptr, nullptr, newCard);
    if(!interrupt){
        if(newCard.CardID() == 0) hand.push_back(character.Hyper());
        else hand.push_back(newCard);
    }
    interrupt = false;
}
void Player::AddStars(int starNum) {
    CheckEffects(TRIGGER_ADDSTARS, starNum);
    if(!interrupt){
        stars += starNum * AddStarsMult;
        ResetAddStarsMult();
    }
    interrupt = false;
}
void Player::AddWins(int winNum){
    CheckEffects(TRIGGER_ADDWINS, winNum);
    if(!interrupt){
        wins += winNum;
    }
    interrupt = false;
}
void Player::PlayCard(int toPlay, Player* opp, EUnit* npcOp){
    CheckEffects(TRIGGER_PLAYCARD, 0, nullptr, npcOp, opp, hand[toPlay]);
    if(!interrupt){
        if(Battling()) { //forcibly call the baBttle card version of playCard, this is somewhat deranged but i'm not sure if there's a saner/safer way to do this
            BattleCard* myCard = static_cast<BattleCard*>(&hand[toPlay]);
            myCard->playCard(this, opp, npcOp);
        } else{
            hand[toPlay].playCard(this);
        }
        hand[toPlay] = hand.back(); //this is sort of like a discard, but playing a card explicitly does not trigger discard effects,
        hand.pop_back(); //except on gift cards which are discarded on play, but if i were to implement them i would make them add a passive effect,
        //that triggers discard and interrupts this function if it detects the card being played is the gift card,
        //and also, i'm not adding gift cards because that would suck.
    }
    interrupt = false;
}
void Player::DisCard(int pos){
    CheckEffects(TRIGGER_DISCARD, pos);
    if(!interrupt && pos > 0 && pos < hand.size()){
        hand[pos] = hand.back();
        hand.pop_back();
    }
    interrupt = false;
}

void Player::Heal(int healAmnt, bool overheal){
    if(Alive()){
        CheckEffects(TRIGGER_HEAL, healAmnt);
        if(!interrupt){
            curHP = overheal? (curHP + healAmnt) : (min(curHP + healAmnt, MaxHP()));
        }
    }
    interrupt = false;
}
void Player::Hurt(int dmgAmnt){
    if(Alive()){
        CheckEffects(TRIGGER_HURT, dmgAmnt);
        if(!interrupt){
            curHP -= dmgAmnt;
        }
        if(curHP <= 0){
            KO();
        }
    }
    interrupt = false;
}
void Player::SetHP(int setTo){
    if(Alive()){
        CheckEffects(TRIGGER_SETHP, setTo);
        if(!interrupt){
            curHP = setTo;
        }
        if(curHP <= 0){
            KO();
        }
    }
    interrupt = false;
}
void Player::KO(){
    if(Alive()){
        CheckEffects(TRIGGER_KO);
        if(!interrupt && alive){
            curHP = 0;
            alive = false;
            revRolls = 0;
        }
    }
    interrupt = false;
}
void Player::Land(Tile* landedOn){
    CheckEffects(TRIGGER_LAND, 0, landedOn);
    if(!interrupt){
        currTile = landedOn;
        landedOn->landOn(this);
    }
    interrupt = false;
}

void Player::NormaUp(){
    CheckEffects(TRIGGER_LEVELUP);
    if(!interrupt){
        int expectedWins;
        int expectedStars;
        norma++;
        if(norma < 5){
            switch (norma){
            case 1:
                expectedWins = 2;
                expectedStars = 30;
                break;
            case 2:
                expectedWins = 5;
                expectedStars = 70;
                break;
            case 3:
                expectedStars = 120;
                expectedWins = 9;
                break;
            case 4:
                expectedStars = 200;
                expectedWins = 14;
                break;
            default:
                expectedStars = 10;
                expectedWins = 1;
                break;
            }
            if(UNIT_CONTROLLER_PLAYER) cout<<"Star requirement: "<<expectedStars<<", Wins requirement:"<<expectedWins<<endl; 
            int picker = Choose(NormaPick);
            if(picker == 0){
                cout<<"Player "<<playerID<<" has chosen Stars. They need "<<expectedStars<<" to level up. "<<endl;
                goalType = GOAL_STARS;
                goal = expectedStars;
            } else {
                cout<<"Player "<<playerID<<" has chosen Wins. They need "<<expectedWins<<" to level up. "<<endl;
                goalType = GOAL_WINS;
                goal = expectedWins;
            }
        }
        else wonGame = true;
        if(norma == 4){
            board->summonBoss();
        }
    }
    interrupt = false;
}
void Player::Draw(){
    CheckEffects(TRIGGER_DRAW);
    if(!interrupt){
        AddCard(mainDeck->drawCard());
    }
    interrupt = false;
}

PlayerChoice CardOrBattle = {{"Cards", "Fight"}, {1, 1}, "Do you want to play a card or start the fight?"};
PlayerChoice DefEvd = {{"Defend", "Evade"}, {1, 1}, "Do you defend or evade?"};

void EUnit::ResetStatMods(){
    tempStatMods[0] = 0;
    tempStatMods[1] = 0;
    tempStatMods[2] = 0;
    tempStatMods[3] = 0;
}

void EUnit::WinBattle(Player* opponent){
    int KOStars = opponent->Stars() * opponent->KOStarsMult();
    opponent->ResetKOStars();
    stars = stars + KOStars;
    opponent->LoseStars(KOStars);
    opponent->resetWinsDeath();
}

void Player::StartBattle(Player* opponent, bool goFirst){
    startedBattle = true;
    CheckEffects(TRIGGER_BATTLESTART, 0, nullptr, nullptr, opponent);
    opponent->CheckEffects(TRIGGER_BATTLESTART, 0, nullptr, nullptr, this);
    cout<<"Player "<<pID()<<" vs. Player"<<opponent->pID()<<endl;
    if(!interrupt && !opponent->interrupt){
        int choice = 0;
        bool hasBattleCards = false;
        for(int i = 0; i < hand.size(); i++){
            if(hand[i].canPlay(this)){
                hasBattleCards = true;
                return;
            }
        }
        if(hasBattleCards){
            choice = Choose(CardOrBattle);
            if(choice == 0){
                PlayCard(PickCardFromHand(), opponent, nullptr);
            }
        }
        hasBattleCards = false;
        for(int i = 0; i < opponent->hand.size(); i++){
            if(opponent->hand[i].canPlay(this)){
                hasBattleCards = true;
                return;
            }
        }
        if(hasBattleCards){
            choice = opponent->Choose(CardOrBattle);
            if(choice == 0){
                PlayCard(PickCardFromHand(), opponent, nullptr);
            }
        }

        if(Alive() && opponent->Alive()){
            int rounds = battleRounds;
            bool myTurn = goFirst;
            bool battleWon = false;
            int prevHP = 0;
            int postHP = 0;
            int damageRoll = 0;
            PlayerChoice deforevdPicker = DefEvd;
            cout<<"P"<<pID()<<" Stats: Atk = "<<Atk()<<", Def = "<<Def()<<", Evd = "<<Evd()<<". Current HP:"<<CurHP()<<". Stars dropped on loss: "<<Stars() * starsLostOnKOMult;
            cout<<"P"<<opponent->pID()<<" Stats: Atk = "<<opponent->Atk()<<", Def = "<<opponent->Def()<<", Evd = "<<opponent->Evd()<<". Current HP:"<<opponent->CurHP()<<". Stars dropped on loss: "<<opponent->Stars() * opponent->starsLostOnKOMult;
            while(rounds > 0 && !battleWon){
                CheckEffects(TRIGGER_BATTLEROUNDSTART, 0, nullptr, nullptr, opponent);
                if(myTurn){
                    if(combatActions[0]){
                        prevHP = opponent->CurHP();
                        damageRoll = Roll() + Atk();
                        cout<<"Outgoing roll: "<<damageRoll<<endl;
                        deforevdPicker.validChoices[0] = opponent->combatActions[1];
                        deforevdPicker.validChoices[1] = opponent->combatActions[2];
                        choice = opponent->Choose(deforevdPicker);
                        if(choice == 0){
                            opponent->Hurt(max(1, damageRoll - (opponent->Roll() + opponent->Def())));
                        }
                        if(choice == 1){
                            if((opponent->Roll() + opponent->Evd()) <= damageRoll) opponent->Hurt(damageRoll);
                        }
                        postHP = CurHP();

                        cout<<prevHP - postHP<<" damage! Current P"<<opponent->pID()<<" HP: "<<opponent->CurHP()<<endl;
                        if(!opponent->Alive()){
                            battleWon = true;
                            WinBattle(opponent);
                        }
                    }
                    myTurn = false;
                } else{
                    if(combatActions[1] && opponent->combatActions[0]|| combatActions[2] && opponent->combatActions[0]){
                        prevHP = CurHP();
                        damageRoll = opponent->Roll() + opponent->Atk();
                        cout<<"Incoming roll: "<<damageRoll<<endl;
                        deforevdPicker.validChoices[0] = combatActions[1];
                        deforevdPicker.validChoices[1] = combatActions[2];
                        choice = Choose(deforevdPicker);
                        if(choice == 0){
                            Hurt(max(1, damageRoll - (Roll() + Def())));
                        }
                        if(choice == 1){
                            if((Roll() + Evd()) <= damageRoll) Hurt(damageRoll);
                        }
                        postHP = CurHP();
                        cout<<prevHP - postHP<<" damage! Current P"<<pID()<<" HP: "<<opponent->CurHP()<<endl;
                        if(!Alive()){
                            cout<<"P"<<pID()<<" lost!"<<endl;
                            battleWon = true;
                            opponent->WinBattle(this);
                        }
                    }
                    myTurn = true;
                }
            }
        }
    }
    interrupt = false;
    opponent->interrupt = false;
    combatActions[0] = true;
    combatActions[1] = true;
    combatActions[2] = true;
    opponent->combatActions[0] = true;
    opponent->combatActions[1] = true;
    opponent->combatActions[2] = true;
    tempStatMods[0] = 0;
    tempStatMods[1] = 0;
    tempStatMods[2] = 0;
    tempStatMods[3] = 0;
    opponent->tempStatMods[0] = 0;
    opponent->tempStatMods[1] = 0;
    opponent->tempStatMods[2] = 0;
    opponent->tempStatMods[3] = 0;
    startedBattle = false;
    battleRounds = 2;
}

void Player::StartBattle(EUnit* opponent, bool goFirst){
    startedBattle = true;
    CheckEffects(TRIGGER_BATTLESTART, 0, nullptr, opponent);
    cout<<"Player "<<pID()<<" vs. "<<opponent->Name()<<endl;
    if(!interrupt){
        int choice = 0;
        bool hasBattleCards = false;
        for(int i = 0; i < hand.size(); i++){
            if(hand[i].canPlay(this)){
                hasBattleCards = true;
                return;
            }
        }
        if(hasBattleCards){
            choice = Choose(CardOrBattle);
            if(choice == 0){
                PlayCard(PickCardFromHand(), nullptr, opponent);
            }
        }
        if(Alive() && opponent->Alive()){
            int rounds = battleRounds;
            bool myTurn = goFirst;
            bool battleWon = false;
            int prevHP = 0;
            int postHP = 0;
            int damageRoll = 0;
            PlayerChoice deforevdPicker = DefEvd;
            cout<<"P"<<pID()<<" Stats: Atk = "<<Atk()<<", Def = "<<Def()<<", Evd = "<<Evd()<<". Current HP:"<<CurHP()<<". Stars dropped on loss: "<<Stars() * starsLostOnKOMult;
            cout<<opponent->Name()<<" Stats: Atk = "<<opponent->Atk()<<", Def = "<<opponent->Def()<<", Evd = "<<opponent->Evd()<<". Current HP:"<<opponent->CurHP()<<". Stars dropped on loss: "<<opponent->Stars();
            while(rounds > 0 && !battleWon){
                CheckEffects(TRIGGER_BATTLEROUNDSTART, 0, nullptr, opponent);
                if(myTurn){
                    if(combatActions[0]){
                        prevHP = opponent->CurHP();
                        cout<<"Player "<<pID()<<"'s attack!"<<endl;
                        opponent->BattleRoll(false, Roll() + Atk());
                        postHP = opponent->CurHP();
                        cout<<prevHP - postHP<<" damage! Current "<<opponent->Name()<<" HP: "<<opponent->CurHP()<<endl;
                        if(!opponent->Alive()){
                            battleWon = true;
                            WinBattle(opponent);
                        }
                    }
                    myTurn = false;
                } else{
                    if(combatActions[1] || combatActions[2]){
                        prevHP = CurHP();
                        damageRoll = opponent->BattleRoll(true);
                        cout<<"Incoming roll: "<<damageRoll<<endl;
                        deforevdPicker.validChoices[0] = combatActions[1];
                        deforevdPicker.validChoices[1] = combatActions[2];
                        choice = Choose(deforevdPicker);
                        if(choice == 0){
                            Hurt(max(1, damageRoll - (Roll() + Def())));
                        }
                        if(choice == 1){
                            if((Roll() + Evd()) <= damageRoll) Hurt(damageRoll);
                        }
                        postHP = CurHP();
                        cout<<prevHP - postHP<<" damage! Current P"<<pID()<<" HP: "<<opponent->CurHP()<<endl;
                        if(!Alive()){
                            cout<<"P"<<pID()<<" lost!"<<endl;
                            battleWon = true;
                            CheckEffects(TRIGGER_BATTLELOSE, 0, nullptr, opponent);
                            if(!interrupt){
                                opponent->WinBattle(this);
                            }
                            interrupt = false;
                        }
                    }
                    myTurn = true;
                }
            }
        }
    }
    interrupt = false;
    combatActions[0] = true;
    combatActions[1] = true;
    combatActions[2] = true;
    opponent->setCombatRestrictions({true, true, true});
    tempStatMods[0] = 0;
    tempStatMods[1] = 0;
    tempStatMods[2] = 0;
    tempStatMods[3] = 0;
    opponent->ResetStatMods();
    startedBattle = false;
    battleRounds = 1;
}
void Player::WinBattle(Player* opponent){
    CheckEffects(TRIGGER_BATTLEWIN, 0, nullptr, nullptr, opponent);
    opponent->CheckEffects(TRIGGER_BATTLELOSE, 0, nullptr, nullptr, this);
    if(!interrupt && !opponent->interrupt){
        int KOStars = opponent->Stars() * opponent->KOStarsMult();
        ResetKOStars();
        opponent->ResetKOStars();
        AddStars(KOStars);
        opponent->LoseStars(KOStars);
        AddWins(opponent->WinsOnDeath());
        resetWinsDeath();
        opponent->resetWinsDeath();
    }
    interrupt = false;
    opponent->interrupt = false;
}//14
void Player::WinBattle(EUnit* opponent){
    CheckEffects(TRIGGER_BATTLEWIN, 0, nullptr, opponent);
    if(!interrupt){
        ResetKOStars();
        resetWinsDeath();
        AddStars(opponent->Stars());
        AddWins(1);
        opponent->KO();
        if(opponent->IsBoss()){
            GetBoard()->killBoss();
        }
    }
    interrupt = false;
}//14

void Player::Revive(){
    if(!Alive()){
        CheckEffects(TRIGGER_REVIVE);
        if(!interrupt && alive){
            tempStatMods[4] = 0;
            curHP = MaxHP();
            alive = true;
            revRolls = 0;
        }
    }
    interrupt = false;
}

bool Player::NormaCheck(){
    switch(goalType){
        case GOAL_STARS:
            if (Stars() >= goal) return true;
            break;
        case GOAL_WINS:
            if (Wins() >= goal) return true;
    }
    return false;
}

void Player::RollToMove(){
    int moveRoll = Roll();
    CheckEffects(TRIGGER_MOVEROLL, moveRoll += Mov());
    moveRoll += Mov();
    if(!interrupt){
        vector<Tile*> destinations = { CurrTile() };
        vector<Tile*> newDestinations = {};
        vector<Tile*> fightDestinations = {};
        vector<Player*> playersFightDestinations = {};
        vector<Tile*> stopDestinations = {};
        int rollTemp = moveRoll;
        int xposTemp = 0;
        int yposTemp = 0;
        bool wayOut = false;
        while(rollTemp > 0){
            for(int i = 0; i = destinations.size(); i++){
                wayOut = false;
                xposTemp = destinations[i]->xPos;
                yposTemp = destinations[i]->yPos;
                if(destinations[i]->movesNWSE[0]){ //north
                    yposTemp = yposTemp - 1;
                    if(board->tileAt(xposTemp, yposTemp)){
                        newDestinations.push_back(board->tileAt(xposTemp, yposTemp));
                    }
                    wayOut = true;
                    yposTemp = yposTemp + 1;
                }
                if(destinations[i]->movesNWSE[1]){ //west
                    xposTemp = xposTemp + 1;
                    if(board->tileAt(xposTemp, yposTemp)){
                        newDestinations.push_back(board->tileAt(xposTemp, yposTemp));
                    }
                    wayOut = true;
                    xposTemp = xposTemp - 1;
                }
                if(destinations[i]->movesNWSE[2]){ //south
                    yposTemp = yposTemp + 1;
                    if(board->tileAt(xposTemp, yposTemp)){
                        newDestinations.push_back(board->tileAt(xposTemp, yposTemp));
                    }
                    wayOut = true;
                    yposTemp = yposTemp - 1;
                }
                if(destinations[i]->movesNWSE[3]){ //east
                    xposTemp = xposTemp - 1;
                    if(board->tileAt(xposTemp, yposTemp)){
                        newDestinations.push_back(board->tileAt(xposTemp, yposTemp));
                    }
                    wayOut = true;
                    xposTemp = xposTemp - 1;
                }
                if(!wayOut) newDestinations.push_back(destinations[i]);
                if(destinations[i]->type == TILE_HOME && destinations[i]->homeID == pID()) stopDestinations.push_back(destinations[i]);
                for(int i = 0; i < 4; i++){
                    if(xposTemp == allPlayers[i]->XPos() && yposTemp == allPlayers[i]->YPos()){
                        fightDestinations.push_back(destinations[i]);
                        playersFightDestinations.push_back(allPlayers[i]);
                    }
                }
            }
            destinations = newDestinations;
            newDestinations = {};
            rollTemp--;
        }
        for(int i = 0; i < stopDestinations.size(); i++){
            destinations.push_back(stopDestinations[i]);
        }
        if(destinations.size() + fightDestinations.size() > 1){
            //dummy
        } else{
            currTile = destinations[0];
        }
        currTile->landOn(this);
    }
    interrupt = false;
}

void Player::warpTo(Tile* warpTo){ //we explicitly dont trigger landing effects here
    CheckEffects(TRIGGER_WARP, 0, warpTo);
    if(!interrupt){
        currTile = warpTo;
    }
    interrupt = false;
}