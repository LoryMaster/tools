#ifndef LS_STRING_H
#define LS_STRING_H

#include "win32.h"
#include "lsCRT.h"

//TODO: Make size = -1 meaning undefined, and size = 0, meaning a constant string,
//      to allow the string functions to know if they're dealing with constant strings or not.

//NOTE: The minus 1 is to ignore the NULL terminator at the end of string literals.
#define ls_strConst(s) {s, sizeof(s)/sizeof(s[0])-1, sizeof(s)/sizeof(s[0])-1}

struct string
{
    char *data;
    u32  len;
    u32  size;
};

struct view
{
    string s;
    
    char *next;
    u32  len;
};

extern "C" //STRINGS
{
    //Create/Destroy
    string  ls_strAlloc(u32 size);
    string *ls_strAllocPtr(u32 size);
    void    ls_strFree(string *s);
    void    ls_strFreePtr(string *s);
    void    ls_strFreeArr(string *s, u32 arrSize);
    
    
    //Manage
    string  ls_strInit(char *s);
    void    ls_strClear(string *s);
    string  ls_strCopy(string s);
    void	ls_strNCopy(string s, string *dst, size_t size);
    string  ls_strCopySubstr(string s, u32 beginIdx, u32 _endIdx = (u32)-1);
    
    
    //C Bullshit
    void    ls_strNullTerminate(string *s);
    char   *ls_strToCStr(string s);
    b32     ls_strToCStr_t(string s, char *buff, s32 buffSize);
    
    
    //OperateOn
    void    ls_strReverse(string *s);
    void    ls_strRmSubstr(string *s, u32 beginIdx, u32 endIdx);
    void    ls_strRmIdx(string *s, u32 idx);
    void    ls_strRmAllNonTextChar(string *s);
    
    //NOTE: Maybe reword these?
    string  *ls_breakByDelimeter(string s, u32 *numOfStrings, char c);
    string  *ls_breakByLine(string s, u32 *numOfLines);
    string  *ls_breakByWhitespace(string s, u32 *numOfStrings);
    string  *ls_breakBySpace(string s, u32 *numOfStrings);
    string  *ls_breakBySpaceUntilDelimiter(string s, char delimiter, u32 *numOfStrings);
    u32     ls_strLeftFind(string s, char c);
    u32     ls_strRightFind(string s, char c);
    
    
    //Merge
    string  ls_strConcat(string s1, string s2);
    void    ls_strConcatOn(string s1, string s2, string *out);
    string  ls_strCatChar(string s1, char c);
    string  ls_strCatCStr(string s1, char *c);
    void    ls_strPrepend(string *s1, string s2);
    void    ls_strPrependChar(string *s, char c);
    void    ls_strPrependCStr(string *s, char *c);
    void    ls_strAppend(string *s1, string s2);
    void    ls_strAppendView(string *s1, view v);
    void    ls_strAppendChar(string *s1, char c);
    void    ls_strAppendCStr(string *s1, char *c);
    void    ls_strAppendNCStr(string *s1, char *c, u32 len);
    
    
    //To/From Data
    b32     ls_strIsANumber(string s);
    string  ls_itos(s64 x);
    void    ls_itosOn(s64 x, string *out);
    string  ls_itoh(u64 x);
    s64     ls_stoi(string s);
    f32	 ls_stof(string s);
    string  ls_ftos(f32 x);
    
    
    //Operator
    b32     operator==(string s1, string s2);
    b32     operator!=(string s1, string s2);
    
    b32     ls_strIsEqualNCStr(string s1, char *s2, u32 len);
};



extern "C" //VIEWS
{
    //Create/Destroy
    view ls_viewCreate(string s);
    
    //OperateOn
    view ls_viewEatWhitespace(view v);
    view ls_viewNextNChars(view v, u32 n);
    view ls_viewNextDelimiter(view v, char c);
    view ls_viewNextWord(view v);
    view ls_viewNextLine(view v);
    view ls_viewNextLineSkipWS(view v);
    
    b32 ls_viewIsLineEmpty(view v);
};


#endif //LS_STRING_H


#ifdef LS_STRING_IMPLEMENTATION

/*vv INTERNAL vv*/
static void ls_strGrow(string *s, u32 amount)
{
    u32 newSize = s->size + amount;
    
    char *newData = (char *)ls_alloc(sizeof(char)*newSize);
    if(s->data)
    {
        ls_memcpy(s->data, newData, s->len);
        ls_free(s->data);
    }
    
    s->data = newData;
    s->size = newSize;
}
/*^^ INTERNAL ^^*/



