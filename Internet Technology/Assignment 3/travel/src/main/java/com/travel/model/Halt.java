package com.travel.model;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Time;

public class Halt {
	int hid;
	int fid;
	String ccode;
	Time aTime;
	Time dTime;
	float cost;
	int seq;
	
	public Halt(int fid, String ccode, Time aTime, Time dTime, float cost, int seq) {
		super();
		this.fid = fid;
		this.ccode = ccode;
		this.aTime = aTime;
		this.dTime = dTime;
		this.cost = cost;
		this.seq = seq;
	}
	
	public void add (Connection conn) throws SQLException {
		String query = "INSERT INTO `halt` (`fid`, `ccode`, `aTime`, `dTime`, `cost`, `seq`) VALUES (?, ?, ?, ?, ?, ?);";
		PreparedStatement stmt = conn.prepareStatement(query);
		stmt.setInt(1, fid);
		stmt.setString(2, ccode);
		stmt.setTime(3, aTime);
		stmt.setTime(4, dTime);
		stmt.setString(5, String.format("%.02f", cost));
		stmt.setInt(6, seq);
		stmt.execute();
	}
}
