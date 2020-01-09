/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * SID: 1660213
 * Date: 4/18/19
 * Assignment: 12B PA2
*/
import java.lang.StringBuilder;

public class Queens {
	public static void main(String[] args) {
		int n = 0;
		/*
		 * / Start Test int[][] Testing = new int[2][2]; for (int i = 0; i <
		 * Testing.length; ++i) { for (int j = 0; j < Testing.length; ++j) {
		 * Testing[i][j] = 0; System.out.println("Init 0"); } } placeQueen(Testing, 1,
		 * 1); printBoard(Testing); System.exit(0);
		 */
		if (args.length == 2 && !args[0].equals("-v")) {
			err();
		}
		if (args.length == 1) {
			try {
				n = Integer.parseInt(args[0]);
			} catch (Exception e) {
				err();
			}
		}
		if (args.length == 2) {
			try {
				n = Integer.parseInt(args[1]);
			} catch (Exception e) {
				err();
			}
		}
		if (n < 1 || n > 15) {
			err();
		}
		if (n == 2 || n == 3) {
			System.out.println(n + "-Queens has 0 solutions");
			System.exit(0);
		}
		int[][] B = new int[n + 1][n + 1];
		for (int i = 0; i < B.length; ++i) {
			for (int j = 0; j < B.length; ++j) {
				B[i][j] = 0;
			}
		}
		if (args.length == 1)
			System.out.println(n + "-Queens has " + findSolutions(B, 1, "") + " solutions");
		if (args.length == 2)
			System.out.println(n + "-Queens has " + findSolutions(B, 1, "verbose") + " solutions");
	}

	static void placeQueen(int[][] B, int column, int row) {
		B[0][row] = column;
		B[column][row] = 1;
		int counter = 0;
		for (int k = row - 1; k > 0; --k) { // Above
			++counter;
			if (column - counter > 0) // Above left
				--B[column - counter][row];
			if (column + counter < B.length) // Above right
				--B[column + counter][k];
			--B[column][k]; // Directly above
		}
		counter = 0;
		for (int k = column - 1; k > 0; --k) { // Directly left
			--B[k][row];
		}
		for (int k = column + 1; k < B.length; ++k) { // Directly right
			--B[k][row];
		}
		for (int k = row + 1; k < B.length; ++k) { // Below
			++counter;
			if (column - counter > 0) // Below left
				--B[column - counter][k];
			if (column + counter < B.length) // Below right
				--B[column + counter][k];
			--B[column][k]; // Directly below

		}
		counter = 0;
	}

	static void removeQueen(int[][] B, int column, int row) {
		B[0][row] = column;
		B[column][row] = 0;
		int counter = 0;
		for (int k = row - 1; k > 0; --k) { // Above
			++counter;
			if (column - counter > 0) // Above left
				++B[column - counter][row];
			if (column + counter < B.length) // Above right
				++B[column + counter][k];
			++B[column][k]; // Directly above
		}
		counter = 0;
		for (int k = column - 1; k > 0; --k) { // Directly left
			++B[k][row];
		}
		for (int k = column + 1; k < B.length; ++k) { // Directly right
			++B[k][row];
		}
		for (int k = row + 1; k < B.length; ++k) { // Below
			++counter;
			if (column - counter > 0) // Below left
				++B[column - counter][k];
			if (column + counter < B.length) // Below right
				++B[column + counter][k];
			++B[column][k]; // Directly below
		}
	}

	static void printBoard(int[][] B) {
		StringBuilder output = new StringBuilder();
		output.append("(");
		for (int i = 1; i < B.length; ++i) {
			output.append(B[0][i] + ", ");
		}
		output.delete(output.length() - 2, output.length());
		output.append(")");
		System.out.println(output);
	}

	static void err() {
		System.err.println("Usage: Queens [-v] number");
		System.err.println("Option: -v verbose output, print all solutions");
		System.exit(1);
	}

	static int findSolutions(int[][] B, int row, String mode) { // Recursive algorithm
		int output = 0;
		if (row < B.length) {
			for (int j = 1; j < B.length; ++j) {
				if (B[j][row] >= 0) {
					placeQueen(B, j, row);
					output += findSolutions(B, row + 1, mode);
					removeQueen(B, j, row);
				}
			}
		} else if (mode.equals("verbose")) {
			++output;
			printBoard(B);
		} else {
			++output;
		}
		return output;

	}
}
