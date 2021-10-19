import java.io.Serializable;

@SuppressWarnings("serial")
public class Tema implements Serializable{// Objeto tema serializável
	int views;
	String title;
	String[] links;// array de links 
	String text;// descrição do tema
	
	public Tema(String titulo){ 
		this.title = titulo;
		this.views = 0;
		links = null;
		text = null;
	}
	public Tema(String titulo,String[] links, String text) {
		this.title = titulo;
		this.links = links;
		this.text = text;
	}
	
	
}
