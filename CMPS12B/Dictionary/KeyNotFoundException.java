/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa3
 * Date: 4/30/2019
 * Description: KeyNotFoundException thrown by Dictionary.java
 */
public class KeyNotFoundException extends RuntimeException {
	public KeyNotFoundException() {
	      super("cannot delete non-existent key");
	   }
}
