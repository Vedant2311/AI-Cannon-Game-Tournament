#include<bits/stdc++.h>
#include <chrono>

using namespace std ;

using namespace std::chrono ;
#define pi pair<int,int>


// Global variables

int empty = 0;
int black = 1;
int white = 2;
int blackKing = 3;
int whiteKing = 4;
int m,n ;
int search_depth = 5 ;
float depth_para = 10 ;
float time_left ;
int speedCount = -1 ;
float powers[10] = {0.00,1.00,2.8,5.2,8.0,11.15,14.7,18.5,22.6,27.0} ;
bool isValid (int Xpos, int Ypos){
	
	if((Xpos>=0)&&(Ypos>=0)&&(Xpos < n)&&(Ypos < m)) {
		return true ;
	}
	else {
		return false ;
	}
	
}

//
class Move{

	public:
	 pi initPos ;
	 pi finalPos ;
	 char type ;
	Move(int x,int y,int z,int w,char s){
		initPos = make_pair(x,y) ;
		finalPos = make_pair(z,w) ;
		type = s ;
	}

	Move(){
		initPos = make_pair(-1,-1) ;
		finalPos = make_pair(-1,-1) ;
		type = 'x' ;
	}

	void PrintMove(){
		cout << "Move from " << initPos.first << " " << initPos.second << " To " <<  finalPos.first << " " << finalPos.second << endl ;
	}
} ;

class soldier{

public:
	pi pos ;
	vector<Move> moves ;
	int color ;

	soldier(int x,int y,int col){
		pos = make_pair(x,y) ;
		color = col ;
	}


	// Can improve by adding a canMoveto function. Have to check for color and king of color at (x1,y1) , (x2,y2), (x3,y3)
	void updateMoves(vector<vector<int>> &board){

		//cout << "TEST2" << endl ;
		int Ypos = pos.second ;
		int Xpos = pos.first ;
		moves.clear() ;
		int color2 ;
		int colorKing;
		int color3  ;
		if(color == black){
			//cout << "TEST3" << endl ;
			color2 = white ;
			colorKing = blackKing;
			color3 = whiteKing ;
			
			int x1 = Xpos+1;
			int y1 = Ypos - 1;
			// cout << x1 << " " << y1 << endl ;
			// cout << "Board : " << board[x1][y1] << endl ;
			int x2 = Xpos;
			int y2 = Ypos - 1;
			
			// cout << x2 << " " << y2 << endl ;
			// cout << "Board : " << board[x2][y2] << endl ;
			int x3 = Xpos-1;
			int y3 = Ypos - 1;
			// cout << x3 << " " << y3 << endl ;
			// cout << "Board : " << board[x3][y3] << endl ;
			// backward positions
			
			int x4 = Xpos + 2;
			int y4 = Ypos + 2;
			
			int x5 = Xpos - 2;
			int y5 = Ypos + 2;
			
			int x6 = Xpos ;
			int y6 = Ypos + 2 ;


			// Attacking position
			
			int x7 = Xpos + 1;
			int y7 = Ypos;
			
			int x8 = Xpos - 1;
			int y8 = Ypos;
			
			if((isValid(x2,y2))&&(board[x2][y2]!=color)) {
				//cout << "TEST2" << endl ;
				Move temp(Xpos,Ypos,x2,y2,'s') ;
				moves.push_back(temp);
			}

			if((isValid(x1,y1))&&(board[x1][y1]!=color)){
				//cout << "TEST2" << endl ;
				Move temp(Xpos,Ypos,x1,y1,'s') ;
				 moves.push_back(temp);
			}

			if((isValid(x3,y3))&&(board[x3][y3]!=color)){
				//cout << "TEST2" << endl ;
				Move temp(Xpos,Ypos,x3,y3,'s') ;
			 	moves.push_back(temp);
			}
			
			
			if (isGettingAttacked(board)){
				if((isValid(x4,y4))&&(board[x4][y4] != color) && (board[x4][y4] != colorKing)){
					Move temp(Xpos,Ypos,x4,y4,'s') ;
			 		moves.push_back(temp);
				}
				if((isValid(x5,y5))&&(board[x5][y5] != color)&& (board[x5][y5] != colorKing)) {
					Move temp(Xpos,Ypos,x5,y5,'s') ;
			 		moves.push_back(temp);
				}
				if((isValid(x6,y6))&&(board[x6][y6] !=color)&& (board[x6][y6] != colorKing)){
					Move temp(Xpos,Ypos,x6,y6,'s') ;
			 		moves.push_back(temp);
				}
			}

			if((isValid(x7,y7))&&((board[x7][y7]==color2) || (board[x7][y7] == color3))) {
					Move temp(Xpos,Ypos,x7,y7,'s') ;
			 		moves.push_back(temp);
				}	

			if((isValid(x8,y8))&&((board[x8][y8]==color2) || (board[x8][y8] == color3))) {
				Move temp(Xpos,Ypos,x8,y8,'s') ;
		 		moves.push_back(temp);
			}	

		}

		else{
			//cout << "TEST4" << endl ;
			color2 = black ;
			colorKing = whiteKing;
			color3 = blackKing ;
			
			int x1 = Xpos+1;
			int y1 = Ypos + 1;
			// cout << x1 << " " << y1 << endl ;
			// cout << "Board : " << board[x1][y1] << endl ;
			int x2 = Xpos;
			int y2 = Ypos + 1;
			// cout << x2 << " " << y2 << endl ;
			// cout << "Board : " << board[x2][y2] << endl ;
			int x3 = Xpos-1;
			int y3 = Ypos + 1;
			// cout << x3 << " " << y3 << endl ;
			// cout << "Board : " << board[x3][y3] << endl ;
			// backward positions
			
			int x4 = Xpos + 2;
			int y4 = Ypos - 2;
			
			int x5 = Xpos - 2;
			int y5 = Ypos - 2;
			
			int x6 = Xpos ;
			int y6 = Ypos - 2 ;


			// Attacking position
			
			int x7 = Xpos + 1;
			int y7 = Ypos;
			
			int x8 = Xpos - 1; 
			int y8 = Ypos;
			
			if((isValid(x2,y2))&&(board[x2][y2]!=color)) {
				//cout << "TEST2" << endl ;
				Move temp(Xpos,Ypos,x2,y2,'s') ;
				moves.push_back(temp);
			}
			if((isValid(x1,y1))&&(board[x1][y1]!=color)){
				//cout << "TEST2" << endl ;
				Move temp(Xpos,Ypos,x1,y1,'s') ;
				 moves.push_back(temp);
			}
			if((isValid(x3,y3))&&(board[x3][y3]!=color)){
				//cout << "TEST2" << endl ;
				Move temp(Xpos,Ypos,x3,y3,'s') ;
			 	moves.push_back(temp);
			}
			
			
			if (isGettingAttacked(board)){
				if((isValid(x4,y4))&&(board[x4][y4] != color) && (board[x4][y4] != colorKing)){
					Move temp(Xpos,Ypos,x4,y4,'s') ;
			 		moves.push_back(temp);
				}
				if((isValid(x5,y5))&&(board[x5][y5] != color)&& (board[x5][y5] != colorKing)) {
					Move temp(Xpos,Ypos,x5,y5,'s') ;
			 		moves.push_back(temp);
				}
				if((isValid(x6,y6))&&(board[x6][y6] != color)&& (board[x6][y6] != colorKing)){
					Move temp(Xpos,Ypos,x6,y6,'s') ;
			 		moves.push_back(temp);
				}

			}

			if((isValid(x7,y7))&&((board[x7][y7]==color2) || (board[x7][y7] == color3))) {
					Move temp(Xpos,Ypos,x7,y7,'s') ;
			 		moves.push_back(temp);
				}
			if((isValid(x8,y8))&&((board[x8][y8]==color2) || (board[x8][y8] == color3))) {
				Move temp(Xpos,Ypos,x8,y8,'s') ;
		 		moves.push_back(temp);
			}	
	}

	}

