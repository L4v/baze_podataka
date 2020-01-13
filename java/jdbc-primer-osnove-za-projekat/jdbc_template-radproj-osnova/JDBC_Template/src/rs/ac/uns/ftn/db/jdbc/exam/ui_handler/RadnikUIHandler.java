package rs.ac.uns.ftn.db.jdbc.exam.ui_handler;

import java.sql.SQLException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

import rs.ac.uns.ftn.db.jdbc.exam.dao.RadnikDAO;
import rs.ac.uns.ftn.db.jdbc.exam.dao.impl.RadnikDAOImpl;
import rs.ac.uns.ftn.db.jdbc.exam.model.Radnik;

public class RadnikUIHandler {
	// private static final RadnikDAO radnikDAO = new RadnikDAOImpl();
	private static final RadnikDAO radnikDAO = new RadnikDAOImpl();
	public void handleRadnikMenu() {
		String answer;
		do {
			System.out.println("\nOdaberite opciju za rad sa radnicima:");
			System.out.println("1 - Prikaz svih");
			System.out.println("2 - Prikaz po identifikatoru");
			System.out.println("3 - Unos jednog");
			System.out.println("4 - Unos vise");
			System.out.println("5 - Izmena po identifikatoru");
			System.out.println("6 - Brisanje po identifikatoru");
			System.out.println("X - Izlazak iz rukovanja radnicima");

			answer = MainUIHandler.sc.nextLine();

			switch (answer) {
			case "1":
				showAll();
				break;
			case "2":
				showById();
				break;
			case "3":
				handleSingleInsert();
				break;
			case "4":
				handleMultipleInserts();
				break;
			case "5":
				handleUpdate();
				break;
			case "6":
				handleDelete();
				break;

			}

		} while (!answer.equalsIgnoreCase("X"));
	}

	private void showAll() {
		System.out.println(Radnik.getFormattedHeader());
		try {
			for(Radnik r : radnikDAO.findAll())
			{
				System.out.println(r);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			System.out.println(e.getMessage());
		}
	}

	private void showById() {
		Scanner s = new Scanner(System.in);
		int id = s.nextInt();
		try {
			System.out.println(Radnik.getFormattedHeader());
			System.out.println(radnikDAO.findById(id));
		} catch (SQLException e) {
			System.out.println(e.getMessage());
		}
		s.close();
	}

	private void handleSingleInsert() {
		Scanner s = new Scanner(System.in);
		System.out.println("MBR:");
		int id = Integer.parseInt(s.nextLine());
		System.out.println("IME:");
		String ime = s.nextLine();
		System.out.println("Prezime:");
		String prz = s.nextLine();
		System.out.println("Sef:");
		int sef = Integer.parseInt(s.nextLine());
		System.out.println("Plata:");
		int plt = Integer.parseInt(s.nextLine());
		System.out.println("Premija:");
		int pre = Integer.parseInt(s.nextLine());
		System.out.println("Godiste:");
		DateFormat date = new SimpleDateFormat("dd.MM.yyyy");
		try {
			Date god = date.parse(s.nextLine());
			Radnik tmp = new Radnik(id, ime, prz, sef, plt, pre, god);
			radnikDAO.save(tmp);
		} catch (ParseException e) {
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		s.close();
	}

	private void handleUpdate() {

	}

	private void handleDelete() {

	}

	private void handleMultipleInserts() {

	}

}
