<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ taglib prefix="s" uri="/struts-tags" %>    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Credit Manager</title>
</head>
<body>
	<div style="border: 1px solid red;width:500px;">
	<center>
	<h1>WELCOME TO YOUR BANK</h1>
	<s:form action="resultAction" namespace="/">
	<s:textfield key="RFC" />
	<s:select label="Select a month" 
	headerKey="-1" headerValue="Select Operation"
	list="#{'1':'Display', '2':'New Loan', '3':'Clean Load', '4':'Payment'}" 
	name="ops" 
	value="-1" />
	<br/>
	<s:submit value="submit"/>
	</center>
    </s:form>
	
	</div>
</body>
</html>