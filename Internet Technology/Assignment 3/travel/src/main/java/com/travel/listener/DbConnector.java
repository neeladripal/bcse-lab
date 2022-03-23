package com.travel.listener;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

/**
 * Application Lifecycle Listener implementation class DbConnector
 *
 */
@WebListener
public class DbConnector implements ServletContextListener {

    /**
     * Default constructor. 
     */
    public DbConnector() {
        // TODO Auto-generated constructor stub
    }

	/**
     * @see ServletContextListener#contextDestroyed(ServletContextEvent)
     */
    public void contextDestroyed(ServletContextEvent sce)  { 
         ServletContext sc = sce.getServletContext();
         Connection conn = (Connection) sc.getAttribute("connection");
         if (conn != null) {
        	 try {
				conn.close();
				sc.removeAttribute("connection");
			} catch (SQLException e) {
				e.printStackTrace();
			}
         }
    }

	/**
     * @see ServletContextListener#contextInitialized(ServletContextEvent)
     */
    public void contextInitialized(ServletContextEvent sce)  { 
    	ServletContext sc = sce.getServletContext();
    	String connString = sc.getInitParameter("connectionString");
    	String dbuname = sc.getInitParameter("dbuname");
    	String dbpass = sc.getInitParameter("dbpass");
    	
    	try {
    		Class.forName("com.mysql.cj.jdbc.Driver");
			Connection conn = DriverManager.getConnection(connString, dbuname, dbpass);
			sc.setAttribute("connection", conn);
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
	
}
