package rs.ac.uns.ftn.db.jdbc.exam.ui_handler;

import java.sql.SQLException;

import rs.ac.uns.ftn.db.jdbc.exam.dao.ProjekatDAO;
import rs.ac.uns.ftn.db.jdbc.exam.dao.impl.ProjekatDAOImpl;
import rs.ac.uns.ftn.db.jdbc.exam.model.Projekat;

public class ProjekatUIHandler {
	private static final ProjekatDAO projekatDAO = new ProjekatDAOImpl();

	public void handleProjekatMenu() {	
		String answer;
		do {
			System.out.println("\nOdaberite opciju za rad sa projektima:");
			System.out.println("1 - Prikaz svih");
			System.out.println("2 - Prikaz po identifikatoru");
			System.out.println("3 - Unos jednog");
			System.out.println("4 - Unos vise");
			System.out.println("5 - Izmena po identifikatoru");
			System.out.println("6 - Brisanje po identifikatoru");
			System.out.println("X - Izlazak iz rukovanja projektima");

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
		System.out.println(Projekat.getFormattedHeader());
		try {
			for(Projekat p : projekatDAO.findAll())
			{
				System.out.println(p);
			}
		} catch (SQLException e) {
			System.out.println(e.getMessage());
		}
	}

	private void showById() {
		
	}

	private void handleSingleInsert() {

	}

	private void handleUpdate() {

	}

	private void handleDelete() {

	}

	private void handleMultipleInserts() {

	}

}
