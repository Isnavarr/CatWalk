/* INCLUDES */
#include "TraceWriter.h"
#include "pin.H"
#include <iostream>
#include <fstream>
#include <sstream>


/* STATIC VARIABLES */

bool TraceWriter::_prefixMode;
std::ofstream TraceWriter::_prefixDataFileStream;

/* VARIABLES FOR COUNTING */
/**
UINT64 count = 0;
bool memAccessed = false;
char prevMemPg;
**/

/* TYPES */

TraceWriter::TraceWriter(std::string filenamePrefix)
{
    // Remember prefix
    _outputFilenamePrefix = filenamePrefix;

    // Open prefix output file
	std::string filename = filenamePrefix + "prefix.trace";
    OpenOutputFile(filename);
}

TraceWriter::~TraceWriter()
{
    // Close file stream
    _outputFileStream.close();
}

void TraceWriter::InitPrefixMode(const std::string& filenamePrefix)
{
    // Start trace prefix mode
    _prefixMode = true;

    // Open prefix metadata output file
    _prefixDataFileStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	std::string prefixDataFilename = filenamePrefix + "prefix_data.txt";
    _prefixDataFileStream.open(prefixDataFilename.c_str(), std::ofstream::out | std::ofstream::trunc);
    if(!_prefixDataFileStream)
    {
        std::cerr << "Error: Could not open prefix metadata output file '" << prefixDataFilename << "'." << std::endl;
        exit(1);
    }
    std::cerr << "Trace prefix mode started" << std::endl;
}

TraceEntry* TraceWriter::Begin()
{
    return _entries;
}

TraceEntry* TraceWriter::End()
{
    return &_entries[ENTRY_BUFFER_SIZE];
}

void TraceWriter::OpenOutputFile(std::string& filename)
{
    // Open file for writing
    _outputFileStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    _currentOutputFilename = filename;
    _outputFileStream.open(_currentOutputFilename.c_str(), std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
    if(!_outputFileStream)
    {
        std::cerr << "Error: Could not open output file '" << _currentOutputFilename << "'." << std::endl;
        exit(1);
    }
}

void TraceWriter::WriteBufferToFile(TraceEntry* end)
{
    // Write buffer contents
    if(_testcaseId != -1 || _prefixMode)
        _outputFileStream.write(reinterpret_cast<char*>(_entries), reinterpret_cast<ADDRINT>(end) - reinterpret_cast<ADDRINT>(_entries));
}

void TraceWriter::TestcaseStart(int testcaseId, TraceEntry* nextEntry)
{
    // Exit prefix mode if necessary
    if(_prefixMode)
        TestcaseEnd(nextEntry);

    // Remember new testcase ID
    _testcaseId = testcaseId;

    // Open file for writing
    std::stringstream filenameStream;
    filenameStream << _outputFilenamePrefix << "t" << std::dec << _testcaseId << ".trace";
	std::string filename = filenameStream.str();
    OpenOutputFile(filename);
    std::cerr << "Switched to testcase #" << std::dec << _testcaseId << std::endl;
}

void TraceWriter::TestcaseEnd(TraceEntry* nextEntry)
{
    // Save remaining trace data
    if(nextEntry != _entries)
        WriteBufferToFile(nextEntry);

    // Close file handle and reset flags
    _outputFileStream.close();
    _outputFileStream.clear();

    // Exit prefix mode if necessary
    if(_prefixMode)
    {
        _prefixDataFileStream.close();
        _prefixMode = false;
        std::cerr << "Trace prefix mode ended" << std::endl;
    }
    else
    {
        // Notify caller that the trace file is complete
		std::cout << "t\t" << _currentOutputFilename << std::endl;
    }

    // Disable tracing until next test case starts
    _testcaseId = -1;
}

void TraceWriter::WriteImageLoadData(int interesting, uint64_t startAddress, uint64_t endAddress, std::string& name)
{
    // Prefix mode active?
    if(!_prefixMode)
    {
        std::cerr << "Image load ignored: " << name << std::endl;
        return;
    }

    // Write image data
    _prefixDataFileStream << "i\t" << interesting << "\t" << std::hex << startAddress << "\t" << std::hex << endAddress << "\t" << name << std::endl;
}

bool TraceWriter::CheckBufferFull(TraceEntry* nextEntry, TraceEntry* entryBufferEnd)
{
    return nextEntry != NULL && nextEntry == entryBufferEnd;
}

/* FUNCTIONS FOR COUNTING */

/**
void TraceWriter::doCount() {
    count++;
}

void TraceWriter::writeCount() {
    std::cout << "i:" << count << std::endl;
    count = 0;
}

void TraceWriter::InsertMemoryReadEntry(ADDRINT instructionAddress, ADDRINT memoryAddress)
{
    // get the string of memAddr and keep only the last 4 digits
    std::string memAddr (StringFromAddrint(memoryAddress));
    std::string subAddr (memAddr.substr(memAddr.length() - 4));
    
    if(!memAccessed || subAddr[0] != prevMemPg) {
        // print out the count and reset
        writeCount();
        
        // print out the addresses
        std::cout << "mr:" << StringFromAddrint(instructionAddress) << ":" << subAddr << std::endl;
        
        // save as prev page by the digit 4th from the end
        prevMemPg = subAddr[0];
        memAccessed = true;
    } else {
        std::cout << StringFromAddrint(instructionAddress) << std::endl;
        doCount();
    }
}

void TraceWriter::InsertMemoryWriteEntry(ADDRINT instructionAddress, ADDRINT memoryAddress)
{
    // get the string of memAddr and keep only the last 4 digits
    std::string memAddr (StringFromAddrint(memoryAddress));
    std::string subAddr (memAddr.substr(memAddr.length() - 4));
    
    if(!memAccessed || subAddr[0] != prevMemPg) {
        // print out the count and reset
        writeCount();
        
        // print out the addresses
        std::cout << "mw:" << StringFromAddrint(instructionAddress) << ":" << subAddr << std::endl;
        
        // save as prev page by the digit 4th from the end
        prevMemPg = subAddr[0];
        memAccessed = true;
    } else {
        std::cout << StringFromAddrint(instructionAddress) << std::endl;
        doCount();
    }
}

**/

TraceEntry* TraceWriter::InsertAllocSizeParameterEntry(TraceEntry* nextEntry, UINT64 size)
{
    // Check whether given entry pointer is valid (we might be in a non-instrumented thread)
    if(nextEntry == NULL)
        return nextEntry;

    // Create entry
    nextEntry->Type = TraceEntryTypes::AllocSizeParameter;
    nextEntry->Param1 = size;
    return ++nextEntry;
}

TraceEntry* TraceWriter::InsertCallocSizeParameterEntry(TraceEntry* nextEntry, UINT64 count, UINT64 size)
{
    return InsertAllocSizeParameterEntry(nextEntry, count * size);
}

TraceEntry* TraceWriter::InsertAllocAddressReturnEntry(TraceEntry* nextEntry, ADDRINT memoryAddress)
{
    // Check whether given entry pointer is valid (we might be in a non-instrumented thread)
    if(nextEntry == NULL)
        return nextEntry;

    // Create entry
    nextEntry->Type = TraceEntryTypes::AllocAddressReturn;
    nextEntry->Param2 = memoryAddress;
    return ++nextEntry;
}

TraceEntry* TraceWriter::InsertFreeAddressParameterEntry(TraceEntry* nextEntry, ADDRINT memoryAddress)
{
    // Check whether given entry pointer is valid (we might be in a non-instrumented thread)
    if(nextEntry == NULL)
        return nextEntry;

    // Create entry
    nextEntry->Type = TraceEntryTypes::FreeAddressParameter;
    nextEntry->Param2 = memoryAddress;
    return ++nextEntry;
}

/**
void TraceWriter::InsertBranchEntry(ADDRINT sourceAddress, ADDRINT targetAddress)
{
    //PIN_LockClient();
    writeCount();
    std::cout << "b:" << StringFromAddrint(sourceAddress) << std::endl;
    memAccessed = false;
    //std::cout << IMG_Name(IMG_FindByAddress(targetAddress)) << std::endl;
    //PIN_UnlockClient();
}

void TraceWriter::InsertRetBranchEntry(ADDRINT sourceAddress, CONTEXT* contextAfterRet)
{
    writeCount();
    std::cout << "r:" << StringFromAddrint(sourceAddress) << std::endl;
    memAccessed = false;
}
**/

TraceEntry* TraceWriter::InsertStackPointerInfoEntry(TraceEntry* nextEntry, ADDRINT stackPointerMin, ADDRINT stackPointerMax)
{
    // Create entry
    nextEntry->Type = TraceEntryTypes::StackPointerInfo;
    nextEntry->Param1 = stackPointerMin;
	nextEntry->Param2 = stackPointerMax;
    return ++nextEntry;
}

ImageData::ImageData(bool interesting, std::string name, UINT64 startAddress, UINT64 endAddress)
{
    _interesting = interesting;
    _name = name;
    _startAddress = startAddress;
    _endAddress = endAddress;
}

bool ImageData::ContainsBasicBlock(BBL basicBlock)
{
    // Check start address
    return _startAddress <= INS_Address(BBL_InsHead(basicBlock)) && INS_Address(BBL_InsTail(basicBlock)) <= _endAddress;
}

bool ImageData::IsInteresting()
{
    return _interesting;
}