	bool isGettingAttacked (vector<vector<int>> &board){

		int Xpos = pos.first ;
		int Ypos = pos.second ;
		if(color == black){
			if(((isValid(Xpos+1,Ypos)) && (board[Xpos+1][Ypos]==white)) || ((isValid(Xpos+1,Ypos-1)) && (board[Xpos+1][Ypos-1]==white)) || ((isValid(Xpos,Ypos-1)) && (board[Xpos][Ypos-1]==white)) ||((isValid(Xpos-1,Ypos-1)) && (board[Xpos-1][Ypos-1]==white))||((isValid(Xpos-1,Ypos)) && (board[Xpos-1][Ypos]==white))){ 
					return true ;
			}
			else 
				return false ;
		}
		
		else {
		
			if(((isValid(Xpos+1,Ypos)) && (board[Xpos+1][Ypos]==black))||((isValid(Xpos+1,Ypos+1)) && (board[Xpos+1][Ypos+1]==black))||((isValid(Xpos,Ypos+1)) && (board[Xpos][Ypos+1]==black))||((isValid(Xpos-1,Ypos+1)) && (board[Xpos-1][Ypos+1]==black))||((isValid(Xpos-1,Ypos)) && (board[Xpos-1][Ypos]==black))) {
					return true ;
			}
			else 
				return false ;

		
		}
	}

	void updatePos(pi x){
			//cout << pos.first << " " << pos.second << endl  ;
			pos = x ;
			//cout << pos.first << " " << pos.second << endl  ;
			return ;
	}	
};

class cannon{
public:
	int initX ;
	int initY ;
	string type ;
	int color ;
	int move_X ;
	int move_Y ;
	vector<Move> shots ;
	int validShots ;


	cannon(int i,int j,string t,int colo){
		initX = i ;
		initY = j ;
		type = t ;
		color = colo ;

    	validShots = 0;
		if(type == "Horz"){
			move_X = 1 ;
			move_Y = 0 ;
		}
		else if(type == "Vert"){
			move_X = 0 ;
			move_Y = 1 ;
		}
		else if(type == "BR_diag"){
			move_X = 1 ;
			move_Y = 1 ;
		}
		else{
			move_X = 1 ;
			move_Y = -1 ;
		}

	}

	// void moveCannon(vector<vector<int>> board){

	// 	int finalX = initX + 2*move_X ;
	// 	int finalY = initY + 2*move_Y ;
	// 	if(isValid(finalX + move_X,finalY + move_Y) && board[finalX + move_X][finalY + move_Y] == empty){
	// 		Solmove m(initX,initY,finalX + move_X,finalY + move_Y) ;
	// 		// m.initPos = make_pair(initX,initY) ;
	// 		// m.finalPos = make_pair(finalX + x,finalY + y) ;
	// 		moves.push_back(m) ;
	// 	}
	// 	if(isValid(initX - move_X,initY - move_Y) && board[finalX + move_X][finalY + move_Y] == empty){
	// 		Solmove m(finalX,finalY,initX - move_X,initY - move_Y) ;
	// 		// m.initPos = make_pair(finalX,finalY) ;
	// 		// m.finalPos = make_pair(initX - x,initY - y) ;
	// 		moves.push_back(m) ;
	// 	}


	// }

