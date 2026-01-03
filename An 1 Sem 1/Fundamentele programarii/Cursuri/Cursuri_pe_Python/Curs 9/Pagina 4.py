def isPalindrome(str):
    """
        verify if a string is a palindrome
        str - string
        return True if the string is a palindrome False otherwise
    """
    dict = locals()
    print(id(dict), dict)

    if len(str) == 0 or len(str) == 1:
        return True

    return str[0] == str[-1] and isPalindrome(str[1:-1])
