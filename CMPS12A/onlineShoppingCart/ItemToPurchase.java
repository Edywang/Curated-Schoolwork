package onlineShoppingCart;
public class ItemToPurchase{
	//private fields such as itemName, itemPrice, and itemQuantity
	private String itemName;
	private int itemPrice;
	private int itemQuantity;
	private String itemDesc;
	//default constructor
	ItemToPurchase(){
		itemName = "none";
		itemPrice = 0;
		itemQuantity = 0;
		itemDesc = "none";
	}
	ItemToPurchase(String name, String desc, int price, int quant){
		itemName = name;
		itemPrice = price;
		itemQuantity = quant;
		itemDesc = desc;
	}
	//setName method
	public void setName(String name) {
		itemName = name;
	}
	//getName method
	public String getName() {
		return itemName;
	}
	//setPrice method
	public void setPrice(int price) {
		itemPrice = price;
	}
	//getPrice method
	public int getPrice() {
		return itemPrice;
	}
	//setQuantity method
	public void setQuantity(int quant) {
		itemQuantity = quant;
	}
	//getQuantity method
	public int getQuantity() {
		return itemQuantity;
	}
	//setDescription method
	public void setDescription(String desc) {
		itemDesc = desc;
	}
	//getDescription method
	public String getDescription() {
		return itemDesc;
	}
	//printItemCost method
	public void printItemCost() {
		System.out.println(itemName + " " + itemQuantity + " @ $" + itemPrice + " = $" + (itemQuantity * itemPrice));
	}
}