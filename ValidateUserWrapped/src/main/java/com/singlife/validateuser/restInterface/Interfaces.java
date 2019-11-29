
/**
 * @author Jayendra
 *
 */

package com.singlife.validateuser.restInterface;
import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;

import com.singlife.validateuser.entity.PartyAccount;


@Path("/")
public interface Interfaces {

	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	@Path("/ValidateUser")
	public String ValidateUser1 (PartyAccount map);
	
	@GET
	@Produces(MediaType.APPLICATION_JSON)
	@Path("/user")
	public String getUsers (@QueryParam("name") String name, @QueryParam("lastname") String lastname);
	
	@GET
	@Produces(MediaType.APPLICATION_JSON)
	@Path("/user/{id}")
	public String getUserByID (@PathParam("id")String id);
	
	
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	@Path("/user")
	public String createUser (PartyAccount map);
	
	@PUT
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	@Path("/user/{id}")
	public String editUser (@PathParam("id")String id, PartyAccount map);
	
	@DELETE
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	@Path("/user/{id}")
	public String deleteUser (@PathParam("id")String id);
	
}
