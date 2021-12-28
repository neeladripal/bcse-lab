# import regex module
import re

# class to carry out several formatting operations on a piece of text
class TextFormatter:

    def __init__(self, str) -> None:
        self.text = str     # the string to work on

    def removeSpecialChars(self) -> None:
        """Replace any character which is not alphanumeric or space or dot with empty character"""
        self.text = re.sub('[^a-zA-z0-9\n\.\s]', '', self.text)

    def removeSingleChars(self) -> None:
        """Replace a pattern of [space,any character except spa,space] with [space,space]"""
        self.text = re.sub('\s[^\n\s]\s', '  ', self.text)

    def removeMultipleSpaces(self) -> None:
        """Remove multiple spaces in the text with a single space"""
        self.text = re.sub('\s+', ' ', self.text)

    def toLowerCase(self) -> None:
        """Convert the text to lower case"""
        self.text = self.text.lower()

    def expandContractions(self) -> None:
        """Convert the words into literal form from their contracted form (e.g., Couldn’t -> Could not)"""
        expansions = (("'m"," am"), ("'s"," is"), ("t's", "t us"), ("'re"," are"), ("n't"," not"))
        for c, u in expansions:
            self.text = re.sub(c, u, self.text, flags=re.MULTILINE)

    def __str__ (self) -> str:
        return self.text
    
    @classmethod
    def operationMenu(cls) -> int:
        """Menu of operations which can be performed on the text"""
        print("Text File Operations -->")
        print("1. Remove special characters.")
        print("2. Remove all single characters.")
        print("3. Remove multiple spaces.")
        print("4. Convert the text into lower case.")
        print("5. Expand the contractions in the text.")
        op = int(input("Enter option: "))
        return op

filename = input("\nEnter file name: ") 

try:
    with open(filename, 'r') as file:
        content = TextFormatter(file.read())        # store content of file
# in case the file does not exist on the path
except FileNotFoundError as e:
    print (e, "\nExiting..")
    exit (0)

ch = 'y'

while ch == 'y' or ch == 'Y' :
    ch == 'n'
    print ("\nBefore editing, text :- ", content, "\n")
    option = TextFormatter.operationMenu()
    if option == 1:
        content.removeSpecialChars()
    elif option == 2:
        content.removeSingleChars()
    elif option == 3:
        content.removeMultipleSpaces()
    elif option == 4:
        content.toLowerCase()
    elif option == 5: 
        content.expandContractions()
    else:
        print("Invalid option.")
    print ("\nAfter editing, text :- ", content)
    ch = input("\nDo you want to edit more? (y/n) ")

with open(filename, 'w') as file:
    file.write(str(content))            # write content back to the file