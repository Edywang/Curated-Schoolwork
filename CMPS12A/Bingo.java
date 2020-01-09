public class Bingo {
    public Player[] players;
    public String Winners = "";
    
    public Bingo(Player[] players) { //Creates an object of Bingo game using an array of Player objects passed as an argument.
        this.players = players;
    }
    
    public String play(int number) {
        /*
         This is the main method for playing the game. It takes a number (the number that is called)
and marks the cells with that number in all players’ cards. It also returns the name of the
winner, if any. If there is no winner, it return an empty string. If there is more than one
winner, it returns the name of all winners as one string, separated by space (again, no space
         */
        for(int i = 0; i < players.length; ++i) {
            players[i].markNumber(number);
            if (players[i].isWinner()) {
                Winners = Winners + players[i].getName() + " ";
            }
        }
        
        return Winners.trim();
        
    }
    
}

public class Player {
	private String name;
	private Card[] cards;
	private int Row;
	private int Column;

	public Player(String name, Card[] cards) { //Creates a Player object using the name of the player and an array of bingo cards for the player
		this.name = name;
		this.cards = cards;
	}

	public String getName() { //Returns the name of the player.
		return this.name;
	}

	public Card[] getCards() { //Returns player’s bingo cards.
		return this.cards;
	}

	public boolean isWinner() { //Checks if the player is a winner.
		int Count = 0;

		for(int i = 0; i < cards.length; ++i) {
			for(Row = 0; Row < 5; ++Row) { //Checks if rows are all marked
				for(Column = 0; Column < 5; ++Column) {
					if(this.cards[i].isMarked(Row, Column)) {
						Count = Count + 1;
					}
				}
				if(Count == 5) {
					break;
				}
				else if(Count != 5) {
					Count = 0;
				}
			}

			for(Column = 0; Column < 5; ++Column) { //Checks if columns are all marked
				if(Count == 5) {
					break;
				}
				else if(Count != 5) {
					Count = 0;
					for(Row = 0; Row < 5; ++Row) {
						if(this.cards[i].isMarked(Row, Column)) {
							Count = Count + 1;
						}
					}
				}
			}

			Row = 0;
			if(Count != 5) {
				Count = 0;
				for(Column = 0; Column < 5; ++Column) { //Top left to bottom right diagonal
					if(Count == 5) {
						break;
					}
					if(this.cards[i].isMarked(Row, Column)) {
						++Count;
					}
					++Row;
				}
			}


			Row = 4;
			if(Count != 5) {
				Count = 0;
				for(Column = 0; Column < 5; ++Column) { //Bottom left to top right diagonal
					if(Count == 5) {
						break;
					}
					if(this.cards[i].isMarked(Row, Column)) {
						++Count;
					}
					--Row;
				}

			}
		}

		if(Count == 5) {
			return true;
		}
		else {
			return false;
		}
	}

	public void markNumber(int number) { //Takes a number and marks that number in all bingo cards of the player.
		for(int i = 0; i < this.cards.length; ++i) {
			this.cards[i].markNumber(number);
		}
	}

}

public class Card {
    private int[][] numbers = new int[5][5];
    private int[][] marks = new int[5][5];
    
    public Card(int[][] numbers) { //Uses an array of 5 x 5 and fills the bingo card by those numbers.
        this.numbers = numbers;
    }
    
    public int getNumber(int Row, int Column) { //Returns the number in the cell at row and column of the bingo card.
        return this.numbers[Row][Column];
    }
    
    public boolean isMarked(int row, int column) { //If the cell at row and column of the card is marked, returns true, otherwise, returns false.
        if(this.marks[row][column] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    
    public void markNumber(int number) { //Takes a number and if the number exists in the card, marks that cell of the card.
        for(int Row = 0; Row < 5; ++Row) {
            for(int Column = 0; Column < 5; ++Column) {
                if(number == this.numbers[Row][Column]) {
                    this.marks[Row][Column] = 1;
                }
            }
        }
    }
    
}
