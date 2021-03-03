from BranchObject import BranchObject

addrs = {} # {addrs: <type, dict{ins count: [input]}, totalCount>}

startFile = 1
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
            break
            # this is the end of our trace file

        addrtype = trace[0]    # 'm' = memory access, 'b' = branch, 'r' = branching return. 's' = start
        if (addrtype == 's'):
            start = int(trace[1],16)
            addr = 0
        else:
            addr = int(trace[1],16) - start   # actual address - start to get offset

        inscount = int(trace_file.readline().strip()[2:])    # read inscount after this address

        if hex(addr) not in addrs:
            addrs[hex(addr)] = BranchObject(hex(addr), addrtype)
        
        addrs[hex(addr)].update(inscount, testNum)

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
