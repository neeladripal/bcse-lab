package assignment_6;

// import the necessary packages
import java.sql.Timestamp;
import java.time.Instant;
import java.util.*;

// class designed to store observations of patients over time
class TestResults {
	private Timestamp ts;
	private int weight;
	private float bp;
	private float temp;

	// method to input information regarding tests on a patient and record them
	public void setData () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter weight: ");
		weight = sc.nextInt ();

		System.out.print ("Enter blood pressure: ");
		bp = sc.nextFloat ();

		System.out.print ("Enter temperature: ");
		temp = sc.nextFloat ();

		ts = Timestamp.from(Instant.now());
		System.out.println ("Patient data recorded successfully at " + ts +"\n");
	}

	// method to display test results
	public void showData () {
		System.out.println ("\nTimestamp:- " + ts);
		System.out.println ("Weight: " + weight + "\tBlood pressure: " + bp + "\tTemperature: " + temp);
	}
}

// class designed to store details of patients
class Patient {
	private String name;			// name of patient
	private int age;				// age of patient
	private ArrayList <TestResults> tr_list;			// list of observations
	private boolean assn_stat;			// doctor assigned status

	Patient () {
		assn_stat = false;			// denotes doctor not assigned
		tr_list = new ArrayList <TestResults> ();
	}

	// method to return assign status
	public boolean getAssignStatus () {
		return assn_stat;
	}

	// method to set assign status
	public void setAssignStatus (boolean a) {
		assn_stat = a;
	}

	// method to return name of patient
	public String getName () {
		return name;
	}

	// method to receive patient details
	public void setData () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter patient name: ");
		name = sc.nextLine ();

		System.out.print ("Enter age: ");
		age = sc.nextInt ();
	}

	// method to show patient details
	public void showData () {
		System.out.println ("Name : " + name + "\tAge: "+ age);
	}

	// method to record observations from a test on the patient
	public void recordTestData () {
		System.out.println ("\nPatient Info -->");
		showData ();
		TestResults tr = new TestResults ();
		tr.setData();		// record test data
		tr_list.add (tr);		// add to the list
	}

	// method to show the list of test results
	public void showTestData () {
		if (tr_list.isEmpty())
			System.out.println ("No observations recorded.\n");
		else {
			System.out.println ("\nTest Results -->");
			for (TestResults tr: tr_list)		// traverse the list
				tr.showData ();					// show test data
			System.out.println ("---------------X---------------\n");
		}
	}
}

class Doctor {
	private String name;		// name of doctor
	private String qual;		// qualification of doctor

	// method to return name of doctor
	public String getName () {
		return name;
	}

	// method to recieve details of doctor
	public void setData () {
		Scanner sc = new Scanner (System.in);

		System.out.print ("\nEnter doctor name: ");
		name = sc.nextLine ();

		System.out.print ("Enter qualification: ");
		qual = sc.nextLine ();
	}

	// method to display details of a doctor
	public void showData () {
		System.out.println ("Name : " + name + "\tQualification: "+ qual + "\n");
	}
}

class Hospital {
	Map <String, Patient> plist;			// list of patients
	Map <String, Doctor> dlist;				// list of doctors
	Map <String, ArrayList<String>> assign;			// map -- key: doctorID, value: list of patient IDs
	String last_pid;				// ID of last registered patient
	String last_did;				// ID of last registered doctor

	Hospital () {
		plist = new HashMap <String, Patient> ();
		dlist = new HashMap <String, Doctor> ();
		assign = new HashMap <String, ArrayList<String>> ();
		last_pid = "PAT000";			// ID of a registered patient begins at PAT001
		last_did = "DOC000";			// ID of a registered doctor begins at DOC001
	}

	// method to get the next ID for registration
	private String getNextId (String s) {
		int k = Integer.parseInt(s.substring (3,6));
		k++;
		s = s.substring (0,3);
		if (k < 10)
			s = s + "00" + k;
		else if (k < 100)
			s = s + "0" + k;
		else
			s = s + k;
		return s;
	}

