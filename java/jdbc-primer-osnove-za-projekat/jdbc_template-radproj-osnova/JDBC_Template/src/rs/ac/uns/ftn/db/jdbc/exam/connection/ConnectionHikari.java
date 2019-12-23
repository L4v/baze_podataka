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
		// NOTE(Jovan): Povezivanje na lokalnu bp
		// sa odgovarajucim podacima
		conf.setJdbcUrl(ConnectionParams.LOCAL_CONNECTIO_STRING);
		conf.setUsername(ConnectionParams.USERNAME);
		conf.setPassword(ConnectionParams.PASSWORD);
		conf.setMaximumPoolSize(10);
		conf.addDataSourceProperty("cachePrepStmts", "true");
		conf.addDataSourceProperty("prepStmtCacheSize", "250");
		conf.addDataSourceProperty("", "");
		ds = new HikariDataSource(conf);
	};
	
	// NOTE(Jovan): Override praznog konstruktora
	private ConnectionHikari()
	{}
	
	// NOTE(Jovan): Getter za konekciju
	public static Connection getConnection() throws SQLException
	{
		return ds.getConnection();
	}
}
