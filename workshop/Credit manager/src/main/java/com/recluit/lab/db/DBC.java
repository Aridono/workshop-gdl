package com.recluit.lab.db;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBC {
	private Connection conn;
	public  Connection connectToOracle(){
		try{
			Class.forName("oracle.jdbc.OracleDriver"); // LOAD DRIVER INTO MEMORY
			conn = DriverManager.getConnection("jdbc:oracle:thin:@127.0.0.1:1521:ariel","system","naru61");
			System.out.println("connection established: " + conn);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return conn;
	}
}