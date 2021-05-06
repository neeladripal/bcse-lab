package assignment_2;

import java.util.*;

//custom exception class
class NegativeIntegerException extends Exception {

	NegativeIntegerException (String attribute) {
		super (attribute + " must be a positive integer.\n");
	}
}

class ItemDetails {
	private float rate;
	private ArrayList <Boolean> availability;

	// constructor to initialize an item object
	ItemDetails () {
		rate = 0;
		availability = new ArrayList <Boolean>();
	}

	// method to assign item code based on name and entry order
	private String generateCode (String pref, int n) {
		String icode = pref;
		if (n < 10)
			icode = icode + "00" + n;		// add two zeroes to the count portion of the itemcode
		else if (n < 100)
			icode = icode + "0" + n;		// add one zero to the count portion of the itemcode
		else
			icode = icode + n;
		return icode;
 	}

 	// method to compute available quantity
	int computeQuantity () {
		int q = 0;
		for (boolean a: availability)
			if (a)			// if the availability of a certain item is invalid
				q++;
		return q;
	}

	// method to return rate of an item
	public float getRate () {
		return rate;
	}

	// method to set the input details of a new item
	public void setData (String pref, char mode) throws NegativeIntegerException {
		Scanner sc = new Scanner (System.in);

		if (mode == 'n') {			// if new item is being added, else stocks are added to existing item
			System.out.print ("Enter item rate: ");
			rate = sc.nextFloat ();
			if (rate < 0)
				throw new NegativeIntegerException ("Rate");
		}

		System.out.print ("Enter item quantity (>0): ");
		int quantity = sc.nextInt ();
		if (quantity < 0)
			throw new NegativeIntegerException ("Quantity");
		else
			while (quantity-- > 0) {		// generate item codes for every single piece of item added
				String icode = generateCode (pref, availability.size() + 1);
				System.out.println ("Item successfully added. Code assigned:- " + icode);
				availability.add (true);
			}
	}

	// method to display details of the item
	void showData () {
		System.out.print ("Rate: " + rate + "\t");
		System.out.println ("Quantity listed in stock: " + availability.size() + "\tQuantity available for issue: " + computeQuantity());
	}

	// method to update rate of an item
	void updateRate () throws NegativeIntegerException {
		Scanner sc = new Scanner (System.in);
		System.out.print ("Enter rate: ");
		rate = sc.nextFloat();
		if (rate < 0)
			throw new NegativeIntegerException ("Rate");
	}

	// method to update availability on issue of multiple items of same type
	float updateAvailabilityOnIssue (String pref, int qty) {
		if (qty <= computeQuantity()) {			// if issue quantity is less than available quantity
			System.out.println ("\nItems issued successfully. Item codes :-");
			int q = qty;

			// set availability status of first 'qty' available items to false
			for (int i = 0; i < availability.size() && q > 0; i++)
				if (availability.get (i)) {
					availability.set (i, false);
					System.out.print (generateCode (pref, i + 1) + " ");		// generate code to show item code of available items
					q--;
				}
			System.out.print ("\n");
			return rate * qty;			// return price of issued items
		}
		else {
			System.out.println ("Item not available in desired quantity.\n");
			return 0;					// issue not possible, so price is zero
		}
	}

	// method to update availability on return a single item
	void updateAvailabilityOnReturn (int c) {
		if (c <= availability.size() + 1) {				// if an item with this code exists
			if (availability.get (c - 1) == false) {		// if the item is issued
				availability.set (c - 1, true);				// set availability status to true
				System.out.println ("returned successfully.\n");
			}
			else
				System.out.println ("is already in stock.\n");
		}
		else
			System.out.println ("does not exist.\n");
	}
}

// custom exception class
class ItemNotFoundException extends Exception {
	ItemNotFoundException () {
		super ("Item not listed in stock.\n");
	}
}

// custom exception class
class EmptyListException extends Exception {
	EmptyListException () {
		super ("List is empty.\n");
	}
}

class ItemList {
	private Map <String, String> abbrev;		// hashmap where key: item prefix, value: item name
	private Map <String, ItemDetails> list;		// hashmap where key: item prefix, value: item details

	// constructor to initialize an item object
	ItemList () {
		abbrev = new HashMap <String, String> ();
		list = new HashMap <String, ItemDetails> ();
	}

