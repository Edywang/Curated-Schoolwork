/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa4
 * Date: 5/04/2019
 * Description: QueueEmptyException thrown by Queue.java
 */

public class QueueEmptyException extends RuntimeException {
	private static final long serialVersionUID = 1L;

	public QueueEmptyException(String e) {
		super(e);
	}
}
