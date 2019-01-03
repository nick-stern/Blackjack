/*
By: Nicholas Stern
Program that creates a deck of cards and you can play different games
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
using namespace std;

class Card{
	private:
	int number;//number value of every card
	char suite;//which suite ♥♦♣♠ the card is
	string value;//name of the card ex. ace, king, queen, jack, ..., two
	
	public:
	int getNumber();
	char getSuite();
	string getValue();
	
	void setNumber(int);
	void setSuite(char);
	void setValue(string);
	
	Card();
	
};


Card::Card(){//initializes all the info to null
	number = 0;
	suite;
	value = "undefined";
}

//retrieves data of a card object
int Card::getNumber(){
	return number;
}
char Card::getSuite(){
	return suite;
}
string Card::getValue(){
	return value;
}

//sets the info of a card object
void Card::setNumber(int n){
	number = n;
}
void Card::setSuite(char s){
	suite = s;
}
void Card::setValue(string v){
	value = v;
}


/*************************************************************************************************/


int menu();

vector<Card> createDeck();
void blackjack(int);
Card deal(vector<Card>&);


/**************************************************************************************************/


class Player{
	private:
		vector<Card> Hand;//the players hand of cards during the game
		int money;// amount of money the player has left to bet
	public:
		Player(){};
		void addHand(vector<Card>&);
		void clearHand(vector<Card>&);
		void displayHand(int);
		int getHand();
		int getHandSize();//returns number of cards in hand
};

