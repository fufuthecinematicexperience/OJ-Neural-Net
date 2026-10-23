#include "ojDefs.h"
#include "ojCards.h"
#include <random>
namespace { //so other files don't break
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> pIDRand(1, 4);
    uniform_int_distribution<int> airStrikeRand(1, 3);
}

void DashEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_TURNEND:
                Deplete();
                break;
            case TRIGGER_MOVEROLL:
                effOwner->AddDice(1);
                break;
        }
    }

void CrystEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_LAND:
                if(effOwner->CurrTile()->trapped){
                    effOwner->CurrTile()->trapClear();
                    Deplete();
                }
                break;
        }
    }

void ExtendEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_TURNSTART:
                if(!effOwner->Alive()){
                    effOwner->Revive();
                    Deplete();
                }
                break;
        }
    }

void LittleWarEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_BATTLESTART:
                effOwner->SetRounds(4);
                break;
            case TRIGGER_TURNEND:
                Deplete();
                break;
        }
    }

void HyperEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_TURNSTART:
                if(!effOwner->Alive()){
                    effOwner->Revive();
                }
                Deplete();
                break;
            case TRIGGER_BATTLEDRAW:
            case TRIGGER_BATTLEWIN:
                Deplete();
                break;
            case TRIGGER_BATTLELOSE:
                effOwner->skipAction();
                break;
        }
    }

void BoundEff1::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_TURNSTART:
                effOwner->skipAction();
                break;
            case TRIGGER_BATTLESTART:
                effOwner->AddStatMods({0, 0, 0, -2, 0, 0, 0});
                break;
            case TRIGGER_TURNEND:
                Deplete();
                break;
        }
    }

void BoundEff1::OnLose(Player* effOwner){
    effOwner->AddEffect(BoundEff2());
}

void BoundEff2::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_BATTLESTART:
                effOwner->AddStatMods({0, 0, 0, -2, 0, 0, 0});
                break;
            case TRIGGER_TURNEND:
                Deplete();
                break;
        }
    }

void DangerousPuddingEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_TURNSTART:
                effOwner->skipAction();
                break;
            case TRIGGER_TURNEND:
                Deplete();
                break;
        }
    }



void OutOfAmmoEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_PLAYCARD:
                    effOwner->skipAction();
                break;
            default:
                if(effOwner->GetBoard()->chapter > (turnstarted+1) || effOwner->GetBoard()->chapter > turnstarted && effOwner->pID() > pidstarted){
                    Deplete();
                }
                break;
        }
    } //technically, Little War should have a similar implementation to its effect, probably on turn end rather than default,
//but in a practical sense, the way this card is usually played around means this one kind of matters more
//and also, it's annoying to set up, so I would rather do it like this only if i have to,
//which in this case, i do.
//Ideally I should implement global effects that affect every player
//(this would theoretically allow the addition of Banner cards)
//but I don't really want to do that for two cards

void JingleEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_LAND:
                if(optTile != nullptr && optTile->type == TILE_BONUS){
                    effOwner->SetAddStarsMult(2);
                    Deplete();
                }
                break;
        }
    }

void FlipEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_LAND:
                if(optTile != nullptr && optTile->type == TILE_DROP){
                    int ownerRoll = effOwner->Roll();
                    int mostStars = -1;
                    int mostStarsPID = 1;
                    for(int i = 1; i < 5; i++){
                        Player* curPlayerCheck = effOwner->GetPlayers(i);
                        if(effOwner->pID() != curPlayerCheck->pID() && curPlayerCheck->Stars() > mostStars){
                            mostStars = curPlayerCheck->Stars();
                            mostStarsPID = curPlayerCheck->pID();
                        }
                    }
                    effOwner->LoseStars(optTile->DropFormula(ownerRoll, effOwner));
                    effOwner->GetPlayers(mostStarsPID)->LoseStars(optTile->DropFormula(ownerRoll, effOwner));
                    effOwner->skipAction();
                    Deplete();
                }
                break;
        }
    }

void ProtagEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_BATTLESTART:
                roundsThisFight = 0;
                break;
            case TRIGGER_BATTLEROUNDSTART:
                if(effOwner->StartedBattle()){
                    if(roundsThisFight = 0){
                        if(optPlyr != nullptr){
                            optPlyr->CombatRestrict({true, false, false}, {false, false, false});
                        }
                        if(optEnemy != nullptr){
                            optEnemy->setCombatRestrictions({true, false, false});
                        }
                    }
                    if(roundsThisFight = 3){
                        if(optPlyr != nullptr){
                            optPlyr->CombatRestrict({false, false, false}, {true, false, false});
                        }
                        if(optEnemy != nullptr){
                            optEnemy->setCombatRestrictions({false, false, false});
                        }
                    }
                    roundsThisFight++;
                }
                break;
            case TRIGGER_TURNEND:
                Deplete();
                break;
        }
    }

void AccelEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_TURNSTART:
                Deplete();
                break;
        }
    }

void AccelEff::OnApply(Player* owner){
    owner->AddDice(1, true);
}

void AccelEff::OnLose(Player* owner){
    owner->LoseDice(1, false);
}

void SpecsEff::OnApply(Player* effOwner){
        effOwner->SetDiceType(DICE_SPECS);
    }

void SpecsEff::OnLose(Player* effOwner){
        effOwner->SetDiceType(DICE_NORMAL);
    }

void SpecsEff::Enact(Player* effOwner, int triggerID, int optionalNum, Tile* optTile, EUnit* optEnemy, Player* optPlyr, Card optCard){
        switch(triggerID){
            case TRIGGER_TURNEND:
                Deplete();
        }
    }

void Dash::playCard(Player* owner){
    owner->LoseStars(cost);
    owner->AddEffect(DashEff());
}

void Cookie::playCard(Player* owner){
    owner->LoseStars(cost);
    owner->Heal(1);
}

void Pudding::playCard(Player* owner){
    owner->LoseStars(cost);
            owner->SetHP(owner->MaxHP());
        }

void NicePresent::playCard(Player* owner){
            owner->LoseStars(cost);
            owner->Draw();
            owner->Draw();
        }

void Jingle::playCard(Player* owner){
            owner->LoseStars(cost);
            owner->AddEffect(JingleEff());
        }

void Flip::playCard(Player* owner){
    owner->LoseStars(cost);
            owner->AddEffect(FlipEff());
}

void Shot::playCard(Player* owner){
            Player* target = owner->choosePlayer();
            if(target != nullptr){
                owner->LoseStars(cost);
                owner->choosePlayer()->Hurt(1);
            }
            else{
                owner->skipAction();
            }
}

void Extend::playCard(Player* owner){
            owner->LoseStars(cost);
            owner->AddEffect(ExtendEff());
        }

void StiffCrystal::playCard(Player* owner){
            owner->LoseStars(cost);
            owner->AddEffect(CrystEff());
        }

bool Princess::typePlayable(Player* owner){
            if(owner->Hand()->size() == 1 || owner->Hand()->size() >= 3){
                return !owner->Battling();
            }
            return false;
        }

void  Princess::playCard(Player* owner){
            owner->LoseStars(cost);
            for(int i = 0; i < owner->Hand()->size(); i ++){
                owner->DisCard(0);
            }
            owner->Draw();
            owner->Draw();
            owner->Draw();
        }

void Protagonist::playCard(Player* owner){
            owner->LoseStars(cost);
            owner->AddEffect(ProtagEff());
        }

void Ubiquitous::playCard(Player* owner){
    Player* target = owner->choosePlayer(false);
    
    int starSteals = target->Norma() * 10;
    owner->warpTo(target->CurrTile());
    owner->AddStars(min(starSteals - (starSteals - target->Stars()), starSteals));
    target->LoseStars(starSteals);
    }

