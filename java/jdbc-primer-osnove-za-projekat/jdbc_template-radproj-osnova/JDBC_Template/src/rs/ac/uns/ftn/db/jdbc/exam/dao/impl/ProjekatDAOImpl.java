package rs.ac.uns.ftn.db.jdbc.exam.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import rs.ac.uns.ftn.db.jdbc.exam.connection.ConnectionHikari;
import rs.ac.uns.ftn.db.jdbc.exam.dao.ProjekatDAO;
import rs.ac.uns.ftn.db.jdbc.exam.model.Projekat;

public class ProjekatDAOImpl implements ProjekatDAO{

	@Override
	public int count() throws SQLException {
		int Result = -1;
		String query = "select count(*) from projekat";
		try(Connection connection = ConnectionHikari.getConnection();
				PreparedStatement prepSt = connection.prepareStatement(query);
				ResultSet resultSet = prepSt.executeQuery())
		{
			if(resultSet.next())
			{
				Result = resultSet.getInt(1);
			}
		}
		return Result;
	}

	@Override
	public void delete(Projekat entity) throws SQLException {
		String query = "delete from projekat where spr=?";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(query))
		{
			prepSt.setInt(1, entity.getSpr());
			prepSt.executeUpdate();
		}
	}

	@Override
	public void deleteAll() throws SQLException {
		String query = "delete from projekat";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(query);)
		{
			prepSt.executeUpdate();
		}
	}

	@Override
	public void deleteById(Integer id) throws SQLException {
		String query = "delete from projekat where spr=?";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(query);)
		{
			prepSt.setInt(1, id);
			prepSt.executeUpdate();
		}
	}

	@Override
	public boolean existsById(Integer id) throws SQLException {
		boolean Result = false;
		String query = "select * from projekat where spr=?";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(query);)
		{
			prepSt.setInt(1, id);
			try(ResultSet resultSet = prepSt.executeQuery())
			{
				Result = resultSet.isBeforeFirst();
			}
		}
		return Result;
	}

	@Override
	public Iterable<Projekat> findAll() throws SQLException {
		ArrayList<Projekat> Result = new ArrayList<Projekat>();
		String query = "select spr, ruk, nap, nar from projekat";
		
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(query);
				ResultSet resultSet = prepSt.executeQuery())
		{
			while(resultSet.next())
			{
				// NOTE(Jovan): Formira se novi projekat -> dodaje u listu
				Projekat p = new Projekat(resultSet.getInt(1), resultSet.getInt(2),
						resultSet.getString(3), resultSet.getString(4));
				Result.add(p);
			}
		}
		return Result;
	}

	@Override
	public Iterable<Projekat> findAllById(Iterable<Integer> ids) throws SQLException {
		ArrayList<Projekat> Result = new ArrayList<Projekat>();
		StringBuilder sb = new StringBuilder();
		String query = "select spr, ruk, nap, nar from projekat where spr in(";
		sb.append(query);
		for(@SuppressWarnings("unused") Integer id : ids)
		{
			sb.append("?,");
		}
		sb.deleteCharAt(sb.length()-1);
		sb.append(")");
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(query))
		{
			int i = 0;
			for(Integer id : ids)
			{
				prepSt.setInt(++i, id);
			}
				try(ResultSet resultSet = prepSt.executeQuery())
				{
					while(resultSet.next())
					{
						Projekat p = new Projekat(resultSet.getInt(1), resultSet.getInt(2),
								resultSet.getString(3), resultSet.getString(4));
						Result.add(p);
					}
				}
		}
		
		return Result;
	}

	@Override
	public Projekat findById(Integer id) throws SQLException {
		Projekat Result = null;
		String query = "select spr ruk nap nar from projekat where spr=?";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(query))
		{
			prepSt.setInt(1, id);
			try(ResultSet resultSet = prepSt.executeQuery())
			{
				Result = new Projekat(resultSet.getInt(1), resultSet.getInt(2),
						resultSet.getString(3), resultSet.getString(4));
			}
		}
		return Result;
	}

	@Override
	public void save(Projekat entity) throws SQLException {
		String insert = "insert into projekat (ruk, nap, nar, spr) values (?, ?, ? ,?)";
		String update = "update projekat set ruk=?, nap=?, nar=? where spr=?";
		int i = 1;
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepSt = c.prepareStatement(existsById(entity.getSpr()) ? update : insert))
		{
			prepSt.setInt(i++, entity.getRuk());
			prepSt.setString(i++, entity.getNap());
			prepSt.setString(i++, entity.getNar());
			prepSt.setInt(i++, entity.getSpr());
			prepSt.executeUpdate();
		}
	}

	@Override
	public void saveAll(Iterable<Projekat> entities) throws SQLException {
		String insert = "insert into projekat (ruk, nap, nar, spr) values(?, ?, ?, ?)";
		String update = "update projekat ruk=?, nap=?, nar=?, where spr=?";
		
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement prepStInsert = c.prepareStatement(insert);
				PreparedStatement prepStUpdate = c.prepareStatement(update))
		{
			c.setAutoCommit(false);
			for(Projekat p : entities)
			{
				int i = 1;
				PreparedStatement prepSt;
				if(existsById(p.getSpr()))
				{
					prepSt = prepStUpdate;
				}
				else
				{
					prepSt = prepStInsert;
				}
				
				prepSt.setInt(i++, p.getRuk());
				prepSt.setString(i++, p.getNap());
				prepSt.setString(i++, p.getNar());
				prepSt.setInt(i++, p.getSpr());
				
				prepSt.execute();
			}
			c.commit();
		}
	}

}