//------------------//
//  Create/Destroy  //

string ls_strAlloc(u32 size)
{
    char *data = (char *)ls_alloc(sizeof(char)*size);
    string Result = {data, 0, size};
    
    return Result;
}

string *ls_strAllocPtr(u32 size)
{
    string *Result = (string *)ls_alloc(sizeof(string));
    *Result = ls_strAlloc(size);
    
    return Result;
};

void ls_strFree(string *a)
{
    ls_free(a->data);
    a->data = 0;
    a->len = 0;
    a->size = 0;
}

void ls_strFreePtr(string *a)
{
    ls_free(a->data);
    a->data = 0;
    a->len = 0;
    a->size = 0;
    
    ls_free(a);
}

void ls_strFreeArr(string *s, u32 arrSize)
{
    for(u32 i = 0; i < arrSize; i++)
    { ls_strFree(&s[i]);}
    
    ls_free(s);
}

//  Create/Destroy  //
//------------------//


//------------------//
//     Manage       //

string ls_strInit(char *s)
{
    u32 len = ls_len(s);
    
    string Result = ls_strAlloc(len);
    ls_memcpy(s, Result.data, len);
    Result.len = len;
    
    return Result;
}

void ls_strClear(string *s)
{ s->len = 0; }

string ls_strCopy(string s)
{
    string Result = ls_strAlloc(s.len);
    ls_memcpy(s.data, Result.data, s.len);
    Result.len = s.len;
    
    return Result;
}

void ls_strNCopy(string src, string *dst, size_t size)
{
    u32 copySize = size;
    if(size > src.len) { copySize = src.len; }
    
    if(dst->data == NULL) { *dst = ls_strAlloc(copySize); }
    
    if(dst->size < src.len)
    {
        u32 growAmount = (dst->size - src.len + 32);
        ls_strGrow(dst, growAmount);
    }
    
    ls_memcpy(src.data, dst->data, copySize);
    dst->len = copySize;
}

string ls_strCopySubstr(string s, u32 beginIdx, u32 _endIdx)
{
    u32 endIdx = 0;
    if(_endIdx == (u32)-1) { endIdx = s.len-1; }
    else { endIdx = _endIdx; }
    
    if((beginIdx < 0 || beginIdx >= s.size) ||
       (endIdx < 0 || endIdx >= s.size) ||
       (endIdx - beginIdx >= s.size))
    { string error = {}; return error; }
    
    //TODO: Remove THIS
    // Need NULL terminator cause I haven't changed
    // All my functions to work with strings yet...
    string result = ls_strAlloc(((endIdx - beginIdx) + 1) + 1);
    
    ls_memcpy(s.data + beginIdx, result.data, result.size);
    result.len = (endIdx - beginIdx + 1);
    result.data[result.len] = 0;
    
    return result;
}

//      Manage      //
//------------------//


//------------------//
//    C Bullshit    //

void ls_strNullTerminate(string *s)
{
    if(s->len == s->size)
    { ls_strGrow(s, 1); }
    
    s->data[s->len] = 0;
}

char *ls_strToCStr(string s)
{
    char *result = (char *)ls_alloc(s.len + 1);
    ls_memcpy(s.data, result, s.len);
    result[s.len] = 0;
    
    return result;
}

b32 ls_strToCStr_t(string s, char *buff, s32 buffSize)
{
    if(buffSize < s.len+1) { ls_printf("C String Buff not large enough.\n"); return FALSE; }
    
    ls_memcpy(s.data, buff, s.len);
    buff[s.len] = 0;
    
    return TRUE;
}


//    C Bullshit    //
//------------------//


//------------------//
//     OperateOn    //

void ls_strReverse(string *s)
{
    char *Begin = s->data;
    char *End = s->data + s->len;
    if(*End == 0) { End--; } //Ignore null-terminator
    while (Begin < End)
    {
        char temp = *Begin;
        *Begin = *End;
        *End = temp;
        Begin++;
        End--;
    }
}