	bool updateShots(vector<vector<int>> &board,bool findEmpty){
		if ((m==8) && (n==8))
			findEmpty =false;

		validShots=0;
		shots.clear() ;
		vector<pi> pos_to_check[2] ;
		int finalX = initX + 2*move_X ;
		int finalY = initY + 2*move_Y ;
//		cout << "Xi,Yi" << initX << " " << initY << " " << "Xf,Yf" << finalX << " " << finalY << endl;
		for(int i = 1 ; i <= 3 ; i++){
			pos_to_check[0].push_back(make_pair(initX -i*move_X,initY - i*move_Y)) ;
		}
		for(int i = 1 ; i <= 3 ; i++){
			pos_to_check[1].push_back(make_pair(finalX +i*move_X,finalY + i*move_Y)) ;
		}
		int color1,color2 ;
		if(color == black){
			color1 = white ;
			color2 = whiteKing ;
		}
		else{
			color1 = black ;
			color2 = blackKing ;
		}
		int tempx,tempy ;
		for(int i = 0 ; i < 2 ; i++){
			if (!isValid(pos_to_check[i][0].first,pos_to_check[i][0].second)){
				continue ;
			}
			else if(board[pos_to_check[i][0].first][pos_to_check[i][0].second] != empty){
				//cout << "CockBlocked" << endl ;
				continue ;
			}
			else{
				if(i == 0){
					Move m(finalX,finalY,initX - move_X,initY - move_Y,'s') ;
					shots.push_back(m) ;
					validShots++;
				}
				else{
					Move m(initX,initY,finalX + move_X,finalY + move_Y,'s') ;
					shots.push_back(m) ;
					validShots++;

				}
				for(int j = 1 ; j <= 2 ; j++){
					tempx = pos_to_check[i][j].first ;
					tempy = pos_to_check[i][j].second ;
					if(isValid(tempx,tempy)){

						validShots++;
						int tempcolor = board[tempx][tempy] ;
						if(tempcolor == color1 || tempcolor == color2){
							Move temp(initX,initY,tempx,tempy,'c') ;
							shots.push_back(temp) ;

						}
						if(tempcolor == empty && findEmpty){
							Move temp(initX,initY,tempx,tempy,'c') ;
							shots.push_back(temp) ;
							findEmpty = false ;
						}
					}
				}
			}
		}
		return findEmpty ;

	}
} ;

// The board is m * n 


//  Need to add situation where piece is being attacked in retreat position

// This functions counts the pieces on the board(black,white,blackHall,whiteHall) and returns their count as a vector of size 4.Counts are following --- black(0),white(1),blackHall(2),whiteHall(3)

//Designed function to calculate cost fast... please check validity of outputs once


void updateBoard (int initX, int initY, int finalX, int finalY, vector<vector<int>> board, int color){

	board[initX][initY] = empty;
	board[finalX][finalY] = color;
	
}

// Function to find cannons on current configuration of board
// Severe refactoring in this piece of code. Review with Raval for sure


class Game{
public:
	vector<vector<int>> board ;
	vector<soldier> player1 ; // Black
	vector<soldier> player2 ; // 
	vector<cannon> player1_cannon ;
	vector<cannon> player2_cannon ;
	int blackHalls ;
	int whiteHalls ;
	ofstream outfile;
	
	//vector<Game*> children ;
	// vector<cannon> can_player1 ;
	// vector<cannon> can_player2 ;
	int n ; //Columns
	int m ; //Rows


	Game(int n,int m){

		this->n = n ;
		this->m = m ;
		setBoard(n,m) ;
		initializePlayers() ;
		initializeCannons();

		if(n==8){
			blackHalls = 4 ;
			whiteHalls = 4 ;
		}

		else{
			blackHalls = 5;
			whiteHalls = 5;
		}

		outfile.open("afile21.txt") ;
		
	}

	void setBoard(int n,int m){

		for(int i = 0 ; i < n ; i++){
			vector<int> temp ;
			for(int j = 0 ; j < m ; j++){
				temp.push_back(empty) ;
			}
			board.push_back(temp) ;
		}

		for(int j = 0 ; j < n ; j+= 2){
			board[j][0] = whiteKing ;
		}
		for(int j = 1 ; j < n ; j += 2){
			for(int i = 0 ; i < 3 ; i++){
				board[j][i] = white ;
			}
		}

		for(int j = 1 ; j < n ; j+= 2){
			board[j][m-1] = blackKing ;
		}
		for(int j = 0 ; j < n ; j += 2){
			for(int i = 0 ; i < 3 ; i++){
				board[j][m-1-i] = black ;
			}
		}

		return ;
	}

	void initializePlayers(){

		for(int i = 0 ; i < n ; i++){
			for(int j = 0 ; j < m ; j++){
				if(board[i][j] == white){
					soldier s(i,j,white) ;
					player2.push_back(s) ;
				}
				else if(board[i][j] == black){
					soldier s(i,j,black) ;
					player1.push_back(s) ;
				}
			}
		}

	}

	void initializeCannons(){
		player1_cannon = CannonData(true) ;
		player2_cannon = CannonData(false) ;
		return ;
	}

	vector<cannon> CannonData (bool isBlack){

		vector<cannon> result;
		int color ;
		if(isBlack){
			color = black ;
		}
		else{
			color = white ;
		}

	   for(int i=0; i<n ; i++){
	   		for(int j=0; j<m ; j++){
	   			if(j < m-2){
					if((board[i][j]==color)&&(board[i][j+1]==color)&&(board[i][j+2]==color)) {
							cannon temp(i,j,"Vert",color) ;
							result.push_back(temp);
						}
				}

				if(i<n-2){
					if(j<m-2){
						
						if((board[i][j]==color)&&(board[i+1][j+1]==color)&&(board[i+2][j+2]==color)) {
							cannon temp(i,j,"BR_diag",color) ;
							result.push_back(temp);
						}
					}
					
					if(j>=2){
					
						if((board[i][j]==color)&&(board[i+1][j-1]==color)&&(board[i+2][j-2]==color)) {
							cannon temp(i,j,"BL_diag",color) ;
							//cout << "TEST" << endl ;
							result.push_back(temp);
						}
					}

					if((board[i][j]==color)&&(board[i+1][j]==color)&&(board[i+2][j]==color)) {
						cannon temp(i,j,"Horz",color) ;
						result.push_back(temp);
					}
					
				}

				
				
				
			}
	   }

		return result;
	}

	string printBoard(){

		string s = "" ;
		for(int i = 0 ; i < m ; i++){
			for(int j = 0 ; j < n ; j++){
				s += to_string(board[j][i]);
			}
			s += "\n" ;
		}

		return s ;
	}

