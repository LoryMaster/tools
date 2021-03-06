#ifndef LS_CRT_H
#define LS_CRT_H

#ifdef _DEBUG
#define Assert(condition) if(!(condition)){DebugBreak();}
#else
#define Assert(condition) ((void)0);
#endif

#define internal static
#define global   static

#define Bytes(n)       (n)
#define Kilobytes(n)   1024ULL*Bytes(n)
#define Megabytes(n)   1024ULL*Kilobytes(n)
#define Gigabytes(n)   1024ULL*Megabytes(n)
#define Kb		     Kilobytes
#define Mb			 Megabytes
#define Gb			 Gigabytes
#define KBytes		 Kb
#define MBytes		 Mb
#define GBytes		 Gb
#define KB		     Kb
#define MB	   	  Mb
#define GB   		  Gb

#define ArraySize(a) (sizeof(a) / sizeof((a)[0]))

#ifdef LS_PLAT_WINDOWS

#ifndef LS_WINDOWS_H
#include "lsWindows.h"
#endif

#define LS_STDOUT 0
#define LS_STDIN  0
#define LS_STDERR 0

#endif

#ifdef LS_PLAT_LINUX

#ifndef LS_LINUX_H
#include "lsLinux.h"
#endif

#define LS_STDOUT STDOUT_FILENO
#define LS_STDIN  STDIN_FILENO
#define LS_STDERR STDERR_FILENO

#endif

#include "lsString.h"
#include "lsMath.h"


/*For Variadic Functions*/
#include <stdarg.h>



////////////////////////////////////////////////////
//	STRUCTURES
////////////////////////////////////////////////////

struct Date
{
    u32 milliseconds;
    u32 seconds;
    u32 minutes;
    u32 hour;
    
    u32 day;
    char *dayName;
    
    u32 month;
    char *monthName;
    
    u32 year;
};

#if 0
/*forward declare lsWindows functions? */
#ifdef LS_PLAT_WINDOWS
u64 windows_ReadCosole(char *, u32);
u64 windows_ReadFile(char *, char **, u32);
u64 windows_ReadFileByOffset(char *, char **, u64, u32);
u64 windows_WriteConsole(char *, u32);
u64 windows_WriteFile(char *, void *, u32, b32);
b32 windows_fileExists(char *AbsPath);
u32 windows_countFilesInDir(char *);
u32 windows_countFilesInDirByExt(char *, char *);
u32 windows_countFilesInDirRecursive(char *, u32);
void windows_getFileNamesInDir(char *, u32, char ***, u32 *, u32 **);
void windows_getFileNamesInDirByExt(char *, u32, char *, u32, char ***, u32 *, u32 **);
void windows_getFileNamesInDirRecursive(char *, u32, char ***, u32 *, u32 **);
void windows_getFilePathsInDirRecursive(char *, u32, char ***, u32 *, u32 **);
u32 windows_getFullPathName(char *, u32 , char *);
u64 windows_GetWindowsTimeInMicrosec();
u64 windows_GetWindowsTimeIn100Nanosec();
u32 windows_GetUnix32Time();
u64 windows_GetUnix64Time();
windowsDate windows_GetDate(b32);
void windows_setupWindow(WindowInfo *);
void windows_setupOpenGLContext(WindowInfo *);
void windows_sleep(u64 milliseconds);
#endif

#ifdef LS_PLAT_LINUX
u64 linux_ReadConsole(s32, char *, u32);
u64 linux_ReadFile(char *, char **, u32);
u64 linux_WriteConsole(s32, char *, u32);
u64 linux_WriteFile(char *, void *, u32);
u64 linux_GetTime();
linuxDate linux_GetDate(b32);
#endif

#endif

