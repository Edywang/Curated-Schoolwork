import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Scanner;

public class FileReverse {

	public static void main(String[] args) {
		Scanner in = null;
		PrintWriter out = null;
		if (args.length != 2) {
			err();
		}
		try {
			in = new Scanner(new File(args[0]));
			out = new PrintWriter(new FileWriter(args[1]));
		} catch (Exception e) {
			err();
		}
		while(in.hasNextLine()) {
			out.println(stringReverse(in.nextLine(), 1));
		}

	}

	private static void err() {
		System.err.println("Usage: FileReverse <input file> <output file>");
		System.exit(0);
	}

	public static String stringReverse(String s, int n) {
		String output = "";
		int leftIndex;
		int rightIndex;
		char leftPlaceholder;
		if (n <= s.length() / 2) {
			if (s.length() % 2 == 1) { // Odd length string
				leftIndex = s.length() / 2 - n;
				rightIndex = s.length() / 2 + n;
				leftPlaceholder = s.charAt(leftIndex);
			} else { // Even length string
				leftIndex = s.length() / 2 - n;
				rightIndex = s.length() / 2 + n - 1;
				leftPlaceholder = s.charAt(leftIndex);
			}
			for (int i = 0; i < s.length(); ++i) {

				if (i == leftIndex) {
					output += s.charAt(rightIndex);
				} else if (i == rightIndex) {
					output += leftPlaceholder;
				} else {
					output += s.charAt(i);
				}
			}
			return stringReverse(output, ++n);
		} else {
			return s;
		}

	}

}
