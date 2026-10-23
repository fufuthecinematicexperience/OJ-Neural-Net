#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <array>
#include "ojDefs.h"
#include "ojCards.h"
#include "ojBoards.h"
#include <numeric>

using namespace std;

vector<Card> deckableCardList = {Dash(),Cookie(),Pudding(),NicePresent(),Jingle(),Flip(),Shot(),Extend(),StiffCrystal(),HereAndThere(),
    OutOfAmmo(),GiftExchange(),LittleWar(),HolyNight(),AllOutMode(),Dinner(),Seagulls(),SealedGuardian(), OhMyFriend(), ForcedRevival(), RainbowColoredCircle(),
    Rbits(), ImOnFire(), FinalBattle(), ReverseAttributeField(), BigMagnum(), Shield(), Assault(), MimyuusHammer(), BadPudding(),
    DangerousPudding(), SkyRestaurantPures(), PiggyBank(), Invasion(), GoAway(), Heat300(), TragedyInTheDeadOfNight(), Exchange(), Flamethrower(), ForTheFutureOfTheToyStore()};
    //we skip over hypers because they should never be in the main deck
    //it's kinda weird how the 2009 release's card distribution is skewed, looking at this in full
    //like a third of the cards here are traps, which are... generally the least useful card type
    //battle cards and boost cards, which are nowadays the most common and generally the most useful, are the smallest categories here
    //a distribution skewed against the better card types makes this game seem like it was intended to be lower-power than it is now,
    //though that's somewhat moot because you're expected to choose your own deck, so you can stuff it with these strong cards anyways,
    //and i'd argue the game is more skill-based with stronger cards.
    //testing skill shouldn't be too hard (I want a performance assesment like "can the neural network consistently outperform the random choice picker?")
    //but it might be better to have a more updated card list.
    //however that would suuuuuuuuuuuuuuuuuuuuuuuuuuck to implement so I'm not doing it right now

PuddingChase boardPudding;

namespace { //so other files don't break
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> deckableCardRand(0, deckableCardList.size()-1);
}


vector<Card> RandomCardDeck(){
    vector<int> cardsAddedCount(deckableCardList.size());
    vector<Card> randomCardVecs(40);
    int intRand = 0;
    for(int i = 0; i < 4; i++){ //the final deck is a jumble of all four players' deck, so we generate each player deck one by one
        cardsAddedCount = vector<int>(deckableCardList.size()); //reset card max restriction
        for(int j = 0; j < 10; j++){ //specific player deck contents
            intRand = deckableCardRand(mt);
            while(cardsAddedCount[intRand] >= deckableCardList[intRand].Max()){ //check max, pick another random card
                intRand = deckableCardRand(mt);
            }
            randomCardVecs[(i*10) + j] = deckableCardList[intRand];
        }
    }
    return randomCardVecs;
}

//

void mainPrintBoard(const Board& inpBoard){
    array<vector<string>, 3> printArr = {{{}, {}, {}}};
    int yPosChecker = 0;
    vector<Tile> boardTiles = inpBoard.tiles;
    cout<<boardTiles[0].type;
    for(int i = 0; i < inpBoard.tiles.size(); i++){
        if(boardTiles[i].yPos > yPosChecker){
            cout<<reduce(printArr[0].begin(), printArr[0].end())<<endl<<reduce(printArr[1].begin(), printArr[1].end())<<endl<<reduce(printArr[2].begin(), printArr[2].end())<<endl;
            yPosChecker = boardTiles[i].yPos;
            printArr = {{{}, {}, {}}};
        }
        if(boardTiles[i].type == TILE_BLANK){
            printArr[0].push_back("     ");
            printArr[1].push_back("     ");
            printArr[2].push_back("     ");
        } else{
            printArr[0].push_back("-----");
            printArr[1].push_back("|   |");
            printArr[2].push_back("-----");
        }
    }
}

int main(){
    mainPrintBoard(boardPudding);
    return 0;
}