	vector<int> countPieces(){
		vector<int> count ;
		count.push_back(player1.size()) ;
		count.push_back(player2.size()) ;
		count.push_back(blackHalls) ;
		count.push_back(whiteHalls) ;

		return count ;
	}

	float getShotScore(vector<Move> &m){

		float x = 0.0 ;
		for(int i = 0 ; i < m.size() ; i++){
			if(m[i].initPos.first == m[i].finalPos.first){
				x += 0.03 ;
			}
			else{
				x += 0.05 ;
			}
		}

		return x ;
	}

	float getPositionAdvantage(int player){

		float x = 0.0 ;
		float y = 0.0 ;
		for(int i = 0 ; i < player1.size() ; i++){
			x += (powers[m-1-player1[i].pos.second])/100 ;
		}
		for(int i = 0 ; i < player2.size() ; i++){
			y += (powers[player2[i].pos.second])/100 ;
		}

		if(player == 0){
			return x - y ;
		}
		else{
			return y - x ;
		}
	}

	float NoOtherMoves(int side,int num1){

		if(side == 0){
			if(num1 == 0){
				return true ;
			}
			else if(num1 == 1 && player1[0].pos.second == 0){
				return true ;
			}
			else{
				return false ;
			}
		}
		else{
			if(num1 == 0){
				return true ;
			}
			else if(num1 == 1 && player2[0].pos.second == m-1){
				return true ;
			}
			else{
				return false ;
			}
		}
	}
	float getOrientationAdvantage(int player,float factor){

		float armyCannonBlack = 0 ;
		float armyCannonWhite = 0 ;

		float totalShotsBlack = 0.0;
		float totalShotsWhite = 0.0;

		float shotWeight = 0.25;

	  //  vector<Move> shots1 = getCannonShots(player1_cannon) ;
	  //  vector<Move> shots2 = getCannonShots(player2_cannon) ;


		for(int i = 0 ; i < player1_cannon.size() ; i++){
			totalShotsBlack = totalShotsBlack + shotWeight * ((float) player1_cannon[i].validShots);

			if(player1_cannon[i].move_X == 1 && player1_cannon[i].move_Y == 0){

			
				if ((m==8) && (n==8)){
					if ((player1_cannon[i].initX < 3) || (player1_cannon[i].initX > (n-5)))
						armyCannonBlack += 0.009;
					else
						armyCannonBlack += 0.01 + factor* 0.04;

				}

				else{
					armyCannonBlack += 0.01 + factor*0.04 ;

				}


			}
			else if(player1_cannon[i].move_X == 0 && player1_cannon[i].move_Y == 1){
				armyCannonBlack += 0.04 ;


			}
			else{
				armyCannonBlack += 0.03 ;
			}

//			outfile << "black: " << player1_cannon[i].validShots << endl;
		}
		for(int i = 0 ; i < player2_cannon.size() ; i++){
			totalShotsWhite = totalShotsWhite + shotWeight * ((float) player2_cannon[i].validShots);

			if(player2_cannon[i].move_X == 1 && player2_cannon[i].move_Y == 0){
				if ((m==8) && (n==8)){
					if ((player2_cannon[i].initX < 3) || (player2_cannon[i].initX > (n-5)))
						armyCannonWhite += 0.009;
					else
						armyCannonWhite += 0.01 + factor* 0.04;

				}

				else{
					armyCannonWhite += 0.01 + factor*0.04 ;

				}
				

		
			}
			else if(player2_cannon[i].move_X == 0 && player2_cannon[i].move_Y == 1){
				armyCannonWhite += 0.04 ;


			}
			else{
				armyCannonWhite += 0.03 ;
			}
//			outfile << "white: " << player2_cannon[i].validShots << endl;

		}

		if(player == 0){
			return armyCannonBlack - armyCannonWhite + totalShotsBlack ;
		}
		else{
			return armyCannonWhite - armyCannonBlack + totalShotsWhite ;		
		}
		
}


