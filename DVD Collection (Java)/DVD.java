/**
 * @author David Gibson
 * This class is designed to store information about a DVD
 * 
 * Specifically, this class stores:
 * The DVD's title
 * The DVD's category
 * The DVD's runtime
 * The DVD's year of release
 * The DVD's price
 * 
 * title does not have a setter as the DVD's title is not permitted to be changed
 * 
 * This class contains two overridden methods: toString() and equals()
 */
package assg6_Gibsond18;

public class DVD {
	private String title;
	private String category;
	private String runtime;
	private String year;
	private String price;
	
	/**
	 * Constructor when given all of the appropriate information
	 * @param newTitle		Title for the new DVD object
	 * @param newCategory	Category for the new DVD object
	 * @param newRuntime	Runtime for the new DVD object
	 * @param newYear		Year of release for the new DVD object
	 * @param newPrice		Price for the new DVD object
	 */
	public DVD(String newTitle, String newCategory, String newRuntime, String newYear, String newPrice) {
		title = newTitle;
		category = newCategory;
		runtime = newRuntime;
		year = newYear;
		price = newPrice;
	}
	
	//GETTERS
	/**
	 * Fetches the DVD's title
	 * @return The DVD's title
	 */
	public String getTitle() {
		return title;
	}
	
	/**
	 * Fetches the DVD's category
	 * @return The DVD's category
	 */
	public String getCategory() {
		return category;
	}
	
	/**
	 * Fetches the DVD's runtime
	 * @return The DVD's runtime
	 */
	public String getRuntime() {
		return runtime;
	}
	
	/**
	 * Fetches the DVD's year of release
	 * @return The DVD's year of release
	 */
	public String getYear() {
		return year;
	}
	
	/**
	 * Fetches the DVD's price
	 * @return The DVD's price
	 */
	public String getPrice() {
		return price;
	}	
	
	//SETTERS
	/**
	 * Sets the DVD's category to a new value
	 * @param newCategory Value to be assigned to category
	 */
	public void setCategory(String newCategory) {
		this.category = newCategory;
	}
	
	/**
	 * Sets the DVD's runtime to a new value
	 * @param newRuntime Value to be assigned to runtime
	 */
	public void setRuntime(String newRuntime) {
		this.runtime = newRuntime;
	}
	
	/**
	 * Sets the DVD's year of release to a new value
	 * @param newYear Value to be assigned to year
	 */
	public void setYear(String newYear) {
		this.year = newYear;
	}
	
	/**
	 * Sets the DVD's price to a new value
	 * @param newPrice Value to be assigned to price
	 */
	public void setPrice(String newPrice) {
		this.price = newPrice;
	}
	
	//OVERRIDDEN METHODS
	/**
	 * Overrides the toString method to output the DVD information in the proper formatting
	 */
	@Override
	public String toString() {
		return "Title: " + this.title +"\nCategory: " + this.category + "\nRuntime: " + this.runtime + "\nYear: " + this.year + "\nPrice: $" + this.price;
	}
	
	/**
	 * Overrides the equals method to compare the titles of two DVD objects
	 */
	@Override
	public boolean equals(Object otherDVD) {
		if (otherDVD == null) {
			return false;
		}
		else if (otherDVD instanceof DVD) {
			return this.title == ((DVD) otherDVD).getTitle();
		}
		else {
			return false;
		}
	}
}
