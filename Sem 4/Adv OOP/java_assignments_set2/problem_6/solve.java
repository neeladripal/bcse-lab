package problem_6;

// import the necessary packages
import java.util.*;

// designing the class for a person in an Institute
abstract class Person {
	private String name;			// name
	private String phno;			// phone number
	private String emailid;			// email id
	private Address addr;			// address

	// class for address fields
	class Address {
		private int prmno;			// premise number
		private String street;		// street
		private String city;		// city
		private int pin;			// PIN
		private String state;		// state

		// setter function to set the attributes of address field
		public void setData () {
			Scanner sc = new Scanner (System.in);
			System.out.println ("\nProvide your address -->");
			System.out.print ("Premise number: ");
			prmno = sc.nextInt();
			System.out.print ("Street : ");
			sc.skip ("\\s*");
			street = sc.nextLine();
			System.out.print ("City : ");
			sc.skip ("\\s*");
			city = sc.nextLine();
			System.out.print ("PIN: ");
			sc.skip ("\\s*");
			pin = sc.nextInt();
			System.out.print ("State : ");
			sc.skip ("\\s*");
			state = sc.nextLine();
		}

		// setter function to return premise number
		public void setPremiseNo () {
			Scanner sc = new Scanner (System.in);
			System.out.print ("\nEnter your premise number: ");
			prmno = sc.nextInt();
			System.out.println ("Premise number updated.");
		}

		// setter function to return street
		public void setStreet () {
			Scanner sc = new Scanner (System.in);
			System.out.print ("\nEnter your street: ");
			street = sc.nextLine();
			System.out.println ("Street updated.");
		}

		// setter function to return city
		public void setCity () {
			Scanner sc = new Scanner (System.in);
			System.out.print ("\nEnter your city: ");
			city = sc.nextLine();
			System.out.println ("City updated.");
		}

		// setter function to return pin
		public void setPin () {
			Scanner sc = new Scanner (System.in);
			System.out.print ("Enter your PIN: ");
			pin = sc.nextInt();
			System.out.println ("PIN updated.");
		}

		// setter function to return state
		public void setState () {
			Scanner sc = new Scanner (System.in);
			System.out.print ("Enter your state : ");
			state = sc.nextLine();
			System.out.println ("State updated.");
		}

		// method to display the address
		public void showData () {
			System.out.println ("\nAddress ->");
			System.out.println ("Premise Number: " + prmno +"\nStreet: " + street + "\nCity: " + city + "\nPIN: " + pin + "\nState: " + state);
		}
	}

	// method to initialize the attributes of a person
	public void setData () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("Enter name: ");
		name = sc.nextLine ();
		System.out.print ("Enter phone number: ");
		sc.skip ("\\s*");
		phno = sc.nextLine ();
		System.out.print ("Enter email id: ");
		sc.skip ("\\s*");
		emailid = sc.nextLine ();
		addr = new Address ();
		addr.setData ();
	}

	// method to show the details of a person
	public void showData () {
		System.out.println ("\nName: " + name + "\nPhone number: " + phno + "\nEmail Id: " + emailid);
		addr.showData ();
	}

	// method to change address of a person partially
	public void changeAddress () {
		Scanner sc = new Scanner (System.in);
		System.out.println ("\nChoose what you want to change:\n1. Premise Number\t2. Street\t3. City\t4. PIN\t5. State");
		int ch = sc.nextInt ();
		switch (ch) {
			case 1: addr.setPremiseNo (); break;
			case 2: addr.setStreet (); break;
			case 3: addr.setCity (); break;
			case 4: addr.setPin (); break;
			case 5: addr.setState (); break;
			default: System.out.println ("\nWrong choice.");
		}
	}

	abstract protected String generateId (int i);			// abstract method which generates unique id for any person
}

class Student extends Person {
	private String roll;					// roll number (unique id)
	private String course;					// course of study

	// method to generate unique roll number based on number of students already registered in institute
	protected String generateId (int i) {
		return "STU" + i;
	}

	// parameterized constructor, parameter: no of students registered
	Student (int i) {
		super ();
		roll = generateId (i);
	}

	// accessor method to get the roll of a student
	public String getRoll () {
		return roll;
	}

	// setter method to set the personal details of a student
	public void setData () {
		System.out.println ("\nProvide your personal details -->");
		super.setData ();
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter course of study: ");
		course = sc.nextLine ();
	}

