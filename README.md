# KUHN POKER SOLVER IN C++

## SUMMARY
Solving Kuhn poker in c++ by creating a binary tree
where each node represents a decision in the game tree. 
Using a counter factual regret minimization algorithm in
order to reduce the regret and find the Nash equilibrium.
Hoping to expand this out into a actual poker solver.

### KUHN POKER DESCRIPTION
Kuhn poker is a simplified version of poker. There are only three
possible cards a Jack, a Queen, and a King. A king is the best card
and a Queen the second best card and a Jack is the worst card. Each
Player is randomy dealt one of these random three cards. The entire
deck is comprised only of these three cards so each players hand is
guranteed to be unique and the cards cannot be seen by the other player.
Before the cards are dealt each player also puts a single chip into
the pot.Once the cards are dealt Player 1 can either bet or check. 
If Player1 bets Player 2 can only call or fold. If Player 1 checks 
player 2 can either bet or check. If player 2 checks the player with
the best card wins. If Player 2 bets player 1 can either call the bet
or fold. If he calls the player with the best hand wins. Each bet
can only be for 1 blind. Meaning the minimum pot is 2 blinds
and the maximum pot is 4 blinds meaning the total amount you can win
is 2 blinds and the total amount you can lose is 2 blinds. With 
perfect play player 2 should win about 1/18 blinds per hand.

### DESCRIPTION OF ALGORITHM 
In this solution CFRM (counter factual regret minimization) is used
to find the optimal strategy. We create a game tree where the the left
always represents check and the right always represents bet. A check
after a bet is considered a fold and a bet after a bet is considered 
a call. We start by finding the the payoff at each node recursivley. 
Once we reach a terminal node the payoff is just how much each player 
would win if player 1 had hand X and player 2 had hand Y. We then
go up to the parent node where regret for the child nodes are calculated
using CFRM. The regret is the difference between our current mixed
strategy and only chosing a particular node 100% of the time scaled
by the percentae chance that the other player would allow us to reach
this branch in the game tree.
For instance if we wanted to calculate the regret of folding when
bet to we would determine the payout of folding which is always -1
and the payout at our mixed strategy meaning foling at X% and calling 
at Y %. This difference is our regret and our next strategy will be
directly porportional to our total regret at each node. This mixed
strategy will become our expected value for the parent node and 
we do the same thing until we reach the top of the game tree. Once 
all regrets are updated our new strategy will be a normalized percentage
of the regrets at each branch. meaning we sum all positive regrets
at a branch in the game tree and divide the regrets by the total and 
set an nodes with a negative regret to 0. If all nodes have a negative
regret we set each node at that branch of the game tree to a unfiform
distribution.We do this until a Nash equilibrium is found.
NOTE THAT THE FINAL STRATEGY IS NOT THE LAST STRATEGY PLAYED BUT A 
NORMALIZED AVERAGE OF ALL STRATEGIES PLAYED 
### HOW THE GAME TREE IS REPRESENTED
The game tree is a binary tree where each node keeps track of the 
regrets and strategies for each hand. Because player 1 and player 2
nodes are calculated differently each time we calculate the EV for
the parent node we multiply the result by -1 and flip the x and y 
cordiantes in the array which represent which card is playing against
another card so as to avoid doing a traversal over the game tree twice
to calculate all regrets. The reason we have to reverse the EV and flip
the axis is because each EV is calculated at whatever depth of the game
tree the terminal node is at and each parent node is the opposite of it's 
children. We reverse it because if player 1 folds this is a positive 
result for player 2 and we flip the axis so as to avoid duplicate 
calculations so we don't need to store the result of K v Q and Q v K.

### FILES


| FILE                                                                                                                                                                                                                                                                        | DESCRIPTION                                                                                                                                                        |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [main.cpp](main.cpp)                                                                                                                                                                                                                                                        | Runs the program                                                                                                                                                   |
| [Node.cpp](Node.cpp)                                                                                                                                                                                                                                                        | Contains each decision node. Stores the current strategory for each card along with the expected value of each card against any other card                         |
| [Tree.cpp](Tree.cpp)                                                                                                                                                                                                                                                        | Creates a game tree and generates the nodes. Responsible for calling the proper functions and running the CFRM algo                                                |
| [stupid_python_version.py](stupid_python_version.py) | A manual way of implimenting the algorithm. Included it if anyone wants to see a very straightforward approach of how to solve the problem before it is abstracted | 


### TO DO

1. Clean up code 
2. add threads (not for performance reasons but to steal logic for when I expand this out to a full solver) 
3. Think of more things to do so I can procrastinate making a real poker solver
