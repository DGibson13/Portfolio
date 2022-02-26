/**
 * @author David Gibson
 * 
 * This is an interface file for the ArrayListDVDCollection class
 * It lists all the public methods for that class and describes what they do
 */
package assg6_Gibsond18;

import java.io.*;
import java.util.ArrayList;

public interface DVDCollectionInterface {
	public void loadData(String fileName) throws FileNotFoundException;
	//Loads the data containing the DVD collection entries from a given file
	//Precondition: fileName file should contain the desired DVD entries
	//Postcondition: DVD collection entries are loaded into an arraylist
	//Exception: throws FileNotFoundException if the file does not exist or the file name is incorrect
	
	public DVD lookupEntry(String searchTitle);
	//Searches for a DVD
	//Precondition: title is the name of the DVD being searched for
	//Postcondition: returns the DVD entry if found, or null if it is not found
	
	public DVD addOrChangeDVD(String title, String category, String runtime, String year, String price);
	//Adds a new DVD entry or changes an existing DVD entry
	//Precondition: string inputs are used to write or overwrite information in a DVD entry
	//Postcondition: if the DVD entry already exists, it is updated with the new information and the entry is returned
	//if it does not exist, then a new entry is created with the given information and null is returned
	
	public DVD removeDVD(String title);
	//Searches for an removes an entry from the DVD collection
	//Precondition: title is the entry being searched for
	//Postcondition: If the DVD entry is found, it removes the entry and returns it
	//if it is not found, returns null
	
	public ArrayList<DVD> getDVDsInCategory(String category);
	//Searches for and returns all DVD entries belonging to given category
	//Precondition: category is the specified search parameter
	//Postcondition: returns an arraylist with all the DVDs belonging to the given category
	//if none are found, the arraylist will be size zero
	
	public void save() throws IOException;
	//Writes the DVD collection back to the same file it was loaded from with loadData()
	//Precondition: none
	//Postcondition: the DVD collection file is updated with any changes made during the use of the program
	//Exception: throws IOException if the file is invalid
}
