#Author: coleman7245
#Project: Negamax Tic-Tac-Toe Challenge
#Last Edit: Thursday, February 14, 2019

def main(args):
    games = [TTT(), TTT(), TTT()]
    
    playGames(games, opponent, 9)
	
    return 0
    
def negamax(game, depthLeft):
    # If at terminal state or depth limit, return utility value and move None
    if game.isOver() or depthLeft == 0:
        return game.getUtility(), None
    # Find best move and its value from current state
    bestValue = -float('infinity')
    bestMove = None
    for move in game.getMoves():
        # Apply a move to current state
        game.makeMove(move)
        # Use depth-first search to find eventual utility value and back it up.
        #  Negate it because it will come back in context of next player
        value, _ = negamax(game, depthLeft-1)
        # Remove the move from current state, to prepare for trying a different move
        game.unmakeMove(move)
        if value is None:
            continue
        value = - value
        if value > bestValue:
            # Value for this move is better than moves tried so far from this state.
            bestValue = value
            bestMove = move
    return bestValue, bestMove
    
def negamaxIDS(game, maxDepth):
    for depth in range(maxDepth + 1):
        result = negamax(game, depth)
        if result[0] == game.getWinningValue():
            return result
    return result
    
def negamaxab(game, depthLeft, alpha, beta):
    # If at terminal state or depth limit, return utility value and move None
    if game.isOver() or depthLeft == 0:
        return game.getUtility(), None
    # Find best move and its value from current state
    bestValue = -float('infinity')
    bestMove = None
    for move in game.getMoves():
        # Apply a move to current state
        game.makeMove(move)
        # Use depth-first search to find eventual utility value and back it up.
        #  Negate it because it will come back in context of next player
        value, _ = negamaxab(game, depthLeft-1, -beta, -alpha)
        # Remove the move from current state, to prepare for trying a different move
        game.unmakeMove(move)
        if value is None:
            continue
        value = - value
        if value > bestValue:
            # Value for this move is better than moves tried so far from this state.
            bestValue = value
            bestMove = move
        if value > alpha:
            alpha = value
        if alpha >= beta:
            break
    return bestValue, bestMove
    
def negamaxIDSab(game, maxDepth):
    alpha = -float('infinity')
    beta = float('infinity')
    for depth in range(maxDepth + 1):
        result = negamaxab(game, depth, alpha, beta)
        if result[0] == game.getWinningValue():
            return result
    return result
    
def ebf(nNodes, depth, precision=0.01):
    if depth <= 0:
        return nNodes
    elif nNodes <= 0:
        return 0
    else:
        originalHi = 1
        hi = originalHi
        increment = 1
        lo = 0
        formula = 0
        while True:
            #print('hi =', hi)
            if (hi != 1):
                formula = ((1 - (hi ** (depth + 1))) / (1 - hi))
                #print('formula =', formula)
            if abs(formula - nNodes) <= precision:
                return hi
            #print('lo =', lo)
            if (lo != 1):
                formula = ((1 - (lo ** (depth + 1))) / (1 - lo))
                #print('formula =', formula)
            if abs(formula - nNodes) <= precision:
               return lo
            middle = (lo + hi) / 2
            #print('middle =', middle)
            if (middle != 1):
                formula = ((1 - (middle ** (depth + 1))) / (1 - middle))
                #print('formula =', formula)
            if abs(formula - nNodes) <= precision:
                return middle
            if abs(hi - lo) <= precision:
                originalHi += increment
                #print('originalHi =', originalHi)
                hi = originalHi
                lo = 0
            elif lo > nNodes:
                increment *= .1
                originalHi = 1
                hi = originalHi
                lo = 0
            else:
                if formula > nNodes:
                    hi = (hi + middle) / 2
                else:
                    lo = (lo + middle) / 2
                    
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
        
def opponent(board):
    return board.index(' ')

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
            
def playGames(games,opponent,maxDepth):
    playGameS(negamax,games[0],opponent,maxDepth)
    print('negamax made',len(games[0].locations('X')), 'moves.',games[0].getMovesExplored(),'moves explored for an ebf of',ebf(games[0].getMovesExplored(),maxDepth))
    playGameS(negamaxIDS,games[1],opponent,maxDepth)
    print('negamaxIDS made',len(games[1].locations('X')), 'moves.',games[1].getMovesExplored(),'moves explored for an ebf of',ebf(games[1].getMovesExplored(),maxDepth))
    playGameS(negamaxIDSab,games[2],opponent,maxDepth)
    print('negamaxIDSab made',len(games[2].locations('X')), 'moves.',games[2].getMovesExplored(),'moves explored for an ebf of',ebf(games[2].getMovesExplored(),maxDepth))
    


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
