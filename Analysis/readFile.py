from BranchObject import BranchObject

addrs = {} # {addrs: <type, dict{ins count: [input]}, totalCount>}
testcaseLoop = {} # {testcase, loops}
i = 1

startFile = 3
numFiles = 2
for testNum in range(startFile, startFile + numFiles):
    filename = 'trace' + str(testNum) + '.txt'
    trace_file = open(filename, 'r') # this opens each file

    start = -1  # this is the start address
    # For each line in this file
    while True:
        # Get next line from file
        line = trace_file.readline()    # read address
        if not line:    # break in the event of qan unconventional trace 
            break
        trace = line.strip().split(':')
        
        if trace[0][0] == 't':
            # move the data from the temp dictionary to the final dictionary 
            # update the temp dictionary so that its empty
            # testcase<-address<-visitTotal
            loops = {} # {address, visit count}
            for addr in addrs:
                loops[addr] = addrs[addr].visitTotal #assign visits for branches to each address
                addrs[addr].visitTotal = 0 #reset all visits to 0
            testcaseLoop[i] = loops #assign loops to each test case
            i += 1
            break
            # this is the end of our trace file

        addrtype = trace[0]    # 'm' = memory access, 'b' = branch, 'r' = branching return. 's' = start
        if (addrtype == 's'):
            start = int(trace[1],16)
            addr = 0
        else:
            addr = int(trace[1],16) - start   # actual address - start to get offset

        inscount = int(trace_file.readline().strip()[2:])    # read inscount after this address

        
        if hex(addr) not in addrs: # but now we want to make it so its writing to our temp dictionary 
            addrs[hex(addr)] = BranchObject(hex(addr), addrtype)
        else: 
            addrs[hex(addr)].updateVisitTotal()

        addrs[hex(addr)].update(inscount, testNum) # update our temp but not the final ver yet

    trace_file.close()
  
# print(addrs)
for addr in addrs:
    addrs[addr].printProportions()
    print('---')

















# for line in trace_file:
#     trace = line.strip()
#     if trace[0] == 't':
#         break
#         # this is the end of our trace file

#     if trace[0] == 'a':
#         print(trace[2 : ])
#         # this is an address
#         inscount = 
#         print(inscount)
#     # elif trace[0] == 'i':
#     #     print(trace[2 : ])
#     #     # this is ins count between addresses

#     # else:

        
# trace_file.close()

# creates traces
# *IMPORTANT* Note that we have to print the start address so that we can find the address offset 
# *also note* Is the address a branch of MA (b or m)
# run pintracer on several diff testcases
#   run on a set of predetermined
#   (later) use a fuzzer to generate testcases

# analyze traces
# read through all of the trace files
#   trace1.txt, trace2.txt, etc.
#   takes in # of files
# dictionary [addr: obj]
# for each file
#   for each line in file
#       if line is an address
#           read line2 with ins count
#           if addr is in dictionary
#               update obj at dict[addr] with inscount
#           else 
#               create a new object 
# write to a new file with analysis results 
# print out the percentages of instruction count (eg: for address: 000F 6 ic 72% 5 ic 10% ....)
