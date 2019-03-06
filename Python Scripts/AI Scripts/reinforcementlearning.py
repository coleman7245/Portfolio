#Author: Derek Coleman
#Project: Learning Towers of Hanoi through Reinforcement
#Last Update: 3/6/19

#Import the copy package for copying methods.
import copy
#Import numpy for statistical analysis methods.
import numpy as np

#Method Summary: The main method of execution.
def main(args):
	
	#Print the algorithm title.
    print('Training AI to solve the Towers of Hanoi puzzle...')
    
    #Train the AI through reinforcement learning.
    Q, stepsToGoal = trainQ(50, 0.5, 0.7, validMoves, makeMove)
    #Generate a path through testing the trained AI.
    path = testQ(Q, 20, validMoves, makeMove)
    
    #Print a message saying the training and testing are complete and now the path printing will begin.
    print('Done!\nPrinting path...')
    
    #For every state in the path:
    for s in path:
		#Print the state.
        printState(s)
        #Print a dividing line.
        print()
	
	#Return 0, indicating success.
    return 0

#Method Summary: Print the state of the Towers of Hanoi puzzle. 
def printState(state):
    #Cycle through the 3 pegs first, then the disks:
    for level in range(3):
        #For every peg in the state:
        for peg in state:
			#Store the length of the peg in terms of disks.
            pegLength = len(peg)
            topDisk = peg[pegLength - 3] if (pegLength == 3) else ' '
            middleDisk = peg[pegLength - 2] if (pegLength >= 2) else ' '
            bottomDisk = peg[pegLength - 1] if (pegLength >= 1) else ' '
            #If the disc level is 0:
            if (level == 0):
				#Print the top disks.
                print(topDisk, end=' ')
            #If the disc level is 1:
            elif (level == 1):
				#Print the middle disks.
                print(middleDisk, end=' ')
            #If the disc level is 2:
            else:
				#Print the bottom disks.
                print(bottomDisk, end=' ')
        #Print the dividing space.
        print()
    #Print a dividing line.
    print('------')

