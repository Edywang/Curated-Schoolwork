/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa4
 * Date: 5/04/2019
 * Description: Queue ADT
 */

public class Queue implements QueueInterface {

	// Fields for the Queue class
	private Node head; // reference to first Job in List
	private Node tail; // reference to last Node in List
	private int numItems; // number of items in this Queue

	private class Node {
		Object job;
		Node next;

		Node(Object j) {
			job = j;
			next = null;
		}
	}

	public Queue() {
		head = null;
		tail = null;
		numItems = 0;
	}

	// isEmpty()
	// pre: none
	// post: returns true if this Queue is empty, false otherwise
	public boolean isEmpty() {
		if (numItems == 0)
			return true;
		return false;
	}

	// length()
	// pre: none
	// post: returns the length of this Queue.
	public int length() {
		return numItems;
	}

	// enqueue()
	// adds newItem to back of this Queue
	// pre: none
	// post: !isEmpty()
	public void enqueue(Object newItem) {
		if (numItems == 0) {
			head = new Node(newItem);
			tail = head;
			++numItems;
			return;
		}
		tail.next = new Node(newItem);
		tail = tail.next;
		++numItems;
	}

	// dequeue()
	// deletes and returns item from front of this Queue
	// pre: !isEmpty()
	// post: this Queue will have one fewer element
	public Object dequeue() throws QueueEmptyException {
		if (numItems == 0)
			throw new QueueEmptyException("");
		Object placeholder = head.job;
		if (numItems <= 1) {
			dequeueAll();
			return placeholder;
		}
		head = head.next;
		--numItems;
		return placeholder;
	}

	// peek()
	// pre: !isEmpty()
	// post: returns item at front of Queue
	public Object peek() throws QueueEmptyException {
		if (numItems == 0)
			throw new QueueEmptyException("");
		return head.job;
	}

	// dequeueAll()
	// sets this Queue to the empty state
	// pre: !isEmpty()
	// post: isEmpty()
	public void dequeueAll() throws QueueEmptyException {
		if (numItems == 0)
			throw new QueueEmptyException("");
		head = null;
		tail = null;
		numItems = 0;
	}

	// toString()
	// overrides Object's toString() method
	public String toString() {
		String output = new String("");
		Node node = head;
		while (node != null) {
			output += node.job.toString() + " ";
			node = node.next;
		}
		if (numItems != 0) {
			return output.substring(0, output.length());
		}
		return output;
	}
}
