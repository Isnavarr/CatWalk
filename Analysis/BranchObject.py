class BranchObject:
    def __init__(self, address, addrType):
        self.address = address # addr offset 4
        self.addrType = addrType # addrtype 'm' or 'b' or 'r'
        self.insMap = {} # map {4: {1}, 6: {2, 3}}  set* key instruction, value set of testcases
        self.totalTestcases = 0 # total testcases
        self.visitTotal = {} # 
        self.count = 0
        self.testcase = -1

    def update(self, inscount, testInput): # update(inscount, input):
        if(testcase != self.testcase)
            self.totalTestcases += 1 # totalTestcase += 1
            self.testcase = testInput
            self.visitTotal[count] = {testcase}
            self.count = 0
        if inscount not in self.insMap: # does map have this inscount?
            self.insMap[inscount] = {testInput} # map[inscount] append input map[iscount].add(#)
        else:
            self.insMap[inscount].add(testInput) # map[inscount] = {input}

    def updateVisitTotal(self):
        self.count += 1

    def printProportions(self):
        print(self.addrType + ' addr: ' + str(self.address) + ' total: ' + str(self.totalTestcases))
        for inscount in self.insMap: #   for each inscount in map:
            # print(str(inscount) + ': ' + str(len(self.insMap[inscount])) + " " + str(self.totalTestcases))
            print(str(inscount) + ': ' + str(float(len(self.insMap[inscount])) / (self.totalTestcases)))
        for count in self.visitTotal:
            print(self.address + ' ran ' + (self.count) + 'times: ' 
            + str(float(len(self.visitTotal[count])) / (self.totalTestcases)) + ' this percentage of the time')
            
            # add the total # of times the branch was visited overall
            avg += (count * str(float(len(self.visitTotal[count]))))
            total += (str(float(len(self.visitTotal[count]))))

        avg = (avg / total)
        print( (self.address) + ' runs an average of ' + avg + ' times when it is run.')
            
            
            
            
            
            
            
# addr offset 4
# addrtype 'm' or 'b' or 'r'
# map {4: {1}, 6: {2, 3}}  set* key instruction, value set of testcases
# total testcases

# update(inscount, input):
#   totalTestcase += 1
#   does map have this inscount?
#       map[inscount] append input map[iscount].add(#)
#   else
#       map[inscount] = {input}

# printProportions():
#   for each inscount in map:
#       print(str(inscount) + ': ' + len(map[inscount]) / totalTestcases)