	// method to add a patient to the list
	void addPatient () {
		Patient p = new Patient ();
		p.setData ();							// input patient details
		String pid = getNextId (last_pid);		// compute next id
		plist.put (pid, p);						// add patient to list
		last_pid = pid;							// update last id
		System.out.println ("Patient registered successfully. Assigned ID:- " + pid);
	}

	// method to add a doctor to the list
	void addDoctor () {
		Doctor d = new Doctor ();
		d.setData ();							// input doctor details
		String did = getNextId (last_did);		// compute next id
		dlist.put (did, d);						// add doctor to list
		last_did = did;							// update last id
		assign.put (did, new ArrayList<String> ());
		System.out.println ("Doctor registered successfully. Assigned ID:- " + did);
	}

	// method to find the doctor ID, given patient ID
	private String searchDoctorOfPatient (String pid) {
		for (Map.Entry<String,ArrayList<String>> entry : assign.entrySet()) {
			for (String s: entry.getValue())
				if (s.equals (pid))
					return entry.getKey();
		}
		return null;		// ID not found, i.e, patient not assigned to any doctor
	}

	// method to display details of a patient, given the patient ID
	void displayPatient () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter Patient ID: ");
		String pid = sc.nextLine ();			// input the patient ID

		if (plist.containsKey(pid)) {			// if the patient is registered
			System.out.println ("\nPatient ID :- " + pid);
			Patient p = plist.get(pid);			// fetch the details from the list
			p.showData();
			if (p.getAssignStatus()) {			// if doctor is assigned
				String did = searchDoctorOfPatient(pid);
				System.out.println ("Doctor assigned :- " + dlist.get(did).getName());
			}
			else
				System.out.println ("Doctor not assigned.");
			p.showTestData();					// show test results of the patient, if recorded any
		}
		else
			System.out.println ("Sorry, patient not registered.\n");
	}

	// method to display details of a doctor, given the doctor ID
	void displayDoctor () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter Doctor ID: ");
		String did = sc.nextLine ();			// input the doctor ID

		if (dlist.containsKey(did)) {			// if the doctor is registered
			System.out.println ("\nDoctor ID :- " + did);
			dlist.get(did).showData();			// fetch the details from the list and display
		}
		else
			System.out.println ("Sorry, doctor not registered.\n");
	}

	// method to assign a patient to a doctor
	void assignPatientToDoctor () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter Patient ID: ");
		String pid = sc.nextLine ();			// input the patient ID

		if (plist.containsKey(pid)) {			// if the patient is registered
			System.out.print ("Enter Doctor ID: ");
			String did = sc.nextLine ();		// input the doctor ID

			if (dlist.containsKey(did)) {		// if the doctor is registered
				String old_did = searchDoctorOfPatient (pid);
				if (old_did != null) {			// if the patient is already assigned to a doctor
					System.out.println ("Patient was previously assigned to " + dlist.get(old_did).getName() + " [ID: " + old_did + "].");
					assign.get (old_did).remove (pid);			// unmap the patient ID from the previous doctor ID
				}
				assign.get (did).add (pid);			// map the patient ID to the desired doctor ID
				plist.get (pid).setAssignStatus (true);

				System.out.println ("Patient " + plist.get (pid).getName () + " [ID: " + pid + "] now assigned to " + dlist.get(did).getName() + " [ID: " + did + "].\n");
			}
			else
				System.out.println ("Sorry, doctor not registered.\n");
		}
		else
			System.out.println ("Sorry, patient not registered.\n");
	}

	// method to record obseravtions for a patient
	void recordObservationsOfPatient () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("Enter Patient ID: ");
		String pid = sc.nextLine ();		// input the patient ID

		if (plist.containsKey(pid)) {		// if the patient is registered
			plist.get (pid).recordTestData ();
		}
		else
			System.out.println ("Sorry, patient not registered.\n");
	}

	// method to display patient list assigned to a doctor
	void displayPatientListAssignedToDoctor () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter Doctor ID: ");
		String did = sc.nextLine ();			// input the doctor ID

		if (dlist.containsKey(did)) {			// if the doctor is registered
			System.out.println ("\nDoctor ID :- " + did + "\tName :- " + dlist.get(did).getName());
			ArrayList <String> pid_list = assign.get(did);			// get the patient list form the assign map
			
			if (pid_list.isEmpty())				// if patient list is empty
				System.out.println ("No patients assigned.\n");
			else {
				System.out.println ("\nPatients assigned [count: " + pid_list.size() + "] -->\n");
				for (String pid: assign.get(did)) {				// traverse the patient list
					System.out.println ("Patient ID :- " + pid);
					plist.get(pid).showData ();
				}
				System.out.println ("---------------X---------------\n");
			}
		}
		else
			System.out.println ("Sorry, doctor not registered.\n");
	}

	// method to display list of all patients registered in the hospital
	void displayPatientList () {
		if (plist.isEmpty())			// if the list is empty
			System.out.println ("\nRegistered Patient list is empty.\n");
		else {
			System.out.println ("\nPatient List [count: " + plist.size() + "] -->");
			for (Map.Entry<String,Patient> entry : plist.entrySet()) {		// traverse the list
				System.out.println ("Patient ID :- " + entry.getKey());
				entry.getValue ().showData();			// display patient details
			}
			System.out.println ("---------------X---------------\n");
		}
	}

	// method to display list of all doctors registered in the hospital
	void displayDoctorList () {
		if (dlist.isEmpty())			// if the list is empty
			System.out.println ("\nRegistered Doctor list is empty.\n");
		else {
			System.out.println ("\nDoctor List [count: " + dlist.size() + "] -->\n");
			for (Map.Entry<String,Doctor> entry : dlist.entrySet()) {		// traverse the list
				System.out.println ("Doctor ID :- " + entry.getKey());
				entry.getValue ().showData();			// display doctor details
			}
			System.out.println ("---------------X---------------\n");
		}
	}

	// method to deregister a patient
	void removePatient () {
		Scanner sc = new Scanner (System.in);

		// if list is empty
		if (plist.isEmpty()) {
			System.out.println ("\nRegistered Patient list is empty.\n");
			return;
		}
		
		System.out.print ("\nEnter Patient ID: ");
		String pid = sc.nextLine ();		// input the patient ID

		if (plist.containsKey(pid)) {		// if the patient is registered
			String did = searchDoctorOfPatient (pid);
			if (did != null)				// if the patient was assigned to any doctor
				assign.get (did).remove(pid);			// remove from the patient list assigned to that doctor
				
			System.out.println ("Patient " + plist.get (pid).getName () + " [ID: " + pid + "] removed successfully.\n");
			plist.remove (pid);				// remove the patient from patient list
		}
		else
			System.out.println ("Sorry, patient not registered.\n");
	}
}