	float totalScore (int player){

		vector<int> count = countPieces() ;
		float temp = count[1] + count[0] ;
		float end_game_factor = 1.00 - (temp)/((float)3*n) ;
		float middle_game_factor = 1.5 - abs(1.5 - (temp/(float)n)) ; 
		float armyMarginWhite = float(count[1])/3;
		float armyMarginBlack = float(count[0])/3;
		float ori_advan = getOrientationAdvantage(player,end_game_factor) ;
		float pos_advan = getPositionAdvantage(player) ;

		float eight_factor = 1.0;

		if ((m==8) && (n==8)) {

			if ((temp <= 20) && (((player==0) && ((count[1] > 6) && (count[0] > 6) )) || ((player==1) && (count[0] > 6) && (count[1] > 6))))
				eight_factor = 0.6;
			else 
				eight_factor = 1.0;
		}

		else{

			eight_factor = 1.0;
		}

		int blackHalls = count[2] ;
		int whiteHalls = count[3] ;
		int score_change[] = {0,2,5};
		int sum = 5 ;
		if(player == 0) //The player is black
		{	
			int hallDiff = blackHalls - whiteHalls ;
			if(n<10){

				// if(whiteHalls==2){
				// 	// Direct win
				// 	sum -= score_change[4-blackHalls] ;
				// 	sum += score_change[4-whiteHalls] ;
				// }
				// else if(whiteHalls == 3){
				// 	sum = 8 + (2 * (4 - whiteHalls)) - (2*(4 - blackHalls));
				// }
				if(NoOtherMoves(1,count[1])){
					// Stalemate
					sum = 8 + (2 * (4 - whiteHalls)) - (2*(4 - blackHalls));
				}
				else if(NoOtherMoves(0,count[0])){
					sum = 2 + (2 * (4 - whiteHalls)) - (2*(4 - blackHalls));
				}
				else {
					sum -= score_change[4-blackHalls] ;
					sum += score_change[4-whiteHalls] ;
				}
			}

			else{

				if(NoOtherMoves(1,count[1])){
					// Stalemate
					sum = 8 + (2 * (5 - whiteHalls)) - (2*(5 - blackHalls));
				}
				else if(NoOtherMoves(0,count[0])){
					sum = 2 + (2 * (5 - whiteHalls)) - (2*(5 - blackHalls));
				}
				else {
					sum -= score_change[5-blackHalls] ;
					sum += score_change[5-whiteHalls] ;
				}

			}

			if ((n==8) && (m==8))
				return (sum + ((armyMarginBlack+1)/(armyMarginWhite + 1) + end_game_factor)*(pos_advan/3)*(eight_factor)  + armyMarginBlack - armyMarginWhite + (middle_game_factor+1)*ori_advan/3);
			else
				return (sum + ((armyMarginBlack+1)/(armyMarginWhite + 1) + end_game_factor)*(pos_advan/3)  + armyMarginBlack - armyMarginWhite + (middle_game_factor+1)*ori_advan/3);

		}

		else{
			int hallDiff = whiteHalls - blackHalls ;
			if(n<10){
				if(NoOtherMoves(0,count[0])){
					// Stalemate
					sum = 8 - (2 * (4 - whiteHalls)) + (2*(4 - blackHalls));
				}
				else if(NoOtherMoves(1,count[1])){
					sum = 2 - (2 * (4 - whiteHalls)) + (2*(4 - blackHalls));
				}
				else {
					sum += score_change[4-blackHalls] ;
					sum -= score_change[4-whiteHalls] ;
				}


			}

			else{
				if(NoOtherMoves(0,count[0])){
					// Stalemate
					sum = 8 - (2 * (5 - whiteHalls)) + (2*(5 - blackHalls));
				}
				else if(NoOtherMoves(1,count[1])){
					sum = 2 - (2 * (5 - whiteHalls)) + (2*(5 - blackHalls));
				}
				else {
					sum += score_change[5-blackHalls] ;
					sum -= score_change[5-whiteHalls] ;
				}


			}

			if ((n==8) && (m==8))
				return (sum + ((armyMarginWhite + 1)/(armyMarginBlack + 1)+ end_game_factor)*(pos_advan/3)*(eight_factor) - armyMarginBlack + armyMarginWhite + (middle_game_factor + 1) * ori_advan/3);
			else
				return (sum + ((armyMarginWhite + 1)/(armyMarginBlack + 1)+ end_game_factor)*(pos_advan/3) - armyMarginBlack + armyMarginWhite + (middle_game_factor + 1) * ori_advan/3);

		
		}
	}	

	void removePiece(int x,int y){
		if(board[x][y] == empty){
			//cout << "Empty !" << endl ;
			return ;
		}
		else if(board[x][y] == whiteKing){
			//cout << "Killed a HALL !" << endl 
			whiteHalls--;
			return ;
		}
		else if(board[x][y] ==blackKing){
			blackHalls-- ;
			return ;
		}
		else{
			//cout << "Killing now !" << endl ;
			removeSolFromVec(board[x][y] == black,x,y) ;
			// cout << player1.size() << endl ;
			// cout << player2.size() << endl ;
		}
	}

	void AddPiece(int x ,int y,int color){

		if(color == black){
			soldier s(x,y,color) ;
			player1.push_back(s) ;
		}
		else if(color == white){
			soldier s(x,y,color) ;
			player2.push_back(s) ;
		}
		else if(color == whiteKing){
			whiteHalls++;
		}
		else if(color == blackKing){
			blackHalls++;
		}

		return ;
	}

	bool NoOtherPlayerMoves(int player){
		vector<soldier> soldiers;
		vector<cannon> cannons;
		if(player == 1){
			//cout << "TEST " << endl ;
			soldiers = player1;
			cannons = player1_cannon;
		}
		else{
			soldiers = player2;
			cannons = player2_cannon;
		
		}
		vector<Move> Solmoves = getSolMoves(soldiers);
		vector<Move> cannonMoves = getCannonShots(cannons);

		if(Solmoves.size() + cannonMoves.size() == 0){
			return true ;
		}

		return false ;
	}

	/*void getChildren(bool isBlack){

		//cout << "TEST" << endl ;
		vector<soldier> player;
		vector<cannon> player_cannon;
		if(isBlack){
			player = player1;
			player_cannon = player1_cannon;
		}

		else{

			player = player2;
			player_cannon = player2_cannon;
		
		}

		vector<Move> Solmoves = getSolMoves(player);
		vector<Move> cannonMoves = getCannonShots(player_cannon);
		// cout << Solmoves.size() << endl ;
		// for(int i = 0 ; i < Solmoves.size() ; i++){
		// 	Solmoves[i].PrintMove() ;
		// }
		for(int i=0; i<Solmoves.size(); i++){
			//cout << "TEST" << endl ;
			Game* root_temp =  new Game(*this);
			root_temp->executeMove(Solmoves[i]);
			children.push_back(root_temp);

		}
		//cout << "TEST4" ;
		for(int i=0; i<cannonMoves.size(); i++){
			//cout << "TEST3" << endl ;
			Game* root_temp =  new Game(*this);
			root_temp->executeShot(cannonMoves[i]);

			children.push_back(root_temp);

		}

	}*/