	// method to get the input for details of a new item
	void addNewItem (String iname) {
 		String icode_pref = iname.substring (0, 3);			// extract prefix out of item code
		ItemDetails idet = new ItemDetails();
		
		try {
			if (list.containsKey(icode_pref)) {				// if list contains the item already
				Scanner sc = new Scanner (System.in);
				System.out.print ("Item already exists. Would you like to add more quantity (y/n)? ");
				char ch = sc.next().charAt(0);
				if (ch == 'y' || ch == 'Y') {
					idet = list.get (icode_pref);
					idet.setData (icode_pref, 'e');			// get data for existing item
				}
			}
			else {		// if the list does not contain the item
				idet.setData (icode_pref, 'n');
				abbrev.put (icode_pref, iname);
				list.put (icode_pref, idet);				// put the item in the list
			}
		}

		catch (NegativeIntegerException e) {
			System.out.println (e.getMessage());
			System.out.println ("Item could not be added/updated.\n");
		}
	}

	// method to display details of a particular item
	void displayItem (String icode_pref) throws ItemNotFoundException {
		if (list.containsKey(icode_pref)) {				// if list contains the item already
			System.out.println ("\nItem exists.");
			ItemDetails idet = list.get (icode_pref);	// get the details for the item
			idet.showData ();							// display the details
		}
		else
			throw new ItemNotFoundException();
	}

	// method to update rate of an item
	void updateItemRate (String icode_pref) throws ItemNotFoundException {
		if (list.containsKey(icode_pref)) {				// if list contains the item already
			System.out.println ("Item exists.");
			ItemDetails idet = list.get (icode_pref);		// get the details for the item
			try {
				idet.updateRate ();							// update the rate for the item
			}
			catch (NegativeIntegerException e) {
				System.out.println (e.getMessage());
			}
			System.out.println ("Item rate updated successfully.\n");
		}
		else
			throw new ItemNotFoundException();
	}

	// method to display the whole item list
	void displayList () throws EmptyListException {
		if (list.isEmpty())
			throw new EmptyListException();
		else {
			System.out.println ("\nList of Items -->\n");
			for (Map.Entry<String,ItemDetails> entry : list.entrySet()) {			// traverse the list of items
				System.out.println ("Item Name: " + abbrev.get(entry.getKey()));
				entry.getValue().showData();							// show details of the item
				System.out.println ("\n");
			}
		}
	}

	// method to create an issue request
	float createIssueRequest (String icode_pref) throws ItemNotFoundException, NegativeIntegerException {
		if (list.containsKey (icode_pref)) {				// if the list contains the item
			Scanner sc = new Scanner (System.in);
			ItemDetails idet = list.get (icode_pref);		// get the details for the item
			System.out.print ("Enter issue quantity (> 0): ");
			int iqty = sc.nextInt ();
			if (iqty > 0)
				return idet.updateAvailabilityOnIssue (icode_pref, iqty);		// finish the issue procedure by updating availability of issued items and add to order value
			else
				throw new NegativeIntegerException ("Quantity");
		}
		else
			throw new ItemNotFoundException();
	}

	// method to create a return request
	void createReturnRequest (String icode) throws ItemNotFoundException {
		String icode_pref = icode.substring (0, 3);			// extract prefix out of item code

		if (list.containsKey(icode_pref)) {					// if the list contains the item
			ItemDetails idet = list.get (icode_pref);
			System.out.print ("Item with code " + icode + " ");
			String icode_suf = icode.substring (3, 6);			// extract suffix out of item code
			idet.updateAvailabilityOnReturn(Integer.parseInt (icode_suf));		// get the numeric part of the item code
		}
		else
			throw new ItemNotFoundException();
	}

	// method to check how many items cost more than a given amount
	void itemsCostAbove (float amount) throws EmptyListException {
		if (list.isEmpty())
			throw new EmptyListException();
		else {
			ArrayList <String> items = new ArrayList <String> ();
			for (Map.Entry<String,ItemDetails> entry : list.entrySet())
				if (entry.getValue().getRate() > amount)
					items.add (entry.getKey());			// add item prefices to the list if cost is higher than the given amount

			if (items.isEmpty())				// if there are no items with cost above the given amount
				System.out.println ("Sorry, no items to show.");
			else {
				System.out.println ("\nItems are -->");
				for (String i: items)					// display the list produced
					System.out.print (abbrev.get(i) + "\t\t ");
			}
			System.out.print ("\n\n");
		}
	}
}

// wrapper class for tasks performed by ShopKeeper
class ShopKeeper {
	protected ItemList ilist;			// item list on which the tasks would be performed

	ShopKeeper (ItemList il) {
		ilist = il;
	}

