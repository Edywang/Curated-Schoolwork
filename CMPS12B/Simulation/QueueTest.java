/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa4
 * Date: 5/12/2019
 * Description: Alternate testing main method
 */

public class QueueTest {
	public static void main(String[] args) {
		Queue A = new Queue();
		A.enqueue(new Job(1, 3));
		A.enqueue(new Job(2, 3));
		System.out.println(A); // (1, 3, *) (2, 3, *)
		System.out.println(A.dequeue() + " dequeued"); // (1, 3, *) dequeued
		System.out.println(A.peek() + " peeked"); // (2, 3, *) peeked
		System.out.println(A.length() + " length"); // 1 length
		System.out.println(A); // (2, 3, *)
		System.out.println(A.dequeue() + " dequeued"); // (2, 3, *) dequeued
		System.out.println(A + "Printed"); // null printed
		System.out.println(A.length() + " length"); // 0 length
		System.out.println(A.isEmpty()); // true
		A.enqueue(new Job(1, 3));
		System.out.println(A); // (1, 3, *)
		System.out.println(A.peek() + " peeked"); // (1, 3, *) peeked
		System.out.println(A.length() + " length"); // 1 length
		System.out.println(A.isEmpty()); // false
		A.enqueue(new Job(2, 3));
		System.out.println(A.length() + " length"); // 2 length
		A.dequeueAll();
		System.out.println(A.isEmpty()); // true
		System.out.println(A.length() + " length"); // 0 length
	}
//*****************************
}