	pair<Move,Move> getBestMove(int player){

		vector<soldier> soldiers;
		vector<cannon> cannons;
		if(player == 0){
			//cout << "TEST " << endl ;
			soldiers = player1;
			cannons = player1_cannon;
		}

		else{

			soldiers = player2;
			cannons = player2_cannon;
		
		}
		auto start = high_resolution_clock::now();
		vector<Move> Solmoves = getSolMoves(soldiers);
		vector<Move> cannonMoves = getCannonShots(cannons);
		bool tooMuchTime = false ;
		// cout << Solmoves.size() << endl ;
		// for(int i = 0 ; i < Solmoves.size() ; i++){
		// 	Solmoves[i].PrintMove() ;
		// }
		Move m,n ;
		float mx = -100.0,score ;
		int temp ;
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
//		outfile << "TEST" << time_left << endl ;
//		outfile << "Depth is : " << search_depth << endl ;
//		outfile.flush() ;
		for(int i=0; i<cannonMoves.size(); i++){
			//cout << "TEST3" << endl ;
			//Game* root_temp =  new Game(*this);
			temp = playTurn(cannonMoves[i]);
			score = miniMaxAlphaBeta(1,search_depth,player,mx,100.0) ;
			reverseTurn(cannonMoves[i],temp) ;
			if(score > mx){
				n = m ;
				m = cannonMoves[i] ;
				mx = score ;
			}
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start); 
			float time_taken = ((float)duration.count())/1000000.00 ;
			if(time_taken > min(6.0,(double)time_left/15)){
				tooMuchTime = true ;
				break ;
			}
			//delete root_temp ;

		}
		for(int i=0; i<Solmoves.size(); i++){
			if(tooMuchTime){
				break ; 
			}
			//cout << "TEST" << endl ;
			// Game* root_temp =  new Game(*this);
			temp = executeMove(Solmoves[i]);
			score = miniMaxAlphaBeta(1,search_depth,player,mx,100.00) ;
			reverseMove(Solmoves[i],temp) ;
			if(score > mx){
				n = m ;
				m = Solmoves[i] ;
				mx = score ;
			}
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start); 
			float time_taken = ((float)duration.count())/1000000.00 ;
			if(time_taken > min(6.0,(double)time_left/15)){
				tooMuchTime = true ;
				break ;
			}
			// delete root_temp ;

		}
		duration = duration_cast<microseconds>(stop - start); 
		float time_taken = ((float)duration.count())/1000000.00 ;
		time_left -= time_taken ;
