# Cannon
Simulator supporting a user interface for Cannon, an abstract strategy board game.

## Details
This is a course assignment for the graduate-level Artificial Intelligence course taught by [**Prof. Mausam**](http://homes.cs.washington.edu/~mausam).  
The assignment documentation can be found [here](http://www.cse.iitd.ac.in/~mausam/courses/col333/autumn2019/A5/A5.pdf)

### Teaching Assistants
+ [Divyanshu Saxena](https://github.com/DivyanshuSaxena)
+ [Pratyush Maini](https://github.com/pratyush911)
+ [Shashank Goel](https://github.com/goelShashank007)
+ [Vipul Rathore](https://github.com/rathorevipul28)

## Rules
The rules of the original game can be found [here](https://nestorgames.com/rulebooks/CANNON_EN.pdf)

### Piazza discussions:  
+ The soldier can retreat back if and only if it is adjacent to an enemy soldier.
+ The soldier can kill an enemy soldier or a townhall in a retreat step.
+ Cannon shifts along its length cannot capture a soldier or a townhall.
+ Blank cannon shots are allowed (take care of stagnant game) and are considered valid moves.


### Stalemate
Case 1: Player A (or B) kills the last soldier of Player B (or A).  
Case 2: Both Players have soldiers left, but Player B (or A) has no immediate moves to play

### Stagnant Game
If exactly the same board position is repeated thrice after the move of a player then the player is said to have forced a  Stagnant Game.

## Dependencies
+ Python2.7
+ Chrome Webdriver
+ Jinja2
+ Multiset
+ Numpy
+ Selenium

```sh
pip install -r requirements.txt
```

Download the chrome driver executable according to your chrome version from the following link:
https://chromedriver.chromium.org/downloads

You can check you chrome version following the steps below:
- Launch Google Chrome.
- Click on the icon in the upper right corner that looks like 3 short bars.
- Select About Google Chrome to display the version number.

## Main Files
+ `game.py` - This has an instance of the game. It can be run locally to hand play a game of Cannon or re-play a recorded game. Should be run in `GUI` mode to make game board visible.
+ `RandomPlayer.py` - This is an implementation of a random bot. It is a good place to start understanding the flow of the game and the various game states.
+ `client.py` - This will encapsulate your process and help it connect to the game server.
  > `ip` (mandatory) - The Server IP.  
  > `port` (mandatory) - The Server Port.  
  > `exe` (mandatory) - The Executable.  
  > `mode` (optional) - The View Mode ('GUI' / 'CUI'). Default: 'CUI'  
+ `server.py` - This connects the clients and manages the transfer of information.
  > `port` (mandatory) - The Server Port.  
  > `ip` (optional) - The Server IP. Default: 0.0.0.0   
  > `n` (optional) - The Board Row Size. Default: 8  
  > `m` (optional) - The Board Column Size. Default: 8  
  > `NC` (optional) - Number of Clients. Default: 2  
  > `TL` (optional) - Time Limit. Default:150  
  > `LOG` (optional) - The Log File.  

## Run Instructions
Here are the sample instructions used to match two random players against each other over the server network.

### Setup Server
```sh
python server.py 10000 -n 8 -m 8 -NC 2 -TL 150 -LOG server.log
```
### Setup Client 1
```sh
export PATH=$PATH:'/home/chrome_driver_directory_path'
python client.py 0.0.0.0 10000 RandomPlayer.py -mode GUI
```

### Setup Client 2
```sh
export PATH=$PATH:'/home/chrome_driver_directory_path'
python client.py 0.0.0.0 10000 RandomPlayer.py
```

## Gameplay
The game play consists of the players executing a sequence of moves in a single turn.
A move is a triple: `type` `x` `y`.  

### Movetype
+ `S` - Select a soldier
+ `M` - Move a soldier
+ `B` - Throw a Bomb

### Board Settings
The board is an **n x m** board.
The top-left corner point is the origin.
The horizontal direction towards the right is the positive x-axis.
The vertical direction towards down is the positive y-axis.
The indexing begins with 0 in both the directions.

#### Move a Soldier
To move a soldier from (1, 2) to (2, 4).  
`S 1 2 M 2 4`

#### Throw a Bomb
To throw a bomb, select any of the soldiers of a cannon, and throw it at any viable target of the cannon(s).  
`S 2 4 B 6 4`

### Replay
A server.log file is created during the gameplay that consist of the moves played in the game. You can simulate/re-run it using the following command:
```sh
python game.py server.log
```

## Scoring
At the end of a game both players will be given a score. The scoring for all the three configurations of the game will be as follows: 

### The Town Hall Margin
This score will be based on the extent of victory. It is calculated as follows:  

|Town Halls killed by A	|Town Halls killed by B	|Town Hall Margin Score: A	|Town Hall Margin Score: B|
| ------------- | ------------- | ------------- | ------------- | 
| 2 | 0 | 10 | 0 |
| 2 | 1 | 8  | 2 |

#### Stalemate

**Case 1**: Player A kills the last soldier of Player B.

|Town Halls killed by A	|Town Halls killed by B	|Town Hall Margin Score: A	|Town Hall Margin Score: B|
| ------------- | ------------- | ------------- | ------------- | 
| 1 |	0 |	10 |	0 |
| 0 |	0 |	8  |	2 |
| 1 |	1 |	8  |	2 |
| 0 |	1 |	6  |	4 |

**Case 2**: Both Players have soldiers left, but Player B has no immediate moves to play

|Town Halls killed by A	|Town Halls killed by B	|Town Hall Margin Score: A	|Town Hall Margin Score: B|
| ------------- | ------------- | ------------- | ------------- | 
| 1 |	0 |	8 |	2 |
| 0 |	0 |	6 |	4 |
| 1 |	1 |	6 |	4 |
| 0 |	1 |	4 |	6 |

#### Stagnant Game

Player A forced a Stagnant Game.

|Town Halls killed by A	|Town Halls killed by B	|Town Hall Margin Score: A	|Town Hall Margin Score: B|
| ------------- | ------------- | ------------- | ------------- | 
| 1 |	0 |	7 |	3 |
| 0 |	0 |	5 |	5 |
| 1 |	1 |	5 |	5 |
| 0 |	1 |	3 |	7 |

#### Timeout or Invalid Move

**Note:** In case a player suffers a TIMEOUT or INVALID move, it will automatically lose the game and it will count as a (2 - *x*) defeat towards the player and a (*x* - 2) win for the opponent, where *x* is the number of Town Halls killed by the opponent. 

### The Army Margin
This score directly depends on the number of soldiers you have left at the end of the game. It is calculated as follows:  
```Army Margin Score = # (Soldiers Remaining) / 100```

### Final Score
The final score is simply: ```(Town Hall Margin Score).(Army Margin Score)```
Example. Assume the following:  
Player 1 killed 2 Town Halls and has 12 soldiers left on the board.  
Player 2 killed 1 Town Hall and has 9 soldiers left on the board.  
Player 1 score will be: **8.12**  
Player 2 score will be: **2.09**  

### General Approach for the player bot

* The player Bot is A5.cpp
* We applied a general Mini-max algorithm with an initial depth assigned as:
    * 5 for 8*8 board
    * 4 for other configurations
* Then, we had the search depth being changed along with the game as the game proceeds. We took an
approximation that the progress of the game can be represented as a GM of the number of the soldiers
for the two players left. And the game would be progressed more if this mean is less
* We also applied alpha-beta pruning. For that, we tried to keep a good node ordering by evaluating the moves in this order:
    * Cannon_movement > Cannon_attack > Soldier_movement 
* Also, as an optimization for the alpha-beta procedure to limit the space being utilized, we would do a reverse move after the mini-max calculations for a corresponding node are carried out, so that we don’t save the node corresponding to that move and the initial board configuration is restored on the modified board configuration itself
* Also, we kept a bound for the time of execution of a move as a minimum of 6 seconds and time_left/15

### The Eval function

* Perhaps the most important part of the entire task, we spent a lot of time on improving this
function by trying out different parameters for an eval function or taking two different eval functions and observing battles between them and trying to look for errors in those implementations or trying to find better parameters (This might seem naïve but it’s worth mentioning since without proper observations it is not possible to obtain a good eval function and also since no deep learning methods were implemented to learn the exact eval function. Also it was essential that these observations were made for all the board configurations as well because the functions set for one board configuration wouldn’t work for the other configuration) 
* So, in general, we had our eval function having the following considerations: 

  1. Town hall scores: For the different cases of stalemates and absolute wins as described above
  2. Army Margins: For making the player to try to kill the soldiers of the opponent and to try to save their soldiers. Kept as: Soldiers_left/3
  3. End Game Factor: A function which declines linearly as the game proceeds (As a function of the sum of the number of soldiers left for the two players) 
  4. Middle Game Factor: A function which would start from 0, increases to a certain point (Decided as the exact mid-game point) and then declines again reaching a low value in the end-game (As a function of the sum of the number of soldiers left for the two players)
  5. Eight Factor: This was specifically added for the 8 * 8 board configurations. This was to keep a check for the player getting in the two modes: Defensive and Aggressive as per the configuration of the game. (For keeping things simple, it was just done by a binary thresholding rather than taking a  function). Its value of 1 would mean that the player will be aggressive and the value of 0.6 would mean that it should be relatively defensive
  6. Positional Advantage: This factor was introduced to make the player very aggressive by being defined as the sum of the positions of the soldiers of the players (times some constant C) raised to some power alpha (Between 1 and 2), thus giving a rule that, “The soldiers which are already closer to the area of the opponent player will be more likely to move forward by giving them an advantage for the same”. Multiplied this value by the End_Game_Factor (Plus a variable dependent on the army margins), so that it would ensure all the soldiers to be moving ahead in the end, rather than forming cannons. (It was a heuristic designed by us to make sure that the lone soldiers left for the player will try their best to kill the opponent town-halls) Also, the Eight_Factor was multiplied to reduce the aggression of the player in the states where the player should be playing defensively. The start is surely mean to be aggressive, trying to move its cannons as forward as possible
  7. Orientation Advantage: This factor was introduced for making the player form more meaningful cannons as per the configuration of the game. Different weights were assigned to the different types of cannons, like Horizontal or Vertical etc., and they were added up. Also, these weights weren’t constant and they would change along with the configuration of the game as a function of the End_Game_Factor. Thus giving some cannons more preference over others as the game proceeds. Also, for the 8 * 8 configuration, as a correction for the aggressive approach developed, we gave a fixed priority to certain kinds of horizontal cannons being formed so that they can act as a nice defense and try to prevent the other soldiers or cannons from killing its town halls straightaway. This factor was multiplied with the Middle_Game_Factor, for facilitating the cannon formation in the middle game and making the game aggressive in the start game and end game

* Thus, the eval function can be defined as
    + Eval = dfgdf
  






