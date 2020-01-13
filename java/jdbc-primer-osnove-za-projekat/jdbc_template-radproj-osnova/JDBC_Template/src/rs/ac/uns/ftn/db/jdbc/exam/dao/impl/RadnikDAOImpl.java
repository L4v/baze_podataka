package rs.ac.uns.ftn.db.jdbc.exam.dao.impl;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import rs.ac.uns.ftn.db.jdbc.exam.connection.ConnectionHikari;
import rs.ac.uns.ftn.db.jdbc.exam.dao.RadnikDAO;
import rs.ac.uns.ftn.db.jdbc.exam.model.Radnik;

public class RadnikDAOImpl implements RadnikDAO{

	@Override
	public int count() throws SQLException {
		String query = "select count() from radnik";
		int Result = -1;
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query);
				ResultSet rs = ps.executeQuery())
		{
			if(rs.next())
			{
				Result = rs.getInt(1);
			}
		}
		return Result;
	}

	@Override
	public void delete(Radnik entity) throws SQLException {
		String query = "delete from radnik where mbr=?";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query))
		{
			ps.setInt(1, entity.getMbr());
			ps.executeUpdate();
		}
	}

	@Override
	public void deleteAll() throws SQLException {
		String query = "delete from radnik";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query);)
		{
			ps.executeUpdate();
		}
	}

	@Override
	public void deleteById(Integer id) throws SQLException {
		String query = "delete from radnik where mbr=?";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query);)
		{
			ps.setInt(1, id);
			ps.executeUpdate();
		}
	}

	@Override
	public boolean existsById(Integer id) throws SQLException {
		boolean Result = false;
		String query = "select * from radnik where mbr=?";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query);)
		{
			ps.setInt(1, id);
			try(ResultSet rs = ps.executeQuery())
			{
				Result = rs.isBeforeFirst();
			}
		}
		return Result;
	}

	@Override
	public Iterable<Radnik> findAll() throws SQLException {
		String query = "select mbr, ime, prz, sef, plt, pre, god from radnik";
		ArrayList<Radnik> Result = new ArrayList<Radnik>();
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query);
				ResultSet rs = ps.executeQuery())
		{
			if(rs.isBeforeFirst())
			{
				while(rs.next())
				{
					Radnik tmp = new Radnik(rs.getInt(1), rs.getString(2), rs.getString(3),
							rs.getInt(4), rs.getInt(5), rs.getInt(6), rs.getDate(7));
					Result.add(tmp);
				}
			}
		}
		return Result;
	}

	@Override
	public Iterable<Radnik> findAllById(Iterable<Integer> ids) throws SQLException {
		String query = "select mbr, ime, prz, sef, plt, pre, god from radnik where mbr in (";
		StringBuilder sb = new StringBuilder();
		sb.append(query);
		for(Integer id : ids)
		{
			sb.append("?,");
		}
		sb.deleteCharAt(sb.length()-1);
		sb.append(")");
		ArrayList<Radnik> Result = new ArrayList<Radnik>();
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query))
		{
			int i = 1;
			for(Integer id : ids)
			{
				ps.setInt(i++, id);
			}
			try(ResultSet rs = ps.executeQuery())
			{
				if(rs.isBeforeFirst())
				{
					while(rs.next())
					{
						Radnik tmp = new Radnik(rs.getInt(1), rs.getString(2), rs.getString(3),
							rs.getInt(4), rs.getInt(5), rs.getInt(6), rs.getDate(7));
						Result.add(tmp);
					}
				}
			}
		}
		return Result;
	}

	@Override
	public Radnik findById(Integer id) throws SQLException {
		String query = "select mbr, ime, prz, sef, plt, pre, god from radnik where mbr=?";
		Radnik Result = null;
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(query))
		{
			ps.setInt(1, id);
			try(ResultSet rs = ps.executeQuery())
			{
				if(rs.next())
				{
					Result = new Radnik(rs.getInt(1), rs.getString(2), rs.getString(3),
							rs.getInt(4), rs.getInt(5), rs.getInt(6), rs.getDate(7));
				}
			}
		}
		return Result;
	}

	@Override
	public void save(Radnik entity) throws SQLException {
		String update = "update radnik set ime=?, prz=?, sef=?, plt=?, pre=?, god=? where mbr=?";
		String insert = "insert into radnik (ime, prz, sef, plt, pre, god, mbr) values(?, ?, ?, ?, ?, ? ,?)";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement ps = c.prepareStatement(existsById(entity.getMbr()) ? update : insert))
		{
			int i = 1;
			ps.setString(i++, entity.getIme());
			ps.setString(i++, entity.getPrz());
			ps.setInt(i++, entity.getSef());
			ps.setFloat(i++, (float) entity.getPlt());
			ps.setFloat(i++, (float)entity.getPre());
			ps.setDate(i++, (Date) entity.getGod());
			ps.setInt(i++, entity.getMbr());
			
			ps.execute();
		}
	}

	@Override
	public void saveAll(Iterable<Radnik> entities) throws SQLException {
		String update = "update radnik set ime=?, prz=?, sef=?, plt=?, pre=?, god=? where mbr=?";
		String insert = "insert into radnik (ime, prz, sef, plt, pre, god, mbr) values(?, ?, ?, ?, ?, ?, ?)";
		try(Connection c = ConnectionHikari.getConnection();
				PreparedStatement psU = c.prepareStatement(update);
				PreparedStatement psI = c.prepareStatement(insert))
		{
			c.setAutoCommit(false);
			for(Radnik r : entities)
			{
				PreparedStatement ps;
				if(existsById(r.getMbr()))
				{
					ps = psU;
				}
				else
				{
					ps = psI;
				}
				int i = 1;
				ps.setString(i++, r.getIme());
				ps.setString(i++, r.getPrz());
				ps.setInt(i++, r.getSef());
				ps.setFloat(i++, (float) r.getPlt());
				ps.setFloat(i++, (float)r.getPre());
				ps.setDate(i++, (Date) r.getGod());
				ps.setInt(i++, r.getMbr());
				
				ps.execute();
				
			}
			c.commit();
		}
	}

}
