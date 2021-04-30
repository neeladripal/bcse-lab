package problem_5;

//import the necessary packages
import java.util.*;

// class for managing information related to a particular customer
class Customer {
	private String id;								// customer id
	private String name;							// name
	private String phno;							// phone number
	private double curr_loan_amt;					// current loan amount
	static double credit_limit = 1000.0;			// credit limit for normal customers
	static double credit_limit_pr = 2000.0;			// credit limit for privileged customers
	private boolean privileged;						// true: privileged customer, false: normal customer

	// method to generate id for a new customer
	private String generateId (int i) {
		if (privileged)
			return "PC" + i;
		else
			return "NC" + i;
	}

	// parameterized constructor
	Customer (int i, boolean pr) {
		privileged = pr;
		id = generateId (i);
		name = "NA";
		phno = "NA";
		curr_loan_amt = 0.0;
	}

	// getter function to return the customer id
	public String getCustId () {
		return id;
	}

	// setter function to change name
	public void setName () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter name: ");
		name = sc.nextLine ();
	}

	// setter function to change phone number
	public void setPhoneNumber () throws InvalidPhoneNumberException {
		Scanner sc = new Scanner (System.in);
		System.out.print ("Enter 10-digit phone number: ");
		sc.skip ("\\s*");
		String temp = sc.nextLine ();

		if (temp.length() != 10 || temp.replaceAll ("[0-9]", ""). length() != 0)			// validate phone number
			throw new InvalidPhoneNumberException ();
		phno = temp;
	}

	// method to calculate amount of loan one can seek
	public double amountOfLoanSeekable () {
		if (privileged)
			return credit_limit_pr - curr_loan_amt;
		else
			return credit_limit - curr_loan_amt;
	}

	// method to apply request for a loan
	public void applyForLoan () throws LoanOutOfLimitException, CreditLimitReachedException {
		Scanner sc = new Scanner (System.in);
		double loan_seek = amountOfLoanSeekable();
		if (loan_seek < 0.1) {
			System.out.println ("\nYou have reached credit limit.");
			throw new CreditLimitReachedException ();
		}
			System.out.println ("\nAmount of Loan seekable :- " + loan_seek);

		System.out.print ("\nEnter loan amount: ");
		double amount = sc.nextDouble ();
		
		if (curr_loan_amt + amount <= (privileged ? credit_limit_pr: credit_limit))		// check credit limit
			curr_loan_amt = curr_loan_amt + amount;
		else
			throw new LoanOutOfLimitException ();
	}

	// method to show the information of a customer
	public void showInfo () {
		System.out.println ("\nCustomer ID : " + id);
		System.out.println ("Name : " + name + " \tPhone Number : " + phno);
		System.out.println ("Current Loan Amount : " + curr_loan_amt);
		System.out.println ("Credit Limit : " + (privileged ? credit_limit_pr : credit_limit));
		System.out.println ("You can seek a loan upto " + amountOfLoanSeekable());
	}
}

// custom exception class
class InvalidPhoneNumberException extends Exception {
	InvalidPhoneNumberException () {
		super ("Invalid Phone Number.");
	}
}

// custom exception class
class CreditLimitReachedException extends Exception {
	CreditLimitReachedException () {
		super ("Credit limit reached. You cannot take a loan.");
	}
}

// custom exception class
class LoanOutOfLimitException extends Exception {
	LoanOutOfLimitException () {
		super ("Credit limit exceeded.");
	}
}

class Bank {
	private ArrayList <Customer> list;		// list of registered customers

	// constructor to create a new list
	Bank () {
		list = new ArrayList <Customer> ();
	}

	// method to add a new customer to the list
	public void addCustomer () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter your preference: Normal Customer (press 1), Privileged Customer (press 2) -> ");
		int ch = sc.nextInt ();

		// if entered option is wrong
		if (ch != 1 && ch != 2) {
			System.out.println ("This kind of behaviour shows a low cultural manifestation. Please try again and be careful while choosing the option. Account creation failed.");
			return;
		}

		Customer c = new Customer (list.size() + 1, (ch == 2) ? true : false);		// create a new Customer object
		try {
			c.setName ();				// set name
			c.setPhoneNumber ();		// set phone number
			list.add (c);				// add the Customer to the list
			System.out.println ("\nAccount created successfully.");
			c.showInfo ();				// show information entered
		}
		catch (Exception e) {
			System.out.println (e.getMessage());
			System.out.println ("\nAccount not created.");
		}
	}

	// method to search for an existing Customer by ID
	private int searchCustomer () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter Customer id: ");
		String id = sc.nextLine();

		for (int i = 0; i < list.size(); i++)		// traverse the list and find for a match in the ID
			if (id.equals (list.get(i).getCustId()))
				return i;
		return -1;			// if customer does not exist
	}

	// method to display the details of a Customer
	public void displayCustomerDetails () {
		int i = searchCustomer ();
		if (i == -1)
			System.out.println ("\nCustomer does not exist.");
		else {
			System.out.println ("\nCustomer Details -->");
			list.get(i).showInfo();
		}
	}

	// method to change name and phone number of a customer
	public void changeBioData () {
		int i = searchCustomer ();
		if (i == -1)
			System.out.println ("\nCustomer does not exist.");
		else {
			try {
				list.get(i).setName ();
				list.get(i).setPhoneNumber ();
				System.out.println ("\nChanges applied successfully.");
			}
			catch (Exception e) {
				System.out.println (e.getMessage());
				System.out.println ("Phone Number could not be changed.\n");
			}
		}
	}

	// method to apply for a loan
	public void applyForLoan () {
		int i = searchCustomer ();
		if (i == -1)
			System.out.println ("\nCustomer does not exist.");
		else {
			try {
				list.get(i).applyForLoan();
				System.out.println ("\nLoan sanctioned.");
			}
			catch (Exception e) {
				System.out.println (e.getMessage());
				System.out.println ("\nLoan not sanctioned.");
			}
		}
	}

	// method to display amount of loan an existing customer can seek
	public void checkLoanAmountSeekable () {
		int i = searchCustomer ();
		if (i == -1)
			System.out.println ("\nCustomer does not exist.");
		else
			System.out.println ("You can seek a loan upto " + list.get(i).amountOfLoanSeekable());
	}
}

class Solve {
	public static void main (String args[]) {
		Bank b = new Bank ();
		Scanner sc = new Scanner (System.in);
		char op = 'n';
		do {
			System.out.print ("\nMain Menu -->\n1. Add Customer\n2. Display Customer Details\n3. Change Customer Bio Data\n4. Check for Loan Amount Seekable\n5. Apply for a loan\nEnter your choice: ");
			int ch = sc.nextInt ();

			switch (ch) {
				case 1: b.addCustomer (); break;
				case 2: b.displayCustomerDetails (); break;
				case 3: b.changeBioData (); break;
				case 4: b.checkLoanAmountSeekable (); break;
				case 5: b.applyForLoan (); break;
				default: System.out.println ("\nWrong Choice.");
			}

			System.out.print ("\nDo you want to continue (y/n) ? ");
			sc.skip ("\\s*");
			op = sc.next().charAt(0);
		} while (op == 'y' || op == 'Y');
	}
}