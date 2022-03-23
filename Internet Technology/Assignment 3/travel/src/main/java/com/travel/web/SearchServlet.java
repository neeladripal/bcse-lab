package com.travel.web;

import java.io.IOException;
import java.sql.Connection;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.travel.model.Route;

/**
 * Servlet implementation class SearchServlet
 */
@WebServlet("/search")
public class SearchServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String fromCity = request.getParameter("fromCity");
		String toCity = request.getParameter("toCity");
		
		if (fromCity != toCity) {
			RequestDispatcher rd = request.getRequestDispatcher("search.jsp");
			Connection con = (Connection) request.getServletContext().getAttribute("connection");
			List<Route> rlist = Route.getRoutes(con, fromCity, toCity);
			request.setAttribute("routes", rlist);
			rd.forward(request, response);
		}
	}

}
