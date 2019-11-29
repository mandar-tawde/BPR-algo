package com.singlife.validateuser.service;

import java.sql.SQLIntegrityConstraintViolationException;
import java.util.HashMap;
import java.util.Map;

import org.apache.camel.Exchange;
import org.apache.camel.Message;
import org.apache.cxf.message.MessageContentsList;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.singlife.validateuser.dao.ValidateUserDao;
import com.singlife.validateuser.entity.PartyAccount;

@Service
@Transactional
public class ValidateUserService 
{

	@Autowired
	ValidateUserDao userDao;
	
	private static final Logger log = LoggerFactory.getLogger(ValidateUserService.class);

	
	public void getIsAvailableRequest(Exchange exchange) 
	{	
		
		Message in=exchange.getIn();
		PartyAccount validateUserBean = exchange.getIn().getBody(PartyAccount.class);
		
		if(validateUserBean.getAction().equals("isAvailable")) {
			Boolean status=userDao.find(validateUserBean);
			Map<String,Object>body=new HashMap<>();
			body.put("Status",status);
			in.setBody(body);
		}

		
		if(validateUserBean.getAction().equals("reserveUser")) {
			Boolean status = null;
				try {
					status = userDao.save(validateUserBean);
				} catch (SQLIntegrityConstraintViolationException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					status=false;
				}
			 
			Map<String,Object>body=new HashMap<>();
			body.put("reserved",status);
			in.setBody(body);
		}
	}
	
	
	public void getUsers(Exchange exchange) 
	{	
		System.out.println("Get users");
	}
	
	public void getUserByID(Exchange exchange) 
	{	
		
		Message in=exchange.getIn();
		MessageContentsList contentsList = (MessageContentsList) in.getBody();
		System.out.println("Get user by ID :- " + contentsList.get(0));
	}
	
	public void createUser(Exchange exchange) 
	{	
		
		Message in=exchange.getIn();
		PartyAccount validateUserBean = exchange.getIn().getBody(PartyAccount.class);
		System.out.println("Create User");
	}
	
	public void editUser(Exchange exchange) 
	{	
		
		Message in=exchange.getIn();
		MessageContentsList contentsList = (MessageContentsList) in.getBody();
		PartyAccount validateUserBean = exchange.getIn().getBody(PartyAccount.class);
		System.out.println("Edit User :- " + contentsList.get(0));
	}
	
	public void deleteUser(Exchange exchange) 
	{	
		
		Message in=exchange.getIn();
		MessageContentsList contentsList = (MessageContentsList) in.getBody();
		System.out.println("Delete user :- " + contentsList.get(0));
	}
}
