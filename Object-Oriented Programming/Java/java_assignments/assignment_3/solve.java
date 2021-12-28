package assignment_3;

// import necessary packages to use built-in classes as required
import java.util.*;

// class for a custom stack for storing characters
class Stack {
	LinkedList <Character> list = new LinkedList <Character> ();

	Stack () {
		list.addFirst ('$');	// push the sentinel, here $
	}

	// method to check if the stack is empty
	boolean empty () {
		if (list.getFirst ().charValue () == '$')
			return true;
		else
			return false;
	}

	// method to push an element to the top of stack
	void push (char c) {
		list.addFirst (c);
	}

	// method to pop the element at the top of stack
	char pop () {
		return list.removeFirst ().charValue ();
	}

	// method to return the element at the top of stack
	char top () {
		return list.getFirst ().charValue ();
	}
}

class Solve {
	public static void main (String args[]) {
		Scanner sc = new Scanner (System.in);
		System.out.print ("Enter text stream: ");
		String txt = sc.nextLine();		// take input

		// use hashmap to give odd values to sentinel and opening braces and even values to closing braces
		Map <Character, Integer> hm = new HashMap <Character, Integer> ();
			hm.put ('(', 1);
			hm.put (')', 2);
			hm.put ('{', 3);
			hm.put ('}', 4);
			hm.put ('[', 5);
			hm.put (']', 6);
			hm.put ('$', 7);

		Stack s = new Stack ();		// initialise a Stack object

		boolean flag = true;

		try {
			for (char cStream: txt.toCharArray ()) {
			char cStack = s.top ();

			// if character at the top of stack is sentinel or both characters are opening braces
			if (hm.get(cStack) % 2 == 1 && hm.get (cStream) % 2 == 1)
				s.push (cStream);
			
			// if character at the top of stack is an opening parenthesis and that at the text stream is a closing one
			else if (hm.get (cStream) - hm.get (cStack) == 1)
				s.pop ();

			// if character at the top of stack is a closing parenthesis and that at the text stream is an opening one
			else {
				flag = false;
				break;
			}
		}

		if (txt.isEmpty())
			System.out.println ("Empty string.\n");

		else if (flag && s.empty())
			System.out.println ("Parentheses properly balanced.");
		else
			System.out.println ("Parentheses not properly balanced.");
		}

		catch (Exception e) {		// in case of wrong input
			System.out.println ("Invalid expression.\n");
		}
	}
}