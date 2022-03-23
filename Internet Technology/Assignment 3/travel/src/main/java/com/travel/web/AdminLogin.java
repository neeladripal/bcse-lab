package com.travel.web;

import java.io.IOException;
import java.sql.Connection;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.travel.model.Admin;

/**
 * Servlet implementation class AdminLogin
 */
@WebServlet("/adminLogin")
public class AdminLogin extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		Connection conn = (Connection) request.getServletContext().getAttribute("connection");
		String uname = request.getParameter("uname");
		String pass = request.getParameter("pass");
		
		Admin a = new Admin (uname, pass);
		if (a.exists(conn)) {
			request.getSession().setAttribute("uname", uname);
			response.sendRedirect("dashboard");
		} else {
			response.sendRedirect("admin.jsp");
		}
	}

}