//		outfile << time_left << endl ;
//		outfile.flush() ;
		if(tooMuchTime){
			speedCount = 0 ;
			search_depth-- ;
			return make_pair(m,n) ;
		}
		//cout << "TEST4" ;
		if(speedCount >= 0){
			speedCount++ ;
			if(speedCount == 4){
				search_depth++ ;
				speedCount = -1 ;
			}
		}
		return make_pair(m,n) ;
	}

	float miniMaxAlphaBeta(int height,int depth,int player,float alpha,float beta){

		if(height ==depth) {

			// Evaluation function
			return totalScore(player);

		}
		if(isTermination()){
			float x =totalScore(player) ;
			// float depth_add = isWin*depth_para*(search_depth - depth) ;
			// outfile << x + depth_add << endl ;
			return x ;
		}

		else {
			initializeCannons();
			if(height%2==0){

				vector<soldier> soldiers;
				vector<cannon> cannons;
				if(player == 0){
					//cout << "TEST " << endl ;
					soldiers = player1;
					cannons = player1_cannon;
				}

				else{
					soldiers = player2;
					cannons = player2_cannon;
				
				}
				vector<Move> Solmoves = getSolMoves(soldiers);
				vector<Move> cannonMoves = getCannonShots(cannons);

				if(Solmoves.size() + cannonMoves.size() == 0){
					// outfile << "TERMINATED" << endl ;
					// outfile << printBoard() << endl ;999/
					return totalScore(player) ;
				}
				// Black : Max
				Move m ;
				float score ;
				int temp ;

				for(int i=0; i<cannonMoves.size(); i++){
					//cout << "TEST3" << endl ;
					//Game* root_temp =  new Game(*this);
					temp = playTurn(cannonMoves[i]);
					score = miniMaxAlphaBeta(height+1,depth,player,alpha,beta);
					reverseTurn(cannonMoves[i],temp) ;
					alpha=  max(alpha,score) ;
					if(alpha >= beta){
						return score ;
					}
					//delete root_temp ;

				}

				for(int i=0; i<Solmoves.size(); i++){
					//cout << "TEST" << endl ;
					// Game* root_temp =  new Game(*this);
					temp = executeMove(Solmoves[i]);
					score = miniMaxAlphaBeta(height+1,depth,player,alpha,beta);
					reverseMove(Solmoves[i],temp) ;
					alpha=  max(alpha,score) ;
					if(alpha >= beta){
						return score ;
					}

					// delete root_temp ;

				}
				//cout << "TEST4" ;

				return alpha ;

			}

			else {

				// White : Min
				vector<soldier> soldiers;
				vector<cannon> cannons;
				if(player == 1){
					//cout << "TEST " << endl ;
					soldiers = player1;
					cannons = player1_cannon;
				}

				else{
					soldiers = player2;
					cannons = player2_cannon;
				
				}
				vector<Move> Solmoves = getSolMoves(soldiers);
				vector<Move> cannonMoves = getCannonShots(cannons);

				if(Solmoves.size() + cannonMoves.size() == 0){
					// outfile << "TERMINATED2" << endl ;
					// outfile << printBoard() << endl ;
					return totalScore(player) ;
				}
				// Black : Max
				Move m ;
				float score ;
				int temp ;

				for(int i=0; i<cannonMoves.size(); i++){
					//cout << "TEST3" << endl ;
					//Game* root_temp =  new Game(*this);
					temp = playTurn(cannonMoves[i]);
					score = miniMaxAlphaBeta(height+1,depth,player,alpha,beta);
					reverseTurn(cannonMoves[i],temp) ;
					beta = min(beta,score) ;
					if(alpha >= beta){
						return score ;
					}
					//delete root_temp ;

				}

				for(int i=0; i<Solmoves.size(); i++){
					//cout << "TEST" << endl ;
					// Game* root_temp =  new Game(*this);
					temp = executeMove(Solmoves[i]);
					score = miniMaxAlphaBeta(height+1,depth,player,alpha,beta);
					reverseMove(Solmoves[i],temp) ;
					beta = min(beta,score) ;
					if(alpha >= beta){
						return score ;
					}
					// delete root_temp ;

				}
				//cout << "TEST4" ;

				return beta ;

			}


		}



	}

	soldier* getSoldier(int x,int y,int color){
		soldier* sol ;
		if(color == black){
			//cout << "TEST5"<< endl ;
			for(auto it = player1.begin() ; it != player1.end() ; it++){
				if(it->pos.first == x && it->pos.second == y){
					//cout << "Found black ka piece" << endl ;
					sol = &(*it) ;
					return sol ;
				}
			}
		}
		else{
			//cout << "TEST6"<< endl ;
			for(auto it = player2.begin() ; it != player2.end() ; it++){
				if(it->pos.first == x && it->pos.second == y){
					//cout << "Found white ka piece" << endl ;
					sol = &(*it) ;
					return sol ;
				}
			}
		}

		return NULL ;
	}

	void removeSolFromVec(bool isBlack,int x,int y){
		if(isBlack){
			//cout << "TEST5"<< endl ;
			for(auto it = player1.begin() ; it != player1.end() ; it++){
				if(it->pos.first == x && it->pos.second == y){
					player1.erase(it) ;
					//cout << "Killed black ka piece" << endl ;
					break ;
				}
			}
		}
		else{
			for(auto it = player2.begin() ; it != player2.end() ; it++){
				//cout << "TEST6"<< endl ;
				if(it->pos.first == x && it->pos.second == y){
					player2.erase(it) ;
					//cout << "Killed white ka piece" << endl ;
					break ;
				}
			}
		}
	}


	vector<Move> getSolMoves(vector<soldier> &player){

		vector<Move> total_moves ;
		//cout << "Number of soldiers are : " << player.size() << endl ;
		for(int i = 0 ; i < player.size() ; i++){
			player[i].updateMoves(board) ;
			total_moves.insert(total_moves.end(),player[i].moves.begin(),player[i].moves.end()) ;
		}
		//cout << total_moves.size() << endl ;
		return total_moves ;

	}

	vector<Move> getCannonShots(vector<cannon> &player_cannon){

		vector<Move> total_shots ;
		bool findEmpty = true ;
		for(int i = 0 ; i < player_cannon.size() ; i++){
			findEmpty = player_cannon[i].updateShots(board,findEmpty) ;
			total_shots.insert(total_shots.end(),player_cannon[i].shots.begin(),player_cannon[i].shots.end()) ;
		}

		return total_shots ;
	}



	Move getRandMove(int player){
		vector<Move> moves ;
		if(player == 0){
			moves = getSolMoves(player1) ;
		}
		else{
			moves = getSolMoves(player2) ;
		}
		int index = rand() % moves.size() ;
		Move x = moves[index] ;
		//x.PrintMove() ;
		return x ;
	}

	Move executeRandShot(vector<Move> &shots){

		int index = rand() % shots.size() ;
		Move x = shots[index] ;
		executeShot(x) ;
		//x.PrintMove() ;
		return x ;
	}

	bool isTermination(){

		if(player1.size() == 0 || player2.size() == 0){
			return true ;
		}
		if(((n<10) &&(blackHalls <= 2 || whiteHalls <= 2)) || ((n>=10) &&(blackHalls <= 3 || whiteHalls <= 3))){
			return true ;
		}
		else{
			return false ;
		}
		
	}	

	int  executeShot(Move x){
		if(!isValid(x.finalPos.first,x.finalPos.second)){
			cout << "Invalid Cannon Shot.... Sorry.. Exiting..." << endl ;
			exit(-1) ;
		}
		//cout << "Color at " << x.initPos.first << " " << x.initPos.second << " "<< temp << endl ;
		//cout << "TRUE" << endl ;
		int temp = board[x.finalPos.first][x.finalPos.second] ;
		removePiece(x.finalPos.first,x.finalPos.second) ;
		board[x.finalPos.first][x.finalPos.second] = empty ;
		//cout << printBoard() << endl ;
		
		return temp;
	}

	void reverseShot(Move x,int color){

		board[x.finalPos.first][x.finalPos.second] = color ;
		AddPiece(x.finalPos.first,x.finalPos.second,color) ;

		return ;

	}


	// Add cout << printBoard()  to see state after each turn when testing outside of client
	int executeMove(Move x){
		if(!isValid(x.finalPos.first,x.finalPos.second)){
			cout << "Invalid Move.. Sorry.. Exiting..." << x.initPos.first << "   " << x.initPos.second << "  " << x.finalPos.first << "   " << x.finalPos.second << endl ;
			exit(-1) ;
		}
		int temp = board[x.initPos.first][x.initPos.second] ;
		soldier* s1 = getSoldier(x.initPos.first,x.initPos.second,temp) ;

		if(s1 == NULL){
			x.PrintMove() ;
			cout << printBoard() << endl ;

			cout << "Error could not find soldier . Exiting..." << endl ;
			exit(-1) ;
		}
		//cout << "Color at " << x.initPos.first << " " << x.initPos.second << " "<< temp << endl ;
		//cout << "TRUE" << endl ;
		int color = board[x.finalPos.first][x.finalPos.second] ;
		board[x.initPos.first][x.initPos.second] = empty ;
		removePiece(x.finalPos.first,x.finalPos.second) ;
		board[x.finalPos.first][x.finalPos.second] = temp ;
		s1->updatePos(x.finalPos) ;
		//cout << printBoard() << endl ;
		
		return color;
	}

	void reverseMove(Move x,int color){

		int temp = board[x.finalPos.first][x.finalPos.second] ;
		soldier* s1 = getSoldier(x.finalPos.first,x.finalPos.second,temp) ;
		board[x.finalPos.first][x.finalPos.second] = color ;
		board[x.initPos.first][x.initPos.second] = temp ;
		AddPiece(x.finalPos.first,x.finalPos.second,color) ;
		s1->updatePos(x.initPos) ;

		return ;

	}

	int playTurn(Move m){
		int x ;
		if(m.type == 'c'){
			x= executeShot(m) ;
		}
		else{
			x =executeMove(m) ;
		}
		//cout << game->printBoard() << endl ;
		return x ;
	}

	void reverseTurn(Move m,int color){
		if(m.type == 'c'){
			reverseShot(m,color) ;
		}
		else{
			reverseMove(m,color) ;
		}
		//cout << game->printBoard() << endl ;
		return ;
	}
};

//Refactored code for cannon attack

class Player1{
public:
	int player ;
	int n; //Columns
	int m; //Rows
	Game* game ;
	vector<vector<int>> prevboard[10] ;