#Method Summary: The valid moves possible given the current state.    
def validMoves(state):
	#Create a an empty list of valid moves.
    validMoves = []
    #For every peg in the state:
    for i in range(len(state)):
		#If this peg is the first peg:
        if i == 0:
			#If there are no smaller disks on the middle peg:
            if (len(state[i+1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i+1][0]) or (len(state[i+1]) == 0 and len(state[i]) > 0):
				#Append the move from the first peg to the middle peg.
                validMoves.append([1, 2])
            #If there are no smaller disks on the last peg:
            if (len(state[i+2]) > 0 and len(state[i]) > 0 and state[i][0] < state[i+2][0]) or (len(state[i+2]) == 0 and len(state[i]) > 0):
				#Append the move from the first peg to the last peg.                
                validMoves.append([1, 3])
        #If this peg is the middle peg:
        if i == 1:
			#If there are no smaller disks on the first peg:
            if (len(state[i-1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i-1][0]) or (len(state[i-1]) == 0 and len(state[i]) > 0):
				#Append the move from the middle peg to the first peg.
                validMoves.append([2, 1])
            #If there are no smaller disks on the last peg:
            if (len(state[i+1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i+1][0]) or (len(state[i+1]) == 0 and len(state[i]) > 0):
				#Append the move from the middle peg to the last peg.
                validMoves.append([2, 3])
        #If this peg is the last peg:
        if i == 2:
			#If there are no smaller disks on the middle peg:
            if (len(state[i-1]) > 0 and len(state[i]) > 0 and state[i][0] < state[i-1][0]) or (len(state[i-1]) == 0 and len(state[i]) > 0):
                #Append the move from the last peg to the middle peg.
                validMoves.append([3, 2])
            #If there are no smaller disks on the first peg:
            if (len(state[i-2]) > 0 and len(state[i]) > 0 and state[i][0] < state[i-2][0]) or (len(state[i-2]) == 0 and len(state[i]) > 0):
			     #Append the move from the last peg to the first peg.
                 validMoves.append([3, 1])
    #Return the list of valid moves.
    return validMoves
    
#Method Summary: Creates a tuple of a state and a valid move.
def stateMoveTuple(state,move):
	#Create a list of tuples out of the pegs in the state.
    tList = [tuple(s) for s in state]
    #Return a tuple of the state and the valid move.
    return (tuple(tList),tuple(move))

#Method Summary: Check if this move is a among the valid moves.
def isValidMove(move,validMoves):
	#Return the boolean check.
    return move in validMoves

#Method Summary: Alters the state given a move.
def makeMove(state,move):
	#If the move doesn't exist:
    if len(move) == 0:
		#Return the state.
        return state
    #Create the new state from the values of the old state.
    newState = [copy.copy(s) for s in state]
    #disk: The top disk popped off the given peg.
    disk = newState[move[0] - 1].pop(0)
    #Insert the disk on the target peg.
    newState[move[1]  - 1].insert(0,disk)
    #Return the altered state.
    return newState

#Method Summary: Trains an AI through reinforcement learning.
def trainQ(nRepetitions, learningRate, epsilonDecayFactor, validMovesF, makeMoveF):
    
    #Method Summary: Check if this state and the goal state are one in the same.
    def goalStateF(state, goal):
		#If the length of states are different:
        if len(state) != len(goal):
			#Return false, indicating the states are NOT the same.
            return False
        #For every peg in the state:
        for p in range(len(state)):
			#If the length of the pegs are different:
            if len(state[p]) != len(goal[p]):
				#Return false, indicating the states are NOT the same.
                return False
            #For every disk in the state:
            for pos in range(len(state[p])):
				#If this disk is differnt from the disk at the same position within the goal state.
                if state[p][pos] != goal[p][pos]:
					#Return false, indicating the states are NOT the same.
                    return False
        #Otherwise, the states are the same.
        return True
        
    #Method Summary: Creates a tuple of a state and a valid move.
    def stateMoveTuple(state,move):
	    #Create a list of tuples out of the pegs in the state.
        tList = [tuple(s) for s in state]
        #Return a tuple of the state and the valid move.
        return (tuple(tList),tuple(move))
    
    #Method Summary: Chooses an action depending on the epsilon and Q table values.
    def chooseAction(epsilon, Q, validMoves, state):
		#Create a numpy array out of the valid moves list.
        vMoves = np.array(validMoves)
        #If the drawn sample is less than the epsilon:
        if np.random.uniform() < epsilon:
			#Return the valid move using a random choice as the index.
            return vMoves[np.random.choice(vMoves.shape[0])]
        #If the epsilon is greater or equal to the drawn sample:
        else:
			#Qs: Creates a numpy array out of the retrieved Q table using the state-move tuple as the key.
            Qs = np.array([Q.get(stateMoveTuple(state, m), 0) for m in vMoves])
            #Chose the valid move using the minimum Q value as the index.
            return vMoves[np.argmin(Qs)]
    
    #Create the goal state.                        
    goal = [[],[],[1,2,3]]
    #Q: The function
    Q = {}
    #Create the epsilon value.
    epsilon = 1.0
    #Create a list of steps.
    steps = []
    
    #For every repetition:
    for rep in range(nRepetitions):
		#Scale down the epsilon by a given factor.
        epsilon *= epsilonDecayFactor
        #Create the initial state.
        state = [[1,2,3],[],[]]
        #Create the initial step.
        step = 0
        #Loop invariant.
        done = False
        
        #While the loop invariant still holds:
        while not done:
			#Create a list of valid moves.
            validMoves = validMovesF(state)
            #Increment the step.
            step += 1
            #Choose a move with a Q, epsilon, valid move list, and a state.
            move = chooseAction(epsilon, Q, validMoves, state)
            #Create a new state by making a move.
            newState = makeMoveF(state, move)
            #Create the state-move stuple.
            stateMoveT = stateMoveTuple(state, move)
            #If the state-move tuple is not within the Q keys:
            if stateMoveT not in Q.keys():
				#Create the Q table value using the state-move tuple as its key.
                Q[stateMoveT] = 0
            
            #If the goal state has been reached:
            if goalStateF(newState, goal):
				#Change the Q value of the old state-move tuple to 1.
                Q[oldStateMoveT] = 1
                #Signal the end of the loop invariant.
                done = True
            
            #If the step is greater than 1:
            if step > 1:
				#Modify the old Q table value with the reinforcement learing  forumula.
                Q[oldStateMoveT] += learningRate * (1 + Q[stateMoveT] - Q[oldStateMoveT])
                
            #Create the old state-move tuple.
            oldStateMoveT = copy.copy(stateMoveT)
            #Create the state using the new state's values.
            state = copy.copy(newState)
        
        #Append the step to the list of steps.
        steps.append(step)
    
    #Return the Q table and the list of steps.
    return Q, steps

#Method Summary: Tests the Q table to see if the AI has properly learning to play the Towers of Hanoi game.    
def testQ(Q, maxSteps, validMovesF, makeMoveF):
    
    #Method Summary: Check if this state and the goal state are one in the same.
    def goalStateF(state, goal):
		#If the length of states are different:
        if len(state) != len(goal):
			#Return false, indicating the states are NOT the same.
            return False
        #For every peg in the state:
        for p in range(len(state)):
			#If the length of the pegs are different:
            if len(state[p]) != len(goal[p]):
				#Return false, indicating the states are NOT the same.
                return False
            #For every disk in the state:
            for pos in range(len(state[p])):
				#If this disk is differnt from the disk at the same position within the goal state.
                if state[p][pos] != goal[p][pos]:
					#Return false, indicating the states are NOT the same.
                    return False
        #Otherwise, the states are the same.
        return True
    
    
    #Method Summary: Creates a tuple of a state and a valid move.
    def stateMoveTuple(state,move):
	    #Create a list of tuples out of the pegs in the state.
        tList = [tuple(s) for s in state]
        #Return a tuple of the state and the valid move.
        return (tuple(tList),tuple(move))
        
    #Method Summary: Take the first viable move.
    def greedyAction(Q, validMoves, state):
		#Create a numpy array out of the valid moves list.
        vMoves = np.array(validMoves)
        #Create the Q numpy array out of the q table.
        Qs = np.array([Q.get(stateMoveTuple(state, m), 0) for m in vMoves])
        #Return a valid move using the minimum Q value.
        return vMoves[np.argmin(Qs)]
    
    #Create the goal state.    
    goal = [[],[],[1,2,3]]
    #Create the initial state.
    state = [[1,2,3],[],[]]
    #Create an empty list for the path.
    path = []
    
    #For every step:
    for steps in range(maxSteps):
        
        #If the goal state has been reached:
        if goalStateF(state, goal):
			#Append the current state to the path.
            path.append(state)
            #Return the path.
            return path
        
        #Append the current state to the path.
        path.append(state)
        #Create a valid moves list using a given state.
        validMoves = validMovesF(state)
        #Take the greedy move.
        move = greedyAction(Q, validMoves, state)
        #Use that move to alter the current state.
        newState = makeMoveF(state, move)
        state = copy.copy(newState)
    
    #Return the path.    
    return path
    

#If the main method is invoked:
if __name__ == '__main__':
	#Import the system package.
    import sys
    #Run the main method.
    sys.exit(main(sys.argv))
