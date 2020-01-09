/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa3
 * Date: 4/30/2019
 * Description: DuplicateKeyException thrown by Dictionary.java
 */

public class DuplicateKeyException extends RuntimeException{
	public DuplicateKeyException() {
	      super("cannot insert duplicate keys");
	   }
}