	// method to change the address
	public void changeAddress () {
		super.changeAddress();
	}

	// method to display personal details of a student
	public void showData () {
		System.out.println ("\nStudent details -->");
		System.out.println ("Roll number: " + roll);
		super.showData ();
		System.out.println ("\nCourse: " + course);
	}
}

class Faculty extends Person {
	String empid;			// employee id
	String dept;			// department
	String spl;				// specialisation

	// method to generate unique employee id based on number of faculty already registered in institute
	protected String generateId (int i) {
		return "FAC" + i;
	}

	// parameterized constructor, parameter: no of faculty registered
	Faculty (int i) {
		super ();
		empid = generateId (i);
	}

	// accessor method to get the employee id of a faculty
	public String getEmpId () {
		return empid;
	}

	// setter method to set the personal details of a faculty
	public void setData () {
		System.out.println ("\nProvide your personal details -->");
		super.setData ();
		Scanner sc = new Scanner (System.in);
		System.out.println ("\nEnter department: ");
		dept = sc.nextLine ();
		System.out.println ("\nEnter specialisation: ");
		spl = sc.nextLine ();
	}

	// method to change the address
	public void changeAddress () {
		super.changeAddress();
	}

	// method to display personal details of a faculty
	public void showData () {
		System.out.println ("\nFaculty details -->");
		System.out.println ("Employee Id: " + empid);
		super.showData ();
		System.out.println ("\nDepartment: " + dept + "\nSpecialisation: " + spl);
	}
}

// class to manage lists of students and faculty
class Institute {
	ArrayList <Student> slist;				// list of registered students
	ArrayList <Faculty> flist;				// list of registered faculty

	Institute () {
		slist = new ArrayList <Student> ();
		flist = new ArrayList <Faculty> ();
	}

	// method to register a student
	public void addStudent () {
		Student s = new Student (slist.size() + 1);
		s.setData ();
		slist.add (s);
		System.out.println ("\nStudent registered with roll number " + s.getRoll());
	}

	// method to register a faculty
	public void addFaculty () {
		Faculty f = new Faculty (flist.size() + 1);
		f.setData ();
		flist.add (f);
		System.out.println ("\nFaculty registered with employee id " + f.getEmpId());
	}

	// method to search for student based on roll number
	private int searchStudent (String roll) {
		for (int i = 0; i < slist.size (); i++)
			if (slist.get(i).getRoll().equals (roll))
				return i;
		return -1;		// if not found
	}

	// method to search for faculty based on employee id
	private int searchFaculty (String empid) {
		for (int i = 0; i < flist.size (); i++)
			if (flist.get(i).getEmpId().equals (empid))
				return i;
		return -1;		// if not found
	}

	// method to display the details of a student or a faculty
	public void displayPerson () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter unique id: ");
		String id = sc.nextLine ();
		int i = searchStudent (id);
		if (i == -1) {
			i = searchFaculty (id);
			if (i == -1)
				System.out.println ("\nNo student or faculty by this id exists.");
			else
				flist.get(i).showData ();
		}
		else
			slist.get(i).showData ();
	}

	// method to allow users to change address partially
	public void modifyAddress () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter unique id: ");
		String id = sc.nextLine ();
		int i = searchStudent (id);
		if (i == -1) {
			i = searchFaculty (id);
			if (i == -1)
				System.out.println ("\nNo student or faculty by this id exists.");
			else
				flist.get(i).changeAddress ();
		}
		else
			slist.get(i).changeAddress ();
	}
}

class Solve {
	public static void main (String args[]) {
		Institute i = new Institute ();
		Scanner sc = new Scanner (System.in);
		char op = 'n';
		do {
			System.out.print ("\nMain Menu -->\n1. Add Student\n2. Add Faculty\n3. Display details\n4. Change Address\nEnter your choice: ");
			int ch = sc.nextInt ();

			switch (ch) {
				case 1: i.addStudent (); break;
				case 2: i.addFaculty (); break;
				case 3: i.displayPerson (); break;
				case 4: i.modifyAddress (); break;
				default: System.out.println ("\nWrong Choice.");
			}

			System.out.print ("\nDo you want to continue (y/n) ? ");
			sc.skip ("\\s*");
			op = sc.next().charAt(0);
		} while (op == 'y' || op == 'Y');
	}
}