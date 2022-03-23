package com.travel.web;

import java.io.IOException;
import java.sql.Connection;
import java.sql.Time;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.travel.model.Flight;

/**
 * Servlet implementation class FlightManagerServlet
 */
@WebServlet("/addFlight")
public class FlightManagerServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		Connection conn = (Connection) request.getServletContext().getAttribute("connection");
		String fname = request.getParameter("fname");
		String halts = request.getParameter("halts");
		int discount = Integer.parseInt(request.getParameter("discount"));
		Time startTime = Time.valueOf(request.getParameter("startTime"));
		Time endTime = Time.valueOf(request.getParameter("endTime"));
		
		Flight f = new Flight (fname, discount, startTime, endTime);
		f.setHalts(halts);
		if (f.add(conn))
			response.sendRedirect("dashboard");
		else
			response.sendRedirect("error.jsp");
	}

}
