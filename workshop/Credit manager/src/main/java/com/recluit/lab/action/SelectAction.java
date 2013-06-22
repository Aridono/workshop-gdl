package com.recluit.lab.action;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import com.opensymphony.xwork2.ActionSupport;
import com.recluit.lab.db.DBC;
import com.recluit.lab.db.Loan;

public class SelectAction extends ActionSupport{
	 
	
	private static final long serialVersionUID = -3561538112932319256L;
	private String ops;
	
	private ArrayList<Loan> list = new ArrayList<Loan>();
	
	public ArrayList<Loan> getList() {
		return list;
	}
	public void setList(ArrayList<Loan> list) {
		this.list = list;
	} 
	public String getOperation(){
		return ops;
	}
	public  void setOps(String ops){
		this.ops =  ops;
	}
	public SelectAction(){
	}
	
	public String execute() throws Exception {
		//return SUCCESS;
		switch(ops){
		case "1":
			DBC db = new DBC();
			Connection conn = db.connectToOracle();
			Statement stmt = null;
			try{
			stmt = conn.createStatement();
			String query = " select * from system.loans";
			ResultSet rs = stmt.executeQuery(query);
				while(rs.next())
				{
						Loan e1 = new Loan(rs.getString(1),rs.getString(2),rs.getInt(3),rs.getString(4),rs.getDate(5),rs.getString(6));
						list.add(e1);
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			return "dis";
		case "2":
			return "newl";
		case "3":
			return "clo";
		case "4":
			return "pay";
		default:
			return "error";
		}
	}


}
