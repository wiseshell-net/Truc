#include "headers/deck.h"
#include <iostream>
#include <algorithm>

// Constructs a Deck
/*
 * O: Oros;
 * E: Espases;
 * B: Bastos;
 * C: Copes;
 */
void Deck::initializeDeck(){
    deck.clear();
    char suits[4] = {'O','E','B','C'};
    for(int i=0;i<4;i++){
        for(int j=0;j<13;j++){
            Card c(j+1,suits[i]);
            deck.push_back(c);
        }
    }
    std::random_shuffle(deck.begin(), deck.end());
}

// Getter Function for size of deck
int Deck::getSize(){
    return deck.size();
}

// Deals by returning one card from the deck
Card Deck::deal(){
    int val = (rand()%(deck.size()));
    Card t = deck[val];
    deck.erase(deck.begin()+val);
    return t;
}
