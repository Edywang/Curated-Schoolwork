import java.util.Scanner;
public class Convert {

	public static void main(String[] args) {
		Scanner Scanner = new Scanner(System.in);
		String hour = null;
		String minute;
		int Hour;
		int Minute;
		int M;
		Hour = Scanner.nextInt();
		Minute = Scanner.nextInt();
		M = Scanner.nextInt();
		Scanner.close();
		if(Hour == 12 && M == 1) {
			hour = "00";
		}
		else if(Hour == 12 && M ==2) {
			hour = "12";
		}
		else if(M==2) {
			Hour = Hour+12;
			hour = Integer.toString(Hour);
		}
		else if(Hour<=9) {
			hour = "0" + Hour;
		}
		else {
			hour = Integer.toString(Hour);
		}
		if(Minute<=9) {
			minute = "0" + Minute;
		}
		else {
			minute = Integer.toString(Minute);
		}
		System.out.println(hour + ":" + minute);
	}

}
