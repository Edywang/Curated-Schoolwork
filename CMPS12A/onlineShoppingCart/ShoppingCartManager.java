package onlineShoppingCart;
import java.util.Scanner;

public class ShoppingCartManager {
	private static int totalCost = 0;
	static char input = 'b';
	
	public static void main(String[] args) {
		System.out.println("Enter Customer's Name:");
		Scanner sc = new Scanner(System.in);
		String name = sc.nextLine();
		System.out.println("Enter Today's Date:");
		ShoppingCart cart = new ShoppingCart(name, sc.nextLine());
		System.out.println();
		System.out.println("Customer Name: " + cart.getCustomerName());
		System.out.println("Today's Date: " + cart.getDate());
		printMenu(cart, sc);
	}

	public static void printMenu(ShoppingCart cart, Scanner sc) {
		System.out.println();
		while(input != 'q') {
			input = 'b';
			totalCost = 0;
			System.out.println("MENU");
			System.out.println("a - Add item to cart");
			System.out.println("d - Remove item from cart");
			System.out.println("c - Change item quantity");
			System.out.println("i - Output items' descriptions");
			System.out.println("o - Output shopping cart");
			System.out.println("q - Quit");
			System.out.println();
			System.out.println("Choose an option:");
			input = sc.nextLine().charAt(0);
			while(input != 'a' && input != 'd' && input != 'c' && input != 'i' && input != 'o' && input != 'q') {
			System.out.println("Choose an option:");
			input = sc.nextLine().charAt(0);
			}
			if(input == 'q') {
				break;
			}
			if(input == 'o') {
				System.out.println("OUTPUT SHOPPING CART");
				cart.printTotal();
			}
			if(input == 'i') {
				System.out.println("OUTPUT ITEMS' DESCRIPTIONS");
				System.out.println(cart.getCustomerName() + "'s Shopping Cart - " + cart.getDate());
				System.out.println();
				System.out.println("Item Descriptions");
				for(int i = 0; i < cart.getNumItemsInCart(); ++i) {
					System.out.println(cart.getItemInCart(i).getName() + ": " + cart.getItemInCart(i).getDescription());
				}
				System.out.println();
			}
			if(input == 'a') {
				System.out.println("ADD ITEM TO CART");
				System.out.println("Enter the item name:");
				String itemName = sc.nextLine();
				System.out.println("Enter the item description:");
				String itemDesc = sc.nextLine();
				System.out.println("Enter the item price:");
				int itemPrice = sc.nextInt();
				System.out.println("Enter the item quantity:");
				ItemToPurchase item = new ItemToPurchase(itemName, itemDesc, itemPrice, sc.nextInt());
				cart.addItem(item);
				System.out.println();
				sc.nextLine();
			}
			if(input == 'd') {
				System.out.println("REMOVE ITEM FROM CART");
				System.out.println("Enter name of item to remove:");
				cart.removeItem(sc.nextLine());
			}
			if(input == 'c') {
				ItemToPurchase mod = new ItemToPurchase();
				System.out.println("CHANGE ITEM QUANTITY");
				System.out.println("Enter the item name:");
				mod.setName(sc.nextLine());
				System.out.println("Enter the new quantity:");
				mod.setQuantity(sc.nextInt());
				for(int i = 0; i < cart.getNumItemsInCart(); ++i) {
					if(cart.getItemInCart(i).getName().equals(mod.getName())) {
						mod.setDescription(cart.getItemInCart(i).getDescription());
						mod.setPrice(cart.getItemInCart(i).getPrice());
						break;
					}
				}
				cart.modifyItem(mod);
				sc.nextLine();
			}
		}
	}
}