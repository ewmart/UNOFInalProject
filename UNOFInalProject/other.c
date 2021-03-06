//
//  other.c
//  UNOFInalProject
//
//  Created by Evan Martin & Brian Bedrosian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "other.h"

//input: the static deck array
//populate the deck array with cards (alternative to loading from file)
void generateDeck(card deck[])
{
    card *pt;
    
    int i = 0;
    for (int s = 0; s < 4; s++)
    {
        for(int n = 0; n < 15; n++)
        {
            pt = &deck[i];
            pt->value = n;
            switch (s) {
                case 0:
                    strcpy(pt->color, "♠");
                    break;
                    
                case 1:
                    strcpy(pt->color, "♥");
                    break;
                    
                case 2:
                    strcpy(pt->color, "♣");
                    break;
                    
                default:
                    strcpy(pt->color, "♦");
                    break;
            }
            i++;
        }
        for(int n = 1; n < 13; n++)
        {
            pt = &deck[i];
            pt->value = n;
            switch (s) {
                case 0:
                    strcpy(pt->color, "♠");
                    break;
                    
                case 1:
                    strcpy(pt->color, "♥");
                    break;
                    
                case 2:
                    strcpy(pt->color, "♣");
                    break;
                    
                default:
                    strcpy(pt->color, "♦");
                    break;
            }
            i++;
        }
    }
}

//function to shuffle an array
//input: the array and the number of undrawn cards left in the deck
void shuffle(card deck[], int numCards)
{
    card * pt;
    for (int i = 0; i < numCards * 10; i++)
    {
        int index1 = rand() % numCards;
        card temp = deck[index1];
        int index2 = rand() % numCards;
        pt = &deck[index1];
        *pt = deck[index2];
        pt = &deck[index2];
        *pt = temp;
    }
}

//function for the startup sequence
//input: 4 int pointers
void startSeq(int *loadType, int*players, int*gameVar, int *AIP)        //AIP = AI Player #
{

    printf("Let’s Play a Game of UNO\n");
    
    while(!(*players < 11 && 1 < *players))
    {
    printf("We can accomodate 2-10 players.\nHow many players are participating? ");
    scanf("%d", players);
        if (*players < 2 || 10 < *players)
        {
            printf("Sorry, please enter a valid number of players.\n");
        }
    }
    
    printf("What game variation would you like to play?\n");
    
    while(*gameVar < 1 || *gameVar > 3)
    {
    printf("Classic: 1\tProgressive: 2\tSeven-O: 3\nPlease enter a number to choose: ");
    scanf("%d", gameVar);
        if (*gameVar < 1 || *gameVar > 3)
        {
            printf("Sorry, that is not a valid game variation\n");
        }
    }
    
    switch (*gameVar) {
        case 2:
            printf("Progressive game mode was selected\n");
            break;
            
        case 3:
            printf("Seven-O game mode was selected\n");
            break;
            
        default:
            printf("Classic game mode was selected\n");
            break;
    }
    
    
    int AI = promptAI(*players);
    *AIP = AI-1;
    
    while(*loadType != 1 && *loadType != 2)
    {
    printf("Press 1 to shuffle the UNO deck or 2 to load a deck from a file: ");
    scanf("%d", loadType);
        if(*loadType != 1 && *loadType != 2)
        {
            printf("Sorry, that in not a valid selection.\n");
        }
    }
}

//function to load in a deck from file
//input: deck array and file name
bool readDeck(card deck[], char fileName[])
{
    FILE*inp;
    inp = fopen(fileName, "r");
    int cardNum = 0;
    card *pt;
    
    if(inp == NULL)
    {
        printf("File \"%s\" not found.\n", fileName);
        return false;
    }
    else{
        while (!feof(inp) && cardNum < 108)
        {
            pt = deck;
            char dump;
            fscanf(inp, "%d ", &pt[cardNum].value);
            fscanf(inp, "%s%c", pt[cardNum].color, &dump);
            cardNum++;
        }
    }
    return true;
}

