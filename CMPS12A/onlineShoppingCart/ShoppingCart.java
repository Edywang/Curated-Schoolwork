package onlineShoppingCart;
import java.util.ArrayList;

public class ShoppingCart {
	//private fields such as itemName, itemPrice, and itemQuantity
	private String customerName;
	private String currentDate;
	private ArrayList<ItemToPurchase> cartItems = new ArrayList<ItemToPurchase>();
	private int totalCost = 0;
	private int occ = 0;

	//default constructor
	ShoppingCart(){
		customerName = "none";
		currentDate = "January 1, 2016";
		ArrayList<ItemToPurchase>[] cartItems;
	}

	//Parameterized (non-default) constructor which takes the customer name and date as parameters
	ShoppingCart(String name, String date){
		customerName = name;
		currentDate = date;
		ItemToPurchase[] ItemToPurchase;
	}

	public String getCustomerName() {
		return customerName;
	}

	public String getDate() {
		return currentDate;
	}

	public void addItem(ItemToPurchase item) {
		cartItems.add(item);
	}

	public void removeItem(String itemName) {
		int countRemoved = 0;
		for(int i = 0; i < cartItems.size(); ++i) {
			if(cartItems.get(i).getName().equals(itemName)) {
				++countRemoved;
				cartItems.remove(i);
			}
		}
		if(countRemoved == 0) {
			System.out.println("Item not found in cart. Nothing removed.");
		}
		System.out.println();
	}

	public void modifyItem(ItemToPurchase item) {
		occ = 0;
		if(item.getDescription() != "none" || item.getPrice() != 0 || item.getQuantity() != 0) {
			for(int i = 0; i < cartItems.size(); ++i) {
				if(cartItems.get(i).getName().equals(item.getName())) {
					++occ;
					cartItems.set(i, item);
				}
			}
			if(occ == 0) {
				System.out.println("Item not found in cart. Nothing modified.");
			}
			System.out.println();
		}
	}

	public int getNumItemsInCart() {
		return cartItems.size();
	}

	public ItemToPurchase getItemInCart(int i) {
		return cartItems.get(i);
	}
	
	public int totalNumItems() {
		int total = 0;
		for(int i = 0; i < cartItems.size(); ++i) {
			total = total + cartItems.get(i).getQuantity();
		}
		return total;
	}

	public int getCostOfCart() {
		totalCost = 0;
		for(int i = 0; i < cartItems.size(); ++i) {
			totalCost = totalCost + (cartItems.get(i).getPrice() * cartItems.get(i).getQuantity());
		}
		return totalCost;
	}

	public void printTotal() {
		totalCost = 0;
		System.out.println(customerName + "'s Shopping Cart - " + currentDate);
		System.out.println("Number of Items: " + totalNumItems());
		System.out.println();
		if(cartItems.size() == 0) {
			System.out.println("SHOPPING CART IS EMPTY");
			System.out.println();
			System.out.println("Total: $0");
			System.out.println();
		}
		else {
			for(int i = 0; i < cartItems.size(); ++i) {
				totalCost = totalCost + (cartItems.get(i).getPrice() * cartItems.get(i).getQuantity());
				System.out.println(cartItems.get(i).getName() + " " + cartItems.get(i).getQuantity() + " @ $" + cartItems.get(i).getPrice() + " = $" + (cartItems.get(i).getPrice() * cartItems.get(i).getQuantity()));
			}
			System.out.println();
			System.out.println("Total: $" + totalCost);
			System.out.println();
		}
	}
	public void printDescriptions(){
		for(int i = 0; i < cartItems.size(); ++i) {
			System.out.println(cartItems.get(i).getDescription());
		}
	}

}