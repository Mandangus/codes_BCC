import java.io.Serializable; 

@SuppressWarnings("serial")
public class Usuario implements Serializable{// Objeto serializavel de cada usuario
	
	

	int idade;
	String nome;
	String interesse;
	String desc;
	String tituloComu;// titulo da comunidade pertencente
	
	public Usuario(int ida, String name, String interest, String description) {
		this.desc = description;
		this.nome = name;
		this.interesse = interest;
		this.idade = ida;
	}
}
