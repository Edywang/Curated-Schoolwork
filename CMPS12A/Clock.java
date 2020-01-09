public class Clock {
	private int h;
	private int m;
	private String time;
    private int ha;
    private int ma;
	
	public Clock() { //This is the default constructor of the class. It creates a Clock object and sets the time to midnight, hour = 0, minute = 0.
		this.h = 0;
		this.m = 0;
	}
	
	public Clock(int h) { //This is a one-argument constructor with parameter for the hour. The constructor always sets minute to 0.
		this.h = h;
		this.m = 0;
	}
	
	public Clock(int h, int m) { //This is a two-argument constructor with parameters for the hour and minute.
		this.h = h;
		this.m = m;
	}

	public int getHour() { //Returns the hour.
		return this.h;
	}
	
	public int getMinute() { //Returns the minute.
		return this.m;
	}
	
	public void incrementTimer() { //Basic incremented adds 1 minute to the time.
		if(this.m == 59) {
			this.m = 0;
			if(this.h == 23)
			this.h = 0;
			else {
				this.h = this.h + 1;
			}
		}
		else {
			this.m = this.m + 1;
		}
	}
	
	public void incrementTimer(int x) { //Adds x minutes to the time. (Hint: you can reuse the incrementTimer() method here.)
		for(int i = 0; i < x; ++i) {
			incrementTimer();
		}
	}

	public void setTime(int h, int m) { //Sets the time to be hour = h and minute = m. If invalid data is entered it should print “Invalid Input”. 
		if(h < 24 && m < 60) {
			this.h = h;
			this.m = m;
		}
		else {
			System.out.println("Invalid Input");
		}
	}
	
	public String toString() { //Returns a string in the form of xx:yy PM. eg. “02:53 PM”, “11:05 AM”, or “12:15 AM”
		if(this.h == 0) {
			this.time = "12:";
		}
		else if ((this.h < 10) || (this.h > 12 && this.h < 22)) {
			if(this.h < 10){
                this.time = "0" + this.h + ":";
            }
            else{
                this.time = "0" + (this.h - 12) + ":";
            }
		}
		else {
			this.time = this.h + ":";
		}
		
		if(this.m < 10) {
			this.time = time + "0" + this.m;
		}
		else {
			this.time = time + this.m;
		}
		
		if(this.h > 11) {
			time = time + " PM";
		}
		else {
			time = time + " AM";
		}
		
		return time;
	}

}