void Accelerator::playCard(Player* owner){
            owner->LoseStars(cost);
            owner->AddEffect(AccelEff());
        }


bool X16::typePlayable(Player* owner){
            return (owner->Stars() >= owner->Norma() * 10 && !owner->Battling());
        }

void X16::playCard(Player* owner){
            Player* target = owner->choosePlayer();
            if(target != nullptr){
                cost = owner->Norma() * 10;
                owner->LoseStars(cost);
                target->Hurt(owner->Norma());
                if(!target->Alive()) owner->AddWins(2);
            }
            else{
                owner->skipAction();
            }
        }



void AirStrike::playCard(Player* owner){
            owner->LoseStars(cost);
			for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				if(curPlayerCheck->Alive() && curPlayerCheck->pID() != owner->pID()){
					curPlayerCheck->Hurt(airStrikeRand(mt));
					if(!curPlayerCheck->Alive()){
						owner->AddStars(15);
					}
				}
			}
        }


void Gamble::playCard(Player* owner){
            owner->LoseStars(cost);
            int targID = pIDRand(mt);
			owner->GetPlayers(targID)->KO();
        }


void PresentForYou::playCard(Player* owner){
        owner->LoseStars(cost);
        int cardsDrawn = 0;
			for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				if(curPlayerCheck->Hand()->size() >= curPlayerCheck->HandSize()){
                    curPlayerCheck->Draw();
                    cardsDrawn++;
                } else {
                    while(curPlayerCheck->Hand()->size() < curPlayerCheck->HandSize()){
                    curPlayerCheck->Draw();
                    cardsDrawn++;
                    }
                }
			}
        owner->AddStars(cardsDrawn * 10);
    }


void Chains::playCard(Player* owner){
    owner->LoseStars(cost);
    for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				if(curPlayerCheck->Alive() && curPlayerCheck->pID() != owner->pID()){
					curPlayerCheck->AddEffect(BoundEff1());
				}
			}
}


void Specs::playCard(Player* owner){
            owner->LoseStars(cost);
            owner->AddEffect(SpecsEff());
        }



void MagicalMassacre::playCard(Player* owner){
            owner->LoseStars(cost);
			for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				if(curPlayerCheck->Alive() && curPlayerCheck->CurHP() >= curPlayerCheck->MaxHP()){
					curPlayerCheck->KO();
					if(curPlayerCheck->pID() != owner->pID()){
						owner->AddStatMods({0,0,0,0,1,0,0});
					}
				}
			}
        }

void BlueCrow::playCard(Player* owner, Player* opp, EUnit* npcOp){
            owner->LoseStars(cost);
            int CardsInHand = owner->Hand()->size();
			owner->AddStatMods({0, CardsInHand, CardsInHand, -1 * CardsInHand,0,0,0});
        }


void HyperMode::playCard(Player* owner, Player* opp, EUnit* npcOp){
            owner->LoseStars(cost);
            owner->AddStatMods({0, 3, 0, 0, 0, 0, 0});
            owner->AddEffect(HyperEff());
        }


void HereAndThere::playCard(Player* owner){
            owner->LoseStars(cost);
            uniform_int_distribution<int> boardTileRand (1, owner->GetBoard()->tiles.size());
            for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				curPlayerCheck->warpTo(&owner->GetBoard()->tiles[boardTileRand(mt)]);
			}
        }


void OutOfAmmo::playCard(Player* owner){
            owner->LoseStars(cost);
            for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				curPlayerCheck->AddEffect(OutOfAmmoEff(owner->pID(), owner->GetBoard()->chapter));
			}
        }


void GiftExchange::playCard(Player* owner){ //dummy
            owner->LoseStars(cost);
        }


void LittleWar::playCard(Player* owner){
            owner->LoseStars(cost);
            for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				curPlayerCheck->AddEffect(LittleWarEff());
			}
        }