extern "C"
{
    ////////////////////////////////////////////////////
    //	STRING FUNCTIONS
    ////////////////////////////////////////////////////
    
    u32     ls_len(char *s);
    char    ls_lowerCase(char c);
    b32     ls_isWritable(char c);
    b32	 ls_isANumber(char c);
    b32     ls_isWhitespace(char c);
    char	ls_itoc(s64 x);
    u32	 ls_ctoi(char c);
    
    //NOTE: On heap
    char   *ls_itoa(s64 x);
    char   *ls_ftoa(f64 x);
    
    //NOTE: On stack
    u32    ls_itoa_t(s64 x, char *buff, u32 buffMax);
    u32    ls_ftoa_t(f64 x, char *buff, u32 buffMax);
    
    char   *ls_strstr(char *a, char *b);
    s64     ls_atoi(char *s, u32 len);
    f32     ls_atof(char *s, u32 len);
    s32     ls_strcmp(char *a, char *b);
    s32     ls_strncmp(char *a, char *b, u32 n);
    
    //TODO: Add precision Modifiers to Floating Point Printing
    s32     ls_vsprintf(char *dest, const char *fmt, va_list argList);
    s32 	ls_sprintf(char *dest, const char *format, ...);
    s32     ls_vprintf(const char *fmt, va_list argList);
    s32 	ls_printf(const char *format, ...);
    char    ls_getc();
    
    
    ////////////////////////////////////////////////////
    //	FILE MANIPULATION FUNCTIONS
    ////////////////////////////////////////////////////
    
    void ls_getFileNameFromPath(char *Path, char *out);
    void ls_getFileExtension(char *Path, char *out);
    
    //If bytesToRead is set to 0 the entire file will be read.
    u64  ls_readFile(char *Path, char **Dest, u32 bytesToRead);
    u64  ls_ReadFileByOffset(char *Path, char **Dest, u64 offset, u32 bytesToRead);
    u64  ls_writeFile(char *Path, void *Source, u32 bytesToWrite, b32 append);
    b32  ls_fileExists(char *AbsPath);
    u32  ls_countFilesInDir(char *Dir);
    u32  ls_countFilesInDirByExt(char *Dir, char *ext);
    u32  ls_countFilesInDirRecursive(char *Dir);
    u32  ls_getFileNamesInDir(char *Dir, char ***names, u32 **namesLen);
    u32  ls_getFileNamesInDirByExt(char *Dir, char *ext, char ***names, u32 **namesLen);
    u32  ls_getFileNamesInDirRecursive(char *Dir, char ***names, u32 **namesLen);
    u32  ls_getFilePathsInDirRecursive(char *Dir, char ***names, u32 **namesLen);
    u32  ls_getFullPathName(char *name, char *buff, u32 buffMaxSize);
    
    ////////////////////////////////////////////////////
    //	GENERAL PURPOSE SYSTEM FUNCTIONS
    ////////////////////////////////////////////////////
    
    /* The resolution depends on the OS:
  In Windows the epoch is January 1st, 1601 (UTC) and the value is
  returned in microseconds (even tough resoultion is 100-nanoseconds intervals)
  In Linux the epoch is ***  and the value is returned in *** */
    u64 ls_getTimeSinceEpochInMicrosec();
    u64 ls_getTimeSinceEpochIn100Nanosec();
    
    u32 ls_getUnix32Time(); //NOTE: In seconds
    u64 ls_getUnix64Time(); //NOTE: In seconds
    
    /* If false UTC time is returned instead */
    Date ls_getDateTime(b32 local);
    
    void ls_sleep(u64 milliseconds);
    
    ////////////////////////////////////////////////////
    //	MEMORY FUNCTIONS
    ////////////////////////////////////////////////////
    
    void  ls_memcpy(void *src, void *dest, size_t size);
    void  ls_memset(void *src, u8 v, size_t numBytes);
    b32   ls_memcmp(void *a, void *b, size_t size);
    void  ls_zeroMem(void *mem, size_t size);
    void  ls_zeroMemASM(void *mem, size_t size);
    void *ls_alloc(u64 size);
    void *ls_realloc(void *originalMem, u64 oldSize, u64 newSize);
    void  ls_free(void *p);
    
    u32 ls_bitReverse(u32 a); //NOTE: This doesn't belong anywhere else?
    
    ////////////////////////////////////////////////////
    //	INTRINSICS
    ////////////////////////////////////////////////////
    
    f32 Log2(u64 value);
    f32 Log10(u64 value);
    u32 Log10i(u64 value);
    u32 LeadingZeros32(u32 value);
    u32 LeadingZeros64(u64 value);
    u32 HighestBitIdx32(u32 value);
    u32 HighestBitIdx64(u64 value);
    u16 ByteSwap16(u16 value);
    u32 ByteSwap32(u32 value);
    u64 ByteSwap64(u64 value);
    f32 Ceil(f32 v);
}

#define ARRAY_IDX_NOT_FOUND (u32)-1
template<typename T>
struct Array
{
    T *data;
    u32 count;
    u32 cap;
    
    Array()
    { data = (T *)ls_alloc(32*sizeof(T)); count = 0; cap = 32; }
    
    T& operator[](u32 index)
    {
        Assert(index < count); //NOTE: Should this be a crash or an error?
        return data[index];
    }
    
    void copy(Array<T> *a)
    {
        if(data) { ls_free(data); }
        
        count = a->count;
        cap = a->cap;
        ls_memcpy(a->data, data, a->count);
    }
    
    void grow(u32 amount)
    {
        data = (T *)ls_realloc(data, cap*sizeof(T), (cap + amount)*sizeof(T));
        cap += amount;
    }
    
    u32 push(T val)
    {
        if(count == cap) { grow(32); }
        data[count++] = val;
        
        return (count - 1);
    }
    
    void insert(T val, u32 index)
    {
        if(count == cap) { grow(32); }
        size_t dataSize = sizeof(T);
        
        u32 numElements = count - index;
        Assert(numElements <= cap);
        
        ls_memcpy(data + index, data + index + 1, numElements*dataSize);
        count += 1;
        data[index] = val;
    }
    
    void set(T val, u32 index)
    {
        if(index > cap) { grow(index - cap + 1); }
        data[index] = val;
    }
    
    void remove(T val, u32 index)
    {
        size_t dataSize = sizeof(T);
        u32 numElements = count - index;
        ls_memcpy(data + index + 1, data + index, numElements*dataSize);
        count -= 1;
    }
    
    b32 contains(T val)
    {
        for(u32 i = 0; i < count; i++)
        {
            if (data[i] == val) { return TRUE; }
        }
        
        return FALSE;
    }
    
    u32 getIdx(T val)
    {
        for(u32 i = 0; i < count; i++)
        {
            if (data[i] == val) { return i; }
        }
        
        return (u32)-1;
    }
    
    void clear()
    { count = 0; }
    
    //NOTE:TODO: Can't have Arrays of complex data types, because the free would
    //not work properly! (I would need to iteratively free every element,
    //instead of single call.
    void free()
    {
        ls_free(data);
        count = 0;
        cap = 0;
    }
};

#endif //End of header

#ifdef LS_CRT_IMPLEMENTATION

// NOTE:To get console in 4coder (which doesn't open one for me)
#ifdef LS_EXTERNAL_CONSOLE

b32 ls_dangerousNotToBeCalledInitFunctionHere()
{
    DWORD success = FreeConsole();
    if(success == 0)
    {
        DWORD Err = GetLastError();
        ls_printf("Got error %d when calling Free Console in lsInit\n");
        return FALSE;
    }
    
    success = AllocConsole();
    if(success == 0)
    {
        DWORD Err = GetLastError();
        ls_printf("Got error %d when calling Alloc Console in lsInit\n");
        return FALSE;
    }
    
    return TRUE;
}

b32 globalVarToCallTheSuperDangerousInitCRTfunction =
ls_dangerousNotToBeCalledInitFunctionHere();

#endif

#include "FunctionTables/FunctionTables.h"
#include <immintrin.h>

#ifdef LS_PLAT_WINDOWS
#ifndef __GNUG__
#include <intrin.h>
#endif
#endif