//function to print a row of 5 cards in a player's hand
//inputs: the index numbers for card #1 and #5 in the row, an array of a player's hand
void printRow(int first, int last, card array[])
{
    for (int i = first; i <= last; i++)
    {
        printf("⠴⠖⠒⠲⠶⠶⠶⠶⠄\t");
    }
    printf("\n");
    
    //2
    for (int i = first; i <= last; i++)
    {
        switch (array[i].value) {
            case 13:
                printf("⠯ W ⠽⠿⠿⠿⠿\t");
                break;
                
            case 14:
                printf("⠯+4 ⠽⠿⠿⠿⠿\t");
                break;
                
            default:
                printf("⠯ %s ⠽⠿⠿⠿⠿\t", array[i].color);
                break;
        }
    }
    printf("\n");
    
    //3
    for (int i = first; i <= last; i++)
    {
        printf("⠿⠷⠖⠚⠛⠛⠻⠿⠇\t");
    }
    printf("\n");

    //4
    for (int i = first; i <= last; i++)
    {
        switch (array[i].value) {
            case 10:
                printf("⠿⠇SKIP ⠸⠿\t");
                break;
                
            case 11:
                printf("⠿⠇ REV ⠸⠿\t");
                break;
                
            case 12:
                printf("⠿⠇ +2  ⠸⠿\t");
                break;
                
            case 13:
                printf("⠿⠇WILD ⠸⠿\t");
                break;
                
            case 14:
                printf("⠿⠇ +4  ⠸⠿\t");
                break;
                
            default:
                printf("⠿⠇ %2d  ⠸⠿\t", array[i].value);
                break;
        }
    }
    printf("\n");
    
    //5
    for (int i = first; i <= last; i++)
    {
        printf("⠿⠿⠷⠶⠶⠖⠚⠻⠇\t");
    }
    printf("\n");
    
    //6
    for (int i = first; i <= last; i++)
    {
        switch (array[i].value) {
            case 13:
                printf("⠿⠿⠿⠿⠯ W ⠽\t");
                break;
                
            case 14:
                printf("⠿⠿⠿⠿⠯ +4⠽\t");
                break;
                
            default:
                printf("⠿⠿⠿⠿⠯ %s ⠽\t", array[i].color);
                break;
        }
    }
    printf("\n");
    
    //7
    for (int i = first; i <= last; i++)
    {
        printf("⠙⠛⠛⠛⠛⠓⠒⠚⠁\t");
    }
    printf("\n");
}

//function to print a players hand
//input: the player's head pointer and the player's number
void printHand(card* *head, int playerNum)
{
    card *instance = *head;
    if (instance != NULL)
    {
        int count = cardCount(head);
        
        card array[count];
        instance = *head;
        for (int i = 0; i < count; i++)
        {
            array[i] = *instance;
            if(instance->t != NULL)
            {
                instance = instance->t;
            }
        }
        printf("Player");
        switch (playerNum) {
            case 0:
                printf(" one");
                break;
            case 1:
                printf(" two");
                break;
            case 2:
                printf(" three");
                break;
            case 3:
                printf(" four");
                break;
            case 4:
                printf(" five");
                break;
            case 5:
                printf(" six");
                break;
            case 6:
                printf(" seven");
                break;
            case 7:
                printf(" eight");
                break;
            case 8:
                printf(" nine");
                break;
            case 9:
                printf(" ten");
                break;
            default:
                printf("");
                break;
        }
        printf("'s hand:\n");
        
        int numRows = (int)ceil(count/5.0);
        
        for (int r = 0; r < numRows; r++)
        {
            if (r == numRows - 1)
            {
                printRow(r*5, count-1, array);
            }
            else{
                printRow(r*5, (r*5)+4, array);
            }
            
        }
    }
}

