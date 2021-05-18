package problem_8;

// import the necessary packages
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

// design the class for an employee
class Employee {
    private String emp_id;              // employee ID
    private String name;                // employee name
    private float salary;               // employee salary
    private char grade;                 // employee grade
    private String dept;                // employee department

    // getter method to return id of an employee
    public String getId() {
        return emp_id;
    }

    // setter method to set id of an employee
    public void setId (String id) {
        emp_id = id;
    }

    // getter method to return name of an employee
    public String getName () {
        return name;
    }

    // setter method to set name of an employee
    public void setName (String n) throws IllegalArgumentException {
        if(n == null)
            throw new IllegalArgumentException ();
        name = n;
    }

    // getter method to return salary of an employee
    public float getSalary () {
        return salary;
    }

    // setter method to set salary of an employee
    public void setSalary (float s) {
        salary = s;
    }

    // getter method to return grade of an employee
    public char getGrade () {
        return grade;
    }

    // setter method to set grade of an employee
    public void setGrade (char c) {
        grade = c;
    }

    // getter method to return department of an employee
    public String getDept () {
        return dept;
    }

    // setter method to set department of an employee
    public void setDept (String d) {
        dept = d;
    }

    @Override
    public String toString(){
        return emp_id + "\t" + name + "\t" + salary + "\t" +  grade + "\t" + dept +  "\t\n";
    }
}

// design the panel for adding an employee
class AddEmployeePanel extends JPanel {
    
    // various GUI elements
    private JLabel idLabel;
    private JTextField idTextField;
    private JLabel nameLabel;
    private JTextField nameTextField;
    private JLabel salaryLabel;
    private JTextField salaryTextField;
    private ButtonGroup gradeBg;
    private JLabel gradeLabel;
    private JRadioButton buttonA;
    private JRadioButton buttonB;
    private JRadioButton buttonC;
    private JLabel depLabel;
    private JList<String> depList;

    public AddEmployeePanel () {
        setSize (800, 600);         // set window size
        setLayout (new GridBagLayout());        // use grid bag layout

        idLabel = new JLabel ("Employee ID:");
        idTextField = new JTextField (20);
        nameLabel = new JLabel ("Name:");
        nameTextField = new JTextField (20);  
        salaryLabel = new JLabel ("Salary: "); 
        salaryTextField = new JTextField (20);
        gradeLabel = new JLabel ("Grade: ");   
        buttonA = new JRadioButton ("A");
        buttonB = new JRadioButton ("B");
        buttonC = new JRadioButton ("C");
        gradeBg = new ButtonGroup ();
        depLabel = new JLabel ("Department : ");
        String depts[] = {"Accounts", "Product Management", "Engineering", "Service", "Sales", "IT", "Marketing", "Human Resources"};
        depList = new JList<> (depts);

        GridBagConstraints constraints = new GridBagConstraints ();
        constraints.anchor = GridBagConstraints.WEST;
        constraints.insets = new Insets (10, 10, 10, 10);
    
        // add the elements to the panel using grid constraints
        constraints.gridx = 0; constraints.gridy = 0;
        add (idLabel, constraints);  
        constraints.gridx = 1; constraints.gridy = 0;
        add (idTextField, constraints);  
        constraints.gridx = 0; constraints.gridy = 1;
        add (nameLabel, constraints);  
        constraints.gridx = 1; constraints.gridy = 1;
        add (nameTextField, constraints);  
        constraints.gridx = 0; constraints.gridy = 2;
        add (salaryLabel, constraints);  
        constraints.gridx = 1; constraints.gridy = 2;
        add (salaryTextField, constraints);  
        constraints.gridx = 0; constraints.gridy = 3;
        add (gradeLabel, constraints);
        constraints.gridx = 1; constraints.gridy = 3;
        add (buttonA, constraints);
        constraints.gridx = 1; constraints.gridy = 4;
        add (buttonB, constraints);
        constraints.gridx = 1; constraints.gridy = 5;
        add (buttonC, constraints);
        gradeBg.add (buttonA);
        gradeBg.add (buttonB);
        gradeBg.add (buttonC);
        
        constraints.gridx = 0; constraints.gridy = 6;
        add (depLabel, constraints);
    
        // display list of departments in scroll pane
        JScrollPane scrollList = new JScrollPane();
        scrollList.setViewportView (depList);
        scrollList.setBounds (300,240,200,100);
        depList.setLayoutOrientation (JList.VERTICAL);
        
        constraints.gridx = 1; constraints.gridy = 6;
        add (scrollList, constraints);
    }

