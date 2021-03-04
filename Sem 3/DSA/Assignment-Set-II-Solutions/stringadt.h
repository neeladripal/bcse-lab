#define MAX 100

// structure for String ADT	
typedef struct {
	char* s;		// pointer to dynamically allocate character array to store the string
} String;

// function to return a null string whose maximum length is m characters
String null (int m) {
	String a;
	a.s = (char*)malloc((m + 1) * sizeof(char));	// dynamically allocate (m + 1) characters, 1 character extra for the '\0' delimeter
	a.s[0] = '\0';	// make the string a null (empty) string
	return a;
}

// function to return number of characters in a string
int length (String a) {
	int len = 0;
	while (a.s[len] != '\0') {		// traverse till '\0' delimeter is reached
		++len;
	}
	return len;
}

// function to compare two strings lexicographically, returns 0, -1 or 1 accordingly
int compare (String a, String b) {
	int lena = length(a) ,lenb = length(b);		// get lengths of both the strings
	int i = 0; 
	while (i < lena && i < lenb) {				// check if current index is within the lengths of individual strings
		if (a.s[i] == b.s[i])					// continue to next iteration if same characters at current index 
			i++;
		else if (a.s[i] < b.s[i])				// the first string is lexicographically lesser
			return -1;			
		else									// the first string is lexicographically greater
			return 1;
	}

	// the index has reached the shorter string's end
	if (i == lena && i == lenb)	// if both of the string has come to their end
		return 0;				// then both must be equal
	else if (i != lena)			// if first string has a larger length
		return 1;				// first string must be lexicographically greater
	else						// if second string has a larger length
		return -1;				// first string must be lexicographically lesser
}

// function to check if given string is a null string
int isnull (String a) {
	int lena = length(a);			// get length of a
	String nulla = null(lena);		// create a null string of length equal to that of a
	if (compare(a, nulla) == 0)		// if equal to a null string
		return 1;
	else							// if not equal to a null string
		return 0;
}

// function to concatenate two strings
String concat (String a, String b) {
	int lena = length(a) ,lenb = length(b);		// get lengths of both the strings
	String c = null(lena + lenb);				// create an empty string with length equal to sum of the two strings' lengths
	int i = 0, j = 0;
	while (i < lena) {
		c.s[i] = a.s[i];	// copying a into c
		++i;
	}
	while (j < lenb) {
		c.s[i] = b.s[j];	// concating b into c
		++i;
		++j;
	}
	c.s[i] = '\0';	// set the '\0' delimeter character
	return c;
}

// function to return the substring of the given string of length j starting at index i
String substr(String a, int i, int j) {
	int lena = length(a);			// get length of a
	if (i >= 0 && i < lena && j >= 0 && i + j - 1 < lena) {		// check the validity of the substring
		String sub = null(j);		// get a null string to store the substring
		int ind = i;
		while (ind < i + j) {
			sub.s[ind - i] = a.s[ind];		// copy the substring from string a into the null string
			++ind;
		}
		sub.s[j] = '\0';
		return sub;
	}
	else {
		String sub = null(lena);
		return sub;		// returns a null string
	}
}

// function to input a string
String input() {
	char str[MAX];
	printf("Enter the string: \n");
	scanf(" %[^\n]s", str);	// input a string into a character array
	int lenstr = 0;
	while (str[lenstr] != '\0') {	// find its length
		++lenstr;
	}
	String a = null(lenstr);	// create a null string
	for (int i = 0; i <= lenstr; ++i) {		// copy the input string into the null string
		a.s[i] = str[i];
	}
	return a;
}

// function to diaplay a string
void display (String a) {
	printf("%s\n", a.s);	// print the string
}

// free dynamically allocated string
void clear(String * a) {
	free(a -> s);
}