package problem_8;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

class Employee {
    private String emp_id;
    private String name;
    private String b_salary;
    private String grade;
    private String dept;


    public String getName(){
        return this.name;
    }

    public void setName(String name){
        if(name == null){
            throw new IllegalArgumentException();
        }
        this.name = name;
    }

    public void setId(String id){
        this.emp_id= id;
    }

    public String getId(){
        return this.emp_id;
    }

    public String getSalary(){
        return this.b_salary;
    }
    public void setSalary(String s){
        this.b_salary = s;
    }

    public String getGrade(){
        return this.grade;
    }
    public void setGrade(String c){
        this.grade = c;
    }

    public void setDept(String d){
        this.dept = d;
    }

    public String getDept(){
        return this.dept;
    }
    @Override
    public String toString(){
        return emp_id + "\t" + name + "\t" + b_salary + "\t" +  grade + "\t" + dept +  "\t\n";
    }
}



class RegistrationForm extends JFrame{



    private JLabel heading;
    private JLabel idLabel;
    private JTextField idTextField;
    private JLabel nameLabel;
    private JTextField nameTextField;
    private JLabel salaryLabel;
    private JTextField salaryTextField;
    private ButtonGroup gradeBg;
    private JLabel gradeLabel;
    private JRadioButton A_Button;
    private JRadioButton B_Button;
    private JRadioButton C_Button;
    private JLabel depLabel;
    private JList<String> depList;
    private JButton addEmp;
    private JButton Save;
    private JButton reset;
    private JTextArea tShow;
    private JTextField searchField;
    private JButton search;
    private JButton displayAllButton;
    private JLabel selDep;
    private JButton clButton;
    
    private ArrayList<Employee> empList = new ArrayList<>();

