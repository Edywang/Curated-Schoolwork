import java.util.Scanner;

public class Sequence {

	public static void main(String[] args) {
		Scanner Sc = new Scanner(System.in);
		int One = Sc.nextInt();
		int Two = Sc.nextInt();
		int Three = Sc.nextInt();
		int Reps = Sc.nextInt();
		int [] Result = new int[Reps];
		Result[0] = One;
		Result[1] = Two;
		Result[2] = Three;
		int DiffOne = Result[1] - Result[0];
		int DiffTwo = Result[2] - Result[1];
		for(int i = 3; i < Reps; i++){
			if(i%2 == 1) {
				Result[i] = Result[i-1] + DiffOne;
			}
			else {
				Result[i] = Result[i-1] + DiffTwo;
			}
		}
		for(int i = 0; i < Reps; i++) {
			System.out.print(Result[i] + " ");
		}
	}

}