#ifdef LS_PLAT_LINUX
#include <x86intrin.h>
#endif

////////////////////////////////////////////////////
//	STRING FUNCTIONS
////////////////////////////////////////////////////

u32 ls_len(char *s)
{
    u32 len = 0;
    char *At = s;
    while(*At != 0) { len++; At++; }
    
    return len;
}

char ls_lowerCase(char c)
{
    if ((c > 64) && (c < 91)) { return c + 32; }
    else { return c; }
}

b32 ls_isWritable(char c)
{
    if((c >= 32) && (c <= 126)) { return TRUE; }
    
    return FALSE;
}

b32 ls_isANumber(char c)
{
    if((c >= 48 && c <= 57) || (c == '-') || (c == '+') )
    { return TRUE; }
    
    return FALSE;
}

b32 ls_isWhitespace(char c)
{
    if((c == ' ') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v'))
    { return TRUE; }
    
    return FALSE;
}

char ls_itoc(s64 x)
{
    return ((char)x + '0');
}

u32 ls_ctoi(char c)
{
    return c - '0';
}

char *ls_itoa(s64 x)
{
    char *Result = 0;
    bool isNegative = x < 0;
    s64 value = isNegative ? -x : x;
    
    if (value == 0)
    {
        Result = (char *)ls_alloc(2);
        Result[0] = '0'; Result[1] = '\0';
        return Result;
    }
    
    //My Log10 Function is not super precise at the boundaries between values i.e. 999999 - 1000000. So just to be sure, I give it an extra byte, which is super fine.
    
    //Update months Later: BTW I think this is a fuckin waste of time and processor power, considering no number to be printed is ever going to be bigger than 128 char long
    //I should just waste this 0.000000016% of the average computer FUCKING Memory to just allocate a little bit more than necessary.
    
    //I'm not going to change it now just because it's good training for me to approximate trascendental functions and stuff like that
    
    //Update few days later: Fuck it I'm changing this shitty Log10 functions that sucks freakin balls.
    
    //@TODO @CLEANUP @FIXME: Make a Log2 / Log10 / LOGN Function Tables so that I quit having this stupid shitty problem. (Or maybe see if theres cool ASM for them)
    Result = (char *)ls_alloc(128);
    s32 i = 0;
    
    while (value != 0)
    {
        Result[i++] = value % 10 + '0';
        value = value / 10;
    }
    
    if (isNegative) { Result[i++] = '-'; }
    Result[i] = '\0';
    
    //Flip string, it's in reverse.
    for (int t = 0; t < i / 2; t++)
    {
        Result[t] ^= Result[i - t - 1];
        Result[i - t - 1] ^= Result[t];
        Result[t] ^= Result[i - t - 1];
    }
    
    return Result;
}

u32 ls_itoa_t(s64 x, char *buff, u32 buffMax)
{
    char *Result = buff;
    bool isNegative = x < 0;
    s64 value = isNegative ? -x : x;
    
    if(buffMax < 2) { return 0; }
    
    if (value == 0)
    {
        Result[0] = '0'; Result[1] = '\0';
        return 1;
    }
    
    s32 i = 0;
    while (value != 0)
    {
        if(i == buffMax) { return i; }
        Result[i++] = value % 10 + '0';
        value = value / 10;
    }
    
    if (isNegative) { 
        if(i == buffMax) { return i; }
        Result[i++] = '-'; 
    }
    
    if(i == buffMax) { return i; }
    Result[i] = '\0';
    
    //Flip string, it's in reverse.
    for (int t = 0; t < i / 2; t++)
    {
        Result[t] ^= Result[i - t - 1];
        Result[i - t - 1] ^= Result[t];
        Result[t] ^= Result[i - t - 1];
    }
    
    return i;
}

char *ls_ftoa(f64 x)
{
    char ResultBuffer[32] = {};
    u32 BuffIdx = 0;
    
    char *IntegerPart = ls_itoa((int)x);
    u32 intLen = ls_len(IntegerPart);
    
    char *FractPart = 0;
    u32 fractLen = 0;
    
    ls_memcpy(IntegerPart, ResultBuffer, intLen);
    BuffIdx += intLen;
    
    f32 absX = (x < 0.0f) ? x*(-1.0f) : x;
    if (absX < 1.0f)
    {
        s32 fractValue = s32((absX + 1.0f) * 1000000);
        FractPart = ls_itoa(fractValue);
        fractLen = ls_len(FractPart);
    }
    else if (x >= 10.0f)
    {
        f32 fixedX = (absX - (int)absX) + 1.0f;
        s32 fractValue = s32(fixedX * 1000000);
        FractPart = ls_itoa(fractValue);
        fractLen = ls_len(FractPart);
    }
    else
    {
        s32 fractValue = s32(absX * 1000000);
        FractPart = ls_itoa(fractValue);
        fractLen = ls_len(FractPart);
    }
    
    //NOTE: If Integer is negative Integer part is gonna already
    //Have the '-' prepended. No reason to add another one.
    ResultBuffer[BuffIdx] = '.';
    BuffIdx += 1;
    
    ls_memcpy(FractPart, ResultBuffer + BuffIdx, fractLen);
    BuffIdx += fractLen;
    
    
    ls_free(IntegerPart);
    ls_free(FractPart);
    
    char *Result = (char *)ls_alloc(sizeof(char) * BuffIdx);
    ls_memcpy(ResultBuffer, Result, BuffIdx);
    
    return Result;
}

u32 ls_ftoa_t(f64 x, char *buff, u32 buffMax)
{
    char *ResultBuffer = buff;
    u32 BuffIdx = 0;
    
    char IntegerPart[32] = {};
    u32 intLen = ls_itoa_t((int)x, IntegerPart, 32);
    
    char FractPart[32] = {};
    u32 fractLen = 0;
    
    if(intLen >= buffMax) { return 0; }
    
    ls_memcpy(IntegerPart, ResultBuffer, intLen);
    BuffIdx += intLen;
    
    f32 absX = (x < 0.0f) ? x*(-1.0f) : x;
    if (absX < 1.0f)
    {
        s32 fractValue = s32((absX + 1.0f) * 1000000);
        fractLen = ls_itoa_t(fractValue, FractPart, 32);
    }
    else if (x >= 10.0f)
    {
        f32 fixedX = (absX - (int)absX) + 1.0f;
        s32 fractValue = s32(fixedX * 1000000);
        fractLen = ls_itoa_t(fractValue, FractPart, 32);
    }
    else
    {
        s32 fractValue = s32(absX * 1000000);
        fractLen = ls_itoa_t(fractValue, FractPart, 32);
    }
    
    if(fractLen + intLen + 1 >= buffMax) { return 0; }
    
    //NOTE: If Integer is negative Integer part is gonna already
    //Have the '-' prepended. No reason to add another one.
    ResultBuffer[BuffIdx] = '.';
    BuffIdx += 1;
    
    ls_memcpy(FractPart, ResultBuffer + BuffIdx, fractLen);
    BuffIdx += fractLen;
    
    return BuffIdx;
}

s64 ls_atoi(char *s, u32 len)
{
    if(!s) { Assert(FALSE); }
    
    s64 Result = 0;
    s32 numLen = 0;
    
    char *At = s;
    while(ls_isANumber(*At))
    {
        if((numLen + 1) > len) { break; }
        At += 1; numLen += 1;
    }
    
    b32 isNegative = s[0] == '-' ? TRUE : FALSE;
    b32 hasPositive = s[0] == '+' ? TRUE : FALSE;
    
    if (!isNegative)
    {
        s32 endPoint = hasPositive ? 1 : 0;
        s64 pow10 = 1;
        for (int i = (numLen - 1), k = 0; i >= endPoint; i--, k++)
        {
            Result += ( (s[i] - 48) * pow10 );
            pow10 *= 10;
        }
    }
    else
    {
        s64 pow10 = 1;
        for (int i = (numLen - 1), k = 0; i > 0; i--, k++)
        {
            Result -= ( (s[i] - 48) * pow10 );
            pow10 *= 10;
        }
    }
    
    return Result;
}

f32 ls_atof(char *s, u32 len)
{
    f32 base = 0;
    f32 decimal = 0;
    
    if(len == 0) { return 0.0f; }
    
    char buff[32] = {};
    
    char *At = s;
    u32 count = 0;
    u32 done = 0;
    while (len > 0)
    {
        if (*At == '.') { break; }
        At++; count++;
        len -= 1;
    }
    
    ls_memcpy(s, buff, count);
    done += count + 1;
    
    base = (f32)ls_atoi(buff, count);
    
    //NOTE: Means there's no decimal part. It's an integer.
    if(len == 0) { return base; }
    
    //string clear
    for(u32 i = 0; i < 32; i++) { buff[i] = 0; }
    
    count = 0;
    while (len > 0)
    {
        At++; count++;
        len -= 1;
    }
    
    ls_memcpy(s + done, buff, count);
    
    decimal = (f32)ls_atoi(buff, count);
    
    f32 Result = 0.0f;
    
    Result += base;
    
    u32 tenPow = 1;
    for(u32 i = 0; i < count; i++) { tenPow *= 10; }
    Result += (decimal / (f32)tenPow);
    
    return Result;
}

char *ls_strstr(char *haystack, char *needle)
{
    char *At = haystack;
    char *Bt = needle;
    
    u32 len = ls_len(needle);
    b32 found = FALSE;
    
    while(*At != 0)
    {
        if(*At == *Bt)
        {
            At++; Bt++;
            
            u32 currLen = len - 1;
            while(currLen--)
            {
                if(*At != *Bt) { break; }
                At++; Bt++;
            }
            
            if(currLen == 0) { found = TRUE; }
        }
        
        if(found) { return (At - len); }
        
        Bt = needle;
    }
    
    return NULL;
}

s32 ls_strcmp(char *a, char *b)
{
    s32 string1Len = ls_len(a);
    s32 string2Len = ls_len(b);
    
    char *At1 = a;
    char *At2 = b;
    
    b32 areSame = TRUE;
    while ((string1Len || string2Len) && areSame)
    {
        if (*At1 != *At2)
        {
            areSame = FALSE;
            break;
        }
        
        At1++;
        At2++;
        string1Len--;
        string2Len--;
    }
    
    if (areSame == TRUE)
    {
        return 0;
    }
    else
    {
        return *At1 < *At2 ? -1 : 1;
    }
    
    return 2;
}

s32 ls_strncmp(char *a, char *b, u32 n)
{
    s32 string1Len = ls_len(a);
    s32 string2Len = ls_len(b);
    
    char *At1 = a;
    char *At2 = b;
    
    u32 charsCompared = 0;
    
    b32 areSame = TRUE;
    while ((string1Len || string2Len) && areSame)
    {
        if(charsCompared == n) { break; }
        
        if (*At1 != *At2)
        {
            areSame = FALSE;
            break;
        }
        
        At1++;
        At2++;
        string1Len--;
        string2Len--;
        charsCompared += 1;
    }
    
    if (areSame == TRUE)
    {
        return 0;
    }
    else
    {
        return *At1 < *At2 ? -1 : 1;
    }
    
    return 2;
}

u64 ls_writeConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite);
u64 ls_readConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite);