//function to print the last played card (top of discard pile)
//input: the deck array
void printTopCard(card deck[])
{
    printf("Discard pile:\n");
    printf("⠴⠖⠒⠲⠶⠶⠶⠶⠄ \n");
    printf("⠯ %s ⠽⠿⠿⠿⠿\n", deck[107].color);
    printf("⠿⠷⠖⠚⠛⠛⠻⠿⠇ \n");
    switch (deck[107].value) {
        case 10:
            printf("⠿⠇SKIP ⠸⠿\n");
            break;
            
        case 11:
            printf("⠿⠇ REV ⠸⠿\n");
            break;
            
        case 12:
            printf("⠿⠇ +2  ⠸⠿\n");
            break;
            
        case 13:
            printf("⠿⠇WILD ⠸⠿\n");
            break;
            
        case 14:
            printf("⠿⠇ +4  ⠸⠿\n");
            break;
            
        default:
            printf("⠿⠇ %2d  ⠸⠿\n", deck[107].value);
            break;
    }
    printf("⠿⠿⠷⠶⠶⠖⠚⠻⠇ \n");
    printf("⠿⠿⠿⠿⠯ %s ⠽\n", deck[107].color);
    printf("⠙⠛⠛⠛⠛⠓⠒⠚⠁ \n");
}

//count the amount of cards in a player's hand
//input: the head pointer of a player's hand
int cardCount(card* *head)
{
    card *instance = *head;
    int count = 0;
    if (instance == NULL)
    {
        return count;
    }
    else
    {
        count = 1;
        while(instance->t != NULL)
        {
            count++;
            instance = instance->t;
        }
    }
    
    return count;
}

//function to draw a card from the deck to a player's hand & then shift the unplayed cards down 1 in the deck array
//input: the player's respective head pointer, tail pointer, the deck array, the amount of undrawn cards left in the deck
void drawCard(card* *head, card* *tail, card deck[], int *cardsLeft)
{
    //Copy the data
    card *temp;
    temp = (card *)malloc(sizeof(card));
    *temp = deck[0];
    
    if (*head == NULL) //If empty
    {
        *head = temp;
        *tail = temp;
        temp->t = NULL;
        temp->h = NULL;
    }
    else
    {
        (*tail)->t = temp;
        temp->h = *tail;
        *tail = temp;
        temp->t = NULL;
    }
    
    
    //Shift cards in deck
    card *pt;
    for (int i = 0; i < *cardsLeft - 1; i++)
    {
        pt = &deck[i];
        *pt = deck[i + 1];
    }
    
    //Decrease count of playable cards in deck
    *cardsLeft -= 1;
}

// moves the card from the players hand to the discard pile and shifts the discarded cards down in the array
//inputs: the player's head and tail pointers, the index of desired card to play, the deck array, the amount of undrawn cards left, the amount of cards in the discard pile
void playCard(card* *head, card* *tail, int cardPos, card deck[], int* cardsLeft, int *numPlayed)
{
    card *pt = *head;
    
    card *played;
    for (int i = 1; i < cardPos; i++)
    {
        pt = pt->t;
    }
    if (pt == *head)
    {
        played = pt;
        *head = pt->t;
        if (pt->t != NULL)
        {
        (pt->t)->h = pt->h;
        }
    }
    else if (pt == *tail)
    {
        played = pt;
        *tail = (*tail)->h;
        (*tail)->t = NULL;
    }
    else
    {
        played = pt;
        (pt->h)->t = pt->t;
        (pt->t)->h = pt->h;
    }
    free(pt);
    
    card *disc;
    for(int i = *cardsLeft + 1; i < 107; i++)
    {
        disc = &deck[i];
        *disc = deck[i+1];
    }
    
    disc = &deck[107];
    *disc = *played;
    disc->t = NULL;
    disc->h = NULL;
    
    *numPlayed+= 1;
}

