package com.recluit.lab.db;

import java.sql.Date;

public class Loan{
		
	String id = "";
	String rfc = "";
	Integer loanAmount = 0;
	String qualification = "";
	Date expirationDate;
	String status = "";
	
	public Loan(String id,String rfc,Integer loanAmount,String qualification,Date expirationDate,String status){
		this.id = id;
		this.rfc = rfc;
		this.loanAmount = loanAmount;
		this.qualification  = qualification;
		this.expirationDate = expirationDate;
		this.status = status;
	}
	public Loan(){
	
	}
	public void setId(String id) {
		this.id = id;
	}
	public void setRfc(String rfc) {
		this.rfc = rfc;
	}
	public void setLoanAmount(Integer loanAmount) {
		this.loanAmount = loanAmount;
	}
	public void setQualification(String qualification) {
		this.qualification = qualification;
	}
	public void setExpirationDate(Date expirationDate) {
		this.expirationDate = expirationDate;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	public String getId() {
		return id;
	}
	public String getRfc() {
		return rfc;
	}
	public Integer getLoanAmount() {
		return loanAmount;
	}
	public String getQualification() {
		return qualification;
	}
	public Date getExpirationDate() {
		return expirationDate;
	}
	public String getStatus() {
		return status;
	}
	
}
