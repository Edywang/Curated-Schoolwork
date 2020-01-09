import java.util.Scanner;

public class Narges {

    public static void main(String[] args) {
        Scanner Sc = new Scanner(System.in);
        String St = Sc.nextLine();
        Sc.close();
        int nargindex = 0;
        boolean has = false;
        String narges = "narges";
        for(int i = 0; i < St.length() && nargindex < narges.length(); ++i) {
        	if(narges.charAt(nargindex) == St.charAt(i)) {
        		++nargindex;
        	}
        }
        has = nargindex == narges.length();
        System.out.print(has);
    }
}
