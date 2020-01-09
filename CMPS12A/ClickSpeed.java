package click;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ClickSpeed {
	static final JFrame click = new JFrame(); //Main Frame
	static final JButton go = new JButton("Click me!"); //Center
	static final JButton retry = new JButton("Start"); //North
	static final JButton nty = new JButton("Done"); //South
	static final JButton score = new JButton("Last Score"); //West
	static final JButton author = new JButton("About"); //East
	static int counter = 0; //Counter of clicks
	static Timer timer; //Timer
	static final double delay = 4000; //Timer delta time
	static String last; //last score, ends with " clicks per second"
	static boolean timerActive = false;

	public static void main(String[] args) {
		//Main Button
		ActionListener start = new ActionListener() { //When Clicked
			public void actionPerformed(ActionEvent event) {
				if(timerActive)
				++counter;
				else
					JOptionPane.showMessageDialog(null, "Click Start at the top first!");
			}
		};
		go.addActionListener(start); //Add When Clicked

		//Timer
		ActionListener timerDone = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				last = counter / (delay / 1000) + " clicks per second";
				JOptionPane.showMessageDialog(null, last);
				timer.stop();
				timerActive = false;
			}
		};
		timer = new Timer((int)delay, timerDone);

		ActionListener restart = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				counter = 0;
				timerActive = true;
				JOptionPane.showMessageDialog(null, "Click the button as fast as you can for " + delay + " milliseconds, click OK when you are ready to begin.");
				timer.restart();
			}
		};
		retry.addActionListener(restart); //"Start" North Button

		ActionListener complete = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		};
		nty.addActionListener(complete); //"Done" South Button

		ActionListener lastScore = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(last != null)
					JOptionPane.showMessageDialog(null, "Your last score was: " + last);
				else
					JOptionPane.showInputDialog(null, "Click start and try clicking the big button first!");
			}
		};
		score.addActionListener(lastScore);

		ActionListener authorWanted = new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(null, "Created by Edwin Wang for CMPS 12A at UCSC", "I am so glad you asked", JOptionPane.INFORMATION_MESSAGE);
			}
		};
		author.addActionListener(authorWanted); //East Button

		//Setup frame
		click.setLayout(new BorderLayout(10, 10));
		click.setTitle("Click Speed");
		click.getContentPane().setBackground(Color.DARK_GRAY);
		click.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		click.setExtendedState(JFrame.MAXIMIZED_BOTH); 
		click.add(go, BorderLayout.CENTER);
		click.add(retry, BorderLayout.NORTH);
		click.add(nty, BorderLayout.SOUTH);
		click.add(score, BorderLayout.WEST);
		click.add(author, BorderLayout.EAST);
		click.setUndecorated(true);
		click.setLocationRelativeTo(null);
		click.setVisible(true);
	}
}