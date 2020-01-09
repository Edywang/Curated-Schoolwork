import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;

public class Increment {

	public static void main(String[] args) {
		Scanner Sc = new Scanner(System.in);
		List<Integer> Nums = new ArrayList<Integer>();
		int i=1;
		double Sum = 0;
		Nums.add(Sc.nextInt());
		Nums.add(Sc.nextInt());
		while(Nums.get(i-1) <= Nums.get(i)) {
			Nums.add(Sc.nextInt());
			i++;
		}
		for(int index = 1; index < Nums.size()-1; index++) {
			Sum = Sum + (Nums.get(index) - Nums.get(index-1));
		}
		if(Nums.size()>2) {
		System.out.printf("%.2f%n", Sum / (Nums.size()-2));
		}
		else {
			System.out.print("0.00");
		}
	}

}