void HolyNight::playCard(Player* owner){ //funnily enough i don't need a proper effect for this
            owner->LoseStars(cost);
			owner->GetBoard()->extraStars = owner->GetBoard()->extraStars + 1;
}

void AllOutMode::playCard(Player* owner){ //funnily enough i don't need a proper effect for this
            owner->LoseStars(cost);
			for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				curPlayerCheck->AddStatMods({0,2,0,0,0,0,0});
			} //i "should" make a proper effect so it displays better...
} //but if it's gonna be a neural network doing this I dont think it would care


void Dinner::playCard(Player* owner){
            owner->LoseStars(cost);
			for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				if(curPlayerCheck->Alive()) curPlayerCheck->Heal(3);
			}
        }


void Seagulls::playCard(Player* owner){
            owner->LoseStars(cost);
            int targID = pIDRand(mt);
			owner->GetPlayers(targID)->Hurt(2);
        }

void SealedGuardian::playCard(Player* owner){
            owner->LoseStars(cost);
			for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				if(curPlayerCheck->Alive()) curPlayerCheck->SetHP(1);
			}
        }

void OhMyFriend::playCard(Player* owner){
            owner->LoseStars(cost);
			owner->GetBoard()->summonBoss();
        }


void ForcedRevival::playCard(Player* owner){
            owner->LoseStars(cost);
			for(int i = 1; i < 5; i++){
				Player* curPlayerCheck = owner->GetPlayers(i);
				if(!curPlayerCheck->Alive()) {
                    curPlayerCheck->Revive();
                    curPlayerCheck->SetHP(1);
			}
        }
}


void RainbowColoredCircle::playCard(Player* owner, Player* opp, EUnit* npcOp){
            owner->LoseStars(cost);
			owner->AddStatMods({0, 0, -1, 2, 0, 0, 0});
        }


void Rbits::playCard(Player* owner, Player* opp, EUnit* npcOpp){
            owner->LoseStars(cost);
			owner->AddStatMods({0, 0, 2, 0, 0, 0, 0});
            owner->CombatRestrict({false, false, true}, {false, false, false});
        }


void ImOnFire::playCard(Player* owner, Player* opp, EUnit* npcOpp){
            owner->LoseStars(cost);
			owner->AddStatMods({0, 1, -1, 0, 0, 0, 0});
        }


void FinalBattle::playCard(Player* owner, Player* opp, EUnit* npcOpp){
            owner->LoseStars(cost);
            owner->SetRounds(20);
        }


void ReverseAttributeField::playCard(Player* owner, Player* opp, EUnit* npcOpp){ //dummy
            owner->LoseStars(cost);
            if(opp != nullptr){
                opp->AddStatMods({0, -2 * opp->Atk(), -2 * opp->Def(), -2 * opp->Evd(), 0, 0, 0});
            }
            if(npcOpp != nullptr){
                npcOpp->AddStatMods({0, -2 * npcOpp->Atk(), -2 * npcOpp->Def(), -2 * npcOpp->Evd()});
            }
            owner->AddStatMods({0, -2 * owner->Atk(), -2 * owner->Def(), -2 * owner->Evd(), 0, 0, 0});
        }


void BigMagnum::playCard(Player* owner, Player* opp, EUnit* npcOpp){
            owner->LoseStars(cost);
			owner->AddStatMods({0, 2, 0, 0, 0, 0, 0});
            owner->Hurt(2);
        }

bool Shield::typePlayable(Player* owner){
    return owner->Battling() && !owner->StartedBattle();
}

void Shield::playCard(Player* owner, Player* opp, EUnit* npcOpp){
            owner->LoseStars(cost);
			owner->AddStatMods({0, 0, 3, 0, 0, 0, 0});
        }

