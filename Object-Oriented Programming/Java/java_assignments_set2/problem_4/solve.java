package problem_4;

// import the necessary packages
import java.util.*;

class NaturalNumber {
	private int value;		// integer value of the natural number

	// parameterized constructor, helps convert basic type to object
	NaturalNumber (int v) throws NotNaturalNumberException {
		if (v <= 0)
			throw new NotNaturalNumberException (v);
		value = v;
	}

	// copy constructor
	NaturalNumber (NaturalNumber nn) {
		value = nn.intValue ();
	}

	// convert object to basic type
	public int intValue () {
		return value;
	}

	// convert basic type to string
	public static String toString (int v) throws NotNaturalNumberException {
		if (v <= 0)
			throw new NotNaturalNumberException (v);
		String s = String.valueOf (v);
		return s;
	}

	// convert string to object
	public static NaturalNumber valueOf (String s) throws NotNaturalNumberException {
		int v = Integer.valueOf (s);
		if (v <= 0)
			throw new NotNaturalNumberException (v);
		return new NaturalNumber (v);
	}

	// convert object to string
	@Override
	public String toString () {
		String s = String.valueOf (value);
		return s;
	}
}

// custom exception class
class NotNaturalNumberException extends Exception {
	NotNaturalNumberException (int i) {
		super (i + " is not a natural number.");
	}
}

class Solve {
	public static void main (String args[]) {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter a Natural Number: ");
		int num = sc.nextInt ();
		try {
			if (num <= 0)
				throw new NotNaturalNumberException (num);

			NaturalNumber nn = new NaturalNumber (num);		// basic type converted to object

			System.out.println ("Natural Number Entered: " + nn);		// object converted to string

			int i = nn.intValue ();			// object converted to basic type
			i += 2;
			System.out.println ("Object converted to basic type integer and added 2 to it -> " + i);

			String s = NaturalNumber.toString (i);			// basic type to string
			s = s + "1";
			System.out.println ("Basic type converted to string and \"1\" appended to it -> " + s);

			NaturalNumber nn2 = NaturalNumber.valueOf (s);
			System.out.println ("String converted to object -> " + nn2); // object converted to string
		}
		catch (NotNaturalNumberException e) {
			System.out.println (e.getMessage ());
		}
	}
}