s32 ls_formatStringInternal_(const char *format, char *dest, u32 destLen, va_list argList)
{
    char *buff = dest;
    
    const char *p = format;
    string s = {};
    char *s_label = 0;
    b32 isLong = FALSE;
    
    u64 uLongInt = 0;
    s64 nInt = 0;
    char c = 0;
    f32 nFloat = 0.0f;
    
    s8 maxLen = -1;
    
    s32 i = 0;
    for (p = format; *p != 0; p++)
    {
        //Reset Modifiers after every copied parameter
        b32 isLong = FALSE;
        b32 isBinary = FALSE;
        maxLen = -1;
        
        if(i >= destLen)
        {
            Assert(FALSE);
            int BufferOverrun = 0;
        }
        
        // Just copy wathever is not a passed parameter
        if (*p != '%')
        {
            buff[i] = *p;
            i++;
            continue;
        }
        
        p += 1; //Skip the '%'
        
        //Now check for modifiers
        if(*p == '.')
        {
            p += 1;
            Assert(ls_isANumber(*p) && *p != '0');
            maxLen = ls_ctoi(*p);
            p += 1;
        }
        
        if(*p == 'b') 
        { 
            p += 1; 
            isBinary = TRUE; 
        }
        
        switch (*p)
        {
            case 'l':
            isLong = TRUE;
            p++;
            
            case 'd':
            {
                if (isLong) { nInt = va_arg(argList, s64); }
                else { nInt = (u64)va_arg(argList, s32); }
                
                if(isBinary) {
                    s32 bitCount = HighestBitIdx64(nInt) + 1;
                    bitCount = (bitCount / 8) * 8; //NOTE: Get the closes byte.
                    if(bitCount == 0) { bitCount = 8; }
                    
                    buff[i] = '0';
                    buff[i+1] = 'b';
                    i += 2;
                    
                    s32 tmpCount = bitCount;
                    while(tmpCount != 0)
                    {
                        buff[i + (tmpCount-1)] = (nInt & 0x1) == 0 ? '0' : '1';
                        nInt >>= 1;
                        tmpCount -= 1;
                    }
                    
                    i += bitCount;
                    
                    break;
                }
                
                char *s = ls_itoa(nInt);
                u32 sLen = ls_len(s);
                ls_memcpy(s, buff + i, sLen);
                i += sLen;
                ls_free(s);
            } break;
            
            case 'c':
            {
                if(*(p+1) == 's')
                {
                    s_label = va_arg(argList, char *);
                    char *At = s_label;
                    u32 labelLen = ls_len(s_label);
                    ls_memcpy(s_label, buff + i, labelLen);
                    i += labelLen;
                    p += 1;
                }
                else
                {
                    c = va_arg(argList, int);
                    buff[i] = c;
                    i++;
                }
            } break;
            
            case 'f':
            {
                nFloat = va_arg(argList, f64);
                char *s = ls_ftoa(nFloat);
                u32 sLen = ls_len(s);
                
                u32 dotLen = 1;
                while(s[dotLen-1] != '.') { dotLen++; }
                
                if(maxLen != -1 && maxLen < sLen - dotLen) 
                {
                    ls_memcpy(s, buff + i, dotLen + maxLen);
                    i += dotLen + maxLen;
                }
                else 
                {
                    ls_memcpy(s, buff + i, sLen);
                    i += sLen;
                }
                
                ls_free(s);
            } break;
            
            case 's':
            {
                string tmp = va_arg(argList, string);
                ls_memcpy(tmp.data, buff + i, tmp.len);
                i += tmp.len;
            } break;
            
            case 'b':
            {
                s_label = va_arg(argList, char *);
                u32 size = va_arg(argList, u32);
                ls_memcpy(s_label, buff + i, size);
                i += size;
            } break;
            
            case 'p':
            {
                uLongInt = (u64)va_arg(argList, void *);
                char *s = ls_itoa(uLongInt);
                u32 sLen = ls_len(s);
                ls_memcpy(s, buff + i, sLen);
                i += sLen;
                ls_free(s);
            } break;
            
            case '%':
            buff[i] = '%';
            i++;
            break;
        }
    }
    
    buff[i] = 0;
    i++;
    
    return i;
}

