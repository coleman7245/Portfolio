#Author: coleman7245
#Project: Iterative Deepening vs Depth Limited Search
#Last Edit: Thursday, February 14, 2019

import random

def main(args):
    startState_8p = [0, 1, 3, 2, 4, 5, 6, 7, 8]
    goalState_8p = [1, 3, 0, 2, 4, 5, 6, 7, 8]
    startState_peg15 = [0, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P']
    goalState_peg15 = [0, 0, 0, 'P', 0, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P']
    
    print('Depth-Limited Search Solution with 15 Pegs:\n')
    path_peg15 = depthLimitedSearch(startState_peg15, goalState_peg15, actionsF_peg15, takeActionF_peg15, 15)
    printPath_peg15(startState_peg15, goalState_peg15, path_peg15)
    print('\nIterative-deepening Search Solution with 15 Pegs:\n')
    path_peg15 = iterativeDeepeningSearch(startState_peg15, goalState_peg15, actionsF_peg15, takeActionF_peg15, 15)
    printPath_peg15(startState_peg15, goalState_peg15, path_peg15)
	
    goalState_peg15 = randomGoalState_peg15(startState_peg15, actionsF_peg15, takeActionF_peg15, 20)
    startState_8p = randomStartState_8p(goalState_8p, actionsF_8p, takeActionF_8p, 10)
	
    path_8p = iterativeDeepeningSearch(startState_8p, goalState_8p, actionsF_8p, takeActionF_8p, 20)
    path_peg15 = iterativeDeepeningSearch(startState_peg15, goalState_peg15, actionsF_peg15, takeActionF_peg15, 20)
	
    print('Iterative Deepening Search Solution with 8 Pieces in Random States:')
    printPath_8p(startState_8p, goalState_8p, path_8p)
    print('Iterative Deepening Search Solution with 15 Pieces in Random States:')
    printPath_peg15(startState_peg15, goalState_peg15, path_peg15)
	
    return 0

def findBlank_8p(state):
        r = 0
        c = 0
        for s in state:
            if s == 0:
                return (r, c)
            else:
                c += 1
                if c == 3:
                    r += 1
                    c = 0
        return 'Blank not found!'
        
def actionsF_8p(state):
    
    def findBlank_8p(state):
        r = 0
        c = 0
        for s in state:
            if s == 0:
                return (r, c)
            else:
                c += 1
                if c == 3:
                    r += 1
                    c = 0
    
    actions = []
    rowNColumn = findBlank_8p(state)
    if rowNColumn[1] > 0:
        actions.append('left')
    if rowNColumn[1] < 2:
        actions.append('right')
    if rowNColumn[0] > 0:
        actions.append('up')
    if rowNColumn[0] < 2:
        actions.append('down')
    return actions
    
def actionsF_peg15(state):
    
    def findBlank_peg15(state):
        r = 0
        c = 0
        blanks = []
        for s in state:
            if s == 0:
                blanks.append((r, c))
            c += 1
            if c > r:
                r += 1
                c = 0
        return blanks
    
    def findPeg_peg15(state):
        r = 0
        c = 0
        pegs = []
        for s in state:
            if s == 'P':
                pegs.append((r, c))
            c += 1
            if c > r:
                r += 1
                c = 0
        return pegs
    
    def findNearbyPegs_peg15(space, pegs):
        nearbyPegs = []
        for p in pegs:
            if p == (space[0] - 1, space[1] - 1) or p == (space[0] - 1, space[1]) or p == (space[0], space[1] + 1)or p == (space[0] + 1, space[1] + 1) or p == (space[0] + 1, space[1]) or p == (space[0], space[1] - 1):
                nearbyPegs.append(p)
        return nearbyPegs
    
    def findNearbyBlanks_peg15(space, blanks):
        nearbyBlanks = []
        for b in blanks:
            if b == (space[0] - 1, space[1] - 1) or b == (space[0] - 1, space[1]) or b == (space[0], space[1] + 1) or b == (space[0] + 1, space[1] + 1) or b == (space[0] + 1, space[1]) or b == (space[0], space[1] - 1):
                nearbyBlanks.append(b)
        return nearbyBlanks
    
    def findNearbyMoves_peg15(space):
        nearbyMoves = []
        if space[0] - 2 >= 0:
            nearbyMoves.append((space[0] - 2, space[1]))
            if space[1] - 2 >= 0:
                nearbyMoves.append((space[0] - 2, space[1] - 2))
        if space[0] + 2 <= 4:
            nearbyMoves.append((space[0] + 2, space[1]))
            if space[1] + 2 <= space[0] + 2:
                nearbyMoves.append((space[0] + 2, space[1] + 2))
        if space[1] - 2 >= 0:
            nearbyMoves.append((space[0], space[1] - 2))
        if space[1] + 2 <= space[0]:
            nearbyMoves.append((space[0], space[1] + 2))
        return nearbyMoves
    
    blanks = findBlank_peg15(state)
    pegs = findPeg_peg15(state)
    actions = []
    for p in pegs:
        nearbyMoves = findNearbyMoves_peg15(p)
        nearbyPegs = findNearbyPegs_peg15(p, pegs)
        for np in nearbyPegs:
            nearbyBlanks = findNearbyBlanks_peg15(np, blanks)
            for nb in nearbyBlanks:
                if nb in nearbyMoves:
                    actions.append((p, np, nb))
    return actions
    
def takeActionF_8p(state, action):
    temp = 0
    newState = [s for s in state]
    if action == 'down':
        for i in range(len(newState)):
            if newState[i] == 0:
                temp = newState[i]
                newState[i] = newState[i + 3]
                newState[i + 3] = temp
                break
    elif action == 'up':
        for i in range(len(newState)):
            if newState[i] == 0:
                temp = newState[i]
                newState[i] = newState[i - 3]
                newState[i - 3] = temp
                break
    elif action == 'right':
        for i in range(len(newState)):
            if newState[i] == 0:
                temp = newState[i]
                newState[i] = newState[i + 1]
                newState[i + 1] = temp
                break
    else:
        for i in range(len(newState)):
            if newState[i] == 0:
                temp = newState[i]
                newState[i] = newState[i - 1]
                newState[i - 1] = temp
                break
    return newState
    
def convertRCToInt(t):
        row = int(t[0])
        col = int(t[1])
        num = 0
        for i in range(row+1):
            num += (i + 1)
        num -= (row + 1 - col)
        return num
        
def takeActionF_peg15(state, action):
    
    def convertRCToInt(t):
        row = int(t[0])
        col = int(t[1])
        num = 0
        for i in range(row+1):
            num += (i + 1)
        num -= (row + 1 - col)
        return num
    
    newState = [s for s in state]
    startPeg = int(convertRCToInt(action[0]))
    middlePeg = int(convertRCToInt(action[1]))
    endPeg = int(convertRCToInt(action[2]))
    
    newState[startPeg] = 0
    newState[middlePeg] = 0
    newState[endPeg] = 'P'
    
    return newState
    
def printState_8p(state):
    for i in range(len(state)):
        if i % 3 == 0:
            print(state[i], state[i+1], state[i+2])
            
def printState_peg15(state):
    for i in range(len(state)):
        if i == 0:
            print(' ', ' ', ' ', ' ', state[i], ' ', ' ', ' ', ' ')
        elif i == 1:
            print(' ', ' ', ' ', state[i], ' ', state[i+1], ' ', ' ', ' ')
        elif i == 3:
            print(' ', ' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', ' ')
        elif i == 6:
            print(' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ')
        elif i == 10:
            print(state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ', state[i+4])
            
def printPath_8p(startState, goalState, path):
    
    def printState_8p(state):
        for i in range(len(state)):
            if i % 3 == 0:
                print(state[i], state[i+1], state[i+2])
    
    print('Start State:\n')
    printState_8p(startState)
    print('\nPath:\n')
    for p in path:
        printState_8p(p)
        print()
    print('Goal State:\n')
    printState_8p(goalState)
    
def printPath_peg15(startState, goalState, path):
    
    def printState_peg15(state):
        for i in range(len(state)):
            if i == 0:
                print(' ', ' ', ' ', ' ', state[i], ' ', ' ', ' ', ' ')
            elif i == 1:
                print(' ', ' ', ' ', state[i], ' ', state[i+1], ' ', ' ', ' ')
            elif i == 3:
                print(' ', ' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', ' ')
            elif i == 6:
                print(' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ')
            elif i == 10:
                print(state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ', state[i+4])
    
    print('Start State:\n')
    printState_peg15(startState)
    print('\nPath:\n')
    for p in path:
        printState_peg15(p)
        print()
    print('Goal State:\n')
    printState_peg15(goalState)
    
def randomStartState_8p(goalState, actionsF, takeActionF, nSteps):
    state = goalState
    for i in range(nSteps):
        state = takeActionF(state, random.choice(actionsF(state)))
    return state
    
def randomGoalState_peg15(startState, actionsF, takeActionF, nSteps):
	
    def findPeg_peg15(state):
        r = 0
        c = 0
        pegs = []
        for s in state:
            if s == 'P':
                pegs.append((r, c))
            c += 1
            if c > r:
                r += 1
                c = 0
        return pegs
	
    state = startState
    for i in range(nSteps):
        pegs = findPeg_peg15(state)
        if len(pegs) <= 1:
            return state
        actions = actionsF(state)
        if actions == []:
            return state
        state = takeActionF(state, random.choice(actions))
    return state

def iterativeDeepeningSearch(startState, goalState, actionsF, takeActionF, maxDepth):
    for d in range(maxDepth + 1):
        result = depthLimitedSearch(startState, goalState, actionsF, takeActionF, d)
        if result == 'failure':
            return 'failure'
        elif result != 'cutoff':
            result.insert(0, startState)
            return result
    return 'cutoff'
    
def depthLimitedSearch(startState, goalState, actionsF, takeActionF, depthLimit):
    
    def goalTestF(state, goalState):
        goalOrNot = True
        for i in range(len(state)):
            if state[i] != goalState[i]:
                goalOrNot = False
        return goalOrNot
    
    def recursiveDLS(currentState, actionsF, takeActionF, goalState, goalTestF, depthLimit):
        if goalTestF(currentState, goalState):
            return []
        elif depthLimit <= 0:
            return 'cutoff'
        else:
            cutOff = False
            actions = actionsF(currentState)
            for a in actions:
                nextState = takeActionF(currentState, a)
                result = recursiveDLS(nextState, actionsF, takeActionF, goalState, goalTestF, depthLimit - 1) 
                if result == 'cutoff':
                    cutOff = True
                elif result != 'failure':
                    result.insert(0, nextState)
                    return result
            if cutOff:
                return 'cutoff'
            else:
                return 'failure'
    
    return recursiveDLS(startState, actionsF, takeActionF, goalState, goalTestF, depthLimit)

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
