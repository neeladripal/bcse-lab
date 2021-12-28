package problem_1;

// import the necessary packages
import java.util.*;

// custom exception class
class NegativeIntegerException extends Exception {
	NegativeIntegerException (String attribute) {
		super (attribute + " must be positive.");
	}
}

// custom exception class
class WithdrawalLimitExceededException extends Exception {
	WithdrawalLimitExceededException () {
		super ("Withdrawal amount exceeds balance.");
	}
}

class BankAcct {
	private String accno;				// account number
	private double balance;				// net balance
	private static float irate;			// interest rate

	// method to generate a pseudo random 6-digit account number for a bank account
	private String generateAccountNumber (int n) {
		Random rand = new Random ();
		String no = Integer.toString(100000 + rand.nextInt (100000));
		no = no + n;
		return no;
	}

	// parameterized constructor
	BankAcct (int n) {
		accno = generateAccountNumber (n);
		balance = 0.0;
	}

	// function to set interest rate for all accounts
	public static void setInterestRate (float rate) throws NegativeIntegerException {
		if (rate <= 0)
			throw new NegativeIntegerException ("Interest rate");
		else
			irate = rate;
	}

	// function to get the interest rate
	public static float getInterestRate () {
		return irate;
	}

	// function to update the balance of an account
	public void updateBalance (double amount) throws WithdrawalLimitExceededException {
		if (balance + amount < 0)
			throw new WithdrawalLimitExceededException ();
		balance = balance + amount;
	}

	// function to get the balance of an account
	public double getBalance () {
		return balance;
	}

	// function to compute the interest for an account
	public double computeInterest (int y, int m) {
		int time = y + m / 12;
		return balance * irate * time / 100;
	}
}

class Solve {
	public static void main (String args[]) {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nInitialise Interest Rate. Enter a positive value: ");
		try {
			BankAcct.setInterestRate (sc.nextFloat());
		}
		catch (NegativeIntegerException e) {
			System.out.println (e.getMessage());
		}

		if (BankAcct.getInterestRate () > 0) {
			char op = 'n';
			BankAcct acc = new BankAcct (1);
			do {
				System.out.print ("\nMenu -->\n1. Change Interest Rate\n2. Display Interest Rate\n3. Deposit Amount\n4. Withdraw Amount\n5. Display Balance\n6. Calculate Interest\nEnter your choice: ");
				sc.skip ("\\s*");
				int ch = sc.nextInt ();

				switch (ch) {
					case 1:
						System.out.print ("\nEnter new interest rate: ");
						sc.skip ("\\s*");
						try {
							BankAcct.setInterestRate (sc.nextFloat());
							System.out.println ("\nInterest Rate changed.");
						}
						catch (NegativeIntegerException e){
							System.out.println (e.getMessage ());
						}
						break;

					case 2:
						System.out.format ("\nInterest Rate :- %.2f\n", BankAcct.getInterestRate ());
						break;

					case 3:
						System.out.print ("\nEnter deposit amount: ");
						sc.skip ("\\s*");
						try {
							double am = sc.nextDouble ();
							if (am < 0)
								throw new NegativeIntegerException ("Deposit amount");
							acc.updateBalance (am);
							System.out.println ("\nAmount deposited successfully.");
						}
						catch (Exception e) {
							System.out.println (e.getMessage ());
							System.out.println ("\nTransaction failed.");
						}
						break;

					case 4:
						System.out.print ("\nEnter withdrawal amount: ");
						sc.skip ("\\s*");
						try {
							double am = sc.nextDouble ();
							if (am < 0)
								throw new NegativeIntegerException ("Withdrawal amount");
							acc.updateBalance (am * -1);
							System.out.println ("Amount withdrawn successfully.");
						}
						catch (Exception e) {
							System.out.println (e.getMessage ());
							System.out.println ("Transaction failed.");
						}
						break;

					case 5:
						System.out.format ("\nAccount Balance :- %.4f\n", acc.getBalance ());
						break;

					case 6:
						try {
							System.out.print ("\nEnter no of years: ");
							sc.skip ("\\s*");
							int y = sc.nextInt ();
							if (y < 0)
								throw new NegativeIntegerException ("No. of years");

							System.out.print ("Enter no of months: ");
							sc.skip ("\\s*");
							int m = sc.nextInt ();
							if (y < 0)
								throw new NegativeIntegerException ("No. of months");

							System.out.format ("\nInterest :- %.4f\n", acc.computeInterest(y, m));
						}
						catch (NegativeIntegerException e) {
							System.out.println (e.getMessage());
						}
						break;

					default:
						System.out.println ("\nWrong Choice.");
				}
				System.out.print ("\nDo you want to continue (y/n) ? ");
				sc.skip ("\\s*");
				op = sc.next().charAt(0);
			} while (op == 'y' || op == 'Y');
		}

		System.out.println ("Quitting Program.\n");
	}
}