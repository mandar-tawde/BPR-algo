package com.singlife.validateuser.entity;


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Transient;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;


@Entity
@Table(name="partyAccount")
@JsonIgnoreProperties(ignoreUnknown = true)
public class PartyAccount {

	@Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private long id;
	
	@Column(name = "userName" ,unique=true,nullable = false)
	private	String username;

	@Transient
	private	String action;
	
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	
	public String getAction() {
		return action;
	}
	public void setAction(String action) {
		this.action = action;
	}
	
	@Override
	public String toString() {
		return "ValidateUserBean [username=" + username + ", action=" + action + "]";
	}

}