s32 ls_vsprintf(char *dest, const char *format, va_list argList)
{
    const u32 buffSize = KB(1);
    char buff[buffSize] = {};
    
    s32 charactersWritten = ls_formatStringInternal_(format, buff, buffSize, argList);
    ls_memcpy(buff, dest, charactersWritten);
    
    return charactersWritten - 1; //Remove NULL terminator
}

/* Write a formatted string to dest.
* Returns the numbers of chars written without counting
* the null terminator (which is appended anyway)
*/
s32 ls_sprintf(char *dest, const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vsprintf(dest, format, argList);
    
    va_end(argList);
    
    return ret;
}

s32 ls_vprintf(const char *format, va_list argList)
{
    const u32 buffSize = KB(4);
    char buff[buffSize] = {};
    
    s32 charactersWritten = ls_formatStringInternal_(format, buff, buffSize, argList);
    
    //Write buffer to stdout file.
    ls_writeConsole(LS_STDOUT, buff, charactersWritten);
    
    return charactersWritten;
}

//TODO: Check if format actually has the right number of arguments!
s32 ls_printf(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    
    s32 ret = ls_vprintf(format, argList);
    
    va_end(argList);
    
    return ret;
}

char ls_getc()
{
    char Result = 0;
    ls_readConsole(LS_STDIN, &Result, 1);
    
    return Result;
}

////////////////////////////////////////////////////
//	FILE MANIPULATION FUNCTIONS
////////////////////////////////////////////////////

void ls_getFileNameFromPath(char *Path, char *out)
{
    u32 len = 0;
    char *At = Path;
    while(*At != 0) {len++; At++;}
    
    u32 i = len - 1;
    while (Path[i] != '\\')
    { i--; }
    
    ls_memcpy(Path + (i + 1), out, len - (i + 1));
    
    return;
}

void ls_getFileExtension(char *Path, char *out)
{
    u32 len = 0;
    char *At = Path;
    while(*At != 0) {len++; At++;}
    
    u32 i = len - 1;
    while (Path[i] != '.')
    { i--; }
    
    ls_memcpy(Path + (i + 1),out, len - (i + 1));
    
    return;
}

