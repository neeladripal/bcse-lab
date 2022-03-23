package com.travel.web;

import java.io.IOException;
import java.sql.Connection;
import java.util.List;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpFilter;

import com.travel.model.City;
import com.travel.model.Flight;

/**
 * Servlet Filter implementation class DealFilter
 */
@WebFilter("/index.jsp")
public class HomeFilter extends HttpFilter implements Filter {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	Connection conn;
    /**
     * @see HttpFilter#HttpFilter()
     */
    public HomeFilter() {
        super();
    }

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
		conn = null;
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		List<Flight> flist = Flight.getFLightsBySpecialDeal(conn);
		List<City> clist = City.getCities(conn);
		request.setAttribute("cities", clist);
		request.setAttribute("deals", flist);
		chain.doFilter(request, response);
	}

	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException {
		// TODO Auto-generated method stub
		conn = (Connection) fConfig.getServletContext().getAttribute("connection");
	}

}
