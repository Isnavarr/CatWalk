trace_file = open('trace1.txt', 'r') # replace this with a path 

for line in trace_file:
    trace = line.strip()
    if trace[0] == 't':
        break
        # this is the end of our trace file

    if trace[0] == 'a':
        print(trace[2 : ])
        # this is an address

    elif trace[0] == 'i':
        print(trace[2 : ])
        # this is ins count between addresses

    else:

        
trace_file.close()

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