u64 ls_readConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite)
{
#ifdef LS_PLAT_WINDOWS
    return windows_ReadConsole(Source, bytesToWrite);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_ReadConsole(ConsoleHandle, Source, bytesToWrite);
#endif
}

u64 ls_readFile(char *Path, char **Dest, u32 bytesToRead)
{
#ifdef LS_PLAT_WINDOWS
    return windows_ReadFile(Path, Dest, bytesToRead);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_ReadFile(Path, Dest, bytesToRead);
#endif
}

u64 ls_ReadFileByOffset(char *Path, char **Dest, u64 offset, u32 bytesToRead)
{
#ifdef LS_PLAT_WINDOWS
    return windows_ReadFileByOffset(Path, Dest, offset, bytesToRead);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_ReadFileByOffset(Path, Dest, offset, bytesToRead);
#endif
}

u64 ls_writeConsole(s32 ConsoleHandle, char *Source, u32 bytesToWrite)
{
#ifdef LS_PLAT_WINDOWS
    return windows_WriteConsole(Source, bytesToWrite);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_WriteConsole(ConsoleHandle, Source, bytesToWrite);
#endif
}

u64 ls_writeFile(char *Path, void *Source, u32 bytesToWrite, b32 append)
{
#ifdef LS_PLAT_WINDOWS
    return windows_WriteFile(Path, (char *)Source, bytesToWrite, append);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_WriteFile(Path, Source, bytesToWrite);
#endif
}

b32 ls_fileExists(char *AbsPath)
{
#ifdef LS_PLAT_WINDOWS
    return windows_fileExists(AbsPath);
#endif
}

u32 ls_countFilesInDir(char *Dir)
{
    u32 dirLen = ls_len(Dir);
#ifdef LS_PLAT_WINDOWS
    return windows_countFilesInDir(Dir, dirLen);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_countFilesInDir(cStr, dirLen);
#endif
}

u32 ls_countFilesInDirByExt(char *Dir, char *ext)
{
    u32 dirLen = ls_len(Dir);
    u32 extLen = ls_len(ext);
    
#ifdef LS_PLAT_WINDOWS
    return windows_countFilesInDirByExt(Dir, dirLen,
                                        ext, extLen);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_countFilesInDirByExt(Dir, dirLen,
                                      ext, extLen);
#endif
}

u32 ls_countFilesInDirRecursive(char *Dir)
{
    u32 dirLen = ls_len(Dir);
#ifdef LS_PLAT_WINDOWS
    return windows_countFilesInDirRecursive(Dir, dirLen);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_countFilesInDirRecursive(Dir, dirLen);
#endif
}

u32 ls_getFileNamesInDir(char *Dir, char ***names, u32 **namesLen)
{
    u32 dirLen = ls_len(Dir);
#ifdef LS_PLAT_WINDOWS
    u32 howManyNames = 0;
    windows_getFileNamesInDir(Dir, dirLen, names, &howManyNames, namesLen);
    return howManyNames;
    
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_getFileNamesInDir(cDir, Dir.len);
#endif
}

u32 ls_getFileNamesInDirByExt(char *Dir, char *ext, char ***names, u32 **namesLen)
{
    u32 dirLen = ls_len(Dir);
    u32 extLen = ls_len(ext);
#ifdef LS_PLAT_WINDOWS
    u32 howManyNames = 0;
    windows_getFileNamesInDirByExt(Dir, dirLen, ext, extLen, names, &howManyNames, namesLen);
    return howManyNames;
    
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_countFilesInDirByExt(cDir, Dir.len,
                                      cExt, ext.len);
#endif
}

u32 ls_getFileNamesInDirRecursive(char *Dir, char ***names, u32 **namesLen)
{
    u32 dirLen = ls_len(Dir);
#ifdef LS_PLAT_WINDOWS
    u32 howManyNames = 0;
    windows_getFileNamesInDirRecursive(Dir, dirLen, names, &howManyNames, namesLen);
    return howManyNames;
    
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_getFileNamesInDir(cDir, Dir.len);
#endif
}

u32 ls_getFilePathsInDirRecursive(char *Dir, char ***names, u32 **namesLen)
{
    u32 dirLen = ls_len(Dir);
#ifdef LS_PLAT_WINDOWS
    u32 howManyNames = 0;
    windows_getFilePathsInDirRecursive(Dir, dirLen, names, &howManyNames, namesLen);
    return howManyNames;
    
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_getFileNamesInDir(cDir, Dir.len);
#endif
}

u32 ls_getFullPathName(char *name, char *buff, u32 buffMaxSize)
{
#ifdef LS_PLAT_WINDOWS
    return windows_getFullPathName(name, buffMaxSize, buff);
#endif
    
#ifdef LS_PLAT_LINUX
    char buffer[256] = {};
    return linux_getFullPathName(name, 256, buffer);
#endif
}

////////////////////////////////////////////////////
//	GENERAL PURPOSE SYSTEM FUNCTIONS
////////////////////////////////////////////////////

u64 ls_getTimeSinceEpochInMicrosec()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetWindowsTimeInMicrosec();
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_GetWindowsTime();
#endif
}

u64 ls_getTimeSinceEpochIn100Nanosec()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetWindowsTimeIn100Nanosec();
#endif
}

u32 ls_getUnix32Time()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetUnix32Time();
#endif
}

u64 ls_getUnix64Time()
{
#ifdef LS_PLAT_WINDOWS
    return windows_GetUnix64Time();
#endif
}

