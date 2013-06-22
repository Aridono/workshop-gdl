package com.recluit.socket;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.io.PrintWriter;

public class Socket_con {
	public String returnRFC(){
		Socket s;
		String str ="";
		String sta ="1";
		String id = "116";
		String rfc = "34567ZXCVB";
		String name = "JUANP";
		String add = "MEXICO";
		String loan = "35000";
		String date = "30/6/2013";
		String qua = "GOOD";
		String act = "Y";
		try{
			s = new Socket ("127.0.0.1",3550);
			InputStreamReader stream = new InputStreamReader(s.getInputStream());
			BufferedReader reader =  new BufferedReader(stream);	

			PrintWriter wro = new PrintWriter(s.getOutputStream());	
			//wro.println(rfc);
			wro.println(sta + "|" + id + "|" + rfc + "|" + name + "|" + add + "|" + loan + "|" + date + "|" + qua + "|" + act);
			wro.flush();
			
			str=reader.readLine();

			reader.close();					
			wro.close();	
			
		}catch(IOException e){
			e.printStackTrace();
		}
		return str;
	}
	public static void main(String[] args){
		String val;
		String ent;
		String[] temp;
		val = new Socket_con().returnRFC();
		//~ //System.out.println(val);
		ent = "%";
		temp =val.split(ent);
		System.out.println("The rfc matches the next lines");
		for (int i = 0;i<temp.length-1;i++)
		{
			//if (temp[i].equals(temp[i+1])
				System.out.println(temp[i]);
		}	
	}
}