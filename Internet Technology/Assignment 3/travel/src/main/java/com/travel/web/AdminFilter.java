package com.travel.web;

import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet Filter implementation class AdminFilter
 */
@WebFilter("/dashboard")
public class AdminFilter extends HttpFilter implements Filter {
	private static final long serialVersionUID = 1L;

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		String uname = (String) ((HttpServletRequest) request).getSession().getAttribute("uname");
		if (uname != null) {
			request.setAttribute("username", uname);
			chain.doFilter(request, response);
		}
		else {
			((HttpServletResponse) response).sendRedirect("admin.jsp");
		}
	}
}
