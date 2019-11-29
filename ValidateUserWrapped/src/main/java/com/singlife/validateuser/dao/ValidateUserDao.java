package com.singlife.validateuser.dao;

import java.sql.SQLIntegrityConstraintViolationException;

import com.singlife.validateuser.entity.PartyAccount;

public interface ValidateUserDao {

	public Boolean find(PartyAccount validateUserBean );

	public Boolean save(PartyAccount validateUserBean) throws SQLIntegrityConstraintViolationException;
	
	
}
