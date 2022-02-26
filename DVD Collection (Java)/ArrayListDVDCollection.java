/**
 * @author David Gibson
 * 
 * This class implements the DVDCollectionInterface interface
 * It can read from and write to files
 */
package assg6_Gibsond18;

import java.io.*;
import java.util.*;

public class ArrayListDVDCollection implements DVDCollectionInterface {	
	
	private ArrayList<DVD> collectionList = new ArrayList<DVD>();	//The arraylist to be used to store the DVD collection
	private String collectionFile;									//String variable to store the name of the DVD collection file, used to save changes	
	
	/**
	 * Loads the data containing the DVD collection entries from a given file (fileName) 
	 * into the previously declared arraylist (collectionList)
	 * 
	 * Throws FileNotFoundException if the file does not exist or the file name is incorrect
	 */
	public void loadData(String fileName) throws FileNotFoundException {
		Scanner inputStream = null;
		String title;
		String category;
		String runtime;
		String year;
		String price;
		
		inputStream = new Scanner(new File(fileName));
		
		collectionFile = fileName;
		
		//This while loop operates on the assumption that the DVDCollection.txt
		//is structured as specified in the program requirements
		while (inputStream.hasNextLine()) {			
			title = inputStream.nextLine();
			category = inputStream.nextLine();
			runtime = inputStream.nextLine();
			year = inputStream.nextLine();
			price = inputStream.nextLine();
			
			collectionList.add(new DVD(title, category, runtime, year, price));
		}
		inputStream.close();
	}
	
	/**
	 * Searches the DVD collection arraylist for a DVD with the given title
	 * Returns the DVD object if it is found
	 * Returns null if it is not
	 */
	public DVD lookupEntry(String searchTitle) {		
		for (int i=0; i<collectionList.size(); i++) {
			if (searchTitle.equals(collectionList.get(i).getTitle())) {
				return collectionList.get(i);
			}
		}
		return null;
	}
	
	/**
	 * Searches the DVD collection arraylist for a DVD object with the given title
	 * If it is found, then its information is updated with the given strings
	 * If it is not found, then a new DVD object is created with the given strings
	 */
	public DVD addOrChangeDVD(String title, String category, String runtime, String year, String price) {
		for (int i=0; i<collectionList.size(); i++) {
			if (title.equals(collectionList.get(i).getTitle())) {
				collectionList.get(i).setCategory(category);
				collectionList.get(i).setRuntime(runtime);
				collectionList.get(i).setYear(year);
				collectionList.get(i).setPrice(price);
				
				return collectionList.get(i);
			}
		}
		collectionList.add(new DVD(title, category, runtime, year, price));
		return null;
	}	
	
	/**
	 * Searches the DVD collection arraylist for a DVD object with the given title
	 * If it is found, then it is copied to a temporary DVD object and removed from the arraylist
	 * The temporary DVD object is then returned
	 * If the target DVD object is not found, then this method returns null
	 */
	public DVD removeDVD(String title) {
		for (int i=0; i<collectionList.size(); i++) {
			if (title.equals(collectionList.get(i).getTitle())) {
				DVD temp = new DVD(collectionList.get(i).getTitle(), collectionList.get(i).getCategory(), collectionList.get(i).getRuntime(), collectionList.get(i).getYear(), collectionList.get(i).getPrice());
				collectionList.remove(i);
				return temp;
			}
		}
		return null;
	}	
	
	/**
	 * Searches for and returns all DVD entries belonging to the given category
	 * Returns an arraylist with all the matching DVDs
	 * If none are found, the arraylist will be size zero
	 */
	public ArrayList<DVD> getDVDsInCategory(String category) {
		ArrayList<DVD> temp = new ArrayList<DVD>();
		for (int i=0; i<collectionList.size(); i++) {
			if (category.contentEquals(collectionList.get(i).getCategory())) {
				temp.add(collectionList.get(i));
			}
		}
		return temp;
	}	
	
	/**
	 * Writes the DVD collection back to the same file it was loaded from with loadData()
	 * This effectively updates the collection file with any changes that were made during the program's use
	 * Throws an IOException if the file is invalid
	 */
	public void save() throws IOException {		
		FileWriter saveCollection = new FileWriter(collectionFile);
		for (int i=0; i<collectionList.size(); i++) {
			saveCollection.write(collectionList.get(i).getTitle() + System.lineSeparator());
			saveCollection.write(collectionList.get(i).getCategory() + System.lineSeparator());
			saveCollection.write(collectionList.get(i).getRuntime() + System.lineSeparator());
			saveCollection.write(collectionList.get(i).getYear() + System.lineSeparator());
			saveCollection.write(collectionList.get(i).getPrice() + System.lineSeparator());
		}
		saveCollection.close();
	}	
}
