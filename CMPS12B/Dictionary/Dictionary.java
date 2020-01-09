/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa3
 * Date: 4/30/2019
 * Description: Dictionary ADT
 */

public class Dictionary implements DictionaryInterface {

	// private inner Node class
	private class Node {
		String key;
		String value;
		Node next;

		Node(String k, String v) {
			key = k;
			value = v;
			next = null;
		}
	}

	// Fields for the Dictionary class
	private Node head; // reference to first Node in List
	private Node last; // reference to last Node in List
	private int numItems; // number of items in this Dictionary

	// Dictionary()
	// constructor for the Dictionary class
	public Dictionary() {
		head = null;
		last = null;
		numItems = 0;
	}

	// isEmpty()
	// pre: none
	// returns true if this Dictionary is empty, false otherwise
	@Override
	public boolean isEmpty() {
		if (numItems == 0) {
			return true;
		}
		return false;
	}

	// size()
	// pre: none
	// returns the number of entries in this Dictionary
	@Override
	public int size() {
		return numItems;
	}

	// lookup()
	// pre: none
	// returns value associated key, or null reference if no such key exists
	@Override
	public String lookup(String key) {
		Node node = findKey(key);
		if (node == null)
			return null;
		return node.value;
	}

	// insert()
	// inserts new (key,value) pair into this Dictionary
	// pre: lookup(key)==null
	@Override
	public void insert(String key, String value) {
		Node node = new Node(key, value);
		if (lookup(key) != null) {
			throw new DuplicateKeyException();
		}
		if (numItems == 0) {
			head = node;
			last = node;
		} else {
			last.next = node;
			last = node;
		}
		++numItems;
	}

	// delete()
	// deletes pair with the given key
	// pre: lookup(key)!=null
	@Override
	public void delete(String key) {
		Node node = head;
		if (lookup(key) == null)
			throw new KeyNotFoundException();
		else {
			if (head.key.equals(key))
				head = head.next;
			else
				while (node.next != null) {
					if (node.next.key.equals(key)) {
						if (last == node.next) {
							last = node;
						}
						node.next = node.next.next;
						break;
					}
					node = node.next;
				}
			--numItems;
		}
	}

	// makeEmpty()
	// pre: none
	@Override
	public void makeEmpty() {
		head = null;
		last = null;
		numItems = 0;
	}

	private Node findKey(String key) { // return reference to Node with key, or null otherwise
		Node current = head;
		while (current != null) {
			if (current.key.equals(key)) {
				return current;
			}
			current = current.next;
		}
		return null;
	}

	// toString()
	// returns a String representation of this Dictionary
	// overrides Object's toString() method
	// pre: none
	public String toString() {
		String output = new String("");
		Node node = head;
		while (node != null) {
			output += node.key + " " + node.value + "\n";
			node = node.next;
		}
		return output;
	}

}
