package problem_3;

// import the necessary packages
import java.util.*;

// class for some additional utility function on Stirngs
class StringUtilities {
	
	// method to count the occurences of a character within a string
	public static int countOccurence (String test, char ch) {
		int count = 0, i = 0;
		while (true) {
			i = test.indexOf (ch, i);
			if (i == -1)
				break;
			else {
				count++;
				i++;
			}
		}
		return count;
	}

	// method to count the occurences of a substring within a string
	public static int countOccurence (String test, String sub) {
		int count = 0, i = 0;
		while (true) {
			i = test.indexOf (sub, i);
			if (i == -1)
				break;
			else {
				count++;
				i += sub.length();
			}
		}
		return count;
	}
}

class Solve {
	public static void main (String args[]) {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter the test string: ");
		String ts = sc.nextLine ();			// take the test string as input
		char op = 'n';

		do {
			System.out.print ("\nMain Menu -->\n1. Count Occurrence of \'a\'\n2. Count Occurence of \"and\"\n3. Check if starts with \"The\"\n4. Put into array of characters\n5. Display tokens separated by space or @ or .\nEnter your choice: ");
			int ch = sc.nextInt();

			switch (ch) {
				case 1:
					System.out.println ("\nNo. of occurrences of \'a\' : " + StringUtilities.countOccurence (ts, 'a'));
					break;

				case 2:
					System.out.println ("\nNo. of occurrences of \"and\" : " + StringUtilities.countOccurence (ts, "and"));
					break;

				case 3:
					if (ts.startsWith("The"))
						System.out.println ("\nYes, string starts with \"The\"");
					else
						System.out.println ("\nNo, string does not start with \"The\"");
					break;

				case 4:
					char array[] = ts.toCharArray();					// array holds the string as character array
					
					System.out.println ("\nConverted to character array -->");
					for (int i = 0; i < array.length; i++)
						System.out.print (array[i]);
					System.out.print ("\n");
					break;

				case 5:
					String tokens[] = ts.split ("[ @.]");			// tokens is an array of tokens obtained from the string
					
					System.out.println ("\nTokens -->");
					for (int i = 0; i < tokens.length; i++)
						System.out.println (tokens[i]);
					System.out.println ("----x----");
					break;

				default:
					System.out.println ("\nWrong Choice.");
			}

			System.out.print ("\nDo you want to continue (y/n) ? ");
			sc.skip ("\\s*");
			op = sc.next().charAt(0);
		} while (op == 'y' || op == 'Y');
	}
}