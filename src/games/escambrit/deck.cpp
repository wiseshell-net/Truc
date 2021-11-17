#include "headers/deck.h"
#include <iostream>
#include <algorithm>
#include <assert.h>

// Shuffles a deck
void Deck::shuffleDeck() {
    std::random_shuffle(deck.begin(), deck.end());
}

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
        for(int j=0;j<12;j++){
            Card c(j+1,suits[i]);
            deck.push_back(c);
        }
    }
    shuffleDeck();
}

// Getter Function for size of deck
int Deck::getSize(){
    return deck.size();
}

// Deals by returning one card from the deck
Card Deck::deal(){
    int val = (rand()%(deck.size())); // TODO: Why shuffle again if the deck is initialized and shuffled? Can you choose any card at your will?
    Card t = deck[val];
    deck.erase(deck.begin()+val);
    return t;
}

// Pick a number of cards (default is 1) from the deck (the first one)
Card* Deck::pick(short number=1){
    short val = number;
    Card cards[number-1];
    
    // Test that the number is 1 or more
    assert(number>=1);
    for(short i=0;i<number;i++){
        Card card = deck[0];
        cards[i] = card;
        deck.erase(deck.begin()+val);
    }
    return cards;
}
