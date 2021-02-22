from BranchObject import BranchObject
class MyHashMap:
    branchDict = {}
#string that holds character depending on memory or brach access
#label duh
#makes a string, displays the proportion
    def __init__(self, count, testcases, branchOrMem):
        self.count = count
        self.testcases = testcases

    def addBranch(newBranchAddress)
        if newBranchAddress not in branchDict:
            branchDict[newBranchAddress] = BranchObject(newBranchAddress, "")
            #add to existing stack if its a new sub branch/dont add if already exists.
            
        else:
            
#should we use a stack if we are checking if it contains a certain sub branch?
#idk ive been thinking of nested dictionaries for some reason

#i feel like they should have like the sub branches? idk im just thinking like if theres like a subbranch for the subbranch and then like it goes on for a while its kinda weird. like a loop?
    def branchProportion(self):
        #do we do proportions after we are done getting the total count of instructions
        #also where do we store the counts between branches
        
    #can we do the proportions for each object? I think so. 
    #We can iterate through all items in the hashmap
    def incCount(self):
        count += 1
    
    #Should we try to make an object that acts like the second picture with the stacks for each branch?