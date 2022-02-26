/**
 * @author David Gibson
 * This code is designed to be used with the DVD class, the ArrayListDVDCollection class, and the DVDCollectionInterface interface
 * 
 * Users will directly interact with this program to access the features present in the other classes including:
 * Reading from a file
 * Writing to a file
 * Search an arraylist
 * Editing an arraylist
 */
package assg6_Gibsond18;

import java.io.*;
import java.util.*;

public class DVDApplication {
	//Keeps track of whether changes were made to the collection list
	//Kept outside of main so that it can be used in the addDVD and editDVD methods (explanation line 68)
	private static boolean changes = false;		
	
	/**
	 * Main method
	 * Creates an arraylist from a file
	 * Contains menu loop that can interact with an arraylist and write to a file
	 */
	public static void main(String[] args) {
		boolean exit = false;
		//boolean changes = false;
		String userString;
		int menuChoice;		
		DVD userDVD;	
		ArrayList<DVD> catSearch = new ArrayList<DVD>();
		
		Scanner kbd = new Scanner(System.in);
		
		System.out.println("Loading DVD collection...");
		ArrayListDVDCollection collection = new ArrayListDVDCollection();
		try {
			collection.loadData("DVDCollection.txt");
		}
		catch (FileNotFoundException e){
			System.out.println("Error opening the DVD Collection file");
			e.printStackTrace();
			System.exit(1);
		}
		
		
		//Main menu loop
		while(!exit) {
			System.out.println("Please select an option");
			System.out.println("1: Add new DVD entry");
			System.out.println("2: Change existing DVD entry");
			System.out.println("3: Look up DVD entry");
			System.out.println("4: Display DVDs by category");
			System.out.println("5: Remove DVD entry");
			System.out.println("6: Save data");
			System.out.println("7: Exit");
			
			//Guards against non-integer inputs
			while (!kbd.hasNextInt()) {
				System.out.println("Menu choices are integers only.");
				kbd.nextLine();
			}			
			menuChoice = kbd.nextInt();
						
			kbd.nextLine(); //Cleans up the leftover new line after using nextInt() so that future inputs will work as intended
			
			//Adding and editing were made into separate methods to make the menu code easier to read
			//Add new
			if (menuChoice == 1) {
				addDVD(collection, kbd);				
			}
			
			//Change existing
			else if (menuChoice == 2) {
				editDVD(collection, kbd);
			}
			
			//Lookup
			else if (menuChoice == 3) {
				
				System.out.println("What is the title of the DVD you want to find?");
				userString = kbd.nextLine();
				System.out.println(collection.lookupEntry(userString));
				
			}
			
			//Display category
			else if (menuChoice == 4) {				
				System.out.println("What is the category you want to search for?");
				userString = kbd.nextLine();
				catSearch = collection.getDVDsInCategory(userString);
				if (catSearch.size() == 0) {
					System.out.println("There are no DVDs in that category");
				}
				else {
					for (int i=0; i<catSearch.size(); i++) {
						System.out.println(catSearch.get(i).getTitle());
					}
				}
			}
			
			//Remove entry
			else if (menuChoice == 5) {
				System.out.println("What is the title of the DVD you want to remove?");
				userString = kbd.nextLine();
				userDVD = collection.removeDVD(userString);
				if (userDVD == null) {
					System.out.println("That DVD is not in the collection");
				}
				else {
					System.out.println("This DVD has been removed from the collection");
					System.out.println(userDVD.toString());
				}
			}
			
			//Save data
			else if (menuChoice == 6) {
				try {
					collection.save();
				}
				catch (IOException e){
					System.out.println("An error occurred when saving");
					e.printStackTrace();
					System.exit(1);
				}
			}
			
			//Exit
			else if (menuChoice == 7) {
				exit = true;
			}
		}//End of main menu loop
		
		//Saves if changes were made
		if (changes) {
			try {
				collection.save();
			}
			catch (IOException e){
				System.out.println("An error occurred when saving");
				e.printStackTrace();
				System.exit(1);
			}
		}
		
		kbd.close();
	} //End of main()
	