void ls_strRmSubstr(string *s, u32 beginIdx, u32 endIdx)
{
    if((beginIdx < 0 || beginIdx >= s->size) ||
       (endIdx < 0 || endIdx >= s->size) ||
       (endIdx - beginIdx >= s->size))
    { return; }
    
    u32 remove = ((endIdx - beginIdx) + 1);
    remove = remove > s->len ? s->len : remove;
    u32 copyLen = s->len - (endIdx + 1);
    copyLen = copyLen == 0 ? 1 : copyLen;
    ls_memcpy((void *)(s->data + endIdx + 1), (void *)(s->data + beginIdx), copyLen);
    s->len -= remove;
    s->data[s->len] = 0;
    
    return;
}

void ls_strRmIdx(string *s, u32 idx)
{ ls_strRmSubstr(s, idx, idx); }

void ls_strRmAllNonTextChar(string *s)
{
    string *Result = ls_strAllocPtr(s->size);
    
    for(u32 i = 0; i < s->len; i++)
    {
        char c = s->data[i];
        if(!ls_isANumber(c))
        {
            if(c != '\r' && c != '\n' && c != '\t')
            {
                if(c < 32 || c > 126)
                { continue; }
            }
        }
        
        ls_strAppendChar(Result, c);
    }
    
    ls_free(s->data);
    *s = *Result;
    
    return;
}

string *ls_breakByDelimeter(string s, u32 *numOfStrings, char c)
{
    if(s.data == NULL) { return NULL; }
    
    string *Result = 0;
    //The thing could crash if this buff overflows
    string buff[16384] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        Assert(buffIdx < 16384);
        
        if (*At == c)
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        At++;
        count++;
        
        if ((*At == 0) && (count))
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            break;
        }
        
    } while (*At);
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    
    if(numOfStrings) {*numOfStrings = buffIdx;}
    
    return Result;
}

string *ls_breakByLine(string s, u32 *numOfLines)
{
    if(s.data == NULL) { return NULL; }
    
    u32 numLines = 1; // NOTE: Last line doesn't have newline in string? Can it?
    char *bAt = s.data;
    u32 l = s.len;
    //NOTE: This is currently overcounting when there's two newlines one after the other
    //But it doesn't matter because I only need the base pointer to free this, so no
    //memory is leaked, only slightly overused for most cases.
    while(l--)
    {
        if(*bAt == '\r') { numLines++; bAt += 2; l -= 1; continue; }
        if(*bAt == '\n') { numLines++; bAt += 1; continue; }
        bAt += 1;
    }
    
    string *Result = (string *)ls_alloc(sizeof(string)*numLines);
    
    char *At = s.data;
    u32 count = 0;
    u32 done = 0;
    u32 idx = 0;
    numLines = 0;
    
    u32 currLen = s.len;
    while(currLen--)
    {
        if(*At == '\r' && count == 0) { At += 2; currLen--; done += 2; continue; }
        if(*At == '\n' && count == 0) { At += 1; done += 1; continue; }
        
        
        if(*At == '\n' || currLen == 0)
        {
            u32 extra = 0;
            if(*(At-1) == '\r') { count--; extra = 1; }
            if(currLen == 0) {count += 1;}
            
            Result[idx] = ls_strAlloc(count + 1); numLines += 1;
            ls_memcpy(s.data + done, Result[idx].data, count);
            Result[idx].data[count] = 0;
            Result[idx].len  = count;
            
            done += count + 1 + extra;
            idx++;
            count = 0;
            
            At++;
            continue;
        }
        
        At++;
        count++;
    }
    
    if(numOfLines) { *numOfLines = numLines; }
    return Result;
}

string *ls_breakByWhitespace(string s, u32 *numOfStrings)
{
    if(s.data == NULL) { return NULL; }
    
    string *Result = 0;
    string buff[16384] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        Assert(buffIdx < 16384);
        
        if ((*At == ' ') || (*At == '\n') || (*At == '\t') || (*At == '\r') )
        {
            //TODO: Test this
            if((*At == '\r') && (*(At + 1) == '\n'))
            {
                done++;
                At++;
            }
            
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count + 1;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        At++;
        count++;
        
        if ((*At == 0) && (count))
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*(count + 1));
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].data[count] = 0;
            buff[buffIdx].size = count + 1;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            break;
        }
        
    } while (*At);
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    
    if(numOfStrings) {*numOfStrings = buffIdx;}
    
    return Result;
}

string *ls_breakBySpace(string s, u32 *numOfStrings)
{
    Assert(s.len != 0);
    return ls_breakByDelimeter(s, numOfStrings, ' ');
}

