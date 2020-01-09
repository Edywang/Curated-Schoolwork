/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa1
 * Date: 4/7/2019
 * Description: Takes stdin/command line args of two integers, n and k, and lists all subsets of size k
 * from a set of size n, where the set of size n is of the form: {1, 2, 3...}
 */

public class Subset {

	public static void main(String[] args) {
		int n = -1;
		int k = -1;
		if (args.length != 2) {
			err();
		}
		try {
			n = Integer.parseInt(args[0]);
			k = Integer.parseInt(args[1]);
		} catch (Exception e) {
			err();
		}
		if (n < k || k < 0)
			err();
		else if (k == 0) {
			System.out.println("{}");
		} else {
			int B[] = new int[n + 1];
			for (int i = 0; i <= n; ++i) {
				B[i] = 0;
			}
			printSubsets(B, k, 1);
		}
	}

	static void printSubsets(int B[], int k, int i) {// B.length - 1 choose k, i is index
		int counter = 0;
		for (int j = 1; j < B.length; ++j) {
			if (B[j] == 1)
				++counter;
		}
		if (B.length == i) {
			if (counter == k) {
				setToString(B);
			}
		} else {
			if (counter <= k) {
				B[i] = 1;
				printSubsets(B, k, i + 1);
				B[i] = 0;
				printSubsets(B, k, i + 1);
			}
		}
	}

	static void setToString(int[] B) {
		StringBuffer out = new StringBuffer();
		out.append("{");
		for (int i = 1; i < B.length; ++i) {
			if (B[i] == 1)
				out.append(i + ", ");
		}
		out.delete(out.length() - 2, out.length());
		out.append("}");
		System.out.println(out);
	}

	static void err() {
		System.err.println("Usage: Java Subset <int> <int>");
		System.exit(0);
	}
}