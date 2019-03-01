#Author: coleman7245
#Project: Learning Towers of Hanoi through Reinforcement
#Last Edit: Thursday, February 14, 2019

import copy
import numpy as np

def main(args):
	
    print('Training AI to solve the Towers of Hanoi puzzle...')
    
    Q, stepsToGoal = trainQ(50, 0.5, 0.7, validMoves, makeMove)
    path = testQ(Q, 20, validMoves, makeMove)
    
    print('Done!\nCalculating path...')
    
    for s in path:
        printState(s)
        print()
	
    return 0
    
def printState(state):
    max = 3
    tempState = [copy.copy(s) for s in state]
    for i in range(len(tempState)):
        if len(tempState[i]) < max:
            for j in range(max - len(tempState[i])):
                tempState[i].insert(0, 0)
    for j in range(max):
        for i in range(len(tempState)):
            print(tempState[i][j] if tempState[i][j] != 0 else ' ',end=' ')
        print()
    print('------')
    
def validMoves(state):
    validMoves = []
    for i in range(len(state)):
        if i == 0:
            if (len(state[i+1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i+1][0]) or (len(state[i+1]) == 0 and len(state[i]) > 0):
                validMoves.append([1, 2])
            if (len(state[i+2]) > 0 and len(state[i]) > 0 and state[i][0] < state[i+2][0]) or (len(state[i+2]) == 0 and len(state[i]) > 0):                
                validMoves.append([1, 3])
        if i == 1:
            if (len(state[i-1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i-1][0]) or (len(state[i-1]) == 0 and len(state[i]) > 0):
                validMoves.append([2, 1])
            if (len(state[i+1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i+1][0]) or (len(state[i+1]) == 0 and len(state[i]) > 0):
                validMoves.append([2, 3])
        if i == 2:
            if (len(state[i-1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i-1][0]) or (len(state[i-1]) == 0 and len(state[i]) > 0):
                 validMoves.append([3, 2])
            if (len(state[i-2]) > 0 and len(state[i]) > 0 and state[i][0] < state[i-2][0]) or (len(state[i-2]) == 0 and len(state[i]) > 0):
                 validMoves.append([3, 1])
    return validMoves
    
def stateMoveTuple(state,move):
    tList = [tuple(s) for s in state]
    return (tuple(tList),tuple(move))
    
def isValidMove(move,validMoves):
    return move in validMoves
    
def makeMove(state,move):
    if len(move) == 0:
        return state
    newState = [copy.copy(s) for s in state]
   # print(move)
    disk = newState[move[0] - 1].pop(0)
    newState[move[1]  - 1].insert(0,disk)
    return newState
    
def trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF):
    
    def printState(state):
        max = 3
        tempState = [copy.copy(s) for s in state]
        for i in range(len(tempState)):
            if len(tempState[i]) < max:
                for j in range(max - len(tempState[i])):
                    tempState[i].insert(0, 0)
        for j in range(max):
            for i in range(len(tempState)):
                print(tempState[i][j] if tempState[i][j] != 0 else ' ',end=' ')
            print()
        print('------')
    
    def goalStateF(state, goal):
        if len(state) != len(goal):
            return False
        for p in range(len(state)):
            if len(state[p]) != len(goal[p]):
                return False
            for pos in range(len(state[p])):
                if state[p][pos] != goal[p][pos]:
                    return False
        return True
    
    def stateMoveTuple(state,move):
        tList = [tuple(copy.copy(s)) for s in state]
        return (tuple(tList),tuple(move))
    
    def chooseAction(epsilon, Q, validMoves, state):
        vMoves = np.array(validMoves)
        if np.random.uniform() < epsilon:
            return vMoves[np.random.choice(vMoves.shape[0])]
        else:
            Qs = np.array([Q.get(stateMoveTuple(state, m), 0) for m in vMoves])
            return vMoves[np.argmin(Qs)]
                            
    goal = [[],[],[1,2,3]]
    Q = {}
    epsilon = 1.0
    steps = []
    
    for rep in range(nRepetitions):
        epsilon *= epsilonDecayFactor
        state = [[1,2,3],[],[]]
        step = 0
        done = False
        
        while not done:
            validMoves = validMovesF(state)
            step += 1
            move = chooseAction(epsilon, Q, validMoves, state)
            newState = makeMoveF(state, move)
            stateMoveT = stateMoveTuple(state, move)
            if stateMoveT not in Q.keys():
                Q[stateMoveT] = 0
            
            if goalStateF(newState, goal):
                Q[oldStateMoveT] = 1
                done = True
                
            if step > 1:
                Q[oldStateMoveT] += learningRate * (1 + Q[stateMoveT] - Q[oldStateMoveT])
                
            oldStateMoveT = copy.copy(stateMoveT)
            state = copy.copy(newState)
        
        steps.append(step)
            
    return Q, steps
    
def testQ(Q, maxSteps, validMovesF, makeMoveF):
    
    def goalStateF(state, goal):
        if len(state) != len(goal):
            return False
        for p in range(len(state)):
            if len(state[p]) != len(goal[p]):
                return False
            for pos in range(len(state[p])):
                if state[p][pos] != goal[p][pos]:
                    return False
        return True
    
    def stateMoveTuple(state,move):
        tList = [tuple(copy.copy(s)) for s in state]
        return (tuple(tList),tuple(move))
    
    def greedyAction(Q, validMoves, state):
        vMoves = np.array(validMoves)
        Qs = np.array([Q.get(stateMoveTuple(state, m), 0) for m in vMoves])
        return vMoves[np.argmin(Qs)]
        
    goal = [[],[],[1,2,3]]
    state = [[1,2,3],[],[]]
    path = []
    
    for steps in range(maxSteps):
        
        if goalStateF(state, goal):
            path.append(state)
            return path
        
        path.append(state)
        validMoves = validMovesF(state)
        move = greedyAction(Q, validMoves, state)
        newState = makeMoveF(state, move)
        state = copy.copy(newState)
        
    return path
    


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