string *ls_breakBySpaceUntilDelimiter(string s, char delimiter, u32 *numOfStrings)
{
    string *Result = 0;
    string buff[256] = {};
    u32 buffIdx = 0;
    char *At = s.data;
    
    u32 count = 0;
    u32 done = 0;
    do
    {
        Assert(buffIdx < 256);
        
        if (*At == delimiter)
        {
            if(*(At + 1) == ' ') {done++;}
            done++;
            break;
        }
        
        if (*At == ' ')
        {
            
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*count);
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        At++;
        count++;
        
        if ((*At == 0) && (count))
        {
            buff[buffIdx].data = (char *)ls_alloc(sizeof(char)*count);
            
            ls_memcpy(s.data + done, buff[buffIdx].data, count);
            buff[buffIdx].size = count;
            buff[buffIdx].len  = count;
            
            done += count + 1;
            buffIdx++;
            count = 0;
            At++;
            continue;
        }
        
    } while (*At);
    
    Result = (string *)ls_alloc(sizeof(string)*buffIdx);
    ls_memcpy(buff, Result, sizeof(string)*buffIdx);
    if(numOfStrings) { *numOfStrings = buffIdx; }
    
    return Result;
}

u32 ls_strLeftFind(string s, char c)
{
    char *At = s.data;
    u32 offset = 0;
    
    //NOTE:TODO Is && correct!?
    while ((*At != c) && (At != (s.data + s.len)))
    { At++; offset++; }
    
    return offset;
}

u32 ls_strRightFind(string s, char c)
{
    char *At = s.data + s.len;
    u32 offset = s.len;
    
    //NOTE:TODO Is && correct!?
    while((*At != c) && (At != s.data))
    {
        At--;
        offset--;
    }
    
    return offset;
}

//    OperateOn     //
//------------------//


//------------------//
//      Merge       //

string ls_strConcat(string s1, string s2)
{
    string Result = ls_strAlloc(s1.len + s2.len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len); }
    if(s2.len) { ls_memcpy(s2.data, Result.data + s1.len, s2.len); }
    Result.len = s1.len + s2.len;
    
    return Result;
}

void ls_strConcatOn(string s1, string s2, string *out)
{
    if(out == 0x0) return;
    if(out->data == 0x0) return;
    if(out->size < (s1.len + s2.len)) { return; }
    
    if(s1.len) { ls_memcpy(s1.data, out->data, s1.len); }
    if(s2.len) { ls_memcpy(s2.data, out->data + s1.len, s2.len); }
    out->len = s1.len + s2.len;
}

string ls_strCatChar(string s, char c)
{
    string Result = ls_strAlloc(s.len + 1);
    if(s.len) { ls_memcpy(s.data, Result.data, s.len); }
    Result.data[s.len] = c;
    Result.len = s.len + 1;
    
    return Result;
}

string ls_strCatCStr(string s1, char *s2)
{
    u32 s2Len = ls_len(s2);
    
    string Result = ls_strAlloc(s1.len + s2Len);
    if(s1.len) { ls_memcpy(s1.data, Result.data, s1.len); }
    if(s2Len) { ls_memcpy(s2, Result.data + s1.len, s2Len); }
    Result.len = s1.len + s2Len;
    
    return Result;
}

void ls_strPrepend(string *s1, string s2)
{
    Assert(s1);
    Assert(s1->data);
    Assert(s2.data);
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    //NOTE: TODO: Backwards memcpy
    u32 cpySize = s1->len;
    char *At = s1->data + s1->len - 1;
    char *To = s1->data + s1->len + s2.len - 1;
    while(cpySize--)
    {
        *To = *At;
        At--;
        To--;
    }
    ls_memcpy(s2.data, s1->data, s2.len);
    s1->len = s1->len + s2.len;
}

void ls_strPrependChar(string *s1, char c)
{
    Assert(s1);
    Assert(s1->data);
    
    if(s1->len + 1 > s1->size)
    { ls_strGrow(s1, 32); }
    
    //NOTE: TODO: Backwards memcpy
    u32 cpySize = s1->len;
    char *At = s1->data + s1->len - 1;
    char *To = s1->data + s1->len;
    while(cpySize--)
    {
        *To = *At;
        At--;
        To--;
    }
    ls_memcpy(s1->data, s1->data + 1, s1->len);
    
    s1->data[0] = c;
    s1->len += 1;
}