	Player1(int x,int y,int w){
		player = x-1 ;
		m = y ;
		n = w;
		game = new Game(n,m) ;
		for(int k = 0 ; k < 10 ; k++){
			for(int i = 0 ; i < n ; i++){
				vector<int> temp ;
				for(int j = 0 ; j < m ; j++){
					temp.push_back(empty) ;
				}
				prevboard[k].push_back(temp) ;
			}
		}
		playGame() ;
	}

	// Not complete yet
	Move stringToMove(vector<string> &s){

		int x[4] ;
		int i=0,j = 0;
		x[0] = stoi(s[1]) ;
		x[1] = stoi(s[2]) ;
		x[2] = stoi(s[4]) ;
		x[3] = stoi(s[5]) ;
		//cout << "TEST100" << endl ;
		if(s[3] == "M")
			return Move(x[0],x[1],x[2],x[3],'s') ;
		else
			return Move(x[0],x[1],x[2],x[3],'c') ;
	}

	string moveToString(Move m){
		string s = "S " ;
		s += to_string(m.initPos.first) + " " ;
		if(m.type == 's'){
			s += to_string(m.initPos.second) + " M " ;
		}
		else{
			s += to_string(m.initPos.second) + " B " ;
		}
		s += to_string(m.finalPos.first) + " " ;
		s += to_string(m.finalPos.second)  ;
		return s ;
	}

	void opponentMove(vector<string> &st){
		Move m = stringToMove(st) ;
		game->playTurn(m) ;
	}

	bool compareBoard(vector<vector<int>> b1){
		for(int k = 0 ; k < 10 ; k++){
			bool flag = true ;
			for(int i = 0 ; i < b1.size() ; i++){
				for(int j = 0 ; j < b1[i].size() ; j++){
					//cout << "TEST3" << endl ;
					if(b1[i][j] != prevboard[k][i][j]){
						flag = false ;
						break ;
					}
				}
			}
			if(flag){
				return true ;
			}
		}
		return false ;
	}

	void copyToPrev(vector<vector<int>> b1){

		for(int i = 0 ; i < 9 ; i++){
			prevboard[i+1] = prevboard[i] ;
		}
		prevboard[0] = b1 ;
	}

	void playGame(){

		if(player == 1){
			vector<string> st ;
			string s ;
			for(int i = 0 ; i < 6 ; i++){
				cin >> s ;
				st.push_back(s);
			}
			opponentMove(st) ;
		}
		while(true){
			game->initializeCannons() ;
			pair<Move,Move> move_pair = game->getBestMove(player) ;
			Move move = move_pair.first ;
			int temp = game->playTurn(move) ;
			//cout << "TEST" << endl ;
			// // game->outfile << "Current board" << endl ;
			// for(int i = 0 ; i < m ; i++){
			// 	for(int j = 0 ; j < n ; j++){
			// 		game->outfile << game->board[j][i] << " " ;
			// 	}
			// 	game->outfile << endl ;

			// }
			// game->outfile << "\nPrevious Board" << endl ;
			// for(int i = 0 ; i < m ; i++){
			// 	for(int j = 0 ; j < n ; j++){
			// 		game->outfile << prevboard[0][j][i] << " " ;
			// 	}
			// 	game->outfile << endl ;

			// }
			// game->outfile << "\n\n" ;
			if(compareBoard(game->board)){
				game->reverseTurn(move,temp) ;
				move = move_pair.second ;
				if(!isValid(move.finalPos.first,move.finalPos.second)){
					move = game->getRandMove(player) ;
				}
				game->playTurn(move) ;
			}
			copyToPrev(game->board) ;
			// game->outfile.flush() ;
			string s = moveToString(move) ;
			cout << s << endl ;
			//outfile << game->printBoard() << endl ;
			vector<string> st ;
			for(int i = 0 ; i < 6 ; i++){
				cin >> s ;
				st.push_back(s);
			}
			opponentMove(st) ;
			temp = sqrt(game->player1.size()*game->player2.size()) ;
			if(temp < 3){
				search_depth = 9 ;
			}
			else if(temp <  4){
				search_depth = 8 ;
			}
			else if(temp < 5){
				search_depth = 7 ;
			}
			else if(temp < 7){
				search_depth = 6 ;
			}
			else if(temp < 10){
				search_depth = 5 ;
			}
		}

		game->outfile.close() ;
	}

};


int main(){
	
	int x,y,w,z ;
	srand(time(NULL));
	cin >> x>> y >> w >> z ;
		 m = y;
     n = w;
     time_left = (float)(z) ;

    if(n < 10){
    	search_depth = 5 ;
    }
    else{
    	search_depth = 4 ;
    }
   Player1 p(x,y,w) ;

    
//	 Game g(8,8) ;

//	 cout << g.printBoard() << endl;

	 // for(int i=0; i<8;i++){

	 // 	for(int j=0; j<8 ; j++){
	 // 		g.board[i][j] = 0;
	 // 	}

	 // }

	 // g.board[5][2] = white;
	 // g.board[6][1] = white;
	 // g.board[7][0] = white;

	 //g.board[3][4] = black;
	//  cout << g.printBoard() << endl;
	 // g.initializeCannons();
	 // vector<Move> shots = g.getCannonShots(g.player1_cannon);
	 // for (int i=0; i<g.player1_cannon.size() ; i++){
	 // 	cout << g.player1_cannon[i].validShots << endl;
	 // }
//	  for(int i = 0 ; i < shots.size() ; i++){

	//  	x = g.playTurn(shots[i]) ;
	//  	shots[i].PrintMove() ;
	//  	cout << g.printBoard() << endl ;
	//  	g.reverseTurn(shots[i],x) ;
//	  }
	// x = g.playTurn(shots[0]) ;
	// shots[0].PrintMove();
	// 	 cout << g.printBoard() << endl ;
	//  g.reverseShot(shots[0],x) ;
	//  cout << g.printBoard() << endl ;
	// return 0 ;
	


}

