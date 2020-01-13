package rs.ac.uns.ftn.db.jdbc.exam.connection;

import java.sql.Connection;
import java.sql.SQLException;

import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

public class ConnectionHikari {
	private static HikariConfig conf = new HikariConfig();
	private static HikariDataSource ds;
	
	static
	{
		conf.setJdbcUrl(ConnectionParams.LOCAL_CONNECTION_STRING);
		conf.setUsername(ConnectionParams.USERNAME);
		conf.setPassword(ConnectionParams.PASSWORD);
		conf.addDataSourceProperty("cachePrepStmts", "true");
		conf.addDataSourceProperty("prepStmtCacheSize", "256");
		conf.addDataSourceProperty("", "");
		ds = new HikariDataSource(conf);
	}
	
	private ConnectionHikari() {}
	
	public static Connection getConnection() throws SQLException
	{
		return ds.getConnection();
	}
	
}