void Player::addHand(vector<Card> &Shoe){//adds a random card from the sho to a players hand
	Hand.push_back(deal(Shoe));
}
void Player::clearHand(vector<Card> &Discard){//puts all the cards in the players hand into the discard pile
	for(int i = 0; i<Hand.size(); i++){
		Discard.push_back(Hand[i]);
	}
	Hand.clear();//clears the hand
}
void Player::displayHand(int i){
	cout<<Hand[i].getNumber()<<Hand[i].getSuite();
}
int Player::getHand(){
	int points = 0;
	for(int i=0; i<Hand.size(); i++){
		points += Hand[i].getNumber();
	}
	return points;
}
int Player::getHandSize(){
	return Hand.size();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void displayTable(vector<Player>, Player);
void displayFullTable(vector<Player>, Player);


int main(){
	int play;
	play = menu();
	system("CLS");

	blackjack(play);
	system("PAUSE");
	system("CLS");
	
	
	return 0;
}

int menu(){
	string players;
	int play;
	cout<<"Welcome to Blackjack!"<<endl<<"*********************"<<endl<<endl;//intro text asking for # of players
	cout<<"How many players are going to play(1-5)? ";
	getline(cin, players);
	
	while(true){//making sure the user input is only the #'s 1-5, otherwise ask for another input
		if(!(players.compare("1")) || !(players.compare("2")) || !(players.compare("3")) || !(players.compare("4")) || !(players.compare("5"))){
			break;
		}
		else{
			cout<<"Enter a player count from 1-5: ";
			getline(cin, players);
		}
	}
	play = stoi(players);//converting string to int
	return play;//returning the number of players goint to play
}

vector<Card> createDeck(){//function that creates a deck of cards with all 52 cards
	vector<Card> Deck(52);
	for(int i = 0; i<Deck.size(); i++){//cycles through and sets suite and number value to every card
		if(i<13){
			if(i==0){//sets ace to 11
				Deck[i].setNumber(11);
			}
			else if(i>=9){//sets all face cards to 10
				Deck[i].setNumber(10);
			}
			else{//other numbers set as their number
				Deck[i].setNumber(i+1);
			}
			Deck[i].setSuite('C');
		}
		else if(i<26){
			if(i==13){
				Deck[i].setNumber(11);
			}
			else if(i>=22){
				Deck[i].setNumber(10);
			}
			else{
				Deck[i].setNumber(i-12);
			}
			Deck[i].setSuite('D');
		}
		else if(i<39){
			if(i==26){
				Deck[i].setNumber(11);
			}
			else if(i>=35){
				Deck[i].setNumber(10);
			}
			else{
				Deck[i].setNumber(i-25);
			}
			Deck[i].setSuite('S');
		}
		else if(i<52){
			if(i==39){
				Deck[i].setNumber(11);
			}
			else if(i>=48){
				Deck[i].setNumber(10);
			}
			else{
				Deck[i].setNumber(i-38);
			}
			Deck[i].setSuite('H');
		}
	}
	for(int i = 0; i<Deck.size(); i++){//adds the word value to each card
		switch(i){
			case 1: Deck[i].setValue("Ace");
					break;
			case 2: Deck[i].setValue("Two");
					break;
			case 3: Deck[i].setValue("Three");
					break;
			case 4: Deck[i].setValue("Four");
					break;
			case 5: Deck[i].setValue("Five");
					break;
			case 6: Deck[i].setValue("Six");
					break;
			case 7: Deck[i].setValue("Seven");
					break;
			case 8: Deck[i].setValue("Eight");
					break;
			case 9: Deck[i].setValue("Nine");
					break;
			case 10: Deck[i].setValue("Ten");
					break;
			case 11: Deck[i].setValue("Jack");
					break;
			case 12: Deck[i].setValue("Queen");
					break;
			case 13: Deck[i].setValue("King");
					break;
			
		}
	}	
	
	return Deck;//returns the created deck
}

void blackjack(int players){
	vector<Card> Shoe;//vector of multiple decks to play with at once
	vector<Card> Deck;//vector of 52 standards playing cards
	vector<Card> Discard;//discard pile of used cards
	vector<Player> Table;//vector of players at the table playing
	Player Dealer;//computer dealer that acts as the house
	Deck = createDeck();
	string Answer;
	
	for(int i=0; i<players; i++){//adding a new player object to the table
		Table.push_back(Player());
	}
	
	for(int i=0; i<6; i++){//adding 6 decks to the shoe
		for(int j=0; j<Deck.size(); j++){//adds one deck at a time
			Shoe.push_back(Deck[j]);
		}
	}
	
	

	do{
		system("CLS");
		while(true){//deal
			for(int i=0; i<2; i++){//dealing 2 cards to every player 
			
				for(int j=0; j<Table.size(); j++){//deal to the table and dealer
					Table[j].addHand(Shoe);
				}
				Dealer.addHand(Shoe);
			
			}
			break;
		}
		
		displayTable(Table, Dealer);
		
		for(int i=0; i<Table.size(); i++){
			cout<<"Player "<<i+1<<" about to display hand."<<endl;
			system("PAUSE");
			system("CLS");
			cout<<"Hand: ";
			for(int j=0; j<Table[i].getHandSize(); j++){
				Table[i].displayHand(j);
				cout<<" ";
			}
			cout<<endl<<"Total: "<<Table[i].getHand();
			if(Table[i].getHand()==21){
				cout<<endl<<"Blackjack!";
				continue;
			}
			cout<<endl<<endl;
			displayTable(Table, Dealer);
			
			while(Table[i].getHand()<21){//get player choice to hit or stand
				cout<<"Player "<<i+1<<", hit or stand?";
				getline(cin, Answer);
				transform(Answer.begin(), Answer.end(), Answer.begin(), ::tolower);
				if(!(Answer.compare("hit")) || !(Answer.compare("h")) || !(Answer.compare("stand")) || !(Answer.compare("s"))){
					if(!(Answer.compare("stand")) || !(Answer.compare("s"))){
					system("CLS");
					break;
					}
				else{
					Table[i].addHand(Shoe);
					system("CLS");
					cout<<"Hand: ";
					for(int j=0; j<Table[i].getHandSize(); j++){
						Table[i].displayHand(j);
						cout<<" ";
						}
					cout<<endl<<"Total: "<<Table[i].getHand();
					cout<<endl<<endl;
					displayTable(Table, Dealer);
					continue;
					}
				}
				else{
					cout<<"Enter 'hit' or 'h' to take another card, or 'stand' or 's' to finish turn: ";
					continue;
				}
			
				
			}
			if(Table[i].getHand()>21){
				cout<<"Ooooh, player "<<i+1<<" busts... :("<<endl;
			}
		}
		cout<<"Dealer is about to play his hand... prepare to lose!"<<endl;
		system("PAUSE");
		
		//Dealer recieving cards
		while(Dealer.getHand()<=16){
			Dealer.addHand(Shoe);
		}
		system("CLS");
		displayTable(Table, Dealer);
		cout<<"Dealer hand: ";
					for(int j=0; j<Dealer.getHandSize(); j++){
						Dealer.displayHand(j);
						cout<<" ";	
						}
					cout<<endl<<"Total: "<<Dealer.getHand()<<endl<<endl;
		displayFullTable(Table, Dealer);
		
		//comparison to dealer to determine winners
		for(int i=0; i<Table.size(); i++){
			if(Dealer.getHand()>21){
				cout<<"Dealer busts. Everyone who didn't bust wins!"<<endl;
				break;
			}
			else if((Table[i].getHand() > Dealer.getHand()) && (Table[i].getHand() <= 21)){
				cout<<"Player "<<i+1<<" beat the house!";
			}
			else{
				cout<<"House beat player "<<i+1;
			}
			cout<<endl;
		}
		
		for(int i=0; i<Table.size(); i++)Table[i].clearHand(Discard);
		Dealer.clearHand(Discard);
		
		cout<<"Play another hand (yes/no)?";
		getline(cin, Answer);
		transform(Answer.begin(), Answer.end(), Answer.begin(), ::tolower);
	}while(!(Answer.compare("y")) || !(Answer.compare("yes")));
	/*
	for(int i = 0; i<Shoe.size(); i++){//display what is in the shoe
		cout<<Shoe[i].getSuite()<<Shoe[i].getNumber()<<" ";
		if((i+1)%13 == 0)
			cout<<endl;
	}
	cout<<endl<<endl;
	//*/
		
} 

Card deal(vector<Card> &shoe){
	time_t current_time;
	srand(time(&current_time));//random time seed
	int r = rand()%shoe.size();//random number from 0-# of cards left in the shoe
	
	Card card = shoe[r];//selecting random card
	shoe.erase(shoe.begin()+r);//deleting card from shoe
	return card;//returning chosen card to player hand
	
}

void displayTable(vector<Player> Table, Player Dealer){
	for(int i=0; i<Table.size(); i++){//leaving the first card hidden from everyone else
		cout<<"XX ";
		for(int j=1; j<Table[i].getHandSize(); j++){
				Table[i].displayHand(j);
				cout<<" ";
			}
		cout<<"\t\t";
	}
	cout<<endl<<endl;
	/*
	for(int i=0; i<Table.size(); i++){//displaying the second card face up
		Table[i].displayHand(1);
		cout<<"\t";
		
	}
	*/
	//cout<<endl<<endl;
	
	for(int i=0; i<(Table.size()%2)+1; i++)cout<<"\t";
	cout<<"XX ";
	//for(int i=0; i<(Table.size()%2)+1; i++)cout<<"\t";
	for(int j=1; j<Dealer.getHandSize(); j++){
				Dealer.displayHand(j);
				cout<<" ";
			}
	//Dealer.displayHand(1);
	cout<<endl<<endl;
	
	//system("PAUSE");
	//system("CLS");
}
void displayFullTable(vector<Player> Table, Player Dealer){
	for(int i=0; i<Table.size(); i++){
		cout<<Table[i].getHand();
		cout<<"\t\t";
	}
	cout<<endl<<endl;
	
	for(int i=0; i<(Table.size()%2)+1; i++)cout<<"\t";

	cout<<Dealer.getHand();
	cout<<endl<<endl;
}









