package com.travel.model;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Time;
import java.util.ArrayList;

public class Route {
	String fname;
	String fromCity;
	Time deptTime;
	String toCity;
	Time arrTime;
	Float cost;
	String via;
	int discount;
	
	public Route(String fname, String fromCity, Time deptTime, String toCity, Time arrTime, Float cost) {
		super();
		this.fname = fname;
		this.fromCity = fromCity;
		this.deptTime = deptTime;
		this.toCity = toCity;
		this.arrTime = arrTime;
		this.cost = cost;
	}
	
	public String getFname() {
		return fname;
	}

	public void setFname(String fname) {
		this.fname = fname;
	}

	public String getFromCity() {
		return fromCity;
	}

	public void setFromCity(String fromCity) {
		this.fromCity = fromCity;
	}

	public Time getDeptTime() {
		return deptTime;
	}

	public void setDeptTime(Time deptTime) {
		this.deptTime = deptTime;
	}

	public String getToCity() {
		return toCity;
	}
	
	public void setToCity(String toCity) {
		this.toCity = toCity;
	}

	public Time getArrTime() {
		return arrTime;
	}

	public void setArrTime(Time arrTime) {
		this.arrTime = arrTime;
	}

	public Float getCost() {
		return cost;
	}

	public void setCost(Float cost) {
		this.cost = cost;
	}

	public int getDiscount() {
		return discount;
	}

	public void setDiscount(int discount) {
		this.discount = discount;
	}

	public String getVia() {
		return via;
	}

	public void setVia(String via) {
		this.via = via;
	}

	public static ArrayList<Route> getRoutes(Connection conn, String fromCity, String toCity) {
		try {
			ArrayList<Route> rlist = new ArrayList<>();
			String query = "SELECT \n"
					+ "    f1.fid,\n"
					+ "    f1.fname,\n"
					+ "    h1.ccode AS fromCity,\n"
					+ "    h1.dTime AS deptTime,\n"
					+ "    h2.ccode AS toCity,\n"
					+ "    h2.aTime AS arrTime,\n"
					+ "    h2.cost - h1.cost AS cost,\n"
					+ "    h1.seq AS fromOrder,\n"
					+ "    h2.seq AS toOrder,\n"
					+ "    f2.discount\n"
					+ "FROM\n"
					+ "    halt h1\n"
					+ "        INNER JOIN\n"
					+ "    halt h2 ON h1.ccode = ? AND h2.ccode = ?\n"
					+ "        AND h1.fid = h2.fid\n"
					+ "        AND h1.seq < h2.seq\n"
					+ "        AND h1.ccode != h2.ccode\n"
					+ "        INNER JOIN\n"
					+ "    flight f1 ON f1.fid = h1.fid\n"
					+ "        LEFT JOIN\n"
					+ "    (SELECT \n"
					+ "        fid, discount\n"
					+ "    FROM\n"
					+ "        flight\n"
					+ "    WHERE\n"
					+ "        startTime < CURTIME()\n"
					+ "            AND endTime > CURTIME()) AS f2 ON f2.fid = h1.fid;";
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setString(1, fromCity);
			stmt.setString(2, toCity);
			ResultSet rs = stmt.executeQuery();
			while(rs.next()) {
				Route r = new Route (rs.getString("fname"), rs.getString("fromCity"), rs.getTime("deptTime"), rs.getString("toCity"), rs.getTime("arrTime"), rs.getFloat("cost"));
				r.setDiscount(rs.getInt("discount"));
				if (r.discount > 0)
					r.setCost(r.cost * (100 - r.discount) / 100);
				
				query = "select ccode from halt where fid = ? and seq > ? and seq < ?;";
				stmt = conn.prepareStatement(query);
				stmt.setString(1, rs.getString("fid"));
				stmt.setString(2, rs.getString("fromOrder"));
				stmt.setString(3, rs.getString("toOrder"));
				ResultSet inrs = stmt.executeQuery();
				ArrayList<String> vialist = new ArrayList<> ();
				while (inrs.next()) {
					vialist.add(inrs.getString("ccode"));
				}
				String via = "No Legs";
				if (vialist.size() > 0)
					via = String.join(", ", vialist);
				
				r.setVia(via);
				rlist.add(r);
			}
			rs.close();
			return rlist;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}
}
