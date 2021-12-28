package assignment_5;

// import necessary packages to use necessary classes
import java.util.*;
import java.io.*;

// designing a class similar to a Pair to hold line number and word number
class LineWord {
	private int lineno;
	private int wordno;

	LineWord (int lno, int wno) {
		lineno = lno;
		wordno = wno;
	}

	@Override
	public String toString () {
		return lineno + "-" + wordno;
	}
}

class Glossary {
	private String fn;		// name of the file
	private Map <String, ArrayList<LineWord>> index;	// treemap to keep the words in alphabetic order

	Glossary (String fname) {
		fn = new String (fname);
		fn = "./assignment_5/" + fn;	// change filename depending on directory structure
		index = new TreeMap <String, ArrayList<LineWord>> ();
	}

	// method to create the glossary
	public void createGlossary () {
		try {
			File f = new File (fn);			// create a file object
			Scanner sc = new Scanner (f);
			int line_count = 1;
			while (sc.hasNext()) {
				StringTokenizer st = new StringTokenizer (sc.nextLine());		// tokenize the current line
				int word_count = 1;
				while (st.hasMoreTokens()) {
					// trim the current token of any non-word character and convert into lower case to ignore case-sensitivity
					String s = st.nextToken().replaceAll("[\\W]", "").toLowerCase();
					if (s.length() == 0)		// ignore empty strings
						continue;

					if(index.containsKey(s))		// treemap already conatins the word
                        index.get(s).add(new LineWord(line_count, word_count));
                    else { 			                // treemap doesn't contain the word
                        ArrayList<LineWord> list = new ArrayList<LineWord>();
                        list.add(new LineWord (line_count, word_count));
                        index.put(s, list);			// create a new arraylist and put in the map against the current token as key
                    }
                    word_count++;
				}
				line_count++;
			}
		}
		catch (IOException e) {
			System.out.println (e.getMessage());		// if file is not found
		}
	}

	// method to print the glossary
	public void printGlossary () {
		System.out.println ("Glossary for file " + fn + " ----------->\n\nFormat: Word [Line Number-Word Number]\n");
        for(Map.Entry <String, ArrayList<LineWord>> entry : index.entrySet()) {		// iterate over the entries in map
        	System.out.print (entry.getKey() + "\t[");			// print the word
            for(LineWord lw : entry.getValue())
               	System.out.print (lw + ", ");					// print positions of the word
            System.out.println ("\b\b]");
        }
        System.out.println ("--------------------X--------------------");
	}
}

class Solve {
	public static void main (String []args) {
		Scanner sc = new Scanner (System.in);
		System.out.print ("Enter file name: ");
		String filename = sc.nextLine();

		Glossary g = new Glossary (filename);
		g.createGlossary();
		g.printGlossary();
	}
}