package convert;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Convert {
	static final JLabel string = new JLabel("Convert"); //First
	static final JLabel to = new JLabel("to"); //Fourth
	static final JFrame convert = new JFrame();
	static final JButton go = new JButton("GO!"); //Sixth
	static final JTextField input = new JTextField(15); //Second
	static final String[] originList = {"Mile", "Yard", "Foot", "Inch"};
	static final JComboBox origin = new JComboBox(originList); //Third
	static final String[] finalList = {"Kilometer", "Meter", "Centimeter"};
	static final JComboBox fifth = new JComboBox(finalList); //Fifth
	static JLabel output = new JLabel(); //Seventh
	static double num = 0;
	static int from = 0;
	static int convertTo = 0;
	static double result;

	public static void main(String[] args) {
		run();
	}

	public static void run() {
		//Setup
		input.setEditable(true);
		convert.setTitle("Conversion System");
		convert.setSize(700, 100);
		convert.getContentPane().setBackground(Color.pink);
		convert.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		//Adding
		convert.add(string);
		convert.add(input);
		convert.add(origin);
		convert.add(to);
		convert.add(fifth);
		convert.add(go);
		convert.add(output);
		convert.setLayout(new FlowLayout());

		//Action
		go.addActionListener(new MyListener());

		//Properties
		go.putClientProperty("Num", input); //Number input
		go.putClientProperty("FirstDrop", origin); //Conversion from
		go.putClientProperty("SecondDrop", fifth); //Conversion to
		go.putClientProperty("Output", output);

		//Final
		convert.setVisible(true);
	}

	static class MyListener implements ActionListener{
		//The main important method in the actionlistener is actionperformed method.
		//This method will be called when the listener detects a user interaction with the specific UI element that the listener object is attached to.
		@Override
		public void actionPerformed(ActionEvent event) {
			num = Double.parseDouble(input.getText());
			from = origin.getSelectedIndex();
			convertTo = fifth.getSelectedIndex();
			if(from == 0 && convertTo == 0) //Mi to KM
				result = num * 1.609344;
			else if(from == 0 && convertTo == 1) //Mi to M
				result = num * 1609.344;
			else if(from == 0 && convertTo == 2) //Mi to CM
				result = num * 160934.4;
			else if(from == 1 && convertTo == 0) //Yd to KM
				result = num * 0.0009144;
			else if(from == 1 && convertTo == 1) //Yd to M
				result = num * 0.9144;
			else if(from == 1 && convertTo == 2) //Yd to CM
				result = num * 91.44;
			else if(from == 2 && convertTo == 0) //Ft to KM
				result = num * .0003048;
			else if(from == 2 && convertTo == 1) //Ft to M
				result = num * .3048;
			else if(from == 2 && convertTo == 2) //Ft to CM
				result = num * 30.48;
			else if(from == 3 && convertTo == 0) //In to KM
				result = num * .0000254;
			else if(from == 3 && convertTo == 1) //In to M
				result = num * .0254;
			else if(from == 3 && convertTo == 2) //In to CM
				result = num * 2.54;
			result = Math.round(result * 100.0) / 100.0;
			output.setText(String.format("%.02f", result));
		}
	}

}