void ls_strPrependCStr(string *s1, char *s2)
{
    Assert(s1);
    Assert(s2);
    Assert(s1->data);
    
    u32 s2Len = ls_len(s2);
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    ls_memcpy(s1->data, s1->data + s2Len, s1->len);
    ls_memcpy(s2, s1->data, s2Len);
    s1->len = s1->len + s2Len;
}

//@NOTE:TODO: Something strange appening in strings appending and getting longer
//Looks like memory stomping. Not quite sure how it would happen, since the grow
//seems to be good. - 29/04/2019
void ls_strAppend(string *s1, string s2)
{
    //NOTE: Do I want these asserts?
    Assert(s1);
    Assert(s1->data);
    Assert(s2.data);
    
    if(s1->len + s2.len > s1->size)
    {
        u32 growSize = ((s1->len + s2.len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    ls_memcpy(s2.data, s1->data + s1->len, s2.len);
    s1->len += s2.len;
}

void ls_strAppendView(string *s, view v)
{
    //NOTE: Do I want these asserts?
    Assert(s);
    Assert(s->data);
    
    if(s->len + v.s.len > s->size)
    {
        u32 growSize = ((s->len + v.s.len) - s->size) + 32;
        ls_strGrow(s, growSize);
    }
    
    ls_memcpy(v.s.data, s->data + s->len, v.s.len);
    s->len += v.s.len;
}

void ls_strAppendChar(string *s1, char c)
{
    //NOTE: Do I want these asserts?
    Assert(s1);
    Assert(s1->data);
    
    if(s1->len + 1 > s1->size)
    { ls_strGrow(s1, 32); }
    
    s1->data[s1->len] = c;
    s1->len += 1;
}

void ls_strAppendCStr(string *s1, char *c)
{
    u32 len = ls_len(c);
    ls_strAppendNCStr(s1, c, len);
}

void ls_strAppendNCStr(string *s1, char *c, u32 s2Len)
{
    //NOTE: Do I want these asserts?
    Assert(s1);
    Assert(c);
    Assert(s1->data);
    
    if(s1->len + s2Len > s1->size)
    {
        u32 growSize = ((s1->len + s2Len) - s1->size) + 32;
        ls_strGrow(s1, growSize);
    }
    
    ls_memcpy(c, s1->data + s1->len, s2Len);
    s1->len += s2Len;
}

//      Merge       //
//------------------//


//------------------//
//   To/From Data   //

b32 ls_strIsANumber(string s)
{
    for(u32 i = 0; i < s.len; i++)
    {
        if(ls_isANumber(s.data[i]) == FALSE)
        { return FALSE; }
    }
    
    return TRUE;
}

string ls_itos(s64 x)
{
    string result = ls_strAlloc(32);
    ls_itosOn(x, &result);
    return result;
}

void ls_itosOn(s64 x, string *out)
{
    Assert(out != 0x0);
    Assert(out->data != 0x0);
    Assert(out->size > 20);
    
    bool isNegative = x < 0;
    s64 value = isNegative ? -x : x;
    
    if (value == 0)
    {
        out->data[0] = '0';
        out->data[1] = '\0';
        out->len = 1;
        
        return;
    }
    
    //My Log10 Function is not super precise at the boundaries between values i.e. 999999 - 1000000. So just to be sure, I give it an extra byte, which is super fine.
    
    //Update months Later: BTW I think this is a fuckin waste of time and processor power, considering no number to be printed is ever going to be bigger than 128 char long
    //I should just waste this 0.000000016% of the average computer FUCKING Memory to just allocate a little bit more than necessary.
    
    //I'm not going to change it now just because it's good training for me to approximate trascendental functions and stuff like that
    
    //Update few days later: Fuck it I'm changing this shitty Log10 functions that sucks freakin balls.
    
    //@TODO @CLEANUP @FIXME: Make a Log2 / Log10 / LOGN Function Tables so that I quit having this stupid shitty problem. (Or maybe see if theres cool ASM for them)
    
    s32 i = 0;
    
    while (value != 0)
    {
        out->data[i++] = value % 10 + '0';
        value = value / 10;
    }
    
    if (isNegative) { out->data[i++] = '-'; }
    out->data[i] = '\0';
    
    //@TODO@Speed Never build the string flipped!
    //(Still would need an approx of size.)
    
    //Flip string, it's in reverse.
    for (int t = 0; t < i / 2; t++)
    {
        out->data[t] ^= out->data[i - t - 1];
        out->data[i - t - 1] ^= out->data[t];
        out->data[t] ^= out->data[i - t - 1];
    }
    out->len = (u32)i;
}

string ls_itoh(u64 x)
{
    string buffer = ls_strAlloc(32);
    string Result = ls_strAlloc(64);
    
    u8 *At = (u8 *)&x;
    for(u32 i = 0; i < 8; i++)
    {
        u8 lowNybble = (*At & 0x0F);
        u8 highNybble = (*At & 0xF0) >> 4;;
        
        switch(lowNybble)
        {
            case 0:  ls_strAppendChar(&buffer, '0'); break;
            case 1:  ls_strAppendChar(&buffer, '1'); break;
            case 2:  ls_strAppendChar(&buffer, '2'); break;
            case 3:  ls_strAppendChar(&buffer, '3'); break;
            case 4:  ls_strAppendChar(&buffer, '4'); break;
            case 5:  ls_strAppendChar(&buffer, '5'); break;
            case 6:  ls_strAppendChar(&buffer, '6'); break;
            case 7:  ls_strAppendChar(&buffer, '7'); break;
            case 8:  ls_strAppendChar(&buffer, '8'); break;
            case 9:  ls_strAppendChar(&buffer, '9'); break;
            case 10: ls_strAppendChar(&buffer, 'A'); break;
            case 11: ls_strAppendChar(&buffer, 'B'); break;
            case 12: ls_strAppendChar(&buffer, 'C'); break;
            case 13: ls_strAppendChar(&buffer, 'D'); break;
            case 14: ls_strAppendChar(&buffer, 'E'); break;
            case 15: ls_strAppendChar(&buffer, 'F'); break;
        }
        
        switch(highNybble)
        {
            case 0:  ls_strAppendChar(&buffer, '0'); break;
            case 1:  ls_strAppendChar(&buffer, '1'); break;
            case 2:  ls_strAppendChar(&buffer, '2'); break;
            case 3:  ls_strAppendChar(&buffer, '3'); break;
            case 4:  ls_strAppendChar(&buffer, '4'); break;
            case 5:  ls_strAppendChar(&buffer, '5'); break;
            case 6:  ls_strAppendChar(&buffer, '6'); break;
            case 7:  ls_strAppendChar(&buffer, '7'); break;
            case 8:  ls_strAppendChar(&buffer, '8'); break;
            case 9:  ls_strAppendChar(&buffer, '9'); break;
            case 10: ls_strAppendChar(&buffer, 'A'); break;
            case 11: ls_strAppendChar(&buffer, 'B'); break;
            case 12: ls_strAppendChar(&buffer, 'C'); break;
            case 13: ls_strAppendChar(&buffer, 'D'); break;
            case 14: ls_strAppendChar(&buffer, 'E'); break;
            case 15: ls_strAppendChar(&buffer, 'F'); break;
        }
        At++;
    }
    
    buffer.data[buffer.len] = 0;
    ls_strReverse(&buffer);
    
    ls_strAppendCStr(&Result, (char*)"0x");
    
    while(true)
    {
        if(buffer.len == 2) { break; }
        if((buffer.data[0] != '0') || (buffer.data[1] != '0'))
        { break; }
        else
        { ls_strRmSubstr(&buffer, 0, 1); }
    }
    
    string P = ls_strConcat(Result, buffer);
    ls_strNullTerminate(&P);
    
    ls_strFree(&buffer);
    ls_strFree(&Result);
    
    return P;
}

s64 ls_stoi(string s)
{
    s64 Result = ls_atoi(s.data, s.len);
    return Result;
}

f32 ls_stof(string s)
{
    f64 Result = ls_atof(s.data, s.len);
    return Result;
}

string ls_ftos(f32 x)
{
    string Result = {};
    
    char *data = ls_ftoa(x);
    u32 len = ls_len(data);
    
    Result.data = data;
    Result.len = len;
    Result.size = len;
    
    return Result;
}

//   To/From Data   //
//------------------//


//------------------//
//     Operator     //

b32 operator==(string s1, string s2)
{
    if(s1.len != s2.len) { return FALSE; }
    return ls_memcmp(s1.data, s2.data, s1.len);
}

b32 operator==(string s1, char *v)
{
    u32 len = ls_len(v);
    if(s1.len != len) { return FALSE; }
    return ls_memcmp(s1.data, v, s1.len);
}

b32 operator==(string s1, const char *v)
{
    //NOTE: Maybe shouldn't do this, but it's fine
    char *unConsted = (char *)v;
    
    u32 len = ls_len(unConsted);
    if(s1.len != len) { return FALSE; }
    return ls_memcmp(s1.data, unConsted, s1.len);
}

b32 operator==(string s, char v)
{
    if(s.len != 1) { return FALSE; }
    return (s.data[0] == v ? TRUE : FALSE);
}

b32 operator!=(string s1, string s2)
{ return (!(s1 == s2)); }

b32 operator!=(string s1, char *v)
{ return (!(s1 == v)); }

b32 ls_strIsEqualNCStr(string s1, char *s2, u32 len)
{
    if(s1.len < len) { return FALSE; }
    return ls_memcmp(s1.data, s2, len);
}

//     Operator     //
//------------------//







//VIEWS

//------------------//
//      Create      //

view ls_viewCreate(string s)
{
    view Res = {};
    
    Res.next = s.data;
    Res.len  = s.len;
    
    return Res;
}

//      Create      //
//------------------//


//------------------//
//     OperateOn    //

view ls_viewEatWhitespace(view v)
{
    char *At = v.next;
    u32 advance = 0;
    while(ls_isWhitespace(*At))
    {
        advance += 1;
        At += 1;
    }
    
    view Result = { {}, v.next + advance, v.len - advance};
    
    return Result;
}

view ls_viewNextNChars(view v, u32 n)
{
    view Result = {};
    
    Result.s = {v.next, n, n};
    Result.next = v.next + n;
    Result.len  = v.len - n;
    
    return Result;
}

view ls_viewNextDelimiter(view v, char c)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    u32 wordLen = 0;
    char *At = v.next;
    while(wordLen < v.len)
    {
        if(*At == c)
        { break; }
        
        wordLen++;
        At++;
    }
    
    Assert(wordLen <= v.len);
    
    //NOTE: We don't keep the delimiter in the word
    //      But we skip it in the .next
    u32 nextLen = wordLen + 1;
    if(wordLen == v.len)
    { nextLen = wordLen; }
    
    Result.s = {v.next, wordLen, wordLen};
    Result.next = v.next + nextLen;
    Result.len  = v.len - nextLen;
    
    return Result;
}

view ls_viewNextWord(view v)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    u32 wordLen = 0;
    char *At = v.next;
    while(wordLen < v.len)
    {
        if(ls_isWhitespace(*At))
        { break; }
        
        wordLen++;
        At++;
    }
    
    Result.s = {v.next, wordLen, wordLen};
    Result.next = v.next + wordLen;
    Result.len  = v.len - wordLen;
    
    return Result;
}

view ls_viewNextLineSkipWS(view v)
{
    view Result = {};
    
    v = ls_viewEatWhitespace(v);
    
    u32 lineLen = 0;
    u32 skipWhite = 1;
    
    char *At = v.next;
    while(lineLen < v.len)
    {
        if(*At == '\r')
        { skipWhite += 1; break; }
        if(*At == '\n')
        { break; }
        
        lineLen++;
        At++;
    }
    
    Result.s = {v.next, lineLen, lineLen};
    Result.next = v.next + lineLen + skipWhite;
    Result.len  = v.len - (lineLen + skipWhite);
    
    return Result;
}

view ls_viewNextLine(view v)
{
    view Result = {};
    
    u32 lineLen = 0;
    char *At = v.next;
    while(lineLen < v.len)
    {
        if((*At == '\r') && (*(At+1) == '\n'))
        { lineLen += 2; break; }
        if(*At == '\n') { lineLen += 1; break; }
        
        lineLen += 1;
        At++;
    }
    
    Result.s = {v.next, lineLen, lineLen};
    Result.next = v.next + lineLen;
    Result.len  = v.len - lineLen;
    
    return Result;
}

b32 ls_viewIsLineEmpty(view v)
{
    string s = v.s;
    if(s.len == 1)
    {
        if(s.data[0] == '\n') { return TRUE; }
    }
    else if(s.len == 2)
    {
        if((s.data[0] == '\r') && (s.data[1] == '\n')) { return TRUE; }
    }
    
    return FALSE;
}

//     OperateOn    //
//------------------//

#endif //IMPLEMENTATION
