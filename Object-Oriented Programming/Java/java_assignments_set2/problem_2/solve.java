package problem_2;

//import the necessary packages
import java.util.*;

// custom exception class
class NegativeDistanceException extends Exception {
	NegativeDistanceException () {
		super ("Distance must be non-negative.");
	}
}

// class for conversion of metrics from one unit to another
class Metrics {

	// method to convert distance in kilometres to distance in miles
	public static double toMile (double km) throws NegativeDistanceException {
		if (km < 0)
			throw new NegativeDistanceException ();
		double mile = km / 1.5;
		return mile;
	}

	// method to convert distance in miles to distance in kilometres
	public static double toKilometre (double mile) throws NegativeDistanceException {
		if (mile < 0)
			throw new NegativeDistanceException ();
		double km = mile * 1.5;
		return km;
	}
}

class Solve {
	public static void main (String args[]) {
		Scanner sc = new Scanner (System.in);
		char op = 'n';
		
		do {
			System.out.print ("\n1. Kilometre to Mile\n2. Mile to Kilometre\nEnter your choice: ");
			int ch = sc.nextInt();
			try {
				switch (ch) {
					case 1:
						System.out.print ("\nEnter distance in kilometres: ");
						sc.skip ("\\s*");
						double km = sc.nextDouble ();
						System.out.format ("Distance in miles :- %.4f\n", Metrics.toMile (km));
						break;

					case 2:
						System.out.print ("\nEnter distance in miles: ");
						sc.skip ("\\s*");
						double mile = sc.nextDouble ();
						System.out.format ("Distance in kilometres :- %.4f\n", Metrics.toKilometre (mile));
						break;
				}
			}
			catch (Exception e) {
				System.out.println (e.getMessage ());
			}

			System.out.print ("\nDo you want to continue (y/n) ? ");
			sc.skip ("\\s*");
			op = sc.next().charAt(0);
		} while (op == 'y' || op == 'Y');
	}
}