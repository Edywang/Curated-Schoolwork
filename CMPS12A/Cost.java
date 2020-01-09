import java.util.Scanner;

public class Cost {

	public static void main(String[] args) {

		double miles;
		double eff;
		double cost;
		Scanner Scanner = new Scanner(System.in);
		miles = Scanner.nextDouble();
		eff = Scanner.nextDouble();
		cost = Scanner.nextDouble();
		Scanner.close();
		double TotalCost;
		TotalCost = miles/eff*cost;
		System.out.printf("%.2f",TotalCost);
	}

}