	// method to input the name of the item
	protected String inputItemName () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("\nEnter item name: ");
		return sc.nextLine ().toUpperCase ();
	}

	// method to view details of a single item
	public void viewItem () {
		try {
			String iname = inputItemName();
 			String icode_pref = iname.substring (0, 3);		// extract prefix out of item code
 			ilist.displayItem (icode_pref);				// view the item in the list
		}
		catch (ItemNotFoundException e) {
			System.out.println (e.getMessage());
		}
	}

	// method to issue items
	public void issueItem () {
		Scanner sc = new Scanner (System.in);
		System.out.print ("Enter no of items: ");
		int n = sc.nextInt();				// number of different types of items to be issued

		float order_value = 0;

		for (int i = 1; i <= n; i++) {
			System.out.println ("\nItem " + i + " -->");
			String iname = inputItemName();
 			String icode_pref = iname.substring (0, 3);			// extract prefix out of item name
			
			try {
				order_value += ilist.createIssueRequest (icode_pref);
			}
			catch (Exception e) {
				System.out.println (e.getMessage() + "\nItem " + iname + " could not be issued.");
			}
		}

		System.out.println ("\nTotal Order Value: " + order_value + "\n");			// print the total order value
	}

	// method to return items back into the stock
	public void returnItem () {
		Scanner sc = new Scanner (System.in);
		char op = 'n';
		do {
			System.out.print ("\nEnter item code: ");
			sc.skip ("\\s*");
			String icode = sc.nextLine();
			try {
				ilist.createReturnRequest (icode);
			}
			catch (ItemNotFoundException e) {
				System.out.println (e.getMessage());
			}

			System.out.print ("Do you wish to return more (y/n) ? ");
			sc.skip ("\\s*");
			op = sc.next().charAt(0);
		} while (op == 'y' || op == 'Y');
	}

	// method to check items above a paricular price
	public void checkItemsCostAbove () {
		try {
			Scanner sc = new Scanner (System.in);
			System.out.print ("\nEnter amount: ");
			float amount = sc.nextFloat();			// amount to be used as criteria
			ilist.itemsCostAbove (amount);
		}

		catch (EmptyListException e){
			System.out.println (e.getMessage());
		}
	}
}

// wrapper class for tasks performed by a Stock Entry Operator
class StockEntryOperator extends ShopKeeper {
	StockEntryOperator (ItemList ilist) {
		super (ilist);
	}

	// method to add items into stock
	public void addItem () {
		String iname = inputItemName();
		ilist.addNewItem (iname);
	}

	// method to update rate of an existing item
	public void updateItemRate () {
		try {
			String iname = inputItemName();
	 		String icode_pref = iname.substring (0, 3);		// extract prefix out of item name
	 		ilist.updateItemRate (icode_pref);
	 	}
	 	catch (ItemNotFoundException e) {
	 		System.out.println (e.getMessage());
	 	}
	}

	// method to view the whole item list
	public void viewItemList () {
		try {
			ilist.displayList ();
		}
		catch (EmptyListException e) {
			System.out.println (e.getMessage());
		}
	}
}

class Solve {
	public static void main (String args[]) {
        ItemList ilist = new ItemList ();
        Scanner sc = new Scanner (System.in);
        ShopKeeper sk = new ShopKeeper (ilist);
        StockEntryOperator seo = new StockEntryOperator (ilist);
        char op = 'n';
        boolean seo_mode = true;
        do {
        	if (seo_mode) {
        		System.out.print ("\nSEO Main Menu -->\n1. Add Item\n2. Update rate of item\n3. Display Item list\n4. Display details of an item\n5. Issue items\n6. Return items\n7. Check items above a certain amount\n8. Switch to Shopkeeper Mode\nEnter your choice: ");
        		int ch = sc.nextInt();

	        	switch (ch) {
	        		case 1: seo.addItem(); break;
	        		case 2: seo.updateItemRate(); break;
	        		case 3: seo.viewItemList(); break;
	        		case 4: seo.viewItem(); break;
	        		case 5: seo.issueItem(); break;
	        		case 6: seo.returnItem(); break;
	        		case 7: seo.checkItemsCostAbove (); break;
	        		case 8: seo_mode = false; break;
	        		default: System.out.println ("Wrong choice.\n");
	        	}
        	}

        	else {
        		System.out.print ("\nShopKeeper Main Menu -->\n1. Display details of an item\n2. Issue items\n3. Return items\n4. Check items above a certain amount\n5. Switch to StockEntryOperator Mode\nEnter your choice: ");
	        	int ch = sc.nextInt();

	        	switch (ch) {
	        		case 1: sk.viewItem(); break;
	        		case 2: sk.issueItem(); break;
	        		case 3: sk.returnItem(); break;
	        		case 4: sk.checkItemsCostAbove(); break;
	        		case 5: seo_mode = true; break;
	        		default: System.out.println ("Wrong choice.\n");
        		}
        	}

        	System.out.print ("\nDo you want to continue (y/n) ? ");
        	op = sc.next().charAt(0);
        } while (op == 'y' || op == 'Y');
	}
}