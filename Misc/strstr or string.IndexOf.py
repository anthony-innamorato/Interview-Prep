def strStr(haystack, needle):
    #haystack is of type string
    #needle is of type string
    #return -1 if string is not subString, 0 if len(needle) == 0,
    #starting index if subString is within
    if len(needle) == 0:
        return 0
    if len(needle) > len(haystack):
        return -1
    for i in range(len(haystack)):
        if haystack[i] == needle[0]:
            if len(needle) > len(haystack) - i:
                break
            sameSoFar = True
            j = 1
            while sameSoFar and j < len(needle):
                if haystack[i+j] != needle[j]:
                    sameSoFar = False
                j += 1
            if sameSoFar and j == len(needle):
                return i
    return -1

print(strStr("hello", "llo"))
