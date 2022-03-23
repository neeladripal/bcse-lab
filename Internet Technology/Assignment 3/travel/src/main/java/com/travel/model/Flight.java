package com.travel.model;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Time;
import java.util.ArrayList;
import java.util.Arrays;

public class Flight {
	int fid;
	String fname;
	String halts;
	int discount;
	Time startTime;
	Time endTime;
	
	public Flight(String fname, int discount, Time startTime, Time endTime) {
		super();
		this.fname = fname;
		this.discount = discount;
		this.startTime = startTime;
		this.endTime = endTime;
	}
	public int getFid() {
		return fid;
	}
	public void setFid(int fid) {
		this.fid = fid;
	}
	public String getFname() {
		return fname;
	}
	public void setFname(String fname) {
		this.fname = fname;
	}
	public int getDiscount() {
		return discount;
	}
	public void setDiscount(int discount) {
		this.discount = discount;
	}
	public Time getStartTime() {
		return startTime;
	}
	public void setStartTime(Time startTime) {
		this.startTime = startTime;
	}
	public Time getEndTime() {
		return endTime;
	}
	public void setEndTime(Time endTime) {
		this.endTime = endTime;
	}
	
	public String getHalts() {
		return halts;
	}

	public void setHalts(String legs) {
		this.halts = legs;
	}

	@Override
	public String toString() {
		return "Flight [fid=" + fid + ", fname=" + fname + ", discount=" + discount + ", startTime=" + startTime
				+ ", endTime=" + endTime + ", legs=" + halts + "]";
	}
	
	public String[] parse (String hstr) {
		// ccode(startTime--endTime--cost)
		String[] res = new String[4];
		int i1 = hstr.indexOf("("), i2 = hstr.indexOf(")");
		res[0] = hstr.substring(0, i1);
		String[] rest = hstr.substring(i1 + 1, i2).split("--");
		for (int i = 1; i < 4; i++) {
			res[i] = rest[i-1];
		}
		return res;
	}
	
	public boolean add (Connection conn) {
		try {
			String query = "INSERT INTO `flight` (`fname`, `discount`, `startTime`, `endTime`) VALUES (?, ?, ?, ?);";
			PreparedStatement stmt = conn.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
			stmt.setString(1, fname);
			stmt.setInt(2, discount);
			stmt.setTime(3, startTime);
			stmt.setTime(4, endTime);
			
			stmt.execute();
			
			ResultSet rs = stmt.getGeneratedKeys();
			if (rs.next())
				setFid(rs.getInt(1));
			
			ArrayList<String> hstrlist = new ArrayList<String>(Arrays.asList(halts.split(", ")));
			int idx = 1;
			for (String hstr: hstrlist) {
				String[] hparams = parse(hstr);
				String ccode = hparams[0];
				Time aTime = Time.valueOf(hparams[1]);
				Time dTime = Time.valueOf(hparams[2]);
				float cost = Float.parseFloat(hparams[3]);
				Halt h = new Halt(fid, ccode, aTime, dTime, cost, idx);
				h.add(conn);
				idx++;
			}
			return true;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}

	public static ArrayList<Flight> getFLightsBySpecialDeal (Connection conn) {
		try {
			ArrayList<Flight> flist = new ArrayList<Flight>();
			String query = "select * from flight where startTime <= curtime() and endTime >= curtime()";
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);
			while(rs.next()) {
				int fid = rs.getInt("fid");
				Flight f = new Flight(rs.getString("fname"),rs.getInt("discount"), rs.getTime("startTime"), rs.getTime("endTime"));
				f.setFid(fid);
				flist.add(f);
			}
			rs.close();
			return flist;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public static ArrayList<Flight> getallFlights (Connection conn) {
		try {
			ArrayList<Flight> flist = new ArrayList<Flight>();
			String query = "select * from flight";
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(query);
			while(rs.next()) {
				int fid = rs.getInt("fid");
				Flight f = new Flight(rs.getString("fname"),rs.getInt("discount"), rs.getTime("startTime"), rs.getTime("endTime"));
				f.setFid(fid);
				query = "select ccode, aTime, dTime, cost from halt where fid = " + fid + " order by seq";
				Statement instmt = conn.createStatement();
				ResultSet inrs = instmt.executeQuery(query);
				ArrayList<String> hlist = new ArrayList<>();
				while (inrs.next()) {
					String ccode = inrs.getString("ccode");
					String atime = inrs.getString("aTime");
					String dtime = inrs.getString("dTime");
					String cost = inrs.getString("cost");
					hlist.add(ccode + "(" + atime + "--" + dtime + "--" + cost + ")");
				}
				String halt = "No Legs";
				if (hlist.size() > 0)
					halt = String.join(", ", hlist);
				inrs.close();
				f.setHalts(halt);
				flist.add(f);
			}
			rs.close();
			return flist;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}
}
