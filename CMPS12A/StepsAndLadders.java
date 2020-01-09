class Game {
	Board board;
	Player[] players;
	int current;

	public Game(Board brd, Player[] playr) {
		current = 0;
		board = brd;
		players = playr;
		board.getCells()[0].setOccupied(true);
	}

	public Game(Player[] plyr) {
		players = plyr;
		board = new Board(10);
		board.getCells()[0].setOccupied(true);
	}

	public Player currentPlayer() {
		return players[current];
	}

	public void addPlayer(Player p) {
		p.setPosition(0);
		board.getCells()[0].setOccupied(true);
		Player[] copy = new Player[players.length + 1];
		for(int i = 0; i < players.length; ++i)
			copy[i] = players[i];
		copy[players.length] = p;
		players = copy;
	}

	public boolean winner() {
		return players[current].getPosition() == board.getCells().length - 1;
	}

	public void movePlayer(int n) {
		if(players[current].getPosition() == 0) {
			int peeps = 0;
			for(int i = 0; i < players.length; ++i) {
				if(0 == players[i].getPosition() && i != current)
					++peeps;
			}
			if(peeps == 0)
				board.getCells()[players[current].getPosition()].setOccupied(false);
			else
				board.getCells()[players[current].getPosition()].setOccupied(true);
		}
		else
			board.getCells()[players[current].getPosition()].setOccupied(false);
		int marker = players[current].getPosition() + n;
		if (marker < board.getCells().length)
		{
			players[current].setPosition(marker);
			if (board.getCells()[marker].getSnake() != null)
				players[current].setPosition(board.getCells()[marker].getSnake().getTail());
			else if (board.getCells()[marker].getLadder() != null)
				players[current].setPosition(board.getCells()[marker].getLadder().getTop());
			if (board.getCells()[players[current].getPosition()].isOccupied())
				players[current].setPosition(0);
			else
				board.getCells()[players[current].getPosition()].setOccupied(true);
		}
		else
		{
			players[current].setPosition(0);
			board.getCells()[0].setOccupied(true);
		}
	}


	public boolean play(int moveCount) { //This is the main method in your game, which moves the current player to the correct cell and also checks whether the game is finished or not. If found a winner, returns true, otherwise returns false.
		movePlayer(moveCount);
		if(winner())
			return true;
		++current;
		if(current == players.length)
			current = 0;
		return false;
	}

	public Board getBoard() {
		return board;
	}
}


class Player { //Correctly Implemented
	int pos;
	String name;

	public Player(String n4m3) {
		name = n4m3;
		pos = 0;
	}

	public void setPosition(int position) {
		pos = position;
	}

	public int getPosition() {
		return pos;
	}

	public String getName() {
		return name;
	}

	public String toString() {
		return name + " @ " + pos;
	}
}

class Cell { //Correctly implemented
	private boolean occ = false;
	private int num;
	private Ladder lad = null;
	private Snake snake = null;

	public Cell(int number) {
		num = number;
		if(num == 0)
			occ = true;
	}

	public void setOccupied(boolean occupied) {
		occ = occupied;
	}

	public boolean isOccupied() {
		return occ;
	}

	public Ladder getLadder() {
		return lad;
	}

	public Snake getSnake() {
		return snake;
	}

	public void setLadder(Ladder ladder) {
		lad = ladder;
	}

	public void setSnake(Snake snek) {
		snake = snek;
	}

	public int getNumber() {
		return num;
	}
}

class Board { //Correctly Implemented
	Cell[] board;

	public Board(int n) {
		board = new Cell[n * n];
		for(int i = 0; i < board.length; ++i) {
			board[i] = new Cell(i);
		}
	}

	public void setCellToLadder(int startPosition, int endPosition) {
		board[startPosition].setLadder(new Ladder(startPosition, endPosition));
	}

	public void setCellToSnake(int headPosition, int tailPosition) {
		board[headPosition].setSnake(new Snake(headPosition, tailPosition));
	}

	public Cell[] getCells() {
		return board;
	}
}

class Snake { //Correctly implemented
	int head;
	int tail;

	public Snake(int headPosition, int tailPosition) {
		head = headPosition;
		tail = tailPosition;
	}

	public int getTail() {
		return tail;
	}

	public String toString() {
		return head + " - " + tail;
	}
}

class Ladder { //Correctly Implemented
	private int start;
	private int end;

	public Ladder(int startPosition, int endPosition) {
		start = startPosition;
		end = endPosition;
	}

	public int getTop() {
		return end;
	}

	public String toString() {
		return start + " - " + end;
	}
}