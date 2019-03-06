#Author: Derek Coleman
#Project: Negamax Tic-Tac-Toe Challenge
#Last Update: 3/6/19

#Method Summary: The main method of execution.
def main(args):
	#Create three tic-tac-toe games.
    games = [TTT(), TTT(), TTT()]
    
    #Allow the AI to play the tic-tac-toe games.
    playGames(games, opponent, 9)
	
	#Return 0, indicating success.
    return 0

#Method Summary: The negamax AI advesarial routine.
def negamax(game, depthLeft):
    #If the the game is over or the gameplay extends beyond the depth:
    if game.isOver() or depthLeft == 0:
        return game.getUtility(), None
    #bestValue: The best cost that defines the best move.
    bestValue = -float('infinity')
    #bestMove: The best move chosen by the AI.
    bestMove = None
    #For every move in the list of available moves:
    for move in game.getMoves():
        #Make a move in the game.
        game.makeMove(move)
        #Find the utility value using the recursive call.
        value, _ = negamax(game, depthLeft-1)
        #Back up one move in order to try another one.
        game.unmakeMove(move)
        #If the value is invalid:
        if value is None:
			#Skip this move and continue with the next one.
            continue
        #Negate the value for the next player.
        value = - value
        #If this value is better than the previous best value.
        if value > bestValue:
            #Replace the previous best value with the current one.
            bestValue = value
            #Replace the previous best move with the current one.
            bestMove = move
    #Return the best move and the cost attached to it.
    return bestValue, bestMove

#Method Summary: Runs the negamax as an iterative algorithm.    
def negamaxIDS(game, maxDepth):
	#Every level of depth:
    for depth in range(maxDepth + 1):
		#Store the result from the negamax algorithm.
        result = negamax(game, depth)
        #If the value of the result matches the game winning value.
        if result[0] == game.getWinningValue():
			#Return the result.
            return result
    #Return the result after the depth limit has been reached.
    return result

#Method Summary: The recursive variation of the negamax algorithm with alpha/beta pruning.
def negamaxab(game, depthLeft, alpha, beta):
    # If the game is over or the depth limit has been reached:
    if game.isOver() or depthLeft == 0:
		#Return the game's utility value and None as the valid moveset.
        return game.getUtility(), None
    #bestValue: The best cost that defines the best move.
    bestValue = -float('infinity')
    #bestMove: The best move chosen by the AI.
    bestMove = None
    #For every move in the move list:
    for move in game.getMoves():
        #make a move given the current state.
        game.makeMove(move)
        #Find the utility value using the recursive call.
        #Negate and reverse the beta and alpha values for the next player.
        value, _ = negamaxab(game, depthLeft-1, -beta, -alpha)
        #Reverse the move in order to test the next move.
        game.unmakeMove(move)
        #If the value invalid:
        if value is None:
			#Skip this iteration and move onto the next.
            continue
        #Negate the value for the next player.
        value = - value
        #If this value is better than the previous next value.
        if value > bestValue:
            #Replace the previous best value with this value.
            bestValue = value
            #Replace the previous best move with this move.
            bestMove = move
        #If this value is greater than the alpha value:
        if value > alpha:
			#Replace the previous alpha value with this one.
            alpha = value
        #If the alpha value is better or equal to the beta value:
        if alpha >= beta:
			#Break out of the loop.
            break
    #Return the best move, along with the value associated with it.
    return bestValue, bestMove
    
#Method Summary: The itertive variation of the negamax algorithm with alpha/beta pruning.
def negamaxIDSab(game, maxDepth):
	#alpha: Value that controls the amount of nodes generated for efficiency.
    alpha = -float('infinity')
    #beta: Another value, in conjunction with the alpha value, limits the amount of nodes generated.
    beta = float('infinity')
    #For every level of depth:
    for depth in range(maxDepth + 1):
		#Run the negamax algorithm with alpha beta pruning.
        result = negamaxab(game, depth, alpha, beta)
        #If the result value is the same as the game winning value:
        if result[0] == game.getWinningValue():
			#Return the result.
            return result
    #Return the result if the depth limit has been reached.
    return result
    
#Calculates the effective branching factor of the algorithm.
def ebf(nNodes, depth, precision=0.01):
   #If the depth is less than or equal to 0:
   if depth <= 0:
      #Return the number of nodes.
      return nNodes
   #If the number of nodes is less than or equal to 0:
   elif nNodes <= 0:
      #Return 0.
      return 0
   #All parameters are ligitimate, so calculate the effective branching factor using the binary search.
   else:
      #Increment used to increase the hi end of the range.
      increment = 1
      #The original hi starts at 1.
      originalHi = 1
      #Set hi to be evaluated and returned with the original hi.
      hi = originalHi
      #Set the lo end of the range as 0.
      lo = 0
      #Formula as a function of hi, lo, middle, and depth.
      formula = 0
      #Continue the loop until a value is returned.
      while True:
         #If hi does NOT equal 1:
         if (hi != 1):
            #Compute the formula using the hi.
            formula = ((1 - (hi ** (depth + 1))) / (1 - hi))
            #If the distance between the formula's output and the numer of nodes is less than or equal to the percision:
         if abs(formula - nNodes) <= precision:
            #Return the hi.
            return hi
         #If the lo does NOT equal 1:
         if (lo != 1):
            #Calculate the forumula using the lo.
            formula = ((1 - (lo ** (depth + 1))) / (1 - lo))
         #If the distance between the formula's output and the numer of nodes is less than or equal to the percision:
         if abs(formula - nNodes) <= precision:
            #Return the lo.
            return lo
         #Calculate the middle position.
         middle = (lo + hi) / 2
         #If the middle does NOT equal 1:
         if (middle != 1):
            #Calculate the formula using the middle.
            formula = ((1 - (middle ** (depth + 1))) / (1 - middle))
         #If the distance between the formula's output and the number of nodes is less than or equal to the precision:
         if abs(formula - nNodes) <= precision:
            #Return the middle.
            return middle
         #If the distance between the hi and lo is less than or equal to the precision:
         if abs(hi - lo) <= precision:
            #Increment the original hi by a decreasing increment.
            originalHi += increment
            #Set the hi to the original hi
            hi = originalHi
            #Reset the lo to 0.
            lo = 0
         #If the lo is greater than the number of nodes:
         elif lo > nNodes:
            #Scal the increment by a factor of .1.
            increment *= .1
            #Set the original hi to 1
            originalHi = 1
            #Set hi to the original hi.
            hi = originalHi
            #Set the lop to 0.
            lo = 0
         #If all else fails:
         else:
            #If the formula's output is greater than the number of nodes:
            if formula > nNodes:
               #Advance the hi with the middle.
               hi = (hi + middle) / 2
            #Only one option remains:
            else:
               #Advance the lo using the middle.
               lo = (lo + middle) / 2

#Tic-Tac-Toe class written by Chuck Anderson.                    
class TTT(object):

    def __init__(self):
        self.movesExplored = 0
        self.board = [' ']*9
        self.player = 'X'
        if False:
            self.board = ['X', 'X', ' ', 'X', 'O', 'O', ' ', ' ', ' ']
            self.player = 'O'
        self.playerLookAHead = self.player

    def locations(self, c):
        return [i for i, mark in enumerate(self.board) if mark == c]

    def getMoves(self):
        moves = self.locations(' ')
        return moves

    def getUtility(self):
        whereX = self.locations('X')
        whereO = self.locations('O')
        wins = [[0, 1, 2], [3, 4, 5], [6, 7, 8],
                [0, 3, 6], [1, 4, 7], [2, 5, 8],
                [0, 4, 8], [2, 4, 6]]
        isXWon = any([all([wi in whereX for wi in w]) for w in wins])
        isOWon = any([all([wi in whereO for wi in w]) for w in wins])
        if isXWon:
            return 1 if self.playerLookAHead is 'X' else -1
        elif isOWon:
            return 1 if self.playerLookAHead is 'O' else -1
        elif ' ' not in self.board:
            return 0
        else:
            return None  ########################################################## CHANGED FROM -0.1
        
    def getWinningValue(self):
        return 1

    def isOver(self):
        return self.getUtility() is not None

    def makeMove(self, move):
        self.movesExplored += 1
        self.board[move] = self.playerLookAHead
        self.playerLookAHead = 'X' if self.playerLookAHead == 'O' else 'O'

    def changePlayer(self):
        self.player = 'X' if self.player == 'O' else 'O'
        self.playerLookAHead = self.player

    def unmakeMove(self, move):
        self.board[move] = ' '
        self.playerLookAHead = 'X' if self.playerLookAHead == 'O' else 'O'
        
    def getMovesExplored(self):
        return self.movesExplored

    def __str__(self):
        s = '{}|{}|{}\n-----\n{}|{}|{}\n-----\n{}|{}|{}'.format(*self.board)
        return s

#opponent method written by Chuck Anderson.        
def opponent(board):
    return board.index(' ')

#playGame method written by Chuck Anderson.
def playGame(game,opponent,depthLimit):
    print(game)
    while not game.isOver():
        score,move = negamax(game,depthLimit)
        if move == None :
            print('move is None. Stopping.')
            break
        game.makeMove(move)
        print('Player', game.player, 'to', move, 'for score' ,score)
        print(game)
        if not game.isOver():
            game.changePlayer()
            opponentMove = opponent(game.board)
            game.makeMove(opponentMove)
            print('Player', game.player, 'to', move)
            print(game)
            game.changePlayer()

#playGameS method written by Chuck Anderson.            
def playGameS(searchF,game,opponent,depthLimit):
    print(game)
    while not game.isOver():
        score,move = searchF(game,depthLimit)
        if move == None :
            print('move is None. Stopping.')
            break
        game.makeMove(move)
        print('Player', game.player, 'to', move, 'for score' ,score)
        print(game)
        if not game.isOver():
            game.changePlayer()
            opponentMove = opponent(game.board)
            game.makeMove(opponentMove)
            print('Player', game.player, 'to', move)
            print(game)
            game.changePlayer()

#playGames method written by Chuck Anderson.            
def playGames(games,opponent,maxDepth):
    playGameS(negamax,games[0],opponent,maxDepth)
    print('negamax made',len(games[0].locations('X')), 'moves.',games[0].getMovesExplored(),'moves explored for an ebf of',ebf(games[0].getMovesExplored(),maxDepth))
    playGameS(negamaxIDS,games[1],opponent,maxDepth)
    print('negamaxIDS made',len(games[1].locations('X')), 'moves.',games[1].getMovesExplored(),'moves explored for an ebf of',ebf(games[1].getMovesExplored(),maxDepth))
    playGameS(negamaxIDSab,games[2],opponent,maxDepth)
    print('negamaxIDSab made',len(games[2].locations('X')), 'moves.',games[2].getMovesExplored(),'moves explored for an ebf of',ebf(games[2].getMovesExplored(),maxDepth))
    
#If the main method is invoked:
if __name__ == '__main__':
	#Import the system package.
    import sys
    #Run the main method.
    sys.exit(main(sys.argv))
