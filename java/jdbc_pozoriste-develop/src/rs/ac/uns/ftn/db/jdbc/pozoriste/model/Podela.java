package rs.ac.uns.ftn.db.jdbc.pozoriste.model;

import java.util.Date;

public class Podela {
	private int idPod;
	private double honorar;
	private Date datumd;
	private Date datump;
	private String uloga_idul;
	private int glumac_mbg;

	public Podela() {
		super();
	}

	public Podela(int idPod, double honorar, Date datumd, Date datump, String uloga_idul, int glumac_mbg) {
		super();
		this.idPod = idPod;
		this.honorar = honorar;
		this.datumd = datumd;
		this.datump = datump;
		this.uloga_idul = uloga_idul;
		this.glumac_mbg = glumac_mbg;
	}

	public int getIdPod() {
		return idPod;
	}

	public void setIdPod(int idPod) {
		this.idPod = idPod;
	}

	public double getHonorar() {
		return honorar;
	}

	public void setHonorar(double honorar) {
		this.honorar = honorar;
	}

	public Date getDatumd() {
		return datumd;
	}

	public void setDatumd(Date datumd) {
		this.datumd = datumd;
	}

	public Date getDatump() {
		return datump;
	}

	public void setDatump(Date datump) {
		this.datump = datump;
	}

	public String getUloga_idul() {
		return uloga_idul;
	}

	public void setUloga_idul(String uloga_idul) {
		this.uloga_idul = uloga_idul;
	}

	public int getGlumac_mbg() {
		return glumac_mbg;
	}

	public void setGlumac_mbg(int glumac_mbg) {
		this.glumac_mbg = glumac_mbg;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((datumd == null) ? 0 : datumd.hashCode());
		result = prime * result + ((datump == null) ? 0 : datump.hashCode());
		result = prime * result + glumac_mbg;
		long temp;
		temp = Double.doubleToLongBits(honorar);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		result = prime * result + idPod;
		result = prime * result + ((uloga_idul == null) ? 0 : uloga_idul.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Podela other = (Podela) obj;
		if (datumd == null) {
			if (other.datumd != null)
				return false;
		} else if (!datumd.equals(other.datumd))
			return false;
		if (datump == null) {
			if (other.datump != null)
				return false;
		} else if (!datump.equals(other.datump))
			return false;
		if (glumac_mbg != other.glumac_mbg)
			return false;
		if (Double.doubleToLongBits(honorar) != Double.doubleToLongBits(other.honorar))
			return false;
		if (idPod != other.idPod)
			return false;
		if (uloga_idul == null) {
			if (other.uloga_idul != null)
				return false;
		} else if (!uloga_idul.equals(other.uloga_idul))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Podela [idPod=" + idPod + ", honorar=" + honorar + ", datumd=" + datumd + ", datump=" + datump
				+ ", uloga_idul=" + uloga_idul + ", glumac_mbg=" + glumac_mbg + "]";
	}

}