	/**
	 * Adds a new DVD entry to the collection arraylist using appropriate inputs from the user
	 * @param collection	Receives the ArrayListDVDCollection from main() so that it can interact with the main arraylist
	 * @param kbd			Receives a Scanner from main() to take user inputs
	 */
	public static void addDVD(ArrayListDVDCollection collection, Scanner kbd) {
		String userString;
		String title;
		String category;
		String runtime;
		String year;
		String price;
		
		System.out.println("What is the title of the DVD you would like to add?");
		userString = kbd.nextLine();
		if (collection.lookupEntry(userString) == null) {
			title = userString;
			System.out.println("Please enter the category of the DVD");
			category = kbd.nextLine();
			System.out.println("Please enter the runtime of the DVD");
			runtime = kbd.nextLine();
			System.out.println("Please enter the DVD's year of release");
			year = kbd.nextLine();
			System.out.println("Please enter the price of the DVD");
			price = kbd.nextLine();
			
			changes = true;
			collection.addOrChangeDVD(title, category, runtime, year, price);			
			
		}
		else {
			System.out.println("That DVD is already in the collection.");
		}
	}//End of addDVD
	
	/**
	 * Edits the DVD collection arraylist using the appropriate inputs from the user
	 * It contains a submenu loop so that users can continue editing different info fields for the DVD
	 * @param collection	Receives the ArrayListDVDCollection from main() so that it can interact with the main arraylist
	 * @param kbd			Receives a Scanner from main() to take user inputs
	 */
	public static void editDVD(ArrayListDVDCollection collection, Scanner kbd) {
		String userString;
		int menuChoice;
		DVD userDVD;		
		
		System.out.println("What movie are you searching for?");
		userString = kbd.nextLine();
		if (collection.lookupEntry(userString) != null) {			
			userDVD = collection.lookupEntry(userString);
			String newInfo;
			String title = userDVD.getTitle();
			String category = userDVD.getCategory();
			String runtime = userDVD.getRuntime();
			String year = userDVD.getYear();
			String price = userDVD.getPrice();
			
			System.out.println("Item found");
			
			do {				
				System.out.println("What field would you like to edit?");
				System.out.println("1: Title: " + title);
				System.out.println("2: Category: " + category);
				System.out.println("3: Runtime: " + runtime);
				System.out.println("4: Year of Release: " + year);
				System.out.println("5: Price: " + price);
				System.out.println("0: Return to main menu");
				
				//Guards against non-integer inputs
				while (!kbd.hasNextInt()) {
					System.out.println("Menu choices are integers only.");
					kbd.nextLine();
				}			
				menuChoice = kbd.nextInt();				
				
				kbd.nextLine(); //Cleans up the leftover new line after using nextInt() so that future inputs will work as intended
				
				if (menuChoice == 1) {
					System.out.println("Titles cannot be changed");
				}
				else if (menuChoice == 2) {
					System.out.println("What would you like to change the category to?");
					newInfo = kbd.nextLine();
					category = newInfo;
					collection.addOrChangeDVD(title, category, runtime, year, price);
					changes = true;
				}
				else if (menuChoice == 3) {
					System.out.println("What would you like to change the runtime to?");
					newInfo = kbd.nextLine();
					runtime = newInfo;
					collection.addOrChangeDVD(title, category, runtime, year, price);
					changes = true;
				}
				else if (menuChoice == 4) {
					System.out.println("What would you like to change the year of release to?");
					newInfo = kbd.nextLine();
					year = newInfo;
					collection.addOrChangeDVD(title, category, runtime, year, price);
					changes = true;
				}
				else if (menuChoice == 5) {
					System.out.println("What would you like to change the price to?");
					newInfo = kbd.nextLine();
					price = newInfo;
					collection.addOrChangeDVD(title, category, runtime, year, price);
					changes = true;
				}
				else {
					System.out.println("Please select one of the options");
				}				
				
			}while (menuChoice != 0);
		}
		else {
			System.out.println("DVD not found");
		}
		
	}//End of editDVD
}
