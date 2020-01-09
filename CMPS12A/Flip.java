import java.util.Scanner;
public class Flip {

	public static void main(String[] args) {
		Scanner Scanner = new Scanner(System.in);
		int Num;
		Num = Scanner.nextInt();
		int i;
		for(i=0;i<=1;i++) {
			if(Num%10==0)
				Num=Num/10;
		}
		if(Num <=9) {
			Num = Num * 100;
		}
		else if(Num<=99) {
				int A; //1st Digit
				A = Num%10; //1st Digit
				Num = Num - A; //2nd Digit with one zero
				Num = Num / 10; //2nd Digit
				Num = (Num + A * 10) * 10; //Flip
			}
		else if(Num<=999) {
			int A;
			int B;
			A = Num%10; //1st Digit
			B = Num%100; //2nd Digit + 1st Digit
			Num = Num - B; //3rd Digit with two zeroes
			B = (B-A)/10; //2nd Digit
			Num = Num/100; //3rd Digit
			Num = A*100 + B*10 + Num; //Flip
		}
		System.out.println(Num);
		Scanner.close();
	}
}
