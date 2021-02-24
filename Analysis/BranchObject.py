class BranchObject:
    def __init__(self, address, addrType):
        self.address = address
        self.addrType = addrType
        self.insMap = {}
        self.totalTestcases = 0

    def update(self, inscount, testInput):
        self.totalTestcases += 1
        if inscount not in self.insMap:
            self.insMap[inscount] = {testInput}
        else:
            self.insMap[inscount].add(testInput)
        
    def printProportions(self):
        print('addr: ' + str(self.address) + ' total: ' + str(self.totalTestcases))
        for inscount in self.insMap:
            print(str(inscount) + ': ' + str(float(len(self.insMap[inscount])) / (self.totalTestcases)))

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