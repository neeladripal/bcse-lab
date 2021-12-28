 #define MAX 100

// structure for String ADT	
typedef struct {
	char* s;		// pointer to dynamically allocate character array to store the string
} String;

// function to return a null string whose maximum length is m characters
String null (int m) {
	String S;
	S.s = (char*)malloc((m + 1) * sizeof(char));	// dynamically allocate (m + 1) characters, 1 character extra for the '\0' delimeter
	S.s[0] = '\0';	// make the string a null (empty) string
	return S;
}

// function to input a string
String input () {
	char str[MAX];
	scanf(" %[^\n]s", str);	// input a string into a character array
	int len = 0;
	while (str[len] != '\0') {	// find its length
		++len;
	}
	String S = null (len);	// create a null string
	for (int i = 0; i <= len; ++i) {		// copy the input string into the null string
		S.s[i] = str[i];
	}
	return S;
}

// function to diaplay a string
void display (String S) {
	printf("%s\n", S.s);	// print the string
}

// function to return number of characters in a string
int length (String S) {
	int len = 0;
	while (S.s[len] != '\0') {		// traverse till '\0' delimeter is reached
		++len;
	}
	return len;
}

// function to compare two strings lexicographically, returns 0, -1 or 1 accordingly
int compare (String S1, String S2) {
	int len1 = length (S1) ,len2 = length (S2);		// get lengths of both the strings
	int i = 0; 
	while (i < len1 && i < len2) {				// check if current index is within the lengths of individual strings
		if (S1.s[i] == S2.s[i])					// continue to next iteration if same characters at current index 
			i++;
		else if (S1.s[i] < S2.s[i])				// the first string is lexicographically lesser
			return -1;			
		else									// the first string is lexicographically greater
			return 1;
	}

	// the index has reached the shorter string's end
	if (i == len1 && i == len2)	// if both of the string has come to their end
		return 0;				// then both must be equal
	else if (i != len1)			// if first string has a larger length
		return 1;				// first string must be lexicographically greater
	else						// if second string has a larger length
		return -1;				// first string must be lexicographically lesser
}

// function to check if given string is a null string
int isNull (String S) {
	int len = length (S);			// get length of a
	String nullS = null (len);		// create a null string of length equal to that of a
	if (compare (S, nullS) == 0)		// if equal to a null string
		return 1;
	else							// if not equal to a null string
		return 0;
}

// function to concatenate two strings
String concat (String S1, String S2) {
	int len1 = length (S1) ,len2 = length (S2);		// get lengths of both the strings
	String S = null (len1 + len2);				// create an empty string with length equal to sum of the two strings' lengths
	int i = 0, j = 0;
	while (i < len1) {
		S.s[i] = S1.s[i];	// copying a into c
		++i;
	}
	while (j < len2) {
		S.s[i] = S2.s[j];	// concating b into c
		++i;
		++j;
	}
	S.s[i] = '\0';	// set the '\0' delimeter character
	return S;
}

// function to return the substring of the given string of length j starting at index i
String substr (String S, int i, int m) {
	int len = length(S);			// get length of a
	if (i >= 0 && i < len && m >= 0 && i + m - 1 < len) {		// check the validity of the substring
		String sub = null(m);		// get a null string to store the substring
		int ind = i;
		while (ind < i + m) {
			sub.s[ind - i] = S.s[ind];		// copy the substring from string a into the null string
			++ind;
		}
		sub.s[m] = '\0';
		return sub;
	}
	else {
		String sub = null(len);
		return sub;		// returns a null string
	}
}

// free dynamically allocated string
void clear (String* S) {
	free (S -> s);
}