Date ls_getDateTime(b32 local)
{
    const char *dayLookup[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    u32  dayLenLookup[7] = { 7, 8, 10, 9, 7, 9, 7 };
    const char *monthLookup[12] = {"January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",};
    u32  monthLenLookup[12] = { 8, 9, 6, 6, 4, 5, 5, 7, 10, 8, 9, 9 };
    
    Date Result = {};
    
#ifdef LS_PLAT_WINDOWS
    windowsDate wDate = windows_GetDate(local);
    
    Result.milliseconds = wDate.Milliseconds;
    Result.seconds = wDate.Second;
    Result.minutes = wDate.Minute;
    Result.hour = wDate.Hour;
    Result.day = wDate.Day;
    ls_memcpy((void *)dayLookup[wDate.DayOfWeek], Result.dayName, dayLenLookup[wDate.DayOfWeek]);
    Result.month = wDate.Month;
    ls_memcpy((void *)monthLookup[wDate.Month], Result.monthName, monthLenLookup[wDate.Month]);
    Result.year = wDate.Year;
#endif
    
#ifdef LS_PLAT_LINUX
    linuxDate lDate = linux_GetDate(local);
    
    Result.milliseconds = lDate.Milliseconds;
    Result.seconds = lDate.Second;
    Result.minutes = lDate.Minute;
    Result.hour = lDate.Hour;
    Result.day = lDate.Day;
    Result.dayName = ls_getDayName(lDate.DayOfWeek);
    Result.month = lDate.Month;
    Result.monthName = ls_getMonthName(lDate.Month);
    Result.year = lDate.Year;
#endif
    
    return Result;
}

void ls_sleep(u64 milliseconds)
{
#ifdef LS_PLAT_WINDOWS
    windows_sleep(milliseconds);
#endif
}

////////////////////////////////////////////////////
//	MEMORY FUNCTIONS
////////////////////////////////////////////////////

void ls_memcpy(void *src, void *dest, size_t size)
{
    if(size == 0) { return; }
    
    char *At = (char *)src;
    char *To = (char *)dest;
    size_t it = size;
    
    switch (size)
    {
        case 1:
        *To = *At;
        return;
        case 2:
        *(u16 *)To = *(u16 *)At;
        return;
        case 4:
        *(u32 *)To = *(u32 *)At;
        return;
        case 8:
        *(u64 *)To = *(u64 *)At;
        return;
        case 16:
        *(u64 *)To = *(u64 *)At;
        At += 8; To += 8;
        *(u64 *)To = *(u64 *)At;
        return;
        case 32:
        for (int i = 0; i < 4; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 64:
        for (int i = 0; i < 8; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 128:
        for (int i = 0; i < 16; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 256:
        for (int i = 0; i < 32; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 512:
        for (int i = 0; i < 64; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 1024:
        for (int i = 0; i < 128; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 2048:
        for (int i = 0; i < 256; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 4096:
        for (int i = 0; i < 512; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 8192:
        for (int i = 0; i < 1024; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 16384:
        for (int i = 0; i < 2048; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 32768:
        for (int i = 0; i < 4096; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 65536:
        for (int i = 0; i < 8192; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 131072:
        for (int i = 0; i < 16384; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 262144:
        for (int i = 0; i < 32768; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        return;
        case 524288:
        for (int i = 0; i < 65536; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        case 1048576:
        for (int i = 0; i < 131072; i++)
        { *(((u64 *)To) + i) = *(((u64 *)At) + i); }
        default:
        while (it--)
        {
            *To = *At;
            At++;
            To++;
        }
        return;
    }
}

void ls_memset(void *src, u8 v, size_t numBytes)
{
    u8 *At = (u8 *)src;
    u32 i = 0;
    while(numBytes--, i) { At[i] = v; i += 1; }
}

b32 ls_memcmp(void *a, void *b, size_t size)
{
    char *At = (char *)a;
    char *Bt = (char *)b;
    
    for (u32 i = 0; i < size; i++)
    {
        if (*At != *Bt)
        { return FALSE; }
        At++;
        Bt++;
    }
    
    return TRUE;
}

void ls_zeroMem(void *mem, size_t size)
{
    
    char *To = (char *)mem;
    size_t it = size;
    
    switch (size)
    {
        case 1:
        *To = 0;
        return;
        case 2:
        *(u16 *)To = 0;
        return;
        case 4:
        *(u32 *)To = 0;
        return;
        case 8:
        *(u64 *)To = 0;
        return;
        case 16:
        *(u64 *)To = 0;
        To += 8;
        *(u64 *)To = 0;
        return;
        case 32:
        for (int i = 0; i < 4; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 64:
        for (int i = 0; i < 8; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 128:
        for (int i = 0; i < 16; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 256:
        for (int i = 0; i < 32; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 512:
        for (int i = 0; i < 64; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 1024:
        for (int i = 0; i < 128; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 2048:
        for (int i = 0; i < 256; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 4096:
        for (int i = 0; i < 512; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 8192:
        for (int i = 0; i < 1024; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 16384:
        for (int i = 0; i < 2048; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 32768:
        for (int i = 0; i < 4096; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 65536:
        for (int i = 0; i < 8192; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 131072:
        for (int i = 0; i < 16384; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 262144:
        for (int i = 0; i < 32768; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 524288:
        for (int i = 0; i < 65536; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        case 1048576:
        for (int i = 0; i < 131072; i++)
        { *(((u64 *)To) + i) = 0; }
        return;
        default:
        while (it--)
        {
            *To = 0;
            To++;
        }
        return;
    }
}

//@TODO: Modify ls_alloc to automatically check if the returned pointer is null.
void *ls_alloc(u64 size)
{
#ifdef LS_PLAT_WINDOWS
    return windows_memAlloc(size);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_memAlloc(size);
#endif
}

void *ls_realloc(void *originalMem, u64 oldSize, u64 newSize)
{
    if(originalMem)
    {
        u32 cpySize = oldSize < newSize ? oldSize : newSize;
        void *newMem = windows_memAlloc(newSize);
        ls_memcpy(originalMem, newMem, cpySize);
        windows_memFree(originalMem);
        
        return newMem;
    }
    
    return windows_memAlloc(newSize);
}

void ls_free(void *p)
{
#ifdef LS_PLAT_WINDOWS
    return windows_memFree(p);
#endif
    
#ifdef LS_PLAT_LINUX
    return linux_memFree(p);
#endif
}


u32 ls_bitReverse(u32 a) //NOTE: I don't know where to put this.
{
    //NOTE: Dirty Bit Reverse.
    //Do we really not have any intrinsics for this!?
    u32 Result = 0;
    
    while(a > 0)
    {
        Result <<= 1;
        
        if((a & 1) == 1) { Result ^= 1; }
        
        a >>= 1;
    }
    
    return Result;
}

////////////////////////////////////////////////////
//	INTRINSICS
////////////////////////////////////////////////////

#if _M_IX86
#define LeadingZeros(value) LeadingZeros32((u32)value)
#define HighestBitIdx(value) HighestBitIdx32((u32)value)
#elif _M_X64
#define LeadingZeros(value) LeadingZeros64((u64)value)
#define HighestBitIdx(value) HighestBitIdx64((u64)value)
#endif

u32 LeadingZeros32(u32 value)
{
    unsigned long index = 0;
#ifdef LS_PLAT_WINDOWS
#ifdef __GNUG__
    index = __builtin_clz(value);
    return index;
#else
    _BitScanReverse(&index, value);
    return 31 - index;
#endif
#endif
    
#ifdef LS_PLAT_LINUX
    index = __builtin_clz(value);
    return index;
#endif
}

u32 LeadingZeros64(u64 value)
{
    unsigned long index = 0;
#if _M_IX86
    return LeadingZeros32(value);
#else
    
#ifdef LS_PLAT_WINDOWS
#ifdef __GNUG__
    index = __builtin_clz(value);
    return index;
#else
    _BitScanReverse64(&index, value);
    return 63 - index;
#endif
#endif
    
#ifdef LS_PLAT_LINUX
    index = __builtin_clz(value);
    return index;
#endif
    
#endif
}

// 63 - bsr = clz
// clz - 63 = - bsr
// 63 - clz = bsr

u32 HighestBitIdx32(u32 value)
{
    unsigned long index = 0;
#ifdef LS_PLAT_WINDOWS
#ifdef __GNUG__
    index = __builtin_clz(value);
    return 31 - index;
#else
    _BitScanReverse(&index, value);
    return index;
#endif
#endif
}

u32 HighestBitIdx64(u64 value)
{
    unsigned long index = 0;
#if _M_IX86
    return HighestBitIdx32(value);
#else
    
#ifdef LS_PLAT_WINDOWS
#ifdef __GNUG__
    index = __builtin_clz(value);
    return 63 - index;
#else
    _BitScanReverse64(&index, value);
    return index;
#endif
#endif
    
#endif
}

f32 Log2(u64 value)
{
    unsigned long index = 0;
#ifdef LS_PLAT_WINDOWS
#if _M_IX86
    index = HighestBitIdx32((u32)value);
#else
    index = HighestBitIdx64(value);
#endif
#endif
    
#ifdef LS_PLAT_LINUX
    index = __builtin_ctz(value);
#endif
    
    f32 Result = (f32)index;
    
    if (((value >> (index-1)) & 1u))
    {
        Result += 0.50f;
        if (((value >> (index - 2)) & 1u))
        {
            Result += 0.315f;
            if (((value >> (index - 3)) & 1u))
            { Result += 0.10f; }
        }
    }
    return Result;
}

f32 Log10(u64 v)
{
    f64 x = 0.3010299957f * Log2(v);
    u64 value = (u64)x;
    
    if(((f64)(value + 1) - x) < 0.005f)
    { return f64(value + 1); }
    
    return x;
}

u32 Log10i(u64 value)
{
    if(value < 10ULL) { return 0; }
    else if((value > 10ULL) && (value < 100ULL)) { return 1; }
    else if((value > 100ULL) && (value < 1000ULL)) { return 2; }
    else if((value > 1000ULL) && (value < 10000ULL)) { return 3; }
    else if((value > 10000ULL) && (value < 100000ULL)) { return 4; }
    else if((value > 100000ULL) && (value < 1000000ULL)) { return 5; }
    else if((value > 1000000ULL) && (value < 10000000ULL)) { return 6; }
    else if((value > 10000000ULL) && (value < 100000000ULL)) { return 7; }
    else if((value > 100000000ULL) && (value < 1000000000ULL)) { return 8; }
    else if((value > 1000000000ULL) && (value < 10000000000ULL)) { return 9; }
    else if((value > 10000000000ULL) && (value < 100000000000ULL)) { return 10; }
    else if((value > 100000000000ULL) && (value < 1000000000000ULL)) { return 11; }
    
    return 99999;
}

u16 ByteSwap16(u16 value)
{
#ifdef LS_PLAT_WINDOWS
    return _byteswap_ushort(value);
#endif
    
#ifdef LS_PLAT_LINUX
    return __builtin_bswap16(value);
#endif
}

u32 ByteSwap32(u32 value)
{
#ifdef LS_PLAT_WINDOWS
#ifdef __GNUG__
    return __builtin_bswap32(value);
#else
    return _byteswap_ulong(value);
#endif
#endif
    
#ifdef LS_PLAT_LINUX
    return __builtin_bswap32(value);
#endif
}

u64 ByteSwap64(u64 value)
{
#ifdef LS_PLAT_WINDOWS
#ifdef __GNUG__
    return __builtin_bswap64(value);
#else
    return _byteswap_uint64(value);
#endif
#endif
    
#ifdef LS_PLAT_LINUX
    return __builtin_bswap64(value);
#endif
}

f32 Ceil(f32 v)
{
    
#ifdef LS_PLAT_WINDOWS
#ifdef __GNUG__
    //Shit
    return (int)(v+1);
#else
    __m128 Result = _mm_set_ps1(v);
    Result = _mm_ceil_ps(Result);
    
    return (Result.m128_f32[0]);
#endif
#endif
    
#ifdef LS_PLAT_LINUX
    return 0.0f;
#endif
}

#endif