    // method to return details of employee to be registered
    public Employee getEmployeeDetails () {
        Employee emp = new Employee();

        emp.setId (idTextField.getText());
        emp.setName (nameTextField.getText());
        emp.setSalary (Float.parseFloat(salaryTextField.getText()));

        if (buttonA.isSelected ())
            emp.setGrade (buttonA.getText ().charAt (0));                  
        else if (buttonB.isSelected ())
            emp.setGrade (buttonB.getText ().charAt (0));                   
        else
            emp.setGrade (buttonC.getText ().charAt (0));
        
        String dept = depList.getSelectedValue();
        emp.setDept (dept);
        return emp;
    }
}

class Dashboard extends JFrame {

    // various GUI elements
    private JButton addEmpButton;
    private JTextArea listDisplay;
    private JTextField searchField;
    private JButton searchButton;
    private JButton displayAllButton;
    private JButton clearDisplayButton;
    
    // list of registered employees
    private ArrayList<Employee> empList;

    public Dashboard () {
        setVisible (true);      // make the frame visible
        setSize (1150, 800);    // set window size
        setLayout (null);       // set layout type
        setResizable (true);       // window can be resized
        setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);        // application closes upon clicking close button
        setTitle ("EMPLOYEE REGISTRATION");         // set title of window
        
        searchField = new JTextField();
        searchButton = new JButton("Search");
        listDisplay = new JTextArea();
        displayAllButton = new JButton("Display All");
        clearDisplayButton = new JButton("Clear Display");
        addEmpButton = new JButton("Add Employee");
        empList = new ArrayList<Employee> ();

        // position the GUI elements
        searchField.setBounds (400, 60, 200, 30);
        searchButton.setBounds (650, 60, 100, 30);
        listDisplay.setBounds (600,30,500,400);
        displayAllButton.setBounds (250, 400, 270, 30);
        clearDisplayButton.setBounds (600, 400, 270, 30); 
        addEmpButton.setBounds (460, 550, 200, 40);
        

        // customize the list display area
        JScrollPane scroll = new JScrollPane (listDisplay);
        scroll.setBounds (250,130,630,200); 
        scroll.setHorizontalScrollBarPolicy (JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        scroll.setVerticalScrollBarPolicy (JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        // add the various GUI elements to the frame   
        add (searchField);
        add (searchButton);
        add (scroll);
        add (displayAllButton);
        add (clearDisplayButton);
        add (addEmpButton);

        // set up the action listeners for each event
        addEmpButton.addActionListener (event -> addEmployee ());
        displayAllButton.addActionListener (event -> displayAll ());
        searchButton.addActionListener (event -> search ());
        clearDisplayButton.addActionListener (event -> clearText ());
    
    }

    // method to search an employee by id in list
    private boolean isEmployeeIdInList(String empid) {
        for (Employee emp : empList) {
            if (emp.getId().compareToIgnoreCase(empid) == 0)        // traverse the list and check for a match
                return true;
        }
        return false;
    }
   
    // method to handle employee addition
    private void addEmployee () {
        AddEmployeePanel empPanel = new AddEmployeePanel ();
        int result = JOptionPane.showConfirmDialog (this, empPanel, "Enter Employee Details", JOptionPane.OK_CANCEL_OPTION);

        if (result == JOptionPane.OK_OPTION) {
            Employee emp = empPanel.getEmployeeDetails ();          // get the employee object
            if (isEmployeeIdInList (emp.getId()) == true)
                JOptionPane.showMessageDialog(this, "Error: Employee Id already in the list.","Alert", JOptionPane.WARNING_MESSAGE);
            else {
                empList.add (emp);              // if id is unique, add to list
                displayAll ();
            }
        }
    }

    // method to display list of all registered employees
    private void displayAll () {
        listDisplay.setText ("");
        listDisplay.append("emp_id" + "\t" + "Name" + "\t" + "Base_Salary" + "\t" +  "Grade" + "\t" + "Department" +  "\n\n");
        for (Employee emp : empList) {
            listDisplay.append(emp + "\n");
        }
    }

    // method to handle search of an employee
    private void search() {
        // get the search string , here id to be searched
        String st = searchField.getText();
        if (isEmployeeIdInList (searchField.getText())) {
            // if match found, display the details
            for (Employee emp : empList) {
                if (emp.getId().compareToIgnoreCase(st) == 0) {   
                    listDisplay.setText("");
                    listDisplay.append("emp_id" + "\t" + "Name" + "\t" + "Base_Salary" + "\t" +  "Grade" + "\t" + "Department" +  "\n\n");
                    listDisplay.append(emp + "\n");
                }
            }
        }

        // if match not found, give warning
        else {
            JOptionPane.showMessageDialog(this, "Error: ID not found!", "Alert", JOptionPane.WARNING_MESSAGE);
            searchField.setText("");
        }
    }

    // method to claer list display area
    private void clearText() {
        listDisplay.setText ("");
    }

    public static void main (String[] args) throws Exception {
        SwingUtilities.invokeLater (new Runnable(){
            public void run (){
                new Dashboard ();
            }
        });
    }
}