    public RegistrationForm(){
        setVisible(true);  
        setSize(1150, 800);  
        setLayout(null);  
        setResizable(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
        setTitle("EMPLOYEE REGISTRATION");  
        heading = new JLabel("ENTER THE DETAILS");   
        heading.setFont(new Font("Serif", Font.BOLD, 20));  
        
        idLabel = new JLabel("Employee ID:");
        nameLabel = new JLabel("Name:");  
        salaryLabel = new JLabel("Salary: ");   
        idTextField = new JTextField(20);  
        nameTextField = new JTextField(20);  
        salaryTextField = new JTextField(20);
        searchField = new JTextField(); 
        gradeLabel = new JLabel("Grade: ");   
        A_Button = new JRadioButton("A");
        B_Button = new JRadioButton("B");
        C_Button = new JRadioButton("C");
        gradeBg = new ButtonGroup();  
        addEmp = new JButton("Add Employee");
        clButton = new JButton("Clear Display");
        depLabel = new JLabel("Department : ");
        
        DefaultListModel<String> l1 = new DefaultListModel<>();
        l1.addElement("Accounts");
        l1.addElement("Product Management");
        l1.addElement("Engineering");
        l1.addElement("Service");
        l1.addElement("Sales");
        l1.addElement("IT");
        l1.addElement("Marketing");
        l1.addElement("Human Resources");
        
        depList = new JList<>(l1); 
        Save = new JButton("Save");  
        reset = new JButton("Clear");  
        tShow = new JTextArea();
        search = new JButton("Search");
        displayAllButton = new JButton("Display All");

       
        heading.setBounds(500, 20, 400, 30);  
        idLabel.setBounds(80, 70, 200, 30);  
        nameLabel.setBounds(80, 110, 200, 30);  
        salaryLabel.setBounds(80, 150, 200, 30); 
        gradeLabel.setBounds(80, 200, 200,30);   
        idTextField.setBounds(300, 70, 200, 30);  
        nameTextField.setBounds(300, 110, 200, 30);  
        salaryTextField.setBounds(300, 150, 200, 30);
        A_Button.setBounds(300,180,50,60);
        B_Button.setBounds(350,180,50,60);
        C_Button.setBounds(400,180,50,60);
        addEmp.setBounds(460, 550, 200, 40);
        clButton.setBounds(600, 400, 270, 30);
        
        depLabel.setBounds(80, 240, 200,30);   
        // depList.setBounds(300,240,200,130);  
        Save.setBounds(50, 450, 100, 30);  
        reset.setBounds(170, 450, 100, 30);  
        // tShow.setBounds(600,30,500,400);
        search.setBounds(650, 60, 100, 30);
        searchField.setBounds(400, 60, 200, 30);
        displayAllButton.setBounds(250, 400, 270, 30);
       

        JScrollPane scroll = new JScrollPane(tShow);
        scroll.setBounds(250,130,630,200); 
        scroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        scroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        JScrollPane scrollList = new JScrollPane();
        scrollList.setViewportView(depList);
        scrollList.setBounds(300,240,200,100);
        depList.setLayoutOrientation(JList.VERTICAL);
           
        add(scroll);
        add(addEmp);
        add(clButton);

        // add(tShow);
        add(search);
        add(searchField);
        add(displayAllButton);

        selDep = new JLabel();



        addEmp.addActionListener            (event -> toAddEmployee());
        displayAllButton.addActionListener  (event -> displayAll());
        search.addActionListener            (event -> search());
        clButton.addActionListener          (event -> clearText());

    
    }

    private boolean isEmployeeIdInList(String idStr)
    {
        boolean inList = false;

        for (Employee emp : empList)
        {
            if (emp.getId().compareToIgnoreCase(idStr) == 0)
            {
                inList = true;
            }
        }

        return inList;
    }
    private void toAddEmployee(){
        JPanel dbox = new JPanel(new GridBagLayout());
        
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.anchor = GridBagConstraints.WEST;
        constraints.insets = new Insets(10, 10, 10, 10);
    
        constraints.gridx = 0; constraints.gridy = 0;
        dbox.add(idLabel, constraints);  
        constraints.gridx = 1; constraints.gridy = 0;
        dbox.add(idTextField, constraints);  
        constraints.gridx = 0; constraints.gridy = 1;
        dbox.add(nameLabel, constraints);  
        constraints.gridx = 1; constraints.gridy = 1;
        dbox.add(nameTextField, constraints);  
        constraints.gridx = 0; constraints.gridy = 2;
        dbox.add(salaryLabel, constraints);  
        constraints.gridx = 1; constraints.gridy = 2;
        dbox.add(salaryTextField, constraints);  
        constraints.gridx = 0; constraints.gridy = 3;
        dbox.add(gradeLabel, constraints);
        constraints.gridx = 1; constraints.gridy = 3;
        dbox.add(A_Button, constraints);
        constraints.gridx = 2; constraints.gridy = 3;
        dbox.add(B_Button, constraints);
        constraints.gridx = 3; constraints.gridy = 3;
        dbox.add(C_Button, constraints);
        gradeBg.add(A_Button);
        gradeBg.add(B_Button);
        gradeBg.add(C_Button);
        constraints.gridx = 0; constraints.gridy = 6;
        dbox.add(depLabel, constraints);
    
        JScrollPane scrollList = new JScrollPane();
        scrollList.setViewportView(depList);
        scrollList.setBounds(300,240,200,100);
        depList.setLayoutOrientation(JList.VERTICAL);
        
        constraints.gridx = 1; constraints.gridy = 6;
        dbox.add(scrollList, constraints);
        dbox.setSize(800, 600);
    
        int result = JOptionPane.showConfirmDialog(null, dbox, "Enter Employee Details", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            addEmployee();
        }
    }
    private void addEmployee(){
        if(isEmployeeIdInList (idTextField.getText()) == true){
            JOptionPane.showMessageDialog(this, "Error: Employee Id already in the list.","Alert",JOptionPane.WARNING_MESSAGE);
        }else{
                Employee emp = new Employee();
                emp.setId(idTextField.getText());
                emp.setName(nameTextField.getText());
                emp.setSalary(salaryTextField.getText());

            
                if(A_Button.isSelected()){
                    emp.setGrade(A_Button.getText());                  
                }else if(B_Button.isSelected()){
                    emp.setGrade(B_Button.getText());                   
                }else{
                    emp.setGrade(C_Button.getText());
                }
                
                String data = depList.getSelectedValue();
                selDep.setText(data);
                emp.setDept(selDep.getText());
                
                empList.add(emp);

                displayAll();
                clearAll();
            

        }
    }

    private void clearAll() {
       
        idTextField.setText("");
        nameTextField.setText("");
        salaryTextField.setText("");
        selDep.setText("");
        gradeBg.clearSelection();
        depList.clearSelection();
    
    }
    private void displayAll (){
        tShow.setText ("");
        tShow.append("emp_id" + "\t" + "Name" + "\t" + "Base_Salary" + "\t" +  "Grade" + "\t" + "Department" +  "\n\n");
        for (Employee emp : empList)
        {
            tShow.append(emp+ "\n");
        }
    }

    private void search(){

        boolean inList = false;
        String st = searchField.getText();
        if(isEmployeeIdInList (searchField.getText()) == false){
            JOptionPane.showMessageDialog(this, "Error: Enter a valid id!","Alert",JOptionPane.WARNING_MESSAGE);
            searchField.setText("");
            return;
        }else{
            for (Employee emp : empList)
            {
                if (emp.getId().compareToIgnoreCase(st) == 0)
                {   
                    tShow.setText("");
                    tShow.append("emp_id" + "\t" + "Name" + "\t" + "Base_Salary" + "\t" +  "Grade" + "\t" + "Department" +  "\n\n");
                    inList = true;
                    tShow.append(emp+"\n");
                }
            }
        }

        if(inList == false){
            JOptionPane.showMessageDialog(this, "Error: Enter a valid id!","Alert",JOptionPane.WARNING_MESSAGE);
        }
    }

    private void clearText(){
        tShow.setText("");
    }
    public static void main(String[] args) throws Exception
        {
            SwingUtilities.invokeLater(new Runnable(){
                public void run(){
                    new RegistrationForm();
                }
            });
        }
}