class Solve {
	public static void main (String args[]) {
        Scanner sc = new Scanner (System.in);
        Hospital H = new Hospital ();
        char op = 'n';
        do {
        	System.out.print ("\nMain Menu -->\n1. Register Patient\n2. Register Doctor\n3. Display Patient by ID\n4. Display Doctor by ID\n5. Assign Patient to a Doctor\n6. Record Observations for a patient\n7. View Patient List\n8. View Doctor List\n9. View Patient List allocated to a Doctor\n10. Remove a Patient\nEnter your choice: ");
        	int ch = sc.nextInt();

        	switch (ch) {
        		case 1: H.addPatient(); break;
        		case 2: H.addDoctor(); break;
        		case 3: H.displayPatient(); break;
        		case 4: H.displayDoctor(); break;
        		case 5: H.assignPatientToDoctor(); break;
        		case 6: H.recordObservationsOfPatient(); break;
        		case 7: H.displayPatientList(); break;
        		case 8: H.displayDoctorList (); break;
        		case 9: H.displayPatientListAssignedToDoctor(); break;
        		case 10: H.removePatient (); break;
        		default: System.out.println ("Wrong choice.\n");
        	}

        	System.out.print ("Do you want to continue (y/n) ? ");
        	op = sc.next().charAt(0);
        } while (op == 'y' || op == 'Y');
	}
}