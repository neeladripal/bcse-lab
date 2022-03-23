package com.travel.model;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Admin {
	String uname;
	String pass;
	public Admin(String uname, String pass) {
		super();
		this.uname = uname;
		this.pass = pass;
	}
	public String getUname() {
		return uname;
	}
	public void setUname(String uname) {
		this.uname = uname;
	}
	public String getPass() {
		return pass;
	}
	public void setPass(String pass) {
		this.pass = pass;
	}
	
	public boolean exists (Connection conn) {
		try {
			String query = "select * from admin where uname = ? and pass = ?";
			PreparedStatement stmt = conn.prepareStatement(query);
			stmt.setString(1, uname);
			stmt.setString(2, pass);
			ResultSet rs = stmt.executeQuery();
			if(rs.next()) {
				rs.close();
				return true;
			}
			return false;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}
}
