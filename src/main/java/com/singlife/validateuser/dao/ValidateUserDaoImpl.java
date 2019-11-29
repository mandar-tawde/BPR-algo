package com.singlife.validateuser.dao;

import java.sql.SQLIntegrityConstraintViolationException;
import java.util.List;

import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.criterion.Restrictions;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import com.singlife.validateuser.entity.PartyAccount;

@Repository
public class ValidateUserDaoImpl implements ValidateUserDao {

	private static final Logger log = LoggerFactory.getLogger(ValidateUserDaoImpl.class);
	
	@Autowired
	SessionFactory sessionFactory;
	
	@Override
	public Boolean find(PartyAccount validateUserBean) {
		Criteria criteria = sessionFactory.getCurrentSession().createCriteria(PartyAccount.class);
		 criteria.add(Restrictions.eq("username",validateUserBean.getUsername()));
		 List<PartyAccount> userBeanList= criteria.list();
		 if(userBeanList!=null && !userBeanList.isEmpty()) {
			 return false;
		 }else {
		return	true;
		}
	}


	@Override
	public Boolean save(PartyAccount validateUserBean) throws SQLIntegrityConstraintViolationException  {
	
		if(find(validateUserBean)) {
			
			Session session;
			try {
			session=sessionFactory.getCurrentSession();
			session.persist(validateUserBean);
			}catch (Exception e) {
			e.printStackTrace();
			
			}
			return true;

		}else {
			return false;
		}
		
	}
	
}
