import java.util.Scanner;

public class Minesweeper {

	public static void main(String[] args) {
		Scanner Sc = new Scanner(System.in);
		int m = Sc.nextInt(); //rows
		int n = Sc.nextInt(); //columns
		int b = Sc.nextInt(); //bombs
		int r; //current bomb row
		int c; //current bomb column
		int counter = 0; //count of bombs around
		//using 9 to represent a bomb in the 2d array
		int[][] Mines = new int[m][n];
		for(int i = 0; i < b; i++) {
			r = Sc.nextInt();
			c = Sc.nextInt();
			Mines[r][c] = 9;
		}
		Sc.close();
		for(int row = 0; row < m; row++) {
			for(int column = 0; column < n; column++) {
				if(Mines[row][column] == 9) {
					System.out.print("*");	
				}
				else {
					for(int j = -1; j < 2; j++) {
						for(int i = -1; i < 2; i++) {
							if(i==0&&j==0) {

							}
							else if(column+j < 0 || column+j > Mines[0].length - 1 || row+i < 0 || row + i > Mines.length - 1){
							}
							else {
								if(Mines[row+i][column+j] == 9) {
									counter++;
								}
							}
						}
					}
					System.out.print(counter);
				}
				if(column < Mines[0].length - 1) {
					System.out.print(" ");
				}
					
				counter = 0;
			}
			System.out.println();
		}

	}

}
