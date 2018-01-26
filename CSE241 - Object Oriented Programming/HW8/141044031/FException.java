import java.io.*;
@SuppressWarnings({"serial"})
public class FException extends Exception{
	String message;
	//No param constructure calls supers.
	public FException(){
		super("");
	}
	//No param constructure calls supers with a message.
	public FException(String note){
		super(note);
		message=note;
	}
	//This method returns message
	public String toString(){
		return super.toString();
	}
}