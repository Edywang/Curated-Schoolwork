/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa3
 * Date: 4/30/2019
 * Description: Dictionary ADT Testing Class
 */

public class DictionaryTest {

	public static void main(String[] args) {
		/*
		 * Dictionary A = new Dictionary(); A.insert("1", "a"); A.insert("2","b");
		 * A.insert("3","c"); A.insert("4","d"); A.insert("5","e"); A.insert("6","f");
		 * A.insert("7", "g"); System.out.println(A.size()); // Size wrong after
		 * delete(), Delete head didn't work properly System.out.println(A); // index
		 * out of bounds and size is wrong? Resolved, decremented in delete()
		 * System.out.println(A.lookup("7")); A.delete("1"); // Deleting head causes
		 * errors, resolved? System.out.println(A); A.delete("2"); // Key not found?
		 * Delete not working properly. Key is a // string, not an int, resolved
		 * System.out.println(A); A.delete("3"); System.out.println(A); A.delete("4");
		 * System.out.println(A); A.delete("5"); System.out.println(A); A.delete("6");
		 * System.out.println(A); A.delete("7"); System.out.println(A); //
		 * A.makeEmpty(); // System.out.println(A.isEmpty());
		 * System.out.println(A.lookup("7")); A.insert("1", "a");
		 * System.out.println(A.lookup("1")); System.out.println(A); A.insert("2","b");
		 * A.insert("3","c"); A.insert("4","d"); A.insert("5","e"); A.insert("6","f");
		 * A.insert("7","g"); System.out.println(A); A.delete("7"); System.out.println(A
		 * + "1st"); System.out.println(A.size()); A.delete("6"); System.out.println(A +
		 * "2nd"); System.out.println(A.size()); A.delete("5"); System.out.println(A +
		 * "3rd"); System.out.println(A.size()); A.delete("4"); System.out.println(A +
		 * "4th"); System.out.println(A.size()); A.delete("3"); System.out.println(A +
		 * "5th"); System.out.println(A.size()); A.delete("2"); System.out.println(A +
		 * "6th"); System.out.println(A.size()); A.delete("1"); System.out.println(A +
		 * "7th"); System.out.println(A); System.out.println(A.lookup("1"));
		 * System.out.println(A.lookup("2")); System.out.println(A.lookup("3"));
		 * System.out.println(A.lookup("4")); System.out.println(A.lookup("5"));
		 * System.out.println(A.lookup("6")); System.out.println(A.lookup("7"));
		 * System.out.println(A.size()); A.insert("1","b"); A.insert("2","c");
		 * A.insert("3","d"); A.insert("4","e"); A.insert("5","f"); A.insert("6","g");
		 * System.out.println(A); A.delete("3"); A.delete("5"); System.out.println(A);
		 */
		Dictionary A = new Dictionary();
		Dictionary B = new Dictionary();
		final int test_range = 1000;

		A.insert("test", "123");

		for (int i = 0; i < test_range; i++) {
			A.insert(i + 1 + "", "test" + i + 1);
		}
		System.out.print(A);
		for (int i = test_range * 9 / 10; i < test_range; i++) {
			System.out.println(i);
			A.delete(i + 1 + "");
			System.out.print(A);
		}
	}
}
