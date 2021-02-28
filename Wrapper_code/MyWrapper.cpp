/* INCLUDES */
// OS-specific imports and helper macros
#ifdef _GNU_SOURCE
    #undef _GNU_SOURCE
#endif
#define _EXPORT __attribute__((visibility("default")))
#define _NOINLINE __attribute__((noinline))
#include <sys/resource.h>
// Standard includes
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <iostream>

#include </home/jessicalam/Desktop/CatWalk/Toy2/shared.h>

// Pin notification functions.
// The return values reduce the probability that the compiler uses these function in other places as no-ops (Visual C++ did do this in some experiments).
#pragma optimize("", off)
extern "C" _EXPORT _NOINLINE int PinNotifyTestcaseStart(int t) { return t + 42; }
extern "C" _EXPORT _NOINLINE int PinNotifyTestcaseEnd() { return 42; }
extern "C" _EXPORT _NOINLINE int PinNotifyStackPointer(uint64_t spMin, uint64_t spMax) { return static_cast<int>(spMin + spMax + 42); }
#pragma optimize("", on)


_EXPORT _NOINLINE void InitTarget()
{
	absDiff(0,0);
}

_EXPORT _NOINLINE void RunTarget(int a, int b) {
	//isLoop(a);
	absDiff(a, b);
	//printName(name);
}

// Reads the stack pointer base value and transmits it to Pin.
_EXPORT void ReadAndSendStackPointer()
{
#if defined(_WIN32)
    // Read stack pointer
    _TEB* threadEnvironmentBlock = NtCurrentTeb();
    PinNotifyStackPointer(reinterpret_cast<uint64_t>(threadEnvironmentBlock->tib.StackLimit), reinterpret_cast<uint64_t>(threadEnvironmentBlock->tib.StackBase));
#else
    // There does not seem to be a reliable way to get the stack size, so we use an estimation
    // Compiling with -fno-split-stack may be desired, to avoid surprises during analysis
    // Take the current stack pointer as base value
    uintptr_t stackBase;
    asm("mov %%rsp, %0" : "=r"(stackBase));
    // Get full stack size
    struct rlimit stackLimit;
    if(getrlimit(RLIMIT_STACK, &stackLimit) != 0)
    {
        char errBuffer[128];
        strerror_r(errno, errBuffer, sizeof(errBuffer));
        fprintf(stderr, "Error reading stack limit: [%d] %s\n", errno, errBuffer);
    }
    uint64_t stackMin = reinterpret_cast<uint64_t>(stackBase) - reinterpret_cast<uint64_t>(stackLimit.rlim_cur);
    uint64_t stackMax = (reinterpret_cast<uint64_t>(stackBase) + 0x10000) & ~0x10000ull; // Round to next higher multiple of 64 kB (should be safe on x86 systems)
    PinNotifyStackPointer(stackMin, stackMax);
#endif
}

//void do_something_secretive()
//{
/**
    char secret[] = {1, 0, 1, 1, 5, 1, 2, 3, 0, 0};
    for(int i = 0; i < 10; i++){
        int x = 0;
        if(secret[i])
            x += secret[i];
    }
   **/
//}
// Main trace target function. The following actions are performed:
//     The current action is read from stdin.
//     A line with "t" followed by a numeric ID, and another line with a file path determining a new testcase, that is subsequently loaded and fed into the target function, while calling PinNotifyNextFile() beforehand.
//     A line with "e 0" terminates the program.
extern "C" _EXPORT void TraceFunc()
{
    ReadAndSendStackPointer();
    InitTarget();

    char inputBuffer[512];
    int first;
    int second;
    // char name[512];
    fgets(inputBuffer, sizeof(inputBuffer), stdin);
    // sscanf(inputBuffer, "%s", name);
    sscanf(inputBuffer, "%d %d", &first, &second);

    std::cout << "------- absDiff: |" << first << " - " << second << "|" << std::endl;
    // First transmit stack pointer information
    PinNotifyTestcaseStart(0);
    RunTarget(first, second);
    PinNotifyTestcaseEnd();
    std::cout << "------- done: " << absDiff(first, second) << std::endl; //absDiff(first,second) << std::endl;
}
// Wrapper entry point.
int main(int argc, const char** argv)
{
    // Run target function
    TraceFunc();
    return 0;
}