//prompts the player which card they want to play in their hand and will return the index of chosen card by the player
//inputs: the player's head and tail pointers, the deck array, the player's number
int promptPlayer(card* *head, card deck[], int playerNum){
    
    printTopCard(deck);
    printHand(head, playerNum);
    
    int count = cardCount(head);
    printf("Press 1-%d to play any card from your hand, or press zero to draw a card from the deck:\n", count);
    scanf("%d", &count);
    
    return count;
}

//check if a selected card is valid to play on the discard pile
//inputs: desired card to play, the top of the discard pile
bool cardCheck(card cardPlayed, card base){
    
    if((cardPlayed.value == base.value) || strcmp(cardPlayed.color, base.color) == 0){
        return true;
    }
    else if (cardPlayed.value == 13){
        return true;
    }
    else if (cardPlayed.value == 14){
        return true;        // !! Challenge/rules on +4
    }
    else {
        return false;
    }
    
}

//returns a card in a given player's hand
//inputs: the player's head node, the index position of the desired card
card getCard(card* *head, int pos){
    card *temp = *head;
    for(int i = 1; i < pos; i++)
    {
        temp = temp->t;
    }
    return *temp;
}

//function to prompt user to change color when a wild card iss played
//input: the top card of the discard pile
void colorChange(card *lastCard){
    int i = -1;
    
    while(i < 1 || i > 4)
    {
        printf("Please select what color you wish to change to.\nSpades:1\tHearts:2\tClubs:3\tDiamonds:4\nWhat color are you choosing?: ");
        scanf("%d", &i);
        
        if (i < 1 || i > 4)
        {
            printf("That is not a valid selection.\n");
        }
    }
    
    switch (i) {
        case 1:
            strcpy(lastCard->color, "♠");
            break;
        
        case 2:
            strcpy(lastCard->color, "♥");
            break;
            
        case 3:
            strcpy(lastCard->color, "♣");
            break;
            
        default:
            strcpy(lastCard->color, "♦");
            break;
    }
}

//run win sequence and prompt user whether they wish to play another game
//input: the winning player's number
bool winSeq(int pturn){
    printf("Player");
    switch (pturn) {
        case 0:
            printf(" one");
            break;
        case 1:
            printf(" two");
            break;
        case 2:
            printf(" three");
            break;
        case 3:
            printf(" four");
            break;
        case 4:
            printf(" five");
            break;
        case 5:
            printf(" six");
            break;
        case 6:
            printf(" seven");
            break;
        case 7:
            printf(" eight");
            break;
        case 8:
            printf(" nine");
            break;
        case 9:
            printf(" ten");
            break;
        default:
            printf("");
            break;
    }
    printf(" wins!\n");
    
    char resp = 'a';
    while (resp != 'y' && resp != 'n')
    {
        printf("Would you like to play again? (y/n): ");
        scanf("%*c%c", &resp);
        
        if (resp != 'y' && resp != 'n')
        {
            printf("Please enter a lowercase 'y' or 'n' to respond.\n");
        }
    }
    
    if (resp == 'y'){
        return false;
    }
    else {
        return true;
    }
}

//when the deck has ran out of cards the discard pile will be shifted to the front of the deck array and be shuffled
//inputs: the deck array, number of cards left, number of in discard pile
void resetDeck(card deck[],int *numCards,int *numPlayed){
    card *pt;
    for (int i = 0; i < (108 - *numPlayed); i++)
    {
        pt = &deck[i];
        *pt = deck[(108-*numPlayed)+i];
    }
    for (int i = (108 - *numPlayed); i < 108; i++)
    {
        pt = &deck[i];
        strcpy(pt->color, "X");
        pt->value = -1;
    }
    *numCards = *numPlayed;
    *numPlayed = 0;
}

