package com.travel.model;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

public class City {
	String ccode;
	String cname;
	public City(String ccode, String cname) {
		super();
		this.ccode = ccode;
		this.cname = cname;
	}
	public String getCcode() {
		return ccode;
	}
	public void setCcode(String ccode) {
		this.ccode = ccode;
	}
	public String getCname() {
		return cname;
	}
	public void setCname(String cname) {
		this.cname = cname;
	}
	
	public static ArrayList<City> getCities (Connection conn) {
		try {
			ArrayList<City> flist = new ArrayList<City>();
			String query = "select * from city";
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);
			while(rs.next()) {
				flist.add(new City(rs.getString("ccode"), rs.getString("cname")));
			}
			rs.close();
			return flist;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}
}
