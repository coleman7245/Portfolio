#Author: coleman7245
#Project: A* Search Experiment
#Last Edit: Thursday, February 14, 2019

import random

numOfNodes = 0

def main(args):
    runExperiment([1, 2, 3, 4, 0, 5, 6, 7, 8], [1, 2, 3, 4, 5, 8, 6, 0, 7], [1, 0, 3, 4, 5, 8, 2, 6, 7], [h1_8p, h2_8p, h3_8p])
	
    return 0
    
def h1_8p(state, goal):
        return 0

def h2_8p(state, goal):
		
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
		
    beginning = findBlank_8p(state)
    end = findBlank_8p(goal)
    totalCost = abs(beginning[0] - end[0]) + abs(beginning[1] - end[1])
    return totalCost

def h3_8p(state, goal):
		
    def findSpace_8p(state, space):
        r = 0
        c = 0
        for s in state:
            if s == space:
                return (r, c)
            else:
                c += 1
                if c == 3:
                    r += 1
                    c = 0
        return 'Space not found!'

    totalCost = 0
    for i in range(9):
        beginning = findSpace_8p(state, i)
        end = findSpace_8p(goal, i)
        totalCost += abs(beginning[0] - end[0]) + abs(beginning[1] - end[1])
    return totalCost

def runExperiment(goalState1, goalState2, goalState3, hFunctions):
    
    numOfH = 1
    depths = []
    numOfN = []
    experimentNames = []
    ebfs = []
    
    def goalTestF_8p(state, goalState):
        goalOrNot = True
        for i in range(len(state)):
            if state[i] != goalState[i]:
                goalOrNot = False
        return goalOrNot
    
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
            return 'Blank not found!'

        actions = []
        rowNColumn = findBlank_8p(state)
        if rowNColumn[1] > 0:
            actions.append(('left', 1))
        if rowNColumn[1] < 2:
            actions.append(('right', 1))
        if rowNColumn[0] > 0:
            actions.append(('up', 1))
        if rowNColumn[0] < 2:
            actions.append(('down', 1))
        return actions
    
    def takeActionF_8p(state, action):
        temp = 0
        newState = [s for s in state]
        cost = action[1]
        #print(state)
        if action[0] == 'down':
            for i in range(len(newState)):
                if newState[i] == 0:
                    temp = newState[i]
                    newState[i] = newState[i + 3]
                    newState[i + 3] = temp
                    break
        elif action[0] == 'up':
            for i in range(len(newState)):
                if newState[i] == 0:
                    temp = newState[i]
                    newState[i] = newState[i - 3]
                    newState[i - 3] = temp
                    break
        elif action[0] == 'right':
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
        return (newState, cost)
    
    def ebf(nNodes, depth, precision=0.01):
        if depth <= 0:
            return nNodes
        elif nNodes <= 0:
            return 0
        else:
            increment = 1
            originalHi = 1
            hi = originalHi
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
    
    def randomStartState_8p(goalState, actionsF, takeActionF, nSteps):
        state = goalState
        for i in range(nSteps):
            state = takeActionF(state, random.choice(actionsF(state)))[0]
        return state
    
    def iterativeDeepeningSearch(startState, goalState, actionsF, takeActionF, maxDepth):
        global numOfNodes 
        numOfNodes = 0
        for d in range(maxDepth):
            result = depthLimitedSearch(startState, goalState, actionsF, takeActionF, d)
            if result == 'failure':
                return 'failure'
            elif result != 'cutoff':
                result.insert(0, startState)
                return result
        return 'cutoff'
    
    def depthLimitedSearch(startState, goalState, actionsF, takeActionF, depthLimit):

        def goalTestF(state, goalState):
            #print(state)
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
                    nextState, _ = takeActionF(currentState, a)
                    global numOfNodes
                    numOfNodes += 1
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
    
    class Node:
        def __init__(self, state, f=0, g=0 ,h=0):
            self.state = state
            self.f = f
            self.g = g
            self.h = h
        def __repr__(self):
            return "Node(" + repr(self.state) + ", f=" + repr(self.f) + \
                   ", g=" + repr(self.g) + ", h=" + repr(self.h) + ")"

    def aStarSearch(startState, actionsF, takeActionF, goalTestF, hF):
        global numOfNodes 
        numOfNodes = 0
        h = hF(startState)
        startNode = Node(state=startState, f=0+h, g=0, h=h)
        return aStarSearchHelper(startNode, actionsF, takeActionF, goalTestF, hF, float('inf'))

    def aStarSearchHelper(parentNode, actionsF, takeActionF, goalTestF, hF, fmax):
        if goalTestF(parentNode.state):
            return ([parentNode.state], parentNode.g)
        ## Construct list of children nodes with f, g, and h values
        actions = actionsF(parentNode.state)
        if not actions:
            return ("failure", float('inf'))
        children = []
        for action in actions:
            (childState,stepCost) = takeActionF(parentNode.state, action)
            global numOfNodes
            numOfNodes += 1
            h = hF(childState)
            g = parentNode.g + stepCost
            f = max(h+g, parentNode.f)
            childNode = Node(state=childState, f=f, g=g, h=h)
            children.append(childNode)
        while True:
            # find best child
            children.sort(key = lambda n: n.f) # sort by f value
            bestChild = children[0]
            if bestChild.f > fmax:
                return ("failure",bestChild.f)
            # next lowest f value
            alternativef = children[1].f if len(children) > 1 else float('inf')
            # expand best child, reassign its f value to be returned value
            result,bestChild.f = aStarSearchHelper(bestChild, actionsF, takeActionF, goalTestF,
                                                hF, min(fmax,alternativef))
            if result is not "failure":               
                result.insert(0,parentNode.state)     
                return (result, bestChild.f)       
    
    def printHeader(goalState1, goalState2, goalState3):
        print('         ', goalState1, '   ', goalState2, '   ', goalState3)
        print('Algorithm     Depth   Nodes   EBF             Depth   Nodes   EBF               Depth   Nodes   EBF')
        return
    
    def printExperiment(algorithm, depth, nNodes, ebf):
        print(algorithm, '         ', depth[0], '     ', nNodes[0], '   ', "{0:.4f}".format(ebf[0]), '      ', depth[1], ' ', nNodes[1], ' ', "{0:.4f}".format(ebf[1]), '           ', depth[2], ' ', nNodes[2], ' ', "{0:.4f}".format(ebf[2]))
        return
    
    startState1 = randomStartState_8p(goalState1, actionsF_8p, takeActionF_8p, 20)
    startState2 = randomStartState_8p(goalState2, actionsF_8p, takeActionF_8p, 20)
    startState3 = randomStartState_8p(goalState3, actionsF_8p, takeActionF_8p, 20)
    
    printHeader(goalState1, goalState2, goalState3)
    
    experimentNames.append('IDS')
    result = iterativeDeepeningSearch(startState1, goalState1, actionsF_8p, takeActionF_8p, 20)
    depths.append(len(result) - 1)
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = iterativeDeepeningSearch(startState2, goalState2, actionsF_8p, takeActionF_8p, 20)
    depths.append(len(result) - 1)
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = iterativeDeepeningSearch(startState3, goalState3, actionsF_8p, takeActionF_8p, 20)
    depths.append(len(result) - 1)
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
    
    depths = []
    numOfN = []
    ebfs = []
    
    experimentNames.append('A*h1')
    result = aStarSearch(startState1, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState1), lambda s : hFunctions[0](s, goalState1))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = aStarSearch(startState2, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState2), lambda s : hFunctions[0](s, goalState2))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = aStarSearch(startState3, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState3), lambda s : hFunctions[0](s, goalState3))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
    
    depths = []
    numOfN = []
    ebfs = []
    
    experimentNames.append('A*h2')
    result = aStarSearch(startState1, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState1), lambda s : hFunctions[1](s, goalState1))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = aStarSearch(startState2, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState2), lambda s : hFunctions[1](s, goalState2))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = aStarSearch(startState3, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState3), lambda s : hFunctions[1](s, goalState3))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
    
    depths = []
    numOfN = []
    ebfs = []
    
    experimentNames.append('A*h3')
    result = aStarSearch(startState1, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState1), lambda s : hFunctions[2](s, goalState1))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = aStarSearch(startState2, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState2), lambda s : hFunctions[2](s, goalState2))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    result = aStarSearch(startState3, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState3), lambda s : hFunctions[2](s, goalState3))
    depths.append(result[1])
    numOfN.append(numOfNodes)
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
         

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