void PiggyBank::playCard(Player* owner){
    chapSet = owner->GetBoard()->chapter;
    owner->LoseStars(cost);
    owner->CurrTile()->trapSet(this); //kinda weird but lets me bypass having to give every single trap a setter function
}

void PiggyBank::landedOn(Player* poorSoul, Tile* myTile){
    poorSoul->AddStars(5*(setter->GetBoard()->chapter - chapSet));
}

bool ForTheFutureOfTheToyStore::typePlayable(Player* owner){
    return owner->Battling() && owner->Stars() < 50;
}

void ForTheFutureOfTheToyStore::landedOn(Player* poorSoul, Tile* myTile){
    poorSoul->LoseStars(poorSoul->Stars() / 2);
}

void Assault::landedOn(Player* poorSoul, Tile* myTile){
    setter->StartBattle(poorSoul);
}

void MimyuusHammer::landedOn(Player* poorSoul, Tile* myTile){
    poorSoul->Hurt(1);
}


void BadPudding::landedOn(Player* poorSoul, Tile* myTile){
    uniform_int_distribution<int> handRand (0, poorSoul->Hand()->size() - 1);
    poorSoul->DisCard(handRand(mt));
}


void DangerousPudding::landedOn(Player* poorSoul, Tile* myTile){
    poorSoul->AddEffect(DangerousPuddingEff());
}


void SkyRestaurantPures::landedOn(Player* poorSoul, Tile* myTile){
    poorSoul->LoseStars(poorSoul->Stars() / 2);
}


void Invasion::landedOn(Player* poorSoul, Tile* myTile){
    poorSoul->StartBattle(myTile->fightTileEnemy(), false);
}


void GoAway::landedOn(Player* poorSoul, Tile* myTile){
            uniform_int_distribution<int> boardTileRand (1, poorSoul->GetBoard()->tiles.size());
			poorSoul->warpTo(&poorSoul->GetBoard()->tiles[boardTileRand(mt)]);
        }


void Heat300::landedOn(Player* poorSoul, Tile* myTile){
    poorSoul->AddStatMods({0, 0, -2, 0, 0, 0, 0});
}


void TragedyInTheDeadOfNight::landedOn(Player* poorSoul, Tile* myTile){
    uniform_int_distribution<int> handRand (0, poorSoul->Hand()->size() - 1);
    int posToSteal = handRand(mt);
    setter->AddCard((*poorSoul->Hand())[posToSteal]);
    poorSoul->DisCard(posToSteal);
}


void Exchange::landedOn(Player* poorSoul, Tile* myTile){
    int setterStars = setter->Stars();
    int poorSoulStars = poorSoul->Stars();
    setter->LoseStars(setterStars);
    poorSoul->LoseStars(poorSoulStars);
    setter->AddStars(poorSoulStars);
    poorSoul->AddStars(setterStars);
    // ^ star swap
    Tile* setterTile = setter->CurrTile();
    setter->warpTo(poorSoul->CurrTile());
    poorSoul->warpTo(setterTile);
    //^ tile swap
    vector<Card> setterHand = *setter->Hand();
    vector<Card> poorSoulHand = *poorSoul->Hand();
    for(int i = 0; i < poorSoul->Hand()->size(); i++){
        poorSoul->DisCard(0);
    }
    for(int i = 0; i < setter->Hand()->size(); i++){
        setter->DisCard(0);
    }
    for(int i = 0; i < poorSoulHand.size(); i++){
        setter->AddCard(poorSoulHand[i]);
    }
    for(int i = 0; i < setterHand.size(); i++){
        poorSoul->AddCard(setterHand[i]);
    }
    //^ hand swap
}


void Flamethrower::landedOn(Player* poorSoul, Tile* myTile){
    if(poorSoul->Hand()->size() >= 1){
        for(int i = 0; i < poorSoul->Hand()->size(); i++){
            poorSoul->DisCard(0);
        }
    } else{
        poorSoul->KO();
    }
}