//asks user if they want to play with an AI, then asks user what player they want the AI to play as
//input: the amount of desired players
int promptAI(int numPlayers){

    //if user doesn't want AI return -1
    //if user does want AI return the number that the user inputted for the AI (e.g. if user inputs player 4 to imply they want the AI to play as player 4, then the function will return 4
    
    int playerNumber = 0; //integer that will be stored as the value the user inputs for which player they want the AI to play as
    
    char userChoice='b';
    while (userChoice != 'y' && userChoice != 'n')
    {
        printf("Do you want to play with an AI? y/n: ");
        scanf("%*c%c", &userChoice);
        
        if (userChoice != 'y' && userChoice != 'n')
        {
            printf("Please enter a lowercase 'y' or 'n' to respond.\n");
        }
    }
    
    
    while ((playerNumber<1 || playerNumber>numPlayers) && (userChoice == 'y'))
    {
        printf("Which player do you want the AI to play as? (1-%d): ", numPlayers);
        scanf("%d", &playerNumber);
        
        if (playerNumber<1 || playerNumber>numPlayers)
        {
            printf("Please enter a valid player number\n");
        }
        
    }
    
    if(userChoice=='y'){
        
        return playerNumber;
    }
    
    else{
        return -1;
    }
    
}

//run the AI player's turn sequence and implement strategy
//inputs: the AI's head and tail pointers, the deck array, the play direction, the top of the discard pile, the amount of cards left in the deck, the amount of cards in the discard pile
void AITurn(card* *head, card* *tail, card deck[], int *direction, card discard, int *cardsLeft, int *numPlayed){
    
    int position = 0;
    int *pPt = &position;
    //iterate through hand and check for wild
    card *temp = *head;
    
    if (checkWild(&temp, pPt)){     //prioritize changing color
        playCard(head, tail, *pPt, deck, cardsLeft, numPlayed);
        printf("AI Player has played WILD.\n");
    }
    else if (checkColor(&temp, pPt, discard.color)){    //next prioritize playing any card that fitss the suit
        playCard(head, tail, *pPt, deck, cardsLeft, numPlayed);
        printf("AI Player has played their turn.\n");
    }
    else if (checkValue(&temp, pPt, discard.value)){    //next prioritize playing any card that fitss the value
        playCard(head, tail, *pPt, deck, cardsLeft, numPlayed);
        printf("AI Player has played their turn.\n");
    }
    else if(checkFour(&temp, pPt)){                     //next prioritize playing a draw four card
        playCard(head, tail, *pPt, deck, cardsLeft, numPlayed);
        printf("AI Player has played their turn.\n");
    }
    else{
        drawCard(head, tail, deck, cardsLeft);          //else the AI will draw a card
        printf("AI Player has drawn a card.\n");
    }
    
    printf("AI player now has %d card(s) left.\n", cardCount(head));
    
}

//function to check if hand has a wild card
bool checkWild(card* *head, int *pos){
    card *temp = *head;
    int position = 1;
    while (temp->t != NULL){
        if (temp->value == 13){
            *pos = position;
            return true;
        }
        position++;
        temp = temp->t;
    }
    return false;
}

//function to check if hand has a card matching the top discard's color
bool checkColor(card* *head, int *pos, char color[]){
    card *temp = *head;
    int position = 1;
    while (temp->t != NULL){
        if (strcmp(temp->color, color) == 0){
            *pos = position;
            return true;
        }
        position++;
        temp = temp->t;
    }
    return false;
}

//function to check if hand has a card matching the top discard's value
bool checkValue(card* *head, int *pos, int value){
    card *temp = *head;
    int position = 1;
    while (temp->t != NULL){
        if (temp->value == value){
            *pos = position;
            return true;
        }
        position++;
        temp = temp->t;
    }
    return false;
}

//function to check if hand has a draw four
bool checkFour(card* *head, int *pos){
    card *temp = *head;
    int position = 1;
    while (temp->t != NULL){
        if (temp->value == 14){
            *pos = position;
            return true;
        }
        position++;
        temp = temp->t;
    }
    return false;
}
