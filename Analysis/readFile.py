from BranchObject import BranchObject

addrs = {} # {addrs: <type, dict{ins count: [input]}, totalCount>}

x = 2
for i in range(1, x + 1):
    filename = 'trace' + str(i) + '.txt'
    trace_file = open(filename, 'r') # this opens each file
    
    start = -1   # hold start addr

    # For each line in this file
    while True:
        # Get next line from file
        line = trace_file.readline()    # read address
        if not line:    # break in the event of qan unconventional trace 
            break
        trace = line.strip()
        
        if trace[0] == 't':
            break
            # this is the end of our trace file

        addrtype = trace[0]    # 'm' = memor access, 'b' = branch, 'r' = branching return
        if (start == -1):
            start = int(trace[2:])
            addr = 0
        else:
            addr = int(trace[2:]) - start   # actual address - start to get offset

        inscount = int(trace_file.readline().strip()[2:])    # read inscount after this address
        
        if addr not in addrs:
            addrs[addr] = BranchObject(addr, addrtype)
            # print('create ' + str(addr))
            # addrs[addr] = 0
        
        #update(addrs[addr], inscount)
        # print('update ' + str(addr) + ":" + inscount)
        # addrs[addr] += 1
        addrs[addr].update(inscount, i)

    #     print()
    # print('-